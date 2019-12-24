#pragma once
#include "IBlock.h"

class WriteBlock : public Common::IBlock
{
public:
	WriteBlock() = default;

	std::string operation(const std::string& text, const std::vector<std::string>& data) override;
};

