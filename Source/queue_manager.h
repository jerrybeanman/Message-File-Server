#ifndef _QUEUE_MANAGER_
#define _QUEUE_MANAGER_
#include "global.h"

void mesg_send(struct msg * message);
/* read from queue, look for mtype */
void mesg_recv(struct msg * message, int mtype);
int crt_q(int * msqid);
/* initialize msg structure with corresponding values passed in */
void init_msg(struct msg * message, long type, int priority, char * data);

void kill_q(int sig);
#endif