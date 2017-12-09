#pragma once
#include "RegexExpression.h"
#include <memory>


namespace tl
{
	namespace regex
	{
		class RegexNode
		{
		public:
			tl::regex_internal::Expression::Ref		expression;

			RegexNode(tl::regex_internal::Expression::Ref _expression);

			RegexNode					Some()const;
			RegexNode					Any()const;
			RegexNode					Opt()const;
			RegexNode					Loop(int min, int max)const;
			RegexNode					AtLeast(int min)const;
			RegexNode					operator+(const RegexNode& node)const;
			RegexNode					operator|(const RegexNode& node)const;
			RegexNode					operator%(const RegexNode& node)const;
			RegexNode					operator!()const;

		};

		using namespace std;

		extern RegexNode				rBegin();
		extern RegexNode				rEnd();
		extern RegexNode				rC(wchar_t a, wchar_t b = L'\0');
		extern RegexNode				r_d();
		extern RegexNode				r_l();
		extern RegexNode				r_w();
		extern RegexNode				rAnyChar();
	}
}

