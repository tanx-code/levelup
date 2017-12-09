#pragma once
#include "RegexInterpretor.h"
#include <sstream>

namespace tl
{
	class Regex
	{
	public:
		typedef std::wstring result_t;
		Regex(std::wstring pattern);
		Regex(std::string pattern);
		~Regex();
		void search(std::wstring target, result_t &result);
		regex::RegexResult result_m;
	private:
		std::wstring _pattern;
		regex::RegexInterpretor *re;
	};

}