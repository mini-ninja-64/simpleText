#ifndef textCanvas_h
#define textCanvas_h 

#include <ncurses.h>
#include <string>
#include "textBuffer.h"

class textCanvas
{
public:
	void handleInput(WINDOW * win, int c);
	void update( WINDOW * win );
	void draw( WINDOW * win );

	int init(std::string file);
	void destroy();
private:
	void drawStatus( WINDOW * win );
	int maxX,maxY;
	int cursor[2]; //physical screen cursor
	int doccursor[2]; //theoretical document cursor
	int startLine;
	void onResize(WINDOW * win, int oldx, int oldy);
	std::string status;
	
	textBuffer tBuffer;

};

#endif /* textCanvas_h */