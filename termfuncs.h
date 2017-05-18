#ifndef	TERMFUNCS_H
#define	TERMFUNCS_H
//
// termfuncs.h -- some simple functions for using the terminal nicely
//
//   char getachar()     -- returns next char with no echo and no Enter needed
//   char getacharnow(n) -- like getachar but times out at n/10 sec
//			 -- if timeout, return '\0'
//   void screen_clear() -- clears the screen
//   void screen_home()  -- moves cursor to top of screen
//
//    int get_screen_rows()  -- returns dimensions of terminal
//    int get_screen_cols()
//

#include <string>

using namespace std;

char getachar();
char getacharnow(int);
void screen_clear();
void screen_home();

//
// colors can be "black", "red", "green", "yellow", "blue"
// "magneta", "cyan", "white"
//
// attributes can be "reset", "bright", "dim", "underscore",
//  "blink", "reverse", "hidden"
//
void screen_fg(string);
void screen_bg(string);
void screen_attr(string);

void screen_bright();
void screen_reset();

void place_cursor(int, int);
void place_char(char, int, int);

void hide_cursor();
void show_cursor();

int  random_int(int, int);
void seed_random(int);

int get_screen_rows();
int get_screen_cols();
#endif
