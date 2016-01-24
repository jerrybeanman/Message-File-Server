#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <string>

#define NUM_CMDLARG		4		/* exact number of command line arguments */
#define SERVER_MSG		100		/* message type the server responds to the client */
#define CLIENT_MSG		101		/* message type the client first establishes a query */
#define MAKE_SERVER		1000	/* server service type */
#define MAKE_CLIENT		1001	/* client service type */
#define ERR_SRVICE		2000	/* errno: when invalid service name is pass from argv */
#define FTOK 			2001
#define MSGGET			2002	
#define MSGSND			2003
#define MSGRCV			2004
#define MSGCTL			2005
#define FILE_NOT_FOUND	2006
#define MAX_PRIORITY	10
#define MIN_MSGSZ		(512 - sizeof(long))	/* maximum message size for data in msg struct*/
#define MAX_MSGSZ		MIN_MSGSZ * 10

struct msg
{
	long mtype;
	size_t len;
	int priority;
	char data[MAX_MSGSZ];
};

#include "queue_manager.h"
#include "utility.h"
#include "client.h"
#include "server.h"


#endif
