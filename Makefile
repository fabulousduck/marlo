install_dir=/usr/local
CC = gcc

marlo: main.c src/*.c
	$(CC) main.c src/*.c -g -Wall -o marlo

install: marlo
	sudo install -m 775 marlo $(prefix)/bin

