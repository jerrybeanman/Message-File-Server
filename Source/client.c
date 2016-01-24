#include "client.h"
void client_mngr(char * filename, int priority)
{
	char * c_pids;
	int s_pid, c_pid = getpid();
	struct msg * snd_msg = (struct msg *)malloc(sizeof(struct msg));
	struct msg * rcv_msg = (struct msg *)malloc(sizeof(struct msg));
	rev_atoi(c_pid, &c_pids);
	/* initialize message for query */ 
	init_msg(snd_msg, CLIENT_MSG, 0, c_pids);

	
	/* sending PID to server */
	printf("Client-[%d] Server-[null]: Sending PID\n", c_pid);
	mesg_send(snd_msg);

	/* read msg from server */
	printf("Waiting for server response...\n");
	mesg_recv(rcv_msg, SERVER_MSG);
	s_pid = atoi(rcv_msg->data);
	printf("Client-[%d] Server-[%d]: Recieved response!\n", c_pid, s_pid);

	/* initialize message for file request */
	printf("Client-[%d] Server-[%d]: Sending file name-[%s], Priority-[%d]\n", c_pid, s_pid, filename, priority);
	init_msg(snd_msg, s_pid, priority, filename);
	mesg_send(snd_msg);

	get_qfile(rcv_msg, c_pid, priority);

}

void get_qfile(struct msg * rcv_msg, int c_pid, int priority)
{
	printf("Waiting for message...\n");
	mesg_recv(rcv_msg, c_pid);
	if(rcv_msg->data[0] == '\0')
	{
		err(FILE_NOT_FOUND);
		kill(getpid(), SIGINT);
	}
	printf("%s", rcv_msg->data);

	while(strlen(rcv_msg->data) > MIN_MSGSZ * priority)
	{
		rcv_msg = (struct msg*)malloc(sizeof(struct msg));
		mesg_recv(rcv_msg, c_pid);
		printf("%s", rcv_msg->data);
	}
	printf("\nClient-[%d]: End of file, exiting...\n", getpid());
}
