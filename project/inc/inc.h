/**
 * @file inc.h
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief The main declaration file
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

#ifndef __INC_H__
#define __INC_H__

//? Pre-processor prototype declaration part
#define MAX_PATH 260
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_BPP 32

//? Include prototype declaration part
// Sys include files (gcc)
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// SDL1.2 include files (from SDL)
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// Custom include files
#include "../models/SDL_Msg.h"

//? Structure prototype declaration part
typedef struct Surface {
  SDL_Surface *win;
  SDL_Rect pos;
} surface;  // Surface struct

//? Function Declaration part
void initEverything();
void closeEverything();
void __ttt_game__();

SDL_Surface *load_img(const char *);
void loadResources(surface *);

void initResources(surface *);
void have_coordinate(Sint16 *, Sint16 *, int);
void ttt_scroll_UD(surface *sub, int *taken_pos, int *usr_cp, int direction);
int is_free(int *);

void check_ttt(surface *, int *, int, int *);
int check_rcd(surface *, int *, int);
int check_rows(surface *, int *, int);
int check_columns(surface *, int *, int);
int check_diagonals(surface *, int *, int);

#endif