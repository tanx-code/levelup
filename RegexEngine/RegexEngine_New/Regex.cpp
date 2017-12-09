#include "Regex.h"
#include "RegexAutomaton.h"
#include "RegexExpression.h"
namespace tl
{

	Regex::Regex(std::wstring pattern) : _pattern(pattern)
	{
	}

	Regex::Regex(std::string pattern)
	{
		std::wostringstream oss;
		oss << pattern.c_str();
		_pattern = oss.str();
	}

	Regex::~Regex()
	{
		delete re;
	}

	void Regex::search(std::wstring target, result_t& result)
	{
		using namespace regex_internal;
		regex::RegexResult _result;
		RegexExpression::Ref regex = ParseRegexExpression(_pattern);
		List subsets;
		Expression::Ref expression = regex->expression;
		std::map<State*, State*> nfaStateMap;
		Multimap<State*, State*> dfaStateMap;
		Automaton::Ref eNfa = expression->generateEpsilonNfa();
		Automaton::Ref nfa = EpsilonNfaToNfa(eNfa, epsilonChecker,nfaStateMap);
		Automaton::Ref dfa = NfaToDfa(nfa, dfaStateMap);
		re = new regex::RegexInterpretor(dfa);
		if (!re->matchHead(target.c_str(), target.c_str(), _result))
		{
			result = L"";
			result_m = _result;
			return;
		}
		std::wostringstream oss;
		const wchar_t* input = target.c_str();
		for (size_t i = 0; i < _result.length;i++)
		{
			oss << *input++;
		}
		result_m = _result;
		result = oss.str();
	}

}