#include "textCanvas.h"

int textCanvas::init(std::string file){
	cursor[0] = 0;
	cursor[1] = 0;
	doccursor[0] = 0;
	doccursor[1] = 0;
	init_pair(1, COLOR_WHITE, COLOR_CYAN);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
	status = "Simple Text Editor 1.00" + file;
	tBuffer.init(file);
	startLine = 0;
}

void textCanvas::destroy(){

}

void textCanvas::handleInput(WINDOW * win, int c){
	switch(c){
		case KEY_UP:
			cursor[1]--;
			doccursor[1]--;
			break;
		case KEY_DOWN:
			cursor[1]++;
			doccursor[1]++;
			break;
		case KEY_LEFT:
			cursor[0]--;
			doccursor[0]--;
			break;
		case KEY_RIGHT:
			cursor[0]++;
			doccursor[0]++;
			break;
	}

	//stuff
	if (cursor[0] < 3){ cursor[0] = 3;}
	if (cursor[0] > (maxX-1)){ cursor[0] = maxX-1; }
	if (cursor[1] < 0){
		cursor[1] = 0;
		if (doccursor[1]>0){
			startLine--;
			//onResize(win,0,0);
		}else{
			startLine = 0;
			doccursor[1] = 0;
		}
	}
	if (cursor[1] > (maxY-2)){
		cursor[1] = maxY-2;
		if (doccursor[1]<tBuffer.size()){
			startLine++;
			//onResize(win,0,0);
		}else{
			//startLine = (tBuffer.size()-1);
			doccursor[1] = (tBuffer.size()-1);
		}
	}

	doccursor[0] = cursor[0]-3;
	if (doccursor[0] > (tBuffer.line(doccursor[1]).length()-1)){
		doccursor[0] = (tBuffer.line(doccursor[1]).length()-1);
	}

	if (c == 127){
		std::string tempLine = tBuffer.line(doccursor[1]);//str.erase (10,8);
		tempLine.erase(doccursor[0],1);
		cursor[0] = doccursor[0]-1+3;
		tBuffer.writeLine(doccursor[1],tempLine);

	}

	char keyAsChar = (char)c;

	if ((c >= 32) && (c <= 126)){
		std::string tempLine = tBuffer.line(doccursor[1]);//str.erase (10,8);
		tempLine+=keyAsChar;
		tBuffer.writeLine(doccursor[1],tempLine);
		cursor[0]+=1;
	}

	status = std::to_string(c);
}

void textCanvas::update( WINDOW * win ){
	int oldmX = maxX;
	int oldmY = maxY;
	getmaxyx(win,maxY,maxX);
	if ((oldmX != maxX) || (oldmY != maxY)){
		onResize(win, oldmX,oldmY);
	}
}

void textCanvas::draw( WINDOW * win ){

	//draw text buffer
	onResize(win,0,0);
	int screenI = 0;
	for (int i = startLine; i < tBuffer.size(); i++){
		mvwprintw(win, screenI, 3, tBuffer.line(i).c_str());
		screenI++;
	}

	//draw cursor
	drawStatus( win );

	refresh();
	move(cursor[1],cursor[0]);
}

void textCanvas::onResize(WINDOW * win, int oldx, int oldy){
	std::string screenFill;
	for(int i = 0; i < maxX*maxY; i++){
		screenFill += ' ';
	}
	mvwprintw(win, 0, 0, screenFill.c_str());
}

void textCanvas::drawStatus( WINDOW * win ){
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	//line numbers
	std::string num;
	int lNum=startLine+1;
	for(int i = 0; i < (maxY-1); i++){
		num = std::to_string(lNum);
		while(num.length() < 3){
			num += ' ';
		}
		mvwprintw(win, i, 0, num.c_str());
		lNum++;
	}

	//bottom bar
	//status = "X: " + std::to_string(doccursor[0]) + " Y: " + std::to_string(doccursor[1]);
	for(int x = status.length(); x < maxX; x++){
		status += ' ';
	}
	mvwprintw(win, maxY-1, 0, status.c_str());
	attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
}