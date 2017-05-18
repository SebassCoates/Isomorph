#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

using namespace std;

static const string CSI = "\033[";

// -- NOTE TO COMP11 STUDENTS ----------------
//
//  DO NOT EDIT OR COPY CODE FROM THIS FILE
//  TO USE THESE FUNCTIONS:
//     at the top of your code put: #include "termfuncs.h"
//     when you compile:  g++ -Wall myprog.cpp termfuncs.cpp
//
//  DO NOT DO THIS:
//	#include "termfuncs.cpp"
//
//
// termfuncs.cpp -- some simple functions for using the terminal nicely
//
//   char getachar()     -- returns next char with no echo and no Enter needed
//   char getacharnow(ds)     -- only waits ds/10th seconds
//				 returns '\0' if no input by that time
//   void screen_clear() -- clears the screen
//   void screen_home()  -- moves cursor to top of screen
//   void screen_fg(string color)
//   void screen_bg(string color)
//   void screen_attr(string attr)
//   void screen_bright()
//   void screen_reset()
//   void place_cursor(int, int);   -- move the cursor to row col
//   void place_char(char, int, int)  -- move and place
//   void hide_cursor()
//   void show_cursor()
//
//   int  random_int(int low, int high)
//		returns random int in [low, high]
//		note: if SNAKE_SEED is set then use that for srand
//		      if not, then call srand with time(0) at first call
//   void seed_random(s)
//
//    int get_screen_cols();
//    int get_screen_rows();
//
// hist: 2015-04-07 MAS:  Bug fix:  
//                        signal() was returning NULL as the default signal
//                        handler the first time, so we called it again, which
//                        set prev_handler to our handler, which precipitated
//                        an infinite loop on SIGINT.
//                        The fix is to call signal() at most once and
//                        and then invoke the prior handler only if we set
//                        to something non-NULL.
//                                  
// hist: 2015-04-06 MAS:  getachar: if terminal info cached, need to set
//                                  local vars info and orig to that.
//                                  Question:  why have orig at all?
// hist: 2014-11-17 added get_screen_cols and get_screen_rows
// hist: 2014-09-30 added flush to getachar* and also show_cursor sighandler
// hist: 2014-09-30 added hide/show cursor and random_int
// hist: 2014-07-20 getachar now uses read, not cin >> c which skipped blanks
// hist: 2014-07-01 merged screendraw and termfuncs
//
static string color_names[] = { "black", "red", "green", "yellow",
				"blue",  "magenta", "cyan", "white" };
static const int num_colors = 8;

static string attr_names[] = { 	"reset", "bright", "dim", "", 
				"underscore", "blink", "", 
				"reverse", "hidden" };
static const int num_attrs = 9;

static termios prev_tty_state;
static int prev_state_stored = 0;

static bool sigint_handler_set = false;
static	void (*prev_handler)(int) = NULL;
static inline void ensure_sigint_handled();


//
// getachar
//  returns a char using noecho and -icanon unless not a tty
//
char getachar()
{
	char c;

	cout << std::flush;
	if ( isatty(0) )
	{
		struct termios	info, orig;
		// system("stty -echo -icanon");

		if ( !prev_state_stored ) {
			tcgetattr(0, &info);
			orig = info;
			prev_tty_state = orig;
			prev_state_stored = 1;
		} else {
                        // 2015-04-06:  Added by MAS
                        info = orig = prev_tty_state;  
                }

		ensure_sigint_handled();

		info.c_lflag &= ~ECHO;
		info.c_lflag &= ~ICANON;
		tcsetattr(0, TCSANOW, &info);

		read(0, &c, 1);

		// system("stty echo icanon");
		tcsetattr(0, TCSANOW, &orig);
	}
	else {
		read(0, &c, 1);
	}

	return c;
}
//
// getacharnow
//  returns a char using noecho and -icanon unless not a tty
//
char getacharnow(int decisecs)
{
	char c;

	cout << std::flush;
	if ( isatty(0) ) 
	{
		struct termios	info, orig;
		// system("stty -echo -icanon");
		tcgetattr(0, &info);
		orig = info;
		prev_tty_state = orig;
		prev_state_stored = 1;

		ensure_sigint_handled();

		info.c_lflag &= ~ECHO;
		info.c_lflag &= ~ICANON;
		info.c_cc[VMIN] = 0;
		info.c_cc[VTIME] = decisecs;
		tcsetattr(0, TCSANOW, &info);

		if ( read(0, &c, 1) != 1 )
			c = '\0';

		tcsetattr(0, TCSANOW, &orig);
		// system("stty echo icanon");
	}
	else {
		if ( read(0, &c, 1) != 1 )
			c = '\0';
	}

	return c;
}


static void restore_tty_state()
{
	if ( prev_state_stored )
		tcsetattr(0, TCSANOW, &prev_tty_state);
}
void screen_clear()
{
	cout << (CSI + "H");
	cout << (CSI + "2J");
}

void screen_home()
{
	cout << (CSI + "H");
}


void hide_cursor()
{
	ensure_sigint_handled();
	cout << (CSI + "?25l");
}

void show_cursor()
{
	cout << (CSI + "?25h");
}

void on_sigint(int s)
{
	cout << std::flush;
	show_cursor();
	if ( sigint_handler_set and prev_handler != NULL ){
		prev_handler(s);
	}
	restore_tty_state();
	exit(SIGINT);
}

static inline void ensure_sigint_handled()
{
        if (not sigint_handler_set) {
                prev_handler = signal(SIGINT, on_sigint);
                sigint_handler_set = true;
        }
}

//
// lookup a string in an array
//   args: string to find, list of strings, len of list
//   rets: index of string or -1 for not found
//
static int lookup(string findme, string list[], int num)
{
	int	i;
	for(i=0;i<num;i++)
	{
		if ( list[i] == findme )
			return i;
	}
	return -1;
}
void screen_fg(string color)
{
	int	num = lookup(color, color_names, num_colors);
	if ( num >= 0 ){
		cout << CSI << ( 30 + num ) << "m";
	}
}
void screen_bg(string color)
{
	int	num = lookup(color, color_names, num_colors);
	if ( num >= 0 ){
		cout << CSI << ( 40 + num ) << "m";
	}
}
void screen_attr(string attr)
{
	int	num = lookup(attr, attr_names, num_attrs);
	if ( num >= 0 ){
		cout << CSI << num  << "m";
	}
}
void screen_bright()
{
	screen_attr("bright");
}
void screen_reset()
{
	screen_attr("reset");
}
void place_cursor(int row, int col)
{
	cout << "\033[" << (row+1) << ";" << (col+1) << "H";
	flush(cout);
}
void place_char(char c, int row, int col)
{
	place_cursor(row, col);
	cout << c;
	flush(cout);
}

static int rand_seed = -1;

void seed_random(int s)
{
	if ( s > 0 ){
		srand(s);
		rand_seed = s;
	}
}

int random_int(int lo, int hi)
{
	int	range = hi - lo + 1;
	char	*seed_str;

	if ( rand_seed == -1 ){
		seed_str = getenv( "SNAKE_SEED" );
		if ( seed_str != NULL )
			seed_random( (unsigned) atoi(seed_str) );
		else 
			seed_random( (unsigned) time(NULL) );
	}
	if ( range <= 0 )
		return 17;		// add to function specs

	return lo + ( rand() % range );
}

#include <sys/ioctl.h>

// returns number of rows on the screen
int get_screen_rows()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_row;
}
// returns number of cols on the screen
int get_screen_cols()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}
