#ifndef _SERVER_
#define _SERVER_

#include "global.h"

void server_mngr();
void spawn_clnt_proc(int c_pid, int s_pid);
char * read_file(FILE *fp);
void sub_str(char ** from, char * to, int begin, int end);
void send_packet(std::string fmsg, int priority, int index, int s_pid);
#endif