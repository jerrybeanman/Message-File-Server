/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	queue_manager.c - Manage and control actions to be done on the message queue
-- 
-- PROGRAM:		Message File Server
-- 
-- FUNCTIONS:	void mesg_send(struct msg * message)
--				void mesg_recv(struct msg * message, int mtype)
--				int crt_q(int * msqid)
--				void init_msg(struct msg * message, long type, int priority, char * data)
--				void kill_q(int sig)
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
#include "queue_manager.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	mesg_send
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void mesg_send(struct msg * message)
-- 						struct msg * message : The populated message structure to be sent to the queue
--
-- RETURNS: void
-- 
-- NOTES: Sends a global defiend message structure onto the queue
--------------------------------------------------------------------------------------------------------------------*/
void mesg_send(struct msg * message)
{
	int msqid, len;

	/* map file path and create or open a message queue */
	if(crt_q(&msqid) == -1)
		return;

	/* the mtype is excluded */
	len = sizeof(*message) - sizeof(long);

	/* send the structure */
	if (msgsnd(msqid, message, len, 0) == -1) 
		err(MSGSND);
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	mesg_recv
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void mesg_recv(struct msg * message, int mtype)
-- 						struct msg * message : The message structure that will be populated after a successfully read
--						int mtype : The identifier that the client will be reading from the queue
--
-- RETURNS: void
-- 
-- NOTES: Reads a message structure from the queue with the corresponding mtype 
--------------------------------------------------------------------------------------------------------------------*/
void mesg_recv(struct msg * message, int mtype)
{
	int msqid, len;

	/* map file path and create or open a message queue */
	if(crt_q(&msqid) == -1)
		return;

	/* Exclude the mtype */
	len = sizeof(*message) - sizeof(long);

	/* reads the message from queue*/
	if (msgrcv(msqid, message, len, mtype, 0) == -1) 
		err(MSGRCV);
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	crt_q
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	int crt_q(int * msqid)
-- 						int * msqid : the message queue ID that will be assigned after the queue is created
--
-- RETURNS: -1 when ftok or msgget fails, 0 on success
-- 
-- NOTES:  Map a file's path to a key and open a message queue for it.
--------------------------------------------------------------------------------------------------------------------*/
int crt_q(int * msqid)
{
	key_t key;

	/* map a file's path into a key */
	if ((key = ftok("/dev/random", 'z')) == -1) 
	{
		err(FTOK);
		return -1;
	}

	/* create or open an existing queue */
	if ((*msqid = msgget(key, 0644 | IPC_CREAT)) == -1) 
	{
		err(MSGGET);
		return -1;
	}
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	init_msg
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void init_msg(struct msg * message, long type, int priority, char * data)
-- 						struct * msg message : Predefined message that will be populated with the data
--						long type : The message type 
--						int priority: The priority level 
--						cahr * data : The message content
--
-- RETURN: void
-- 
-- NOTES:  Initializes a msg structure with the corresponding values passed in
--------------------------------------------------------------------------------------------------------------------*/
void init_msg(struct msg * message, long type, int priority, char * data)
{

	message->mtype = type;
	message->priority = priority;
	message->hasNext = 1;
	/* null out the buffer */
	init_empty_buf(message->data);

	if(data != NULL)
	{
		message->len = strlen(data);
		/* copy data into buffer */
		memcpy(message->data, data, message->len); 
	}

}

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	kill_q
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void kill_q(int sig)
-- 						int sig : Signal to be catched, it will be SIGINT
--
-- RETURN: void
-- 
-- NOTES:  When SIGINT is caught, deletes the existing queue and exists the program.
--------------------------------------------------------------------------------------------------------------------*/
void kill_q(int sig)
{
	signal(sig, NULL);
	printf("Exiting application\n");
	int msqid;

	/* Find the current operating message queue */
	if(crt_q(&msqid) == -1)
		return;

	/* close the queue */
	if (msgctl(msqid, IPC_RMID, NULL) == -1)
		err(MSGCTL);

	/* send SIGINT and exits process */
	kill(getpid(), sig);
}