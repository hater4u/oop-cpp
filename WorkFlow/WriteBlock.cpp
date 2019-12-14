#include "WriteBlock.h"
#include "BlockMaker.h"

static BlockMaker<WriteBlock> writefileMaker("writefile");

std::string WriteBlock::operation(std::vector<std::string> data)
{
	std::ofstream out;
	out.open(data[0]);

	out << data[1];

	out.close();
	return "End of flow";
}
