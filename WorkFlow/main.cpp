#include <iostream>
#include "WorkFlow.h"
#include "ReplaceBlock.h"

using namespace Common;

int main()
{
	WorkFlow wf;
	wf.start("workflow.txt");
	return 0;
}