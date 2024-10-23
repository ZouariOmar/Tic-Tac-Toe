/**
 * @file lib.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief Helper src file
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

//? Include prototype declaration part
#include "../inc/inc.h"

//? Global variables prototype declaration part
SDL_Surface* screen;
SDL_Event event;

//? Functions dev part
void initEverything() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {  // SDL initialisation process
    fprintf(stderr, "%s: %s", SDL_ERRMSG00, SDL_GetError());
    exit(1);
  }
  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))  // IMG initialisation process
    printf("SDL_image initialization failed: %s\n", IMG_GetError());
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, (SDL_GetVideoInfo()) ? SDL_HWSURFACE : SDL_SWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
  if (!screen) {
    fprintf(stderr, "%s : %s !", SDL_ERRMSG07, SDL_GetError());
    exit(1);
  }
  SDL_WM_SetCaption("Tic Tac Toe", NULL);  // Set The screen caption
}

/**
 * @brief ### Close SDL resources at exit action
 */
void closeEverything() {
  atexit(IMG_Quit);
  atexit(SDL_Quit);
}

/**
 * @brief ### Load images
 * @param path const char * - Path to the image file
 * @return SDL_Surface * - The optimized SDL surface (or NULL on failure)
 */
SDL_Surface* load_img(const char* path) {
  SDL_Surface *loadedImg = IMG_Load(path),
              *optimizedImg = NULL;
  if (loadedImg) {
    optimizedImg = SDL_DisplayFormatAlpha(loadedImg);
    SDL_FreeSurface(loadedImg);
  } else
    printf("Image optimization error: %s\n", SDL_GetError());
  return optimizedImg;
}

/**
 * @brief ### Free all res (images)
 * @param sub surface *
 */
void freeResources(surface* sub) {
  for (int i = 0; i < 15; i++) SDL_FreeSurface(sub[i].win);
}

/**
 * @brief ### Main tic tac toe function (lancer function)
 */
void __ttt_game__() {
  //* load_part
  surface sub[15];
  loadResources(sub);
  initResources(sub);

  //* usr_info :: range(0, 8)
  int usr_current_pos = 0;

  /*
  ? ttt_info
  * taken_pos[] take by default the index -1             :: none action
  * taken_pos[] take 0 if the usr choice the current pos :: tic action
  * taken_pos[] take 1 if the bot choice a random pos    :: tac action
  */
  int taken_pos[9];
  for (int i = 0; i < 9; i++) taken_pos[i] = -1;
  int ttt_taken_pos = 0;

  //* update the screen
  SDL_Flip(screen);

  while (1) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        //? ------------------- KB BUTTON DOWN CLICK EVENT -------------------
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            //? --- SPACE CLICK OPTION ---
            case SDLK_SPACE:
              /* usr treatment part */
              if (ttt_taken_pos < 9) {
                //* add one for the usr
                ttt_taken_pos++;

                //* update taken_pos[] var
                taken_pos[usr_current_pos] = 0;

                //* del the old usr_postion
                SDL_BlitSurface(sub[0].win, &sub[6].pos, screen, &sub[6].pos);

                //* blit the kayori head (tic action)
                SDL_BlitSurface(sub[3].win, NULL, screen, &sub[6].pos);

                //* check if the usr win or not
                check_ttt(sub, taken_pos, 0, &ttt_taken_pos);
                if (ttt_taken_pos == 9)
                  break;

                //* fill the new usr_position && update the usr_postion
                usr_current_pos = is_free(taken_pos);

                // ! check if the usr_current_pos == -1 or not (this is caused by the game_priority ==> the player will have 5 moves)
                if (usr_current_pos != -1) {
                  //* fill the new usr_rect_index
                  have_coordinate(&(sub[6].pos.x), &(sub[6].pos.y), usr_current_pos);
                  SDL_BlitSurface(sub[6].win, NULL, screen, &sub[6].pos);
                }
              }
              break;

            //? --- UP CLICK OPTION ---
            case SDLK_UP:
              if (ttt_taken_pos < 9)
                ttt_scroll_UD(sub, taken_pos, &usr_current_pos, -3);
              break;

            //? --- DOWN CLICK OPTION ---
            case SDLK_DOWN:
              if (ttt_taken_pos < 9)
                ttt_scroll_UD(sub, taken_pos, &usr_current_pos, 3);
              break;

            //? --- RIGHT CLICK OPTION ---
            case SDLK_RIGHT:
              if (ttt_taken_pos < 9) {
                //* update the usr_postion
                usr_current_pos++;

                // TODO: check if the position is taken
                //* check if the usr_current_pos is out of range
                if (usr_current_pos % 3 == 0) usr_current_pos -= 3;

                //* check if the new_usr_pos is available
                // ? can replace it with is_free()
                while (taken_pos[usr_current_pos] != -1) {
                  usr_current_pos++;
                  if (usr_current_pos >= 9) usr_current_pos = 0;
                }

                //* del the old usr_postion
                SDL_BlitSurface(sub[0].win, &sub[6].pos, screen, &sub[6].pos);

                //* fill the new usr_rect_index
                have_coordinate(&(sub[6].pos.x), &(sub[6].pos.y), usr_current_pos);
                SDL_BlitSurface(sub[6].win, NULL, screen, &sub[6].pos);
              }
              break;

            //? --- LEFT CLICK OPTION ---
            case SDLK_LEFT:
              if (ttt_taken_pos < 9) {
                //* update the usr_postion
                usr_current_pos--;

                //* check if the usr_current_pos is out of range [0, 8]
                if (usr_current_pos % 3 == 2 || usr_current_pos == -1) usr_current_pos += 3;

                //* check if the new_usr_pos is available
                while (taken_pos[usr_current_pos] != -1) {
                  usr_current_pos--;
                  if (usr_current_pos <= -1) usr_current_pos = 8;
                }

                //* del the old usr_postion
                SDL_BlitSurface(sub[0].win, &sub[6].pos, screen, &sub[6].pos);

                //* fill the new usr_rect_index
                have_coordinate(&(sub[6].pos.x), &(sub[6].pos.y), usr_current_pos);
                SDL_BlitSurface(sub[6].win, NULL, screen, &sub[6].pos);
              }
              break;

            //? --- ESCAPE CLICK OPTION ---
            case SDLK_ESCAPE:
              freeResources(sub);
              return;
              break;

            default:
              break;
          }
          break;

        //? ------------------- KB BUTTON UP CLICK EVENT -------------------
        case SDL_KEYUP:
          switch (event.key.keysym.sym) {
            //? --- SPACE CLICK OPTION ---
            case SDLK_SPACE:
              /* bot treatment part */
              if (ttt_taken_pos < 9) {
                //* add one for the bot
                ttt_taken_pos++;

                //* fill the new usr_position
                while (1) {
                  srand(time(NULL));
                  int i = rand() % 9;
                  if (taken_pos[i] == -1) {
                    //* update taken_pos[] var
                    taken_pos[i] = 1;

                    //* del the old usr_postion
                    SDL_BlitSurface(sub[0].win, &sub[6].pos, screen, &sub[6].pos);

                    //* have the available taken_pos[i] position using the index [0, 8]
                    have_coordinate(&(sub[6].pos.x), &(sub[6].pos.y), i);

                    //* blit the enemy (tac action)
                    SDL_BlitSurface(sub[2].win, NULL, screen, &sub[6].pos);

                    //* check if the usr lose
                    check_ttt(sub, taken_pos, 1, &ttt_taken_pos);
                    if (ttt_taken_pos == 9)
                      break;

                    //* have the new usr_position && update the usr_postion
                    usr_current_pos = is_free(taken_pos);

                    //* fill the new usr_rect_index
                    have_coordinate(&(sub[6].pos.x), &(sub[6].pos.y), usr_current_pos);
                    SDL_BlitSurface(sub[6].win, NULL, screen, &sub[6].pos);

                    break;
                  }
                }
              }
              break;

            //? --- OTHER CLICK OPTION ---
            default:
              break;
          }
          break;

        //? --------------------- QUIT CLICK EVENT ---------------------
        case SDL_QUIT:
          freeResources(sub);
          exit(EXIT_SUCCESS);
          break;

        //? --- OTHER CLICK OPTION ---
        default:
          break;
      }
    }

    //* update the screen
    SDL_Flip(screen);
    SDL_Delay(10);
  }
}

void ttt_scroll_UD(surface* sub, int* taken_pos, int* usr_cp, int direction) {
  //* update the usr_postion
  *usr_cp += direction;

  //* check if the usr_current_pos is out of range
  if (*usr_cp < 0)
    *usr_cp += 9;
  else if (*usr_cp > 8)
    *usr_cp -= 9;

  //* check if the new_usr_pos is available
  while (taken_pos[*usr_cp] != -1) {
    (direction == 3) ? (*usr_cp += 3) : (*usr_cp -= 3);
    if (*usr_cp < 0)
      *usr_cp = 8;
    else if (*usr_cp > 8)
      *usr_cp = 0;
  }

  //* del the old usr_postion
  SDL_BlitSurface(sub[0].win, &sub[6].pos, screen, &sub[6].pos);

  //* fill the new usr_rect_index
  have_coordinate(&(sub[6].pos.x), &(sub[6].pos.y), *usr_cp);
  SDL_BlitSurface(sub[6].win, NULL, screen, &sub[6].pos);
}

void have_coordinate(Sint16* x, Sint16* y, int usr_pos) {
  //* initial usr_postion
  *x = 662, *y = 282;

  //* fiend the x of the new usr position
  *x += 232 * (usr_pos % 3);

  //* fiend the y of the new usr postion
  *y += 205 * (usr_pos / 3);
}

int is_free(int* t) {
  for (int i = 0; i < 9; i++) {
    if (t[i] == -1)
      return i;
  }
  return -1;
}

void check_ttt(surface* sub, int* t, int x, int* ttttp) {
  if (*ttttp > (4 + x) && check_rcd(sub, t, x)) {
    *ttttp = 9;
    SDL_BlitSurface(sub[13 + x].win, NULL, screen, (sub[13 + x].pos.x = 740, sub[13 + x].pos.y = 473, &sub[13 + x].pos));
  } else if (*ttttp == 9)
    printf("toe !\n");
}

int check_rcd(surface* sub, int* t, int x) {
  return (check_rows(sub, t, x) || check_columns(sub, t, x) || check_diagonals(sub, t, x));
}

int check_rows(surface* sub, int* t, int x) {
  for (int i = 0; i < 9; i += 3)
    if (t[i] == x && t[i + 1] == x && t[i + 2] == x) {
      //* blit the line depending on the x value (0 : usr or 1 : bot)
      //* for rows the pos.x = 662 (const)
      //* 340 is the pos.x of the index 0
      sub[4 + x].pos.y = 335;
      SDL_BlitSurface(sub[4 + x].win, NULL, screen, (sub[4 + x].pos.x = 662, sub[4 + x].pos.y += 199 * (i / 3), &sub[4 + x].pos));
      return 1;
    }
  return 0;
}

int check_columns(surface* sub, int* t, int x) {
  for (int i = 0; i < 3; i++)
    if (t[i] == x && t[i + 3] == x && t[i + 6] == x) {
      //* blit the line depending on the x value (0 : usr or 1 : bot)
      //* for columns the pos.y = 728 (const)
      //* 728 is the pos.x of the index 0
      sub[7 + x].pos.x = 725;
      SDL_BlitSurface(sub[7 + x].win, NULL, screen, (sub[7 + x].pos.x += 232 * (i % 3), sub[7 + x].pos.y = 242, &sub[7 + x].pos));
      return 1;
    }
  return 0;
}

int check_diagonals(surface* sub, int* t, int x) {
  if (t[0] == x && t[4] == x && t[8] == x) {
    //* blit the line depending on the x value (0 : usr or 1 : bot)
    SDL_BlitSurface(sub[11 + x].win, NULL, screen, (sub[11 + x].pos.x = 685, sub[11 + x].pos.y = 257, &sub[11 + x].pos));
    return 1;

  } else if (t[2] == x && t[4] == x && t[6] == x) {
    //* blit the line depending on the x value (0 : usr or 1 : bot)
    SDL_BlitSurface(sub[9 + x].win, NULL, screen, (sub[9 + x].pos.x = 685, sub[9 + x].pos.y = 257, &sub[9 + x].pos));
    return 1;
  }
  return 0;
}

void ttt_initResources(surface* sub) {
  SDL_BlitSurface(sub[0].win, NULL, screen, (sub[0].pos.x = 0, sub[0].pos.y = 0, &sub[0].pos));
  SDL_BlitSurface(sub[1].win, NULL, screen, (sub[1].pos.x = 603, sub[1].pos.y = 186, &sub[1].pos));
  SDL_BlitSurface(sub[6].win, NULL, screen, (sub[6].pos.x = 662, sub[6].pos.y = 282, &sub[6].pos));
}

/*
? loadResources() void func guide
* load all res using the "load_img() SDL_Surface func"
*/
void loadResources(surface sub[]) {
  for (int i = 0; i < 15; i++) {
    char tmp_path[MAX_PATH];
    sprintf(tmp_path, "../../project/res/img%d.png", i);  // Corrected path format
    sub[i].win = load_img(tmp_path);
    printf("Loading: %s\n", tmp_path);

    if (!sub[i].win) {
      printf("Failed to load image at: %s\n", tmp_path);  // Improved error message
    }
  }
}

/*
? initResources() void func guide
* blit the first viewed res
*/
void initResources(surface* sub) {
  SDL_BlitSurface(sub[0].win, NULL, screen, (sub[0].pos.x = 0, sub[0].pos.y = 0, &sub[0].pos));
  SDL_BlitSurface(sub[1].win, NULL, screen, (sub[1].pos.x = 603, sub[1].pos.y = 186, &sub[1].pos));
  SDL_BlitSurface(sub[6].win, NULL, screen, (sub[6].pos.x = 662, sub[6].pos.y = 282, &sub[6].pos));
}