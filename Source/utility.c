#include "utility.h"

int valid_cmdl(int argc)
{
	if(argc != NUM_CMDLARG)
		return -1;
	return 0;
}

void usage(char * exec)
{
	printf("|-------------------------------------|\n");
	printf("usage: %s type filename priority\n", exec);
	printf("	type: -c[client] || -s[server]\n");
	printf("	filename: file name\n");
	printf("	priority: 0-10, ascending\n");
	printf("|-------------------------------------|\n");
	exit(1);
}

int get_srvice(char * srvice)
{
	if(strcmp(srvice, "-c") == 0)
	{
		printf("|---------------Starting Client Service---------------|\n");
		return MAKE_CLIENT;
	}
	else if (strcmp(srvice, "-s") == 0)
	{
		printf("|-------Starting Server Service-------|\n");
		return MAKE_SERVER;
	}
	return -1;
}

void err(int errno)
{
	switch(errno)
	{
		case ERR_SRVICE:
			fprintf(stderr, "incorrect service name...\n");
			break;
		case FTOK:
			fprintf(stderr, "ftok() failed...\n");
			break;
		case MSGGET:
			fprintf(stderr, "msgget(): creating | opening message queue failed...\n");
			break;
		case MSGSND:
			fprintf(stderr, "msgsnd(): send failed...\n");
			break;
		case MSGCTL:
			fprintf(stderr, "msgctl(): message queue already closed\n");
			break;
		case FILE_NOT_FOUND:
			fprintf(stderr, "fopen(): file not found\n");
			break;
	}
}


/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	init_empty_buf
-- 
-- DATE:		January 20, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	void init_empty_buf(char buf[MAX_MSGSZ]);
--					char buf[MAX_MSGSZ]: buffer that will be NULL terminated for every index
-- 
-- RETURNS: void
-- 
-- NOTES: Initialize buffer to all NULL characters 
--------------------------------------------------------------------------------------------------------------------*/
void init_empty_buf(char * buf)
{
	for(size_t i = 0; i < strlen(buf); i++)
		buf[i] = '\0';
}

void rev_atoi(int num, char ** newbuf)
{
	char buf[6];
	/* convert int to string */
	sprintf(buf, "%d", num);
	*newbuf = (char*)malloc(sizeof(char)*6);
	strcpy(*newbuf, buf);
}