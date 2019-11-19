#include <iostream>
#include "TritSet.h"

int main() {
	TritSet set(5, Trit::False);
	Trit tmp = set[-1];
	set[4] = Trit::Unknown;
	set[2] = set[3] & set[4];
	set.print_tritset();
	return 0;
}