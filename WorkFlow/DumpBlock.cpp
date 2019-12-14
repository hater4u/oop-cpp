#include "DumpBlock.h"
#include "BlockMaker.h"

static BlockMaker<DumpBlock> dumpMaker("dump");

std::string DumpBlock::operation(std::vector<std::string> data)
{
	std::ofstream out;
	out.open(data[0]);

	out << data[1];

	out.close();
	return data[1];
}
