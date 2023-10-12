CC = gcc
CFLAGS = 
VPATH = src




application : application.c colors.c
	$(CC) src/application.c src/colors.c `pkg-config sdl2 --cflags` `pkg-config sdl2 --libs` -o application