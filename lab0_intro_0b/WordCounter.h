#pragma once

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>

class WordCounter
{
private:
	std::map <std::string, int> MyMap;
	std::vector <std::pair<std::string, int> > MyVector;
	int AllCount;


public:
	void InputWordCounter(const std::string &inputf);
	void OutputWordCounter(const std::string &outputf);
};

