#define SOMEVALUE 1000
/* ftok: Mapping a file's path name into a key */
Key_t myKey;
myKey = ftok("/tmp/foobar", 'a');

/* msgget: create or open a message queue, needs the Key_t value */
int msg_id = msgget(myKey, 0644|IPC_CREAT|IPC_EXEL);

/* the kernel stores each message in the queue within the framework
of the msg structure */

/* send a message to the queue denoted by msg_qid, obtained by msgget */
int msg_qid, flags, retval;
struct my_msg
{
	long mytype;
	char mtext[SOMEVALUE];
}message;
struct * my_msg message= (my_msg*)malloc(sizeof(struct * my_msg));
retval = msgsnd(msg_qid, message, size, flags);

/* write wrapper function*/
int send_message(int msg_qid, struct my_msg *buf)
{
	int result, length;
	/* the length is essentially the sie of the structure minus sizeof(mtype) */
	length = sizeof(struct(my_msg)) - sizeof(long);
	if(result = msgsnd(msg_qid, buf, length, 0) == -1)
	{
		return -1;
	}
	return result;
}

/* Read from queue  */
int retval = msgrcv(msg_qid, &message, size, msg_type, flags);

/* third argument size excludes the size of mtype member */
int size = sizeof(struct msgbuf) - sizeof(long

/* msg_type parameter decides what message is actually recieved. 
 it selects according to the value of a message's mtype field */
/* if msg_type == 0, the earliest sent, is read. if msg_type > 0,
first message with that value is read */

int read_message(int qidd, long type, struct msgbuf *qbuf)
{
	int result, length;
	length = sizeof(struct msgbuf) - sizeof(long);

	if((result = msgrcv(qid, qbuf, length, type, 0)) == -1)
	{
		return -1;
	}
	return result;
}

/* msgctl: allows a process to get status info about message queue, to
change some of the limits on message queue, or to delete queue from the 
system altogther*/
int msgqid, commadn, retval;
struct msqid_ds msq_stat;
retval = msgctl(msg_qid, command. &msq_Stat);

/* command paremeter tells the system what operation is to be performed
IPC_STAT : tell system to place status info about the struct into msq_stat
IPC_SET : used to set the values of control variables for the queue, held in msq_stat
IPC_Rmid : removes the message queue from the system.
*/

int remove_queue(int qid)
{
	if(msgctl(qid, IPC_RMID,0) == -1)
	{
		return -1;
	}
	return 0;
}