#ifndef _UTILITY_H
#define _UTILITY_H

/* Function prototype */
#include "global.h"
/* check argc == 4*/
int valid_cmdl(int argc);

/* prints command line arguments usage */
void usage(char * exec);

/* check which kind of service from argv[2]*/
int get_srvice(char * srvice);

/* checks which kind of error number pass in, then prints message to stderr */
void err(int errno);



void init_empty_buf(char buf[MAX_MSGSZ]);
void rev_atoi(int num, char ** newbuf);
#endif