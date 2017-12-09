#include "RegexExpression.h"
#include <memory>
#include <algorithm>
#include "Exception.h"
namespace tl
{
	namespace regex_internal
	{
		using namespace std;

		// ʶ���ַ����ĸ�������

		//�ж��Ƿ�����ַ�c
		bool IsEqChar(const wchar_t*& input, wchar_t c)
		{
			if (*input == c)
			{
				input++;
				return true;
			}
			return false;
		}
		//�ж��Ƿ�����ַ�����chars�е�һ���ַ�
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


		// �����﷨���ĺ���

		
		//����ѭ�� * + ? {a} {a,} {a,b}
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
			expression->preferLong = !IsEqChar(input,L'?'); //*? ����˼�Ǿ������ٵģ����衣
			return expression;
		THROW_EXCEPTION:
			throw tl::ArgumentException(L"������ʽ�﷨����ѭ����ʽ���Ϸ���"
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
			else if (IsEqChar(input, L'\\') || IsEqChar(input, L'/'))	//ת���ַ�������
			{
				shared_ptr<CharSetExpression> expression = shared_ptr<CharSetExpression>
					(new CharSetExpression);
				expression->reverse = false;
				switch (*input)
				{
				case L'.':	//�����ַ�
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
					throw ArgumentException(L"������ʽ�﷨���󣺷Ƿ�ת�����", 
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
							throw ArgumentException(L"������ʽ�﷨������[]�ڲ���ʹ�õ�ת���"
													"ֻ��\"rnt-[]\\/\"��", 
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
						// midState ��ʵ�������ж�һ��С��Ԫ�Ƿ��Ѿ��������Ա�����ǲ��ϴ�����
						if (midState)	// Ϊtrue��ʾ��ǰ�ַ������Ѿ���������
						{
							b = a;
						}
						if (expression->addRangeWithConflict(CharRange(a, b)))	// �����������
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
				throw ArgumentException(L"������ʽ�﷨�����ַ�����ʽ���Ϸ���"
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
		shared_ptr<Expression> ParseFunction(const wchar_t*& input)	//�����߼����ܵĺ���
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
			throw ArgumentException(L"������ʽ�﷨����ȱ����С����\")\"��", 
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
				shared_ptr<Expression> right = ParseUnit(input); // ѭ��parse�����е�join expr
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
