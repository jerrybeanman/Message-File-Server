/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	client.c - Client service type of the program.
-- 
-- PROGRAM:		Message File Server
-- 
-- FUNCTIONS:	void client_mngr(char * filename, int priority)
--				void get_qfile(struct msg * rcv_msg, int c_pid, int priority)
--
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- NOTES: Acts as the client side of the message file server application. When it starts out, the client sends a query 
--	to the message queue and and awaits for the aknowledgement from the server with its process ID as the mtype. After 
--	establishing that connection, the client is able to talk to the server with its PID, and vice versa. It will wrap up
--  the file name and its priority level recieved from command line argument and send it to the server. After that,
--  the server will responding with the file content as packets, which will be read by the client until the last one
--  has been read.
--------------------------------------------------------------------------------------------------------------------*/
#include "client.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	client_mngr
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void client_mngr(char * filename, int priority)
-- 						char * filename : the name of file that will be sent from the client and opened by the server
--						int priority : The priority level of the connection. has to be 1-10
--
-- RETURNS: void
-- 
-- NOTES: The main starting point of the client process. It first query for a connection with the server, and once 
-- the acknowledge has been done, the client will wrap up the file name and priority level into a message and send 
-- to the server.
--------------------------------------------------------------------------------------------------------------------*/
void client_mngr(char * filename, int priority)
{
	char * c_pids;
	int s_pid, c_pid = getpid();
	struct msg * snd_msg = (struct msg *)malloc(sizeof(struct msg));
	struct msg * rcv_msg = (struct msg *)malloc(sizeof(struct msg));

	/* establish connection */
	connect(c_pid, snd_msg, rcv_msg, &s_pid);

	printf("Client-[%d] Server-[%d]: Sending file name-[%s], Priority-[%d]\n", c_pid, s_pid, filename, priority);

	/* initialize message for file request */
	init_msg(snd_msg, s_pid, priority, filename);

	/* send the message */
	mesg_send(snd_msg);

	/* waits for the file packets and read it */
	get_qfile(rcv_msg, c_pid, priority);

}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	connect
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void connect(int c_pid, struct msg * snd_msg, struct msg * rcv_msg, int * s_pid)
-- 						int c_pid : client's process ID
--						struct msg * snd_msg : pointer to the msg structure for sending 
--						struct msg * rcv_msg : pointer to the msg structure for reading
--						int * s_pid : server's process ID
--
-- RETURNS: void
-- 
-- NOTES: For mainly establishing connection with the server. The client will query a message to the queue and waits 
-- for an aknowledgement from the server with its process ID attached. The server process ID will be stored for future 
-- communications.
--------------------------------------------------------------------------------------------------------------------*/
void connect(int c_pid, struct msg * snd_msg, struct msg * rcv_msg, int * s_pid)
{
	char * c_pids;
	/* convert PID into a string */
	rev_atoi(c_pid, &c_pids);
	
	printf("Client-[%d] Server-[null]: Sending PID\n", c_pid);

	/* initialize message with own PID */ 
	init_msg(snd_msg, CLIENT_MSG, 0, c_pids);

	/* send PID to server */
	mesg_send(snd_msg);

	printf("Waiting for server response...\n");
	/* read msg from server */
	mesg_recv(rcv_msg, SERVER_MSG);
	
	/* store the server PID as an int */
	*s_pid = atoi(rcv_msg->data);

	printf("Client-[%d] Server-[%d]: Recieved response!\n", c_pid, s_pid);
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	get_qfile
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void get_qfile(struct msg * rcv_msg, int c_pid, int priority)
-- 						struct msg * rcv_msg : pointer to the message structure for reading
--						int c_pid : The client's process ID
--						int priority : the priority level
--
-- RETURNS: void
-- 
-- NOTES: Reads message packets that contains the file content from the server if the server opened a file name.
--	The size of the message to be read is dependent on the priority assigned. The higher priority makes higher 
--  file content to be read 
--------------------------------------------------------------------------------------------------------------------*/
void get_qfile(struct msg * rcv_msg, int c_pid, int priority)
{
	printf("Waiting for file...\n");

	/* wait for server server message*/
	mesg_recv(rcv_msg, c_pid);

	/* If the server failed to open the file */
	if(rcv_msg->data[0] == '\0')
	{
		err(FILE_NOT_FOUND);
		exit(1);
	}

	/* display message block */
	printf("%s", rcv_msg->data);

	/* keep reading message until the file has been fully read*/
	while(strlen(rcv_msg->data) > MIN_MSGSZ * priority)
	{
		rcv_msg = (struct msg*)malloc(sizeof(struct msg));
		mesg_recv(rcv_msg, c_pid);
		printf("%s", rcv_msg->data);
	}

	printf("\nClient-[%d]: End of file, exiting...\n", getpid());
}
