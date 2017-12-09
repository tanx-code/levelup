#pragma once
#include <string>
#include "RegexAutomaton.h"
#include "RegexExpression.h"
namespace tl
{

	namespace regex
	{
		using namespace std;
		//class RegexResult
		//{
		//public:
		//	std::wstring w;
		//};
		class RegexResult
		{
		public:
			RegexResult()
			{

			}
			RegexResult(RegexResult& r)
			{
				start = r.start;
				length = r.length;
				finalState = r.finalState;
			}
			int start;
			int length;
			int finalState;
		};
		class RegexInterpretor
		{
		public:
			RegexInterpretor(regex_internal::Automaton::Ref dfa);
			~RegexInterpretor();
			bool matchHead(const wchar_t* input,
						   const wchar_t* start, 
						   RegexResult& result);
		private:
			vector<bool> finalStates;
			vector<vector<regex_internal::CharRange>> charStates;
			vector<vector<int>> tranStates;
		};
	}
}