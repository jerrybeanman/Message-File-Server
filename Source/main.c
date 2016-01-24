 #include "global.h"

int main(int argc, char * argv[])
{
	signal(SIGINT, kill_q);
	
	/* check if argc == 4*/
	if(valid_cmdl(argc) == -1)
		usage(argv[0]);
	
	/* retrieves the type of service this process needs to run as */
	switch(get_srvice(argv[1]))
	{
		case -1 :
			usage(argv[0]);
			err(ERR_SRVICE);
			break;
		case MAKE_CLIENT :
			/* go into client mode */
			client_mngr(argv[2] ,atoi(argv[3]));
			break;
		case MAKE_SERVER : 
			/* go into server mode */
			server_mngr();
			break;
	}
	return 0;
}

