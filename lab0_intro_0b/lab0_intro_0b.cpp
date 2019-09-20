#include "WordCounter.h"

int main(int argc, char** argv) {
	WordCounter WC;
	WC.InputWordCounter(argv[1]);
	WC.OutputWordCounter(argv[2]);
	return 0;
}