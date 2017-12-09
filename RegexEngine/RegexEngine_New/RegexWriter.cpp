#include "RegexWriter.h"


namespace tl
{
	namespace regex
	{

		using namespace tl::regex_internal;

		/***********************************************************************
		RegexNode
		***********************************************************************/

		RegexNode::RegexNode(tl::regex_internal::Expression::Ref _expression)
			:expression(_expression)
		{
		}

		RegexNode RegexNode::Some()const
		{
			return Loop(1, -1);
		}

		RegexNode RegexNode::Any()const
		{
			return Loop(0, -1);
		}

		RegexNode RegexNode::Opt()const
		{
			return Loop(0, 1);
		}

		RegexNode RegexNode::Loop(int min, int max)const
		{
			shared_ptr<LoopExpression> target = 
							(shared_ptr<LoopExpression>)new LoopExpression;
			target->min = min;
			target->max = max;
			target->preferLong = true;
			target->expression = expression;
			return RegexNode(target);
		}

		RegexNode RegexNode::AtLeast(int min)const
		{
			return Loop(min, -1);
		}

		RegexNode RegexNode::operator+(const RegexNode& node)const
		{
			shared_ptr<SequenceExpression> target = 
							(shared_ptr<SequenceExpression>) new SequenceExpression;
			target->left = expression;
			target->right = node.expression;
			return RegexNode(target);
		}

		// merge two *charset* expr ,only charset
		RegexNode RegexNode::operator%(const RegexNode& node)const
		{
			// 好奇怪，我居然在const函数里修改了它的成员
			shared_ptr<CharSetExpression> e = 
							dynamic_pointer_cast<CharSetExpression>(node.expression);
			shared_ptr<CharSetExpression> ret = 
							dynamic_pointer_cast<CharSetExpression>(expression);
			for (size_t i = 0;i < e->ranges.size(); i++)
			{
				ret->ranges.push_back(e->ranges[i]);
			}
			return *this;
		}
		// change it's reverse value
		RegexNode RegexNode::operator!() const
		{
			shared_ptr<CharSetExpression> ret = 
							dynamic_pointer_cast<CharSetExpression>(expression);
			ret->reverse = !ret->reverse;
			return *this;
		}
		RegexNode RegexNode::operator|(const RegexNode& node)const
		{
			shared_ptr<AlternateExpression> target =
							(shared_ptr<AlternateExpression>) new AlternateExpression;
			target->left = expression;
			target->right = node.expression;
			return RegexNode(target);
		}


		RegexNode rBegin()
		{
			return RegexNode((shared_ptr<BeginExpression>)new BeginExpression);
		}

		RegexNode rEnd()
		{
			return RegexNode((shared_ptr<EndExpression>)new EndExpression);
		}

		// 声明有默认参数，定义居然就可以不用默认参数了，为什么不要对应啊
		RegexNode rC(wchar_t a, wchar_t b)
		{
			if (!b)b = a;
			shared_ptr<CharSetExpression> target = 
							shared_ptr<CharSetExpression>(new CharSetExpression);
			target->reverse = false;
			target->addRangeWithConflict(CharRange(a, b));
			return RegexNode(target);
		}

		RegexNode r_d()
		{
			return rC(L'0', L'9');
		}

		RegexNode r_l()
		{
			shared_ptr<CharSetExpression> target = 
							(shared_ptr<CharSetExpression>) new CharSetExpression;
			target->reverse = false;
			target->addRangeWithConflict(CharRange(L'_', L'_'));
			target->addRangeWithConflict(CharRange(L'A', L'Z'));
			target->addRangeWithConflict(CharRange(L'a', L'z'));
			return target;
		}

		RegexNode r_w()
		{
			shared_ptr<CharSetExpression> target = 
							(shared_ptr<CharSetExpression>) new CharSetExpression;
			target->reverse = false;
			target->addRangeWithConflict(CharRange(L'_', L'_'));
			target->addRangeWithConflict(CharRange(L'0', L'9'));
			target->addRangeWithConflict(CharRange(L'A', L'Z'));
			target->addRangeWithConflict(CharRange(L'a', L'z'));
			return target;
		}

		RegexNode rAnyChar()
		{
			return rC(1, 65535);
		}
	}
}
