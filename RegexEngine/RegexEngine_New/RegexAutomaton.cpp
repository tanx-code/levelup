#include "RegexAutomaton.h"

namespace tl
{
	namespace regex_internal
	{

		Automaton::Automaton()
		{
			startState = 0;
		}

		State * Automaton::NewState()
		{
			State* state = new State;
			state->finalState = false;
			state->userData = 0;
			states.push_back(shared_ptr<State>(state));
			return state;
		}

		Transition * Automaton::NewTransition(State* start, State* end)
		{
			Transition* transition = new Transition;
			transition->source = start;
			transition->target = end;
			start->transitions.push_back(transition);
			end->inputs.push_back(transition);
			transitions.push_back(shared_ptr<Transition>(transition));
			return transition;
		}

		Transition * Automaton::NewChars(State * start, State * end, CharRange range)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Chars;
			transition->range = range;
			return transition;
		}

		Transition * Automaton::NewEpsilon(State * start, State * end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Epsilon;
			return transition;
		}

		Transition * Automaton::NewBeginString(State * start, State * end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::BeginString;
			return transition;
		}

		Transition * Automaton::NewEndString(State * start, State * end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::EndString;
			return transition;
		}

		Transition * Automaton::NewNop(State * start, State * end)
		{
			Transition* transition = NewTransition(start, end);
			transition->type = Transition::Nop;
			return transition;
		}

		// ��������
		static bool isElementExist(const vector<State*>& v, const State* e)
		{
			for (auto i : v)
			{
				if (i == e)
					return true;
			}
			return false;
		}
		// ��e�߱հ�
		static void CollectEpsilon(State* targetState, State* sourceState, bool(*epsilonChecker)
								   (Transition*), vector<State*>& epsilonStates, 
								   vector<Transition*>& transitions)
		{
			if (!isElementExist(epsilonStates, sourceState))
			{
				epsilonStates.push_back(sourceState);// һ��ʼ������Լ���ȥ
				for (int i = 0;i<sourceState->transitions.size();i++)// ����������ı�
				{
					Transition* transition = sourceState->transitions[i];
					if (epsilonChecker(transition)) // �ж��Ƿ�Ϊepsilon��
					{
						// ���epsilonStates��û�������㣬�Ͱ������ָ��Ľ��ӽ�ȥ
						if (!isElementExist(epsilonStates, transition->target)) 
						{
							if (transition->target->finalState)
							{
								targetState->finalState = true;
							}
							CollectEpsilon(targetState, transition->target, epsilonChecker, 
										   epsilonStates, transitions);
						}
					}
					else
					{
						transitions.push_back(transition);// ������ַ��ߣ��Ͱ��Լ��ӽ�ȥ
					}
				}
			}
		}

		bool epsilonChecker(Transition * t)
		{
			switch (t->type)
			{
			case Transition::Nop:
			case Transition::Epsilon:
				return true;
			default:
				return false;
			}
			return false;
		}

		// ȥEpsilon�ߵ��㷨��
		Automaton::Ref EpsilonNfaToNfa(Automaton::Ref source, 
									   bool(*epsilonChecker)(Transition *), 
									   map<State*, State*>& nfaStateMap)
		{
			Automaton::Ref target = shared_ptr<Automaton>(new Automaton);
			map<State*, State*> stateMap;	//source->target
			vector<State*> epsilonStates;	//ÿ�ε�����ǰ״̬��epsilon�հ�
			vector<Transition*> transitions;//ÿ�ε�����ǰ״̬��epsilon�հ���ת������

			// target һ��ʼ�ǿյġ�
			stateMap.emplace(source->startState, target->NewState());
			// target���½�һ����㣬��Ӧsource��Ŀ�ʼ���
			nfaStateMap.emplace(stateMap[source->startState], source->startState);
			// ��stateMap�Ƿ��ŵ�
			target->startState = target->states[0].get();// ����Ѹոս��Ľ������������ʼ���


			// һ��ʼֻ��һ����ʼ��㡣
			// ÿ��ֻҪ����һ�����ıհ���
			for (int i = 0;i < target->states.size();i++)
			{
				//���epsilonStates�������Լ�
				State* targetState = target->states[i].get();
				State* sourceState = nfaStateMap[targetState];
				if (sourceState->finalState)
				{
					targetState->finalState = true;
				}
				// ÿ�ε�������ա�����epsilon�ߵıհ�
				epsilonStates.clear();// �ҳ�����epsilon״̬�Ľ��
				transitions.clear(); // ��ǰ���ıߵļ���

				// �����в�����epsilonStates���б������������״̬��һ��epsilonֱ��Ŀ��ӽ�ȥ��
				// ����������
				CollectEpsilon(targetState, sourceState, epsilonChecker, epsilonStates, transitions);

				//��������epsilon�հ�ת��
				for (int j = 0;j < transitions.size();j++)
				{
					Transition* transition = transitions[j];
					// �������ҵ��������㣬����stateMap���ʱ��
					// �Ͱ������㣬�ӵ�stateMap����ȥ��
					// Ȼ��״̬����Ҳ�½�һ����㣬�´�ѭ��Ҫ�õģ��������������Ϣ�ǿյ�
					// ��ʵÿ�ε����ĵ�ǰ��㣬��Ϣ���ǿյ�
					// Ѱ�ҵ�һ����epsilon�հ���ʱ�����ӳ��
					if (stateMap.find(transition->target)==stateMap.end())
					{
						stateMap.emplace(transition->target, target->NewState());
						nfaStateMap.emplace(stateMap[transition->target], transition->target);
					}
					//����ת�����Ƶ���״̬����
					Transition* newTransition = target->NewTransition(targetState, stateMap
																	  [transition->target]);
					// �ӵ�ǰ���ָ���ҵ��Ĵ��ַ��ߵĽ��

					// ������ǰѱߵ�ʣ�����Ϣ�����ƹ�ȥ
					newTransition->range = transition->range;
					newTransition->type = transition->type;

					// һ�ε�������ɵĹ����У��ҳ���ǰ���ķ�epsilon�հ�
					// �½���Ӧ�ĿյĽ�㣬�������ǺͿս���ӳ�䣬���ѿյ�
					// ���ӵ��µ�״̬�����States������´ε���Ҫ�õ�ʱ��
					// �Ϳ�����ӳ���ϵȡ����
				}
			}
			return target;
		}

		// �Ķ���Դ���룬�����ȵ�֪����������Ĺؼ��㷨��ʵ�ֵ�Ŀ�꣩
		// �������Ѿ�֪��nfaתdfa���㷨�����֪������Ĺ��̣�ֻ����ģ������㷨
		// ��ʱ����ȥ��ϸ�ڣ��ͱ�ø�������
		static bool isTransitionEqual(Transition* a, Transition* b)
		{
			if (a->type != b->type)return false;
			switch (a->type)
			{
			case Transition::Chars:
				return a->range == b->range;
			default:
				return true;
			}
		}
		Automaton::Ref NfaToDfa(Automaton::Ref source, Multimap<State*, State*>& dfaStateMap)
		{
			Automaton::Ref target = shared_ptr<Automaton>(new Automaton);
			Multimap<Transition*, Transition*> nfaTransitions;
			vector<Transition*> transitionClasses;//��֤ת���Ⱥ�˳�򲻱�nfaTransitions.Keys�ƻ�

			State* startState = target->NewState();
			target->startState = startState;
			dfaStateMap.insert(startState, source->startState);

			vector<State*> transitionTargets;
			vector<State*> relativeStates;


			for (int i = 0;i < target->states.size();i++)
			{
				// dfa�еĴ�����Ľ��
				State* currentState = target->states[i].get();
				nfaTransitions.clear();
				transitionClasses.clear();

				// ���dfa����Ӧ��nfa���Ǹ����
				// �Ը�DFA״̬�����еȼ�NFA״̬���б���
				vector<State*> &nfaStates = dfaStateMap[currentState];
				for (int j = 0;j < nfaStates.size();j++)
				{
					State* nfaState = nfaStates[j];
					//��ÿһ��NFA״̬������ת�����б���
					for (int k = 0;k < nfaState->transitions.size();k++)
					{
						Transition* nfaTransition = nfaState->transitions[k];
						//����NFAת�������Ƿ��Ѿ������Ѿ�����¼
						Transition* transitionClass = 0;
						for (auto it = nfaTransitions.begin();it != nfaTransitions.end();it++)
						{
							Transition* key = (*it).first;
							if (isTransitionEqual(key, nfaTransition))
							{
								transitionClass = key;
								break;
							}
						}
						//�������򴴽�һ��ת������
						if (transitionClass == 0)
						{
							transitionClass = nfaTransition;
							transitionClasses.push_back(transitionClass);
						}
						//ע��ת����һ�Զ�Ľṹ
						nfaTransitions.insert(transitionClass, nfaTransition);
					}
				}

				// ���������õ�ת����transitionClasses���ǽ������ܻ��Ϊ
				// ĳ��dfa���ıߵĽṹ������key������ȡ�����е�һ����
				for (int j = 0;j < transitionClasses.size();j++)
				{
					// ���һ���߶�Ӧ����Щ��
					const vector<Transition*>& transitionSet = 
											nfaTransitions[transitionClasses[j]];
					// �����Щ��ָ��Ľ�㼯��
					transitionTargets.clear();
					for (int l = 0;l < transitionSet.size();l++)
					{
						State* nfaState = transitionSet[l]->target;
						if (!isElementExist(transitionTargets, nfaState))
						{
							transitionTargets.push_back(nfaState);
						}
					}
					// �ж�ת���������ת����NFAĿ��״̬��ɵļ����Ƿ��Ѿ���һ����Ӧ��DFA״̬
					State* dfaState = 0;
					for (auto it = dfaStateMap.begin();it != dfaStateMap.end();it++)
					{
						// ��DFA�ĵȼ�NFA״̬���Ͻ������򣨲�Ȼ����compare�԰ɣ�
						// ��˵�Ҽǵ��ҵ���Ҳ����ôд�� hh
						// dfaStateMap.CopyValuesToCollection(k, relativeStates);
						relativeStates.clear(); // ��������ˣ�debug��һ��
						for (auto i = 0;i < (*it).second.size();i++)
						{
							relativeStates.push_back((*it).second[i]);
						}
						// �������򣬲��ܱȽ�
						sort(relativeStates.begin(),relativeStates.end());
						sort(transitionTargets.begin(), transitionTargets.end());
						// �Ƚ������Ƿ����
						if (relativeStates.size() == transitionTargets.size())
						{
							bool equal = true;
							for (int l = 0;l < relativeStates.size();l++)
							{
								if (relativeStates[l] != transitionTargets[l])
								{
									equal = false;
									break;
								}
							}
							if (equal)
							{
								dfaState = (*it).first;
								break;
							}
						}
					}
					//���������DFA״̬�򴴽�һ��
					if (!dfaState)
					{
						dfaState = target->NewState();
						// �Ѹոյõ�����Щ���ӽ�ȥ
						for (int k = 0;k < transitionTargets.size();k++)
						{
							dfaStateMap.insert(dfaState, transitionTargets[k]);
							if (transitionTargets[k]->finalState)
							{
								dfaState->finalState = true;
							}
						}
					}
					//����ת�����Ƶ���״̬����
					Transition* transitionClass = transitionClasses[j];
					Transition* newTransition = target->NewTransition(currentState, dfaState);
					newTransition->range = transitionClass->range;
					newTransition->type = transitionClass->type;
				}
			}
			return target;
		}

	}
}