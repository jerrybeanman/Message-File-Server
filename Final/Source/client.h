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
#ifndef _CLIENT_
#define _CLIENT_

#include "global.h"

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
void client_mngr(char * filename, int prority);

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
void connect(int c_pid, struct msg * snd_msg, struct msg * rcv_msg, int * s_pid);

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
void get_qfile(struct msg * rcv_msg, int c_pid, int prority);

#endif