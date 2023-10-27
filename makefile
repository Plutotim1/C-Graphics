CC = gcc
CFLAGS = `pkg-config sdl2 --cflags` `pkg-config sdl2_image --cflags` `pkg-config sdl2 --libs` `pkg-config sdl2_image --libs`
VPATH = src




application : application.c colors.c image_helper.c defs.h
	$(CC) src/application.c src/colors.c src/image_helper.c src/defs.h `pkg-config sdl2 SDL2_image --cflags` `pkg-config sdl2 SDL2_image --libs` -o application