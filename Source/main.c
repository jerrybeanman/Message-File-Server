 #include "global.h"

/*------------------------------------------------------------------------------------------------------------------ 
-- FUNCTION:	main
-- 
-- DATE:		January 7, 2015
-- 
-- REVISIONS:	
-- 
-- DESIGNER:	Ruoqi Jia
-- 
-- PROGRAMMER:	Ruoqi Jia
-- 
-- INTERFACE:	int main(int argc, char * argv[])
--						int argc : Number of command line arguments entered
--						int argc : The array of arguments
-- 
-- RETURNS: exit code 
-- 
-- NOTES: The main entry point to the application. User should specify the correct command line arguments in order 
--  to function. The type of service (client or server) created is determined by argv[1]. If a client is created,
-   the filename and priority will be specified as argv[2] and argv[3].
--------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char * argv[])
{
	signal(SIGINT, kill_q);
	
	/* check if argc == 4*/
	if(valid_cmdl(argc, argv[1]) == -1)
		usage(argv[0]);
	
	/* retrieves the type of service this process needs to run as */
	switch(get_srvice(argv[1]))
	{
		/* Invalid service name */
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

