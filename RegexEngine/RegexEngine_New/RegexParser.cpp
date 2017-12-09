#include "RegexExpression.h"
#include <memory>
#include <algorithm>
#include "Exception.h"
namespace tl
{
	namespace regex_internal
	{
		using namespace std;

		// 识别字符串的辅助函数

		//判断是否等于字符c
		bool IsEqChar(const wchar_t*& input, wchar_t c)
		{
			if (*input == c)
			{
				input++;
				return true;
			}
			return false;
		}
		//判断是否等于字符数组chars中的一个字符
		bool IsEqChars(const wchar_t*& input, wchar_t* chars, wchar_t& c)
		{
			const wchar_t* position = ::wcschr(chars, *input);
			if (position)
			{
				c = *input++;
				return true;
			}
			else
			{
				return false;
			}
		}
		bool IsEqChars(const wchar_t*& input, wchar_t* chars)
		{
			wchar_t c;
			return IsEqChars(input, chars, c);
		}
		bool IsPositiveInteger(const wchar_t*& input, int &num)
		{
			bool readed = false;
			num = 0;
			while (L'0'<=*input && *input<=L'9')
			{
				num = num * 10 + (*input++) - L'0';
				readed = true;
			}
			return readed;
		}


		// 生成语法树的函数

		
		//分析循环 * + ? {a} {a,} {a,b}
		shared_ptr<LoopExpression> ParseLoop(const wchar_t*& input)
		{
			int min = 0 , max = 0;
			shared_ptr<LoopExpression> expression = shared_ptr<LoopExpression>(new
																			   LoopExpression);
			if (!*input)
			{
				return 0;
			}
			if (IsEqChar(input, L'*'))	// 0 - infinite
			{
				min = 0;
				max = -1;
			}
			else if (IsEqChar(input, L'?')) // 0 - 1
			{
				min = 0;
				max = 1;
			}
			else if (IsEqChar(input, L'+'))	// 1 - infinite
			{
				min = 1;
				max = -1;
			}
			else if (IsEqChar(input, L'{'))	// {3},{1,3},{1,-1}
			{
				if (IsPositiveInteger(input, min))
				{
					if (IsEqChar(input, L','))
					{
						if (!IsPositiveInteger(input, max))
						{
							max = -1;
						}
					}
					else
					{
						max = min;
					}
					if (!IsEqChar(input, L'}'))
					{
						goto THROW_EXCEPTION;
					}
				}
				else
				{
					goto THROW_EXCEPTION;
				}
			}
			else
			{
				return 0;
			}
			
			expression->min = min;
			expression->max = max;
			expression->preferLong = !IsEqChar(input,L'?'); //*? 的意思是尽量读少的，懒惰。
			return expression;
		THROW_EXCEPTION:
			throw tl::ArgumentException(L"正则表达式语法错误，循环格式不合法。"
										, L"tl::regex_internal::ParseLoop"
										, L"input");
		}
		shared_ptr<Expression> ParseCharSet(const wchar_t*&  input)
		{
			if (!*input)
			{
				return 0;
			}
			else if (IsEqChar(input, L'^'))
			{
				return shared_ptr<Expression>(new BeginExpression);
			}
			else if (IsEqChar(input, L'$'))
			{
				return shared_ptr<Expression>(new EndExpression);
			}
			else if (IsEqChar(input, L'\\') || IsEqChar(input, L'/'))	//转义字符规则定义
			{
				shared_ptr<CharSetExpression> expression = shared_ptr<CharSetExpression>
					(new CharSetExpression);
				expression->reverse = false;
				switch (*input)
				{
				case L'.':	//所有字符
					expression->ranges.push_back(CharRange(1, 65535));
					break;
				case L'r':
					expression->ranges.push_back(CharRange(L'\r', L'\r'));
					break;
				case L'n':
					expression->ranges.push_back(CharRange(L'\n', L'\n'));
					break;
				case L't':
					expression->ranges.push_back(CharRange(L'\t', L'\t'));
					break;
				case L'\\':case L'/':case L'(':case L')':case L'+':case L'*':
				case L'?':case L'|':case L'{':case L'}':case L'[':case L']':
				case L'<':case L'>':case L'^':case L'$':case L'!':case L'=':
					expression->ranges.push_back(CharRange(*input, *input));
					break;
				case L'S':
					expression->reverse = true;
				case L's':
					expression->ranges.push_back(CharRange(L' ', L' '));
					expression->ranges.push_back(CharRange(L'\r', L'\r'));
					expression->ranges.push_back(CharRange(L'\n', L'\n'));
					expression->ranges.push_back(CharRange(L'\t', L'\t'));
					break;
				case L'D':
					expression->reverse = true;
				case L'd':
					expression->ranges.push_back(CharRange(L'0', L'9'));
					break;
				case L'L':
					expression->reverse = true;
				case L'l':
					expression->ranges.push_back(CharRange(L'_', L'_'));
					expression->ranges.push_back(CharRange(L'A', L'Z'));
					expression->ranges.push_back(CharRange(L'a', L'z'));
					break;
				case L'W':
					expression->reverse = true;
				case L'w':
					expression->ranges.push_back(CharRange(L'_', L'_'));
					expression->ranges.push_back(CharRange(L'0', L'9'));
					expression->ranges.push_back(CharRange(L'A', L'Z'));
					expression->ranges.push_back(CharRange(L'a', L'z'));
					break;
				default:
					throw ArgumentException(L"正则表达式语法错误：非法转义符。", 
											L"vl::regex_internal::ParseCharSet", L"input");
				}
				input++;
				return expression;
			}
			else if (IsEqChar(input, L'['))	// case like [a-z] 
			{
				shared_ptr<CharSetExpression> expression = shared_ptr<CharSetExpression>
					(new CharSetExpression);
				if (IsEqChar(input, L'^'))
				{
					expression->reverse = true;
				}
				else
				{
					expression->reverse = false;
				}
				bool midState = false;
				wchar_t a = L'\0';
				wchar_t b = L'\0';
				while (true)
				{
					if (IsEqChar(input, L'\\') || IsEqChar(input, L'/'))
					{
						wchar_t c = L'\0';
						switch (*input)
						{
						case L'r':
							c = L'\r';
							break;
						case L'n':
							c = L'\n';
							break;
						case L't':
							c = L'\t';
							break;
						case L'-':case L'[':case L']':case L'\\':
						case L'/':case L'^':case L'$':
							c = *input;
							break;
						default:
							throw ArgumentException(L"正则表达式语法错误：在[]内部能使用的转义符"
													"只有\"rnt-[]\\/\"。", 
													L"vl::regex_internal::ParseCharSet", 
													L"input");
						}
						input++;
						midState ? b = c : a = c;
						midState = !midState;
					}
					else if (IsEqChars(input, L"-]"))
					{
						goto THROW_EXCEPTION;
					}
					else if (*input)
					{
						midState ? b = *input++ : a = *input++;
						midState = !midState;
					}
					else
					{
						goto THROW_EXCEPTION;
					}

					if (IsEqChar(input, L']'))
					{
						if (midState)
						{
							b = a;
						}
						if (!expression->addRangeWithConflict(CharRange(a, b)))
						{
							goto THROW_EXCEPTION;
						}
						break;
					}
					else if (IsEqChar(input, L'-'))
					{
						if (!midState)
						{
							goto THROW_EXCEPTION;
						}
					}
					else
					{
						// midState 其实是用来判断一个小单元是否已经结束，以便把它们不断存起来
						if (midState)	// 为true表示当前字符集合已经接收完了
						{
							b = a;
						}
						if (expression->addRangeWithConflict(CharRange(a, b)))	// 解决逆向问题
						{
							midState = false;
						}
						else
						{
							goto THROW_EXCEPTION;
						}
					}
				}
				return expression;
			THROW_EXCEPTION:
				throw ArgumentException(L"正则表达式语法错误：字符集格式不合法。"
										, L""
										, L"");
			}
			else if (IsEqChars(input, L"()+*?{}|"))
			{
				input--;
				return 0;
			}
			else
			{
				shared_ptr<CharSetExpression> expression = shared_ptr<CharSetExpression>
															(new CharSetExpression);
				expression->reverse = false;
				expression->ranges.push_back(CharRange(*input, *input));
				input++;
				return expression;
			}
		}
		shared_ptr<Expression> ParseFunction(const wchar_t*& input)	//分析高级功能的函数
		{
			if (IsEqChar(input, L'('))
			{
				shared_ptr<Expression> sub = ParseExpression(input);
				if (!IsEqChar(input, L')'))
				{
					goto NEED_RIGHT_BRACKET;
				}
				return sub;
			}
			else
			{
				return 0;
			}
		NEED_RIGHT_BRACKET:
			throw ArgumentException(L"正则表达式语法错误：缺少右小括号\")\"。", 
									L"vl::regex_internal::ParseFunction", L"input");
		}
		
		// expr
		shared_ptr<Expression> ParseUnit(const wchar_t*& input)
		{
			shared_ptr<Expression> unit = ParseCharSet(input);
			if (!unit)
			{
				unit = ParseFunction(input);
			}
			if (!unit)
			{
				return 0;
			}
			shared_ptr<LoopExpression> loop;
			while (loop = ParseLoop(input))
			{
				loop->expression = unit;
				unit = loop;
			}
			return unit;
		}
		// expr1 expr2
		shared_ptr<Expression> ParseJoin(const wchar_t*& input)
		{
			shared_ptr<Expression> expression = ParseUnit(input);
			while (true)
			{
				shared_ptr<Expression> right = ParseUnit(input); // 循环parse完所有的join expr
				if (right)
				{
					shared_ptr<SequenceExpression> sequence = (shared_ptr<SequenceExpression>)
						new SequenceExpression;
					sequence->left = expression;
					sequence->right = right;
					expression = sequence;
				}
				else
				{
					break;
				}
			}
			return expression;
		}
		// expr1 | expr2
		shared_ptr<Expression> ParseAlt(const wchar_t*& input)
		{
			shared_ptr<Expression> expression = ParseJoin(input);
			while (true)
			{
				if (IsEqChar(input, L'|'))
				{
					shared_ptr<Expression> right = ParseJoin(input);
					if (right)
					{
						shared_ptr<AlternateExpression> alternate = (shared_ptr<AlternateExpression>)new AlternateExpression;
						alternate->left = expression;
						alternate->right = right;
						expression = alternate;
					}
					else
					{
						throw ArgumentException(L"Regular expression syntax error:"
												"Expression expected.", 
												L"vl::regex_internal::ParseAlt", L"input");
					}
				}
				else
				{
					break;
				}
			}
			return expression;

		}
		shared_ptr<Expression> ParseExpression(const wchar_t*& input)
		{
			return ParseAlt(input);
		}

		RegexExpression::Ref ParseRegexExpression(const wstring& code)
		{
			RegexExpression::Ref regex = (RegexExpression::Ref)new RegexExpression;
			const wchar_t* start = code.c_str();
			const wchar_t* input = start;
			try
			{
				regex->expression = ParseExpression(input);
				if (!regex->expression)
				{
					throw ArgumentException(L"Regular expression syntax error: "
											"Expression expected.", 
											L"tl::regex_internal::ParseUnit", L"input");
				}
				if (*input) // if all good, *input will equal to \0
				{
					throw ArgumentException(L"Regular expression syntax error: "
											"Found unnecessary tokens.", 
											L"tl::regex_internal::ParseUnit", L"input");
				}
				return regex;
			}
			catch (const ArgumentException& e)
			{
				throw ParsingException(e.GetMessage(), code, input - start);
			}
		}
	
	}
}
