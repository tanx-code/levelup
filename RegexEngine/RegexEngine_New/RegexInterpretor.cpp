#include "RegexInterpretor.h"
#include "RegexAutomaton.h"
#include <string>
#include <vector>

namespace tl
{

	namespace regex
	{
		using namespace std;
		using namespace regex_internal;
		size_t indexOf(vector<shared_ptr<State>> &v, const State *s)
		{
			for (size_t i = 0; i < v.size();i++)
			{
				if (v[i].get() == s)
					return i;
			}
			return -1;
		}
		RegexInterpretor::RegexInterpretor(regex_internal::Automaton::Ref dfa)
		{
			
			int statesSize = dfa->states.size();

			finalStates = vector<bool>(statesSize);
			charStates = vector<vector<CharRange>>(statesSize);
			tranStates = vector<vector<int>>(statesSize);

			
			vector<shared_ptr<State>> stateList = dfa->states;
			for (size_t i = 0;i < stateList.size();i++)
			{
				finalStates[i] = stateList[i]->finalState;
				for (int j = 0;j < stateList[i]->transitions.size();j++)
				{

					charStates[i].push_back(stateList[i]->transitions[j]->range);
					tranStates[i].push_back(indexOf(stateList, 
											stateList[i]->transitions[j]->target));
				}
			}
		}


		RegexInterpretor::~RegexInterpretor()
		{
		}

		bool RegexInterpretor::matchHead(const wchar_t * input, const wchar_t * start, 
										 RegexResult & result)
		{
			int currentState = 0;
			const wchar_t * begin = input;
			start = nullptr;
			RegexResult midResult;
			midResult.finalState = 0;
			midResult.length = 0;
			midResult.start = -1;
			while (*input)
			{
				bool enter = false;

				for (size_t j = 0;j < charStates[currentState].size();j++)
				{
					if (*input >= charStates[currentState][j].begin &&
						*input <= charStates[currentState][j].end)
					{
						currentState = tranStates[currentState][j];
						if (!start)
						{
							start = input;
						}
						enter = true;
						break;
					}
				}

				if (!enter)
				{
					if (finalStates[currentState])
					{
						result.length = input - start;
						result.finalState = currentState;
						result.start = start - begin;
						return true;
					}
					if (start)
						--input;
					start = nullptr;
					currentState = 0;
					++input;
				}
				else if(enter && start)
				{
					++input;
				}

				if (finalStates[currentState])
				{
					midResult.length = input - start;
					midResult.finalState = currentState;
					midResult.start = start - begin;
					if (*input)
						continue;
					result.length = input - start;
					result.finalState = currentState;
					result.start = start - begin;
					return true;
				}
			}

			if (finalStates[midResult.finalState])
			{
				result = midResult;
				return true;
			}

			result.length = 0;
			result.finalState = currentState;
			result.start = -1;
			return false;
		}
	}
}