#include "queue_manager.h"

/* send a message struct */
void mesg_send(struct msg * message)
{
	int msqid, len, retval;

	/* map file path and create or open a message queue */
	if(crt_q(&msqid) == -1)
		return;

	/* the mtype is excluded */
	len = sizeof(*message) - sizeof(long);
	if ((retval = msgsnd(msqid, message, len, 0)) == -1) 
	{
		err(MSGSND);
		return;
	}

}

/* read from queue, look for mtype */
void mesg_recv(struct msg * message, int mtype)
{
	int msqid, len, retval;
	len = sizeof(*message) - sizeof(long);
	/* map file path and create or open a message queue */
	if(crt_q(&msqid) == -1)
		return;
	if ((retval = msgrcv(msqid, message, len, mtype, 0)) == -1) 
	{
		err(MSGRCV);
		return;
	}
}

/* map file path and create message queue*/
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

void init_msg(struct msg * message, long type, int priority, char * data)
{

	message->mtype = type;
	message->len = strlen(data);
	message->priority = priority;

	/* null out the buffer */
	init_empty_buf(message->data);

	if(data != NULL)
		/* copy data into buffer */
		memcpy(message->data, data, message->len);

}

void kill_q(int sig)
{
	signal(sig, NULL);
	printf("Exiting application\n");
	int msqid;
	if(crt_q(&msqid) == -1)
		return;
	if (msgctl(msqid, IPC_RMID, NULL) == -1)
		err(MSGCTL);
	kill(getpid(), sig);
}