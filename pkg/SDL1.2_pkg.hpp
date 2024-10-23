/**
 * @file SDL1.2_pkg.hpp
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-22
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __INC_H__
#define __INC_H__

//? -------------------- DEFINE PROTOTYPE DECLARATION PART --------------------
#define MAX_PATH 260

//? -------------------- INCLUDE PROTOTYPE DECLARATION PART --------------------
//* STANDER LIBS INCLUDE PART
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

//* SDL1.2 INCLUDE PART
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

//? --------------------- PUBLIC VARS DECLARATION PART ---------------------
//* SCREEN SURFACE DECLARATION
extern SDL_Surface *screen;

//* SCREEN RESOLUTION DECLARATION
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;

//* SDL_COLOR PUBLIC DECLARATION
extern const SDL_Color WHITE;
extern const SDL_Color BLACK;

//? --------------------- STRUCT PROTOTYPE DECLARATION PART ----------------------
//? Surface struct
typedef struct Surface {
  SDL_Surface *win;
  SDL_Rect pos;
} surface;

//? -------------------- FUNCTIONS PROTOTYPE DECLARATION PART --------------------

void initEverything();

void setScreen(int);

SDL_Surface *load_img(char *);

void closeEverything();

/* ---------------------------------------------
? --- LOAD && FREEING FUNCS DECLARATION PART ---
------------------------------------------------*/

void set_pos(surface *, char *, int);

void loadResources(surface *, char *, int, int);

void freeResources(surface *, TTF_Font *, Mix_Chunk *, int);

#endif
