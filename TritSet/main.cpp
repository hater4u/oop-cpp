#include <iostream>
#include "TritSet.h"

int main() {
	TritSet set(33, True);
	TritSet a(5);
	TritSet b(True);
	set[0] = False;
	set[50] = Unknown;
	set[40] = False;
	Trit tmp = set[0];
	set[39] = set[40];
	if (set[0] == set[40])
	{
		std::cout << "set[0] = set[40]" << std::endl;
	}
	for (auto it = 0; it < 55; it++) 
	{
		tmp = set[it];
		std::cout << tmp << " ";
	}
	std::cout << std::endl;


	return 0;
}