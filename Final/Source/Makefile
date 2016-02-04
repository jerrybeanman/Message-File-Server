
# Makefile 
# Ruoqi Jia

CC=g++
NAME=msgqcs		
FLAGS=-Wall
SFILES= main.c utility.c client.c queue_manager.c server.c
OFILES=$(SFILES:.c=.o)


$(NAME): 	$(OFILES)
		$(CC) $(FLAGS) -o $(NAME) $(OFILES) 

debug:
		$(CC) $(FLAGS) -g -o $(NAME) $(OFILES) 
clean:
		rm $(OFILES) $(NAME)

remake:
		make clean
		clear
		make
