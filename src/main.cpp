#include <ncurses.h>
#include "textCanvas.h"

bool init(){
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	//curs_set(0);
	//set_tabsize(4);
	return true;
}

int main(int argc, char const *argv[])
{
	bool running = init();
	WINDOW * local_win = stdscr;

	textCanvas can;
	can.init(argv[1]);
	int c;
	while (running){
		can.update( local_win );
		can.draw( local_win );
		c = getch();
		if (c == 27){
			running = false;
		}
		can.handleInput( local_win, c );
	}

	endwin();

	return 0;
}