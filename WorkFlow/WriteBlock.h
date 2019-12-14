#pragma once
#include "IBlock.h"

class WriteBlock : public Common::IBlock
{
public:
	WriteBlock() = default;

	std::string operation(std::vector<std::string> data) override;
};

