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

		// 辅助函数
		static bool isElementExist(const vector<State*>& v, const State* e)
		{
			for (auto i : v)
			{
				if (i == e)
					return true;
			}
			return false;
		}
		// 求e边闭包
		static void CollectEpsilon(State* targetState, State* sourceState, bool(*epsilonChecker)
								   (Transition*), vector<State*>& epsilonStates, 
								   vector<Transition*>& transitions)
		{
			if (!isElementExist(epsilonStates, sourceState))
			{
				epsilonStates.push_back(sourceState);// 一开始是添加自己进去
				for (int i = 0;i<sourceState->transitions.size();i++)// 遍历这个结点的边
				{
					Transition* transition = sourceState->transitions[i];
					if (epsilonChecker(transition)) // 判断是否为epsilon边
					{
						// 如果epsilonStates里没有这个结点，就把这个边指向的结点加进去
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
						transitions.push_back(transition);// 如果是字符边，就把自己加进去
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

		// 去Epsilon边的算法。
		Automaton::Ref EpsilonNfaToNfa(Automaton::Ref source, 
									   bool(*epsilonChecker)(Transition *), 
									   map<State*, State*>& nfaStateMap)
		{
			Automaton::Ref target = shared_ptr<Automaton>(new Automaton);
			map<State*, State*> stateMap;	//source->target
			vector<State*> epsilonStates;	//每次迭代当前状态的epsilon闭包
			vector<Transition*> transitions;//每次迭代当前状态的epsilon闭包的转换集合

			// target 一开始是空的。
			stateMap.emplace(source->startState, target->NewState());
			// target里新建一个结点，对应source里的开始结点
			nfaStateMap.emplace(stateMap[source->startState], source->startState);
			// 跟stateMap是反着的
			target->startState = target->states[0].get();// 这个把刚刚建的结点命名赋给开始结点


			// 一开始只有一个开始结点。
			// 每次只要考虑一个结点的闭包。
			for (int i = 0;i < target->states.size();i++)
			{
				//清空epsilonStates并包含自己
				State* targetState = target->states[i].get();
				State* sourceState = nfaStateMap[targetState];
				if (sourceState->finalState)
				{
					targetState->finalState = true;
				}
				// 每次迭代，清空。来存epsilon边的闭包
				epsilonStates.clear();// 找出来的epsilon状态的结合
				transitions.clear(); // 当前结点的边的集合

				// 对所有产生的epsilonStates进行遍历，计算出该状态的一次epsilon直接目标加进去，
				// 并继续迭代
				CollectEpsilon(targetState, sourceState, epsilonChecker, epsilonStates, transitions);

				//遍历所有epsilon闭包转换
				for (int j = 0;j < transitions.size();j++)
				{
					Transition* transition = transitions[j];
					// 当发现找到的这个结点，不在stateMap里的时候。
					// 就把这个结点，加到stateMap里面去。
					// 然后，状态机里也新建一个结点，下次循环要用的，但是这个结点的信息是空的
					// 其实每次迭代的当前结点，信息都是空的
					// 寻找到一个非epsilon闭包的时候更新映射
					if (stateMap.find(transition->target)==stateMap.end())
					{
						stateMap.emplace(transition->target, target->NewState());
						nfaStateMap.emplace(stateMap[transition->target], transition->target);
					}
					//将该转换复制到新状态机里
					Transition* newTransition = target->NewTransition(targetState, stateMap
																	  [transition->target]);
					// 从当前结点指向，找到的带字符边的结点

					// 下面就是把边的剩余的信息都复制过去
					newTransition->range = transition->range;
					newTransition->type = transition->type;

					// 一次迭代，完成的工作有，找出当前结点的非epsilon闭包
					// 新建对应的空的结点，建立它们和空结点的映射，并把空的
					// 结点加到新的状态机里的States集合里，下次迭代要用的时候，
					// 就可以用映射关系取出来
				}
			}
			return target;
		}

		// 阅读开源代码，你首先得知道代码里面的关键算法（实现的目标）
		// 比如你已经知道nfa转dfa的算法，你就知道这里的过程，只是在模拟这个算法
		// 这时候再去看细节，就变得更主动了
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
			vector<Transition*> transitionClasses;//保证转换先后顺序不被nfaTransitions.Keys破坏

			State* startState = target->NewState();
			target->startState = startState;
			dfaStateMap.insert(startState, source->startState);

			vector<State*> transitionTargets;
			vector<State*> relativeStates;


			for (int i = 0;i < target->states.size();i++)
			{
				// dfa中的待处理的结点
				State* currentState = target->states[i].get();
				nfaTransitions.clear();
				transitionClasses.clear();

				// 获得dfa结点对应的nfa的那个结点
				// 对该DFA状态的所有等价NFA状态进行遍历
				vector<State*> &nfaStates = dfaStateMap[currentState];
				for (int j = 0;j < nfaStates.size();j++)
				{
					State* nfaState = nfaStates[j];
					//对每一个NFA状态的所有转换进行遍历
					for (int k = 0;k < nfaState->transitions.size();k++)
					{
						Transition* nfaTransition = nfaState->transitions[k];
						//检查该NFA转换类型是否已经具有已经被记录
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
						//不存在则创建一个转换类型
						if (transitionClass == 0)
						{
							transitionClass = nfaTransition;
							transitionClasses.push_back(transitionClass);
						}
						//注册转换，一对多的结构
						nfaTransitions.insert(transitionClass, nfaTransition);
					}
				}

				// 遍历上面获得的转换，transitionClasses就是将来可能会成为
				// 某个dfa结点的边的结构，它的key是任意取的其中的一条边
				for (int j = 0;j < transitionClasses.size();j++)
				{
					// 获得一条边对应的那些边
					const vector<Transition*>& transitionSet = 
											nfaTransitions[transitionClasses[j]];
					// 获得那些边指向的结点集合
					transitionTargets.clear();
					for (int l = 0;l < transitionSet.size();l++)
					{
						State* nfaState = transitionSet[l]->target;
						if (!isElementExist(transitionTargets, nfaState))
						{
							transitionTargets.push_back(nfaState);
						}
					}
					// 判断转换类的所有转换的NFA目标状态组成的集合是否已经有一个对应的DFA状态
					State* dfaState = 0;
					for (auto it = dfaStateMap.begin();it != dfaStateMap.end();it++)
					{
						// 将DFA的等价NFA状态集合进行排序（不然不能compare对吧）
						// 话说我记得我当初也是这么写的 hh
						// dfaStateMap.CopyValuesToCollection(k, relativeStates);
						relativeStates.clear(); // 忘记清空了，debug了一年
						for (auto i = 0;i < (*it).second.size();i++)
						{
							relativeStates.push_back((*it).second[i]);
						}
						// 先排下序，才能比较
						sort(relativeStates.begin(),relativeStates.end());
						sort(transitionTargets.begin(), transitionTargets.end());
						// 比较两者是否相等
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
					//不存在这个DFA状态则创建一个
					if (!dfaState)
					{
						dfaState = target->NewState();
						// 把刚刚得到的那些结点加进去
						for (int k = 0;k < transitionTargets.size();k++)
						{
							dfaStateMap.insert(dfaState, transitionTargets[k]);
							if (transitionTargets[k]->finalState)
							{
								dfaState->finalState = true;
							}
						}
					}
					//将该转换复制到新状态机里
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