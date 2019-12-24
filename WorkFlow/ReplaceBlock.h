#pragma once
#include "IBlock.h"

class ReplaceBlock : public Common::IBlock
{
public:
	ReplaceBlock() = default;

	std::string operation(const std::string& text, const std::vector<std::string>& data) override;
};

