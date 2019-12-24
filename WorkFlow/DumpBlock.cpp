#include "DumpBlock.h"
#include "BlockMaker.h"

static BlockMaker<DumpBlock> dumpMaker("dump");

std::string DumpBlock::operation(const std::string& text, const std::vector<std::string>& data)
{
	if (data.empty() || text.empty() || data.size() > 1)
	{
		throw std::runtime_error("EXCEPTION: invalid arguments for dump");
	}
	std::ofstream out;
	out.open(data[0]);
	if (!out.is_open())
	{
		throw new std::exception("EXCEPTION: can't open file");
	}
	out << text;

	out.close();
	return text;
}
