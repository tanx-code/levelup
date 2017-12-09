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
			// ���ﲻ������ָ�룬ֻҪ�����ά��һ�ݣ����ܱ�֤����delete
			vector<Transition*> transitions;
			vector<Transition*> inputs;
			bool finalState;
			void* userData;
		};
		class Transition
		{
		public:
			// Nop���͵ıߴ�����������epsilon��
			// ��ʵ��Ϊ��֮��ȥepsilon�ߵ�ʱ�򣬿�����������
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
			// ��Ҫ������ָ��ӹ���Щָ��һ�Σ���֤�������ն��ܱ��Զ�delete����
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