#include "server.h"
void server_mngr()
{
	char * s_pids;
	int c_pid, s_pid = getpid();
	struct msg * snd_msg = (struct msg *)malloc(sizeof(struct msg));
	struct msg * rcv_msg = (struct msg *)malloc(sizeof(struct msg));
	rev_atoi(s_pid, &s_pids);
	while(1)
	{
		/* query for client PID */
		printf("Queue empty, waiting for query...\n");
		mesg_recv(rcv_msg, CLIENT_MSG);
		c_pid = atoi(rcv_msg->data);
		printf("Client-[%d] Server-[%d]: Recieved query!\n", c_pid, s_pid);

		/* initialize message for response */ 
		init_msg(snd_msg, SERVER_MSG, 0, s_pids);

		/* Respond with PID */
		printf("Client-[%d] Server-[%d]: Responding\n", c_pid, s_pid);
		mesg_send(snd_msg);

		if(fork() == 0)
		{
			spawn_clnt_proc(c_pid, s_pid);
			break;
		}
	}
}

void spawn_clnt_proc(int c_pid, int s_pid)
{
	FILE * fp;
	std::string fmsg;
	int index = 0, msglen, filesz;

	struct msg * rcv_msg = (struct msg *)malloc(sizeof(struct msg));

	printf("Client[%d]: waiting for file name...\n", c_pid);
	/* query for client's file name structure*/
	mesg_recv(rcv_msg, s_pid);

	printf("Client-[%d] Server-[%d]: Recieved File Name-[%s], Priority-[%d]\n", c_pid, s_pid, rcv_msg->data, rcv_msg->priority);

	if((fp = fopen(rcv_msg->data, "r")) == NULL)
	{
		err(FILE_NOT_FOUND);
		return;
	}

	/* get whole file content into buffer */
	fmsg = read_file(fp);
	msglen = rcv_msg->priority * MIN_MSGSZ;
	filesz = fmsg.size();

	printf("Total size-[%d]\n", fmsg.size());
	printf("Client[%d]: Start transferring...\n", c_pid);

	for(index = 0; (index+1) * msglen < filesz; index++)
	{

		send_packet(fmsg, rcv_msg->priority, index, c_pid);
	}
	send_packet(fmsg, rcv_msg->priority, index, c_pid);
	printf("Finished transferring for client: [%d]. exiting...\n", c_pid);
}

char * read_file(FILE *fp)
{
    char * buf = NULL, * tmp = NULL, c;
    size_t size = 0, index = 0;

    do{

        /* Check if we need to expand. */
        if (index >= size) 
        {
            size += MAX_MSGSZ;
            tmp = (char *)realloc(buf, size);
        }
        buf = tmp;
		c = (char)fgetc(fp);
        if(feof(fp))
        	break;
        buf[index++] = c;
    }while (1); 
    return buf;
}

void send_packet(std::string fmsg, int priority, int index, int c_pid)
{
	struct msg * snd_msg;
	int msglen = priority * MIN_MSGSZ;
	int filesz = fmsg.size();
	int from   = index * msglen;
	char * str;

	if((index+1) * msglen < filesz)
		str = (char*)(fmsg.substr(from, msglen).c_str());
	else
		str = (char*)(fmsg.substr(index * msglen, filesz-(index * msglen))).c_str();
	
	printf("Block size:%d\n", strlen(str));
	snd_msg = (struct msg *)malloc(sizeof(struct msg) + strlen(str));
	init_msg(snd_msg, c_pid, 0, str);
	mesg_send(snd_msg);
}

void sub_str(char ** to, char * from, int begin, int end)
{
	int i, len = end - begin;
	*to = (char*)malloc(len);
	for(i = 0; i < len; i++)
	{
		*to[i] = from[begin++];
	}

}