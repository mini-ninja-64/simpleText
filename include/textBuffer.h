#ifndef textBuffer_h
#define textBuffer_h

#include <ncurses.h>
#include <string>
#include <vector>
#include <fstream>

class textBuffer
{
public:
	void init(std::string file);
	// void destroy();
	// void save(std::string file);

	void writeLine(int i, std::string line);
	std::string line(int i);
	int size();
private:
	std::vector<std::string> buff;
};

#endif /* textBuffer_h */