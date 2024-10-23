/**
 * @file SDL1.2_pkg.cpp
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-10-22
 * @copyright Copyright (c) 2024
 * @link https://github.com/ZouariOmar/Cpkg Cpkg @endlink
 */

//? Include Prototype declaration part
#include "../inc/inc.h"

//? Global variables Prototype declaration part
//* SCREEN SURFACE DEFINTION
SDL_Surface *screen = NULL;

//* SCREEN RESOLUTION DEFINTION
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_BPP = 32;

//* SDL_COLOR PUBLIC DEFINTION
const SDL_Color WHITE = {255, 255, 255, 0};
const SDL_Color BLACK = {0, 0, 0, 0};

//? ----------------------- FUNCTIONS PROTOTYPE DEV PART -----------------------

/**
 * @brief ### Initialisation SDL1.2 environment
 */
void __init_sdl__() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {  // SDL initialisation process
    fprintf(stderr, "%s !", SDL_GetError());
    exit(1);
  }
  TTF_Init();                                                                    // TTF initialisation process
  if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024))) {  // Mix initialisation process
    fprintf(stderr, "%s !", SDL_GetError());
    exit(1);
  }
  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);      // IMG initialisation process
  setScreen(0);                               // Set the screen in windowed mode
  SDL_WM_SetCaption("Hollow Vessels", NULL);  // Set the game caption
}

/**
 * @brief ### Close SDL1.2 resources at exit action
 */
void closeEverything() {
  atexit(Mix_Quit);
  atexit(IMG_Quit);
  atexit(TTF_Quit);
  atexit(SDL_Quit);
}

/**
 * @brief ### Optimizing the img process
 * *
 * - #### Creat a new 32 bit img
 * @param path const char *
 * @return SDL_Surface *
 */
SDL_Surface *load_img(const char *path) {
  SDL_Surface *loadedImg = IMG_Load(path),
              *optimizedImg = NULL;
  if (loadedImg) {
    optimizedImg = SDL_DisplayFormatAlpha(loadedImg);
    SDL_FreeSurface(loadedImg);
  }
  return optimizedImg;
}

/**
 * @brief ### Set the screen window mode
 * *
 * - #### x(0) - The screen will be in Windowed Mode
 * *
 * - #### x(SDL_FULLSCREEN) - The screen will be in Fullscreen Mode
 * @param x int
 */
void setScreen(int x) {
  const SDL_VideoInfo *video_info = SDL_GetVideoInfo();
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, ((video_info) ? SDL_HWSURFACE : SDL_SWSURFACE) | SDL_RESIZABLE | SDL_DOUBLEBUF | x);
  if (!screen) {
    fprintf(stderr, "%s !", SDL_GetError());
    exit(1);
  }
}

/**
 * @brief ### Set all (Sint16 x, Sint16 y) surfaces pos from a file
 * @param sub surface *
 * @param path const char *
 * @param nb_res int
 */
void set_pos(surface *sub, const char *path, int nb_res) {
  FILE *file = fopen(path, "r");  // Open the settings file
  if (!file) {
    perror("Error: can't open settings_ref file !");
    exit(EXIT_FAILURE);
  }

  // Fill all surface positions
  int i = 0;
  while (i < nb_res && fscanf(file, "%hd%hd", &(sub[i].pos.x), &(sub[i].pos.y)) == 2) i++;

  fclose(file);  // Close the file
}

/**
 * @brief ### Loading list of resources (images)
 * @param sub surface *
 * @param path const char *
 * @param begin_res int
 * @param nbr_res int
 */
void loadResources(surface *sub, const char *path, int begin_res, int nbr_res) {
  while (begin_res < nbr_res) {
    char tmp_path[260];
    sprintf(tmp_path, "%s%d%s", path, begin_res, ".png");
    sub[begin_res].win = load_img(tmp_path);
    begin_res++;
  }
}

/**
 * @brief ### Free list of resources (surfaces, 1 Font and 1 Chunk) 
 * @param sub surface *
 * @param font TTT_Font *
 * @param pip Mix_Chunk *
 * @param nb_res int
 */
void freeResources(surface *sub, TTF_Font *font, Mix_Chunk *pip, int nb_res) {
  for (int i = 0; i < nb_res; i++)
    SDL_FreeSurface(sub[i].win);
  TTF_CloseFont(font);
  Mix_FreeChunk(pip);
}