CC = gcc
CFLAGS = 
VPATH = src




application : application.c colors.c image_helper.c defs.h
	$(CC) src/application.c src/colors.c src/image_helper.c src/defs.h `pkg-config sdl2 --cflags -ISDL2_image ` `pkg-config sdl2 --libs` -o application