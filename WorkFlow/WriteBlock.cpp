#include "WriteBlock.h"
#include "BlockMaker.h"

static BlockMaker<WriteBlock> writefileMaker("writefile");

std::string WriteBlock::operation(const std::string& text, const std::vector<std::string>& data)
{
	std::ofstream out;
	out.open(data[0]);

	if (!out.is_open())
	{
		throw new std::exception("EXCEPTION: can't open file");
	}
	out << text;

	out.close();
	return "End of flow";
}
