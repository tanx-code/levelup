#pragma once
#include "RegexData.h"
#include <memory>
#include <map>
#include "RegexAutomaton.h"

namespace tl
{

	namespace regex_internal
	{
		using namespace std;
		class IRegexExpressionAlgorithm;

		// ������ʽ���﷨�����

		class Expression
		{
		public:
			typedef shared_ptr<Expression> Ref;
			typedef map<wstring, Expression::Ref> Map;
			virtual void apply(IRegexExpressionAlgorithm& algorithm) = 0;
			Expression();
			~Expression();

			// �㷨�ӿ�
			bool IsEqual(Expression::Ref expression);
			Automaton::Ref generateEpsilonNfa();
		};

		class CharSetExpression : public Expression	//a, [a-b], [^a-b0-9], \ //
		{
		public:
			List ranges;
			bool reverse;

			bool addRangeWithConflict(CharRange range);
			void apply(IRegexExpressionAlgorithm& algorithm);
		};

		class BeginExpression : public Expression	// ^
		{
		public:

			void apply(IRegexExpressionAlgorithm& algorithm);
		};

		class EndExpression : public Expression	// $
		{
		public:

			void apply(IRegexExpressionAlgorithm& algorithm);
		};

		class LoopExpression : public Expression	// a{3}, a{3,}, a{1,3}, a+, a*, a?, LOOP?
		{
		public:
			Expression::Ref	expression;	//��ѭ�����ʽ
			int	min;	//����
			int	max;	//���ޣ�-1��������
			bool preferLong;	//��ƥ������

			void apply(IRegexExpressionAlgorithm& algorithm);
		};

		class SequenceExpression : public Expression	//ab
		{
		public:
			Expression::Ref	left;	//����ʽ
			Expression::Ref	right;	//�ұ��ʽ

			void apply(IRegexExpressionAlgorithm& algorithm);
		};

		class AlternateExpression : public Expression	//a|b
		{
		public:
			Expression::Ref	left;	//����ʽ
			Expression::Ref	right;	//�ұ��ʽ

			void apply(IRegexExpressionAlgorithm& algorithm);
		};

		class RegexExpression
		{
		public:
			typedef shared_ptr<RegexExpression>	Ref;

			Expression::Ref	expression;	//�����ʽ
			Expression::Ref	merge()
			{
			};
		};

		// �㷨����, ���Է����Ӧ�õ�parse��ϵı��ʽ��
		// note: ���д��麯������Ϊ������
		class IRegexExpressionAlgorithm
		{
		public:
			virtual void visit(CharSetExpression* expression) = 0;
			virtual void visit(LoopExpression* expression) = 0;
			virtual void visit(SequenceExpression* expression) = 0;
			virtual void visit(AlternateExpression* expression) = 0;
			virtual void visit(BeginExpression* expression) = 0;
			virtual void visit(EndExpression* expression) = 0;
		};
		
		// ���ڱȽ����ɵ�AST����д��AST���㷨
		class IsEqualAlgorithm : public IRegexExpressionAlgorithm
		{
		public:
			void visit(CharSetExpression* expression)
			{
				result = apply(expression, target);
			}
			void visit(BeginExpression* expression)
			{
				result = apply(expression, target);
			}
			void visit(EndExpression* expression)
			{
				result = apply(expression, target);
			}
			void visit(LoopExpression* expression)
			{
				result = apply(expression, target);
			}
			void visit(SequenceExpression* expression)
			{
				result = apply(expression, target);
			}
			void visit(AlternateExpression* expression)
			{
				result = apply(expression, target);
			}
		public:
			// ������������أ��������������
			bool invoke(Expression::Ref exprSource, Expression::Ref exprTarget)
			{
				target = exprTarget;
				if (!target) return false;
				exprSource->apply(*this);
				return result;
			}
			bool invoke(Expression* exprSource, Expression::Ref exprTarget)
			{
				target = exprTarget;
				if (!target) return false;
				exprSource->apply(*this);
				return result;
			}
		private:
			bool result;
			Expression::Ref target;

			bool apply(CharSetExpression* expression, Expression::Ref _target)
			{
				shared_ptr<CharSetExpression> expected = 
								dynamic_pointer_cast<CharSetExpression>(_target);
				if (expected)
				{
					if (expression->reverse != expected->reverse)return false;
					if (expression->ranges.size() != expected->ranges.size())return false;
					for (size_t i = 0;i<expression->ranges.size();i++)
					{
						if (expression->ranges[i] != expected->ranges[i])return false;
					}
					return true;
				}
				return false;
			}
			bool apply(LoopExpression* expression, Expression::Ref _target)
			{
				shared_ptr<LoopExpression> expected = 
								dynamic_pointer_cast<LoopExpression>(_target);
				if (expected)
				{
					if (expression->min != expected->min)return false;
					if (expression->max != expected->max)return false;
					if (expression->preferLong != expected->preferLong)return false;
					if (!invoke(expression->expression, expected->expression))return false;
					return true;
				}
				return false;
			}
			bool apply(SequenceExpression* expression, Expression::Ref _target)
			{
				shared_ptr<SequenceExpression> expected = 
								dynamic_pointer_cast<SequenceExpression>(_target);
				if (expected)
				{
					if (!invoke(expression->left, expected->left))return false;
					if (!invoke(expression->right, expected->right))return false;
					return true;
				}
				return false;
			}
			bool apply(AlternateExpression* expression, Expression::Ref _target)
			{
				shared_ptr<AlternateExpression> expected = 
								dynamic_pointer_cast<AlternateExpression>(_target);
				if (expected)
				{
					if (!invoke(expression->left, expected->left))return false;
					if (!invoke(expression->right, expected->right))return false;
					return true;
				}
				return false;
			}
			bool apply(BeginExpression* expression, Expression::Ref _target)
			{
				shared_ptr<BeginExpression> expected = 
								dynamic_pointer_cast<BeginExpression>(_target);
				if (expected)
				{
					return true;
				}
				return false;
			}
			bool apply(EndExpression* expression, Expression::Ref _target)
			{
				shared_ptr<EndExpression> expected = 
								dynamic_pointer_cast<EndExpression>(_target);
				if (expected)
				{
					return true;
				}
				return false;
			}
		};


		// �������ɴ�Epsilon�ߵ�NFA���㷨
		class EpsilonNfa
		{
		public:
			State* start;
			State* end;
			EpsilonNfa()
			{
				start = 0;
				end = 0;
			}
		};
		class EpsilonNfaAlgorithm : public IRegexExpressionAlgorithm
		{
		private:
			Automaton* target;
			EpsilonNfa result;
		public:
			EpsilonNfa invoke(Expression::Ref expression, Automaton* automaton)
			{
				target = automaton;
				expression->apply(*this);
				return result;
			}
			EpsilonNfa invoke(Expression* expression, Automaton* automaton)
			{
				target = automaton;
				expression->apply(*this);
				return result;
			}
		public:
			// �ҵ���ֱ�Ӹ����Ǹ��㷨��������������д������
			// ��������ab,a|b,a* ��������ʽ��nfa�ķ���
			// ����������Խ���ǰ�����ɵ�AST���ͣ����Լ�Ӧ���������㷨���Ӷ�������Ե�nfaͼ
			EpsilonNfa Connect(EpsilonNfa a, EpsilonNfa b, Automaton* target)
			{
				if (a.start)
				{
					target->NewEpsilon(a.end, b.start);
					a.end = b.end;
					return a;
				}
				else
				{
					return b;
				}
			}
			vector<CharRange> getIntersection(const vector<CharRange>& result, 
											  const CharRange& target)
			{
				vector<CharRange> ret;
				vector<CharRange> vecTarget;
				if (target.begin != 1)
				{
					vecTarget.push_back(CharRange(1, target.begin-1));
				}
				if (target.end != 65535)
				{
					vecTarget.push_back(CharRange(target.end+1, 65535));
				}
				for (auto i : vecTarget)
				{
					for (auto j : result)
					{
						if (!(j.begin > i.end || j.end < i.begin))
						{
							vector<int> vecsort = { i.begin,i.end,j.begin,j.end };
							sort(vecsort.begin(),vecsort.end());
							ret.push_back(CharRange(vecsort[1],vecsort[2]));
						}
					}
				}
				return ret;
			}
			// ����������·�����������������CharRange�Ľ���
			// �����Ӹ���Ǹ��㷨�ã�������ɵĽ��������Ҫ��׼ȷ��
			// ��ʵ������������leetcode��һ���жϾ�������ཻ����Ŀ
			void normalizeCharSet(CharSetExpression* expression)
			{
				vector<CharRange> result;
				result.push_back(CharRange(1, 65535));
				for (auto i = 0;i< expression->ranges.size(); i++)
				{
					result = getIntersection(result, expression->ranges[i]);
				}
				expression->ranges.clear();
				for (auto i : result)
				{
					expression->ranges.push_back(i);
				}
			}
			EpsilonNfa apply(CharSetExpression* expression)
			{
				EpsilonNfa nfa;
				nfa.start = target->NewState();
				nfa.end = target->NewState();
				if (expression->reverse)
				{
					// �ѱ��Ϊ�����ַ������������һ��С�����͸㶨��
					normalizeCharSet(expression);
				}
				for (int i = 0;i < expression->ranges.size();i++)
				{
					target->NewChars(nfa.start, nfa.end, expression->ranges[i]);
				}
				return nfa;
			}
			EpsilonNfa apply(BeginExpression* expression)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				target->NewBeginString(result.start, result.end);
				return result;
			}
			EpsilonNfa apply(EndExpression* expression)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				target->NewEndString(result.start, result.end);
				return result;
			}
			EpsilonNfa apply(LoopExpression* expression)
			{
				EpsilonNfa head;
				for (int i = 0;i<expression->min;i++)
				{
					EpsilonNfa body = invoke(expression->expression, target);
					head = Connect(head, body, target);
				}
				if (expression->max == -1)
				{
					EpsilonNfa body = invoke(expression->expression, target);
					if (!head.start)
					{
						head.start = head.end = target->NewState();
					}
					State* loopBegin = head.end;
					State* loopEnd = target->NewState();
					if (expression->preferLong)
					{
						target->NewEpsilon(loopBegin, body.start);
						target->NewEpsilon(body.end, loopBegin);
						target->NewNop(loopBegin, loopEnd);
					}
					else
					{
						target->NewNop(loopBegin, loopEnd);
						target->NewEpsilon(loopBegin, body.start);
						target->NewEpsilon(body.end, loopBegin);
					}
					head.end = loopEnd;
				}
				else if (expression->max>expression->min)
				{
					for (int i = expression->min;i<expression->max;i++)
					{
						EpsilonNfa body = invoke(expression->expression, target);
						State* start = target->NewState();
						State* end = target->NewState();
						if (expression->preferLong)
						{
							target->NewEpsilon(start, body.start);
							target->NewEpsilon(body.end, end);
							target->NewNop(start, end);
						}
						else
						{
							target->NewNop(start, end);
							target->NewEpsilon(start, body.start);
							target->NewEpsilon(body.end, end);
						}
						body.start = start;
						body.end = end;
						head = Connect(head, body, target);
					}
				}
				return head;
			}
			EpsilonNfa apply(SequenceExpression* expression)
			{
				EpsilonNfa a = invoke(expression->left, target);
				EpsilonNfa b = invoke(expression->right, target);
				return Connect(a, b, target);
			}
			EpsilonNfa apply(AlternateExpression* expression)
			{
				EpsilonNfa result;
				result.start = target->NewState();
				result.end = target->NewState();
				EpsilonNfa a = invoke(expression->left, target);
				EpsilonNfa b = invoke(expression->right, target);
				target->NewEpsilon(result.start, a.start);
				target->NewEpsilon(a.end, result.end);
				target->NewEpsilon(result.start, b.start);
				target->NewEpsilon(b.end, result.end);
				return result;
			}

			void visit(CharSetExpression* expression)
			{
				result = apply(expression);
			}
			void visit(BeginExpression* expression)
			{
				result = apply(expression);
			}
			void visit(EndExpression* expression)
			{
				result = apply(expression);
			}
			void visit(LoopExpression* expression)
			{
				result = apply(expression);
			}
			void visit(SequenceExpression* expression)
			{
				result = apply(expression);
			}
			void visit(AlternateExpression* expression)
			{
				result = apply(expression);
			}
		};

		//// �Ҿ�Ӧ�������㷨������û��ģ���ˡ�
		//// ���Ӹ���㷨�����ģ��
		//// ����ģ�棬ʹ���㷨���Է��ز�ͬ���͵�ֵ
		//// pΪ��Ҫ���صĲ�ȷ�����͵�ĳ�ֲ�����
		//// ֻ��Ҫ�򵥵�ִ��invoke(expression, p)�Ϳ��Ե��õ��Լ�
		//template<typename ReturnType, typename ParameterType = void*>
		//class RegexExpressionAlgorithm : public IRegexExpressionAlgorithm
		//{
		//private:
		//	ReturnType returnValue;
		//	ParameterType* parameterValue;
		//public:
		//	ReturnType Invoke(Expression::Ref expression, ParameterType parameter)
		//	{
		//		parameterValue = &parameter;
		//		expression->Apply(*this);
		//		return returnValue;
		//	}
		//};
		//// �������������㷨�Ĳ�����������Ϊvoid��ʱ��
		//template<typename ParameterType>
		//class RegexExpressionAlgorithm<void, ParameterType> : public IRegexExpressionAlgorithm
		//{
		//};


	
		// �����﷨���ĺ���
		extern shared_ptr<LoopExpression> ParseLoop(const wchar_t*& input);
		extern shared_ptr<Expression>  ParseCharSet(const wchar_t*& input);
		extern shared_ptr<Expression> ParseFunction(const wchar_t*& input);
		extern shared_ptr<Expression> ParseUnit(const wchar_t*& input);
		extern shared_ptr<Expression> ParseJoin(const wchar_t*& input);
		extern shared_ptr<Expression> ParseAlt(const wchar_t*& input);
		extern shared_ptr<Expression> ParseExpression(const wchar_t*& input);
		extern RegexExpression::Ref	ParseRegexExpression(const wstring& code);
	}
}