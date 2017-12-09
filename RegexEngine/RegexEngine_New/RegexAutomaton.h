#pragma once
#include <iostream>
#include <map>
#include "RegexData.h"
#include <memory>

namespace tl
{
	namespace regex_internal
	{
		using namespace std;

		class State;
		class Transition;

		class State
		{
		public:
			// 这里不用智能指针，只要最后有维护一份，就能保证都能delete
			vector<Transition*> transitions;
			vector<Transition*> inputs;
			bool finalState;
			void* userData;
		};
		class Transition
		{
		public:
			// Nop类型的边代表不可消除的epsilon边
			// 其实是为了之后去epsilon边的时候，可以少做点事
			enum Type
			{
				Chars,
				Epsilon,
				BeginString,
				EndString,
				Nop
			};
			State* source;
			State* target;
			CharRange range;
			Type type;
		};
	
		class Automaton
		{
		public:
			typedef shared_ptr<Automaton> Ref;
			// 需要用智能指针接管这些指针一次，保证它们最终都能被自动delete掉。
			vector<shared_ptr<State>> states; 
			vector<shared_ptr<Transition>> transitions;
			State* startState;

			Automaton();

			//some utility
			State* NewState();
			Transition* NewTransition(State* start, State* end);
			Transition* NewChars(State* start, State* end, CharRange range);
			Transition* NewEpsilon(State* start, State* end);
			Transition*	NewBeginString(State* start, State* end);
			Transition*	NewEndString(State* start, State* end);
			Transition* NewNop(State* start, State* end);
		};

		extern bool epsilonChecker(Transition * t);
		extern Automaton::Ref EpsilonNfaToNfa(Automaton::Ref source, bool(*epsilonChecker)(Transition*), map<State*, State*>& nfaStateMap);
		extern Automaton::Ref NfaToDfa(Automaton::Ref source, Multimap<State*, State*>& dfaStateMap);
	}
}