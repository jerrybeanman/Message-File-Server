/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:	utility.c - Provides wrapper functions and delegates for the file message application
-- 
-- PROGRAM:		Message File Server
-- 
-- FUNCTIONS:	int valid_cmdl(int argc, char * srvice)
--				void usage(char * exec)
-- 				int get_srvice(char * srvice)
--				void err(int errno)
--				void init_empty_buf(char * buf)
--				void rev_atoi(int num, char ** newbuf)
--
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- NOTES: Provides basic error handling functions and delegates.
--------------------------------------------------------------------------------------------------------------------*/
#ifndef _UTILITY_H
#define _UTILITY_H

#include "global.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	valid_cmdl
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	int valid_cmdl(int argc, char * srvice)
-- 						int argc : the number of command line arguments
--						char * srvice : the type of service to execute, taken from argv[1]
--
-- RETURNS: 0 on valid command, -1 on failure
-- 
-- NOTES: Checkes if a valid set of command line arguments is entered. 
--------------------------------------------------------------------------------------------------------------------*/
int valid_cmdl(int argc, char * srvice);

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	usage
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void usage(char * exec)
-- 						char * exec : the name of the application
--
-- RETURNS: 
-- 
-- NOTES: Displays the usage of the program
--------------------------------------------------------------------------------------------------------------------*/
void usage(char * exec);

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	get_srvice
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	int get_srvice(char * srvice)
-- 						char * srvice : the type of server the apllication will act as, either the "client" or "server"
--
-- RETURNS: MAKE_CLIENT or MAKE_SERVER, else -1
-- 
-- NOTES: determine if a valid service name has been enetered 
--------------------------------------------------------------------------------------------------------------------*/
int get_srvice(char * srvice);

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	err
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void err(int errno)
-- 						int errno : The error number defined in global
--
-- RETURNS: void
-- 
-- NOTES: print a message to the corresponding error number passed in 
--------------------------------------------------------------------------------------------------------------------*/
void err(int errno);

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	init_empty_buf
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void init_empty_buf(char * buf);
--					char * buf: buffer that will be NULL terminated for every index
-- 
-- RETURNS: void
-- 
-- NOTES: Initialize buffer to all NULL characters 
--------------------------------------------------------------------------------------------------------------------*/
void init_empty_buf(char buf[MAX_MSGSZ]);

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	rev_atoi
-- 
-- DATE:		January 21, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void rev_atoi(int num, char ** newbuf)
--					int num : The number to convert to string
--					char ** newbuf : the character buffer that will store the converted result
-- 
-- RETURNS: void
-- 
-- NOTES: takes in a number and converts it to a string and store it into newbuf
--------------------------------------------------------------------------------------------------------------------*/
void rev_atoi(int num, char ** newbuf);
#endif