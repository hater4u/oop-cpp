#include <iostream>
#include "TritSet.h"

int main() {
	TritSet set(5, True);
	Trit tmp = set[-1];
	set.print_tritset();
	return 0;
}