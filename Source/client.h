#ifndef _CLIENT_
#define _CLIENT_

#include "global.h"

void client_mngr(char * filename, int prority);
void get_qfile(struct msg * rcv_msg, int c_pid, int prority);

#endif