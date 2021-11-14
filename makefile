CC =gcc
FLAGS =-Wall -Wextra -pedantic

uuc: uuc.c uuc.h
	$(CC) $(FLAGS) -g -o uuc uuc.c
