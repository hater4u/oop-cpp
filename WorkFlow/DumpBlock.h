#pragma once
#include "IBlock.h"

class DumpBlock : public Common::IBlock
{
public:
	DumpBlock() = default;

	std::string operation(const std::string& text, const std::vector<std::string>& data) override;
};

