
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
#ifndef _SERVER_
#define _SERVER_

#include "global.h"


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
void server_mngr();

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
void spawn_clnt_proc(int c_pid, int s_pid);

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
void read_file(int fp, struct msg * snd_msg, int msglen, int c_pid);

#endif