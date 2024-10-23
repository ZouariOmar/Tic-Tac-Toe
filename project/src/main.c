/**
 * @file main.c
 * @author ZouariOmar (zouariomar20@gmail.com)
 * @brief Main src file
 * @version 0.1
 * @date 2024-10-23
 * @copyright Copyright (c) 2024
 */

//? Include prototype declaration part
#include "../inc/inc.h"

//? Main int function dev part

/**
 * @brief # Main app function
 * @return int 
 */
int main() {
  initEverything();
  closeEverything();
  __ttt_game__();
  // SDL_FreeSurface(screen);
  return 0;
}
