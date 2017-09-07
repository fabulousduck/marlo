makemarlo: main.c src/lexer.c src/parser.c
	gcc main.c src/*.c -g -Wall
