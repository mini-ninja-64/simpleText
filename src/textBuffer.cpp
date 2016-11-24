#include "textBuffer.h"

void textBuffer::init(std::string file){
	std::string line;
	std::ifstream f (file);
	if (f.is_open())
	{
		while ( getline (f,line) )
		{
			buff.push_back(line);
		}
		f.close();
	}
}

int textBuffer::size(){
	return buff.size();
}

std::string textBuffer::line(int i){
	return buff[i];
}

void textBuffer::writeLine(int i, std::string str){
	if (buff.size() >= i){
		buff[i] = str;
	}else{
		for (int iy = buff.size(); iy < (i+1); iy++){
			if (i == iy) {
				buff.push_back(str);
			}else{
				buff.push_back("");
			}
		}
	}
}