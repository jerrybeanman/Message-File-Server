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

#ifndef _QUEUE_MANAGER_
#define _QUEUE_MANAGER_
#include "global.h"

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
void mesg_send(struct msg * message);

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
void mesg_recv(struct msg * message, int mtype);

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
int crt_q(int * msqid);

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
void init_msg(struct msg * message, long type, int priority, char * data);

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
void kill_q(int sig);
#endif