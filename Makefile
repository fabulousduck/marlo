makemarlo: main.c src/lexer.c src/parser.c
	gcc main.c src/lexer.c src/parser.c -g -Wall
