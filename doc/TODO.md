<!-- @format -->

# TODO

- TODO: ameliorate the bot choices (using IA for the 8 direction :: (2 toc in row or 1 toc need it to win) && available postion ==> forcing win)
- TODO: make decision about the scrolling part (SDLK_Up && SDLK_Down have 2 bugs)
  ! 2 bugs code info :: taken_pos(1.2.3.4.6.8 // or reversed(2nd bug)) && usr_current_pos = 0 from usr_current_pos to 7 impossible (forcing move to position 5)
- TODO: add the front-end toe part

- actual solution for the 2 bugs :: make the scrolling part (SDLK_Up && SDLK_Down) working the same as the scrolling part (SDLK_Left && SDLK_Right) ==> use scroll_UDLR() void func
