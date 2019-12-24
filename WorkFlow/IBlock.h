#pragma once

#include "WorkFlow.h"

namespace Common
{
	class IBlock
	{
	public:
		virtual std::string operation(const std::string &text, const std::vector<std::string> &data) = 0;

		~IBlock() = default;
	};
}
