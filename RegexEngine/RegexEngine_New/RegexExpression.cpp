#include "RegexExpression.h"
#include "RegexAutomaton.h"
namespace tl
{
	namespace regex_internal
	{
		Expression::Expression()
		{
		}


		Expression::~Expression()
		{
		}
		bool Expression::IsEqual(Expression::Ref expression)
		{
			// 把类里的this往外面传，你把它转换成shareptr，那它将自行delete(造成delete两次)
			return IsEqualAlgorithm().invoke(this, expression);
		}
		Automaton::Ref Expression::generateEpsilonNfa()
		{
			Automaton::Ref automaton(new Automaton);
			EpsilonNfa result = EpsilonNfaAlgorithm().invoke(this, automaton.get());
			automaton->startState = result.start;
			result.end->finalState = true;
			return automaton;
		}
		bool CharSetExpression::addRangeWithConflict(CharRange range)
		{
			if (range.begin>range.end)
			{
				wchar_t t = range.begin;
				range.begin = range.end;
				range.end = t;
			}
			for (size_t i = 0;i<ranges.size();i++)
			{
				if (!(range<ranges[i] || range>ranges[i]))
				{
					return false;
				}
			}
			ranges.push_back(range);
			return true;
		}
		void CharSetExpression::apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.visit(this);
		}
		void BeginExpression::apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.visit(this);
		}
		void EndExpression::apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.visit(this);
		}
		void LoopExpression::apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.visit(this);
		}
		void SequenceExpression::apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.visit(this);
		}
		void AlternateExpression::apply(IRegexExpressionAlgorithm& algorithm)
		{
			algorithm.visit(this);
		}



	}
}
