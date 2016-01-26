
/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	server.c - Server service type of the program.
-- 
-- PROGRAM:		Message File Server
-- 
-- FUNCTIONS:	void server_mngr()
--				void spawn_clnt_proc(int c_pid, int s_pid)
--				char * read_file(FILE *fp)
--				void send_packet(std::string fmsg, int priority, int index, int c_pid)
--				
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- NOTES: Acts as the server side of the message file server application. When it starts out, the server will be in a 
--  wait state waiting for client to query for connections. Once the query has been recieved, the server will send back
--  its process ID to the client and create a child process to handle communicating with the client. The child process 
--  will waits for a file name from the client, and open the file and attempt to send the content to the client until
--  it's done.
--  
--  *The size of the content sent to the server will be dependent on the priority level*
--------------------------------------------------------------------------------------------------------------------*/
#include "server.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	server_mngr
-- 
-- DATE:		January 7, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void server_mngr()
-- 
-- RETURNS: void
-- 
-- NOTES: The main server process process. Responsible for establishing connection from the client and create a 
--  child process to handle communications between that client.
--------------------------------------------------------------------------------------------------------------------*/
void server_mngr()
{
	char * s_pids;
	int c_pid, s_pid = getpid();
	struct msg * snd_msg = (struct msg *)malloc(sizeof(struct msg));
	struct msg * rcv_msg = (struct msg *)malloc(sizeof(struct msg));
	rev_atoi(s_pid, &s_pids);
	while(1)
	{
		/* query for client PID */
		printf("Queue empty, waiting for query...\n");
		mesg_recv(rcv_msg, CLIENT_MSG);
		c_pid = atoi(rcv_msg->data);
		printf("Client-[%d] Server-[%d]: Recieved query!\n", c_pid, s_pid);

		/* initialize message for response */ 
		init_msg(snd_msg, SERVER_MSG, 0, s_pids);

		/* Respond with PID */
		printf("Client-[%d] Server-[%d]: Responding\n", c_pid, s_pid);
		mesg_send(snd_msg);

		/* Create a child process to handle the client */
		if(fork() == 0)
		{
			spawn_clnt_proc(c_pid, s_pid);
			break;
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	spawn_clnt_proc
-- 
-- DATE:		January 7, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void spawn_clnt_proc(int c_pid, int s_pid)
-- 						int c_pid : The client's process ID
--						int s_pid : The parent process ID
-- RETURNS: void
-- 
-- NOTES: Responsible for communicating with the client after connection is established. Waits for a file name and attempt
--  to open it if it exists. When the file is opened, its content is sent as dynamically sized packets based on the priority
--  level to the client until its done. 
--------------------------------------------------------------------------------------------------------------------*/
void spawn_clnt_proc(int c_pid, int s_pid)
{
	FILE * fp;
	std::string fmsg;
	int index = 0, msglen, filesz;

	struct msg * rcv_msg = (struct msg *)malloc(sizeof(struct msg));

	printf("Client[%d]: waiting for file name...\n", c_pid);

	/* query for client's file name structure*/
	mesg_recv(rcv_msg, s_pid);

	printf("Client-[%d] Server-[%d]: Recieved File Name-[%s], Priority-[%d]\n", c_pid, s_pid, rcv_msg->data, rcv_msg->priority);

	/* Open the file */
	if((fp = fopen(rcv_msg->data, "r")) == NULL)
	{
		err(FILE_NOT_FOUND);
		return;
	}

	/* get whole file content into buffer */
	fmsg = read_file(fp);

	/* size of content sent is based off of the priority level */
	msglen = rcv_msg->priority * MIN_MSGSZ;

	filesz = fmsg.size();

	printf("Total size-[%d]\n", fmsg.size());
	printf("Client[%d]: Start transferring...\n", c_pid);

	/* Sends each packet */
	for(index = 0; (index+1) * msglen < filesz; index++)
		send_packet(fmsg, index, msglen, c_pid);

	/* Send last pecket */
	send_packet(fmsg, rcv_msg->priority, index, c_pid);

	printf("Finished transferring for client: [%d]. exiting...\n", c_pid);
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	read_file
-- 
-- DATE:		January 7, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	char * read_file(FILE *fp)
-- 						FILE * fp : Pointer to the currently opened file that will be read
--
-- RETURNS: Address of the buffer which stores the file content after reading 
-- 
-- NOTES: Takes in a FILE pointer, reads it and store it into a dynamically sized string.
--------------------------------------------------------------------------------------------------------------------*/
char * read_file(FILE *fp)
{
    char * buf = NULL, * tmp = NULL, c;
    size_t size = 0, index = 0;

    do{

        /* Check if we need to expand. */
        if (index >= size) 
        {
            size += MAX_MSGSZ;
            tmp = (char *)realloc(buf, size);
        }
        buf = tmp;

        /* Read char by char */
		c = (char)fgetc(fp);

		/* Check if file empty */
        if(feof(fp))
        	break;
        buf[index++] = c;
    }while (1); 

    return buf;
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	send_packet
-- 
-- DATE:		January 7, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void send_packet(std::string fmsg, int priority, int index, int msglen, int c_pid)
-- 						std::string fmsg : Stores the file content as a string
--						int idnex : Index to where the message will begin to send
--						int msglen : The size of the data that will be sent
--						int c_pid : Client's process ID, needed for mtype 
--						
--
-- RETURNS: void
-- 
-- NOTES: Takes in a buffer, determine the size of the message that will be sent, initialize the message and sent it
--  to the queue with the client's process ID as the mtype.
--------------------------------------------------------------------------------------------------------------------*/
void send_packet(std::string fmsg, int index, int msglen, int c_pid)
{
	struct msg * snd_msg = (struct msg *)malloc(sizeof(struct msg) + strlen(str));

	/* Size of the buffer */
	int filesz = fmsg.size();

	/* Position of the starting point in the buffer */
	int from   = index * msglen;

	/* message content to send to the client */
	char * str;

	/* If this is not the last block of data that can be read from the buffer */
	if((index+1) * msglen < filesz)
		str = (char*)(fmsg.substr(from, msglen).c_str());

	/* store the last block of data */
	else
		str = (char*)(fmsg.substr(index * msglen, filesz-(index * msglen))).c_str();
	
	printf("Block size:%d\n", strlen(str));

	/* Populate msg structure with str */
	init_msg(snd_msg, c_pid, 0, str);

	mesg_send(snd_msg);
}

