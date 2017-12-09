#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTestAssert.h>

#include "../RegexExpression.h"
#include "../RegexAutomaton.h"
#include "../RegexData.h"
#include "../RegexWriter.h"
#include "../Regex.h"
#include "../RegexInterpretor.h"
#include <cstdio>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace tl;
using namespace tl::regex;
using namespace tl::regex_internal;


namespace UnitTest
{		
	TEST_CLASS(TestPureRegex)
	{
	public:
		// compare two AST
		bool cmpA(const wstring& input, RegexNode  node)
		{
			RegexExpression::Ref exp = ParseRegexExpression(input);
			return (exp->expression)->IsEqual(node.expression);
		}
		TEST_METHOD(TestCharSet)
		{
			Assert::AreEqual(true, cmpA(L"a", rC(L'a')));
			Assert::AreEqual(true, cmpA(L"arctanx", rC(L'a')+ rC(L'r')+ rC(L'c')+ rC(L't')+ rC(L'a')+ rC(L'n')+ rC(L'x')));

			Assert::AreEqual(true, cmpA(L"/d", r_d()));
			Assert::AreEqual(true, cmpA(L"/l", r_l()));
			Assert::AreEqual(true, cmpA(L"/w", r_w()));
			Assert::AreEqual(true, cmpA(L"/D", !r_d()));
			Assert::AreEqual(true, cmpA(L"/L", !r_l()));
			Assert::AreEqual(true, cmpA(L"/W", !r_w()));
			Assert::AreEqual(true, cmpA(L"/r", rC(L'\r')));
			Assert::AreEqual(true, cmpA(L"/n", rC(L'\n')));
			Assert::AreEqual(true, cmpA(L"/t", rC(L'\t')));

			Assert::AreEqual(true, cmpA(L"\\d", r_d()));
			Assert::AreEqual(true, cmpA(L"\\l", r_l()));
			Assert::AreEqual(true, cmpA(L"\\w", r_w()));
			Assert::AreEqual(true, cmpA(L"\\D", !r_d()));
			Assert::AreEqual(true, cmpA(L"\\L", !r_l()));
			Assert::AreEqual(true, cmpA(L"\\W", !r_w()));
			Assert::AreEqual(true, cmpA(L"\\r", rC(L'\r')));
			Assert::AreEqual(true, cmpA(L"\\n", rC(L'\n')));
			Assert::AreEqual(true, cmpA(L"\\t", rC(L'\t')));


			Assert::AreEqual(true, cmpA(L"^", rBegin()));
			Assert::AreEqual(true, cmpA(L"$", rEnd()));
			Assert::AreEqual(true, cmpA(L"[a]", rC(L'a')));
			Assert::AreEqual(true, cmpA(L"[abc]", rC(L'a')%rC(L'b')%rC(L'c')));
			Assert::AreEqual(true, cmpA(L"[0-9]", r_d()));
			Assert::AreEqual(true, cmpA(L"[a-zA-Z_]", r_l()));
			Assert::AreEqual(true, cmpA(L"[a-zA-Z0-9_]", r_w()));
			Assert::AreEqual(true, cmpA(L"[^0-9]", !r_d()));
			Assert::AreEqual(true, cmpA(L"[^a-zA-Z_]", !r_l()));
			Assert::AreEqual(true, cmpA(L"[^a-zA-Z0-9_]", !r_w()));
			Assert::AreEqual(true, cmpA(L"[^abc]", !((rC(L'a') % rC(L'b') % rC(L'c')))));
			Assert::AreEqual(true, cmpA(L"\\\\\"", rC(L'\\') + rC(L'"')));
			Assert::AreEqual(true, cmpA(L"[^\\\\\"]", (!(rC(L'\\') % rC(L'\"')))));
		}

		TEST_METHOD(TestLoop)
		{
			Assert::AreEqual(true, cmpA(L"/d+", r_d().Some()));
			Assert::AreEqual(true, cmpA(L"/d*", r_d().Any()));
			Assert::AreEqual(true, cmpA(L"/d?", r_d().Opt()));
			Assert::AreEqual(true, cmpA(L"/d{3}", r_d().Loop(3, 3)));
			Assert::AreEqual(true, cmpA(L"/d{3,5}", r_d().Loop(3, 5)));
			Assert::AreEqual(true, cmpA(L"/d{4,}", r_d().AtLeast(4)));

			Assert::AreEqual(true, cmpA(L"\\d+", r_d().Some()));
			Assert::AreEqual(true, cmpA(L"\\d*", r_d().Any()));
			Assert::AreEqual(true, cmpA(L"\\d?", r_d().Opt()));
			Assert::AreEqual(true, cmpA(L"\\d{3}", r_d().Loop(3, 3)));
			Assert::AreEqual(true, cmpA(L"\\d{3,5}", r_d().Loop(3, 5)));
			Assert::AreEqual(true, cmpA(L"\\d{4,}", r_d().AtLeast(4)));
		}

		TEST_METHOD(TestComplex)
		{
			Assert::AreEqual(true, cmpA(L"a+(bc)*", rC(L'a').Some() + (rC(L'b') + rC(L'c')).Any()));
			Assert::AreEqual(true, cmpA(L"(1+2)*(3+4)", (rC(L'1').Some() + rC(L'2')).Any() + (rC(L'3').Some() + rC(L'4'))));
			Assert::AreEqual(true, cmpA(L"[a-zA-Z_][a-zA-Z0-9_]*", r_l() + r_w().Any()));
			Assert::AreEqual(true, cmpA(L"ab|ac", (rC(L'a') + rC(L'b')) | (rC(L'a') + rC(L'c'))));
			Assert::AreEqual(true, cmpA(L"a(b|c)", rC(L'a') + (rC(L'b') | rC(L'c'))));
			Assert::AreEqual(true, cmpA(L"/.*[/r/n/t]", rAnyChar().Any() + (rC(L'\r') % rC(L'\n') % rC(L'\t'))));
			Assert::AreEqual(true, cmpA(L"\\.*[\\r\\n\\t]", rAnyChar().Any() + (rC(L'\r') % rC(L'\n') % rC(L'\t'))));
			Assert::AreEqual(true, cmpA(L"\"([^\\\\\"]|\\\\\\.)*\"", 
							 rC(L'\"')+
							 ( (!(rC(L'\\')% rC(L'\"'))) | 
								(rC(L'\\')+ rAnyChar())
									).Any()+
										rC(L'\"')));
		}
		

		class FileWriter
		{
		public:
			FileWriter(const wstring& ws): filename(ws)
			{
				// 以读/写方式打开或建立一个文本文件，允许读写。
				if ((fileHandle = _wfopen(filename.c_str(), L"wt+,ccs=UTF-8")) == NULL) // C4996
				{
					wprintf(L"_wfopen failed!\n");
					exit(0);
				}
			}
			~FileWriter()
			{
				if (fclose(fileHandle))
				{
					wprintf(L"fclose failed!\n");
				}
			}
			void WriteString(const wstring& s)
			{
				wcscpy_s(str, sizeof(str) / sizeof(wchar_t), s.c_str());
				strSize = wcslen(str);
				if (fwrite(str, sizeof(wchar_t), strSize, fileHandle) != strSize)
				{
					wprintf(L"fwrite failed!\n");
				}
			}
			void WriteLine(const wstring& s)
			{
				wcscpy_s(str, sizeof(str) / sizeof(wchar_t), (s+L"\n").c_str());
				strSize = wcslen(str);
				if (fwrite(str, sizeof(wchar_t), strSize, fileHandle) != strSize)
				{
					wprintf(L"fwrite failed!\n");
				}
			}
			void WriteChar(const wchar_t& s)
			{
				wostringstream oss;
				oss << s;
				wstring t = oss.str();
				wcscpy_s(str, sizeof(str) / sizeof(wchar_t), t.c_str());
				strSize = wcslen(str);
				if (fwrite(str, sizeof(wchar_t), strSize, fileHandle) != strSize)
				{
					wprintf(L"fwrite failed!\n");
				}
			}
		private:
			wstring filename;
			FILE*   fileHandle;
			wchar_t str[100];
			size_t  strSize;
		};

		wstring intToWstring(int i)
		{
			wostringstream oss;
			oss << i ;
			return  oss.str();
		}
		wstring wcToWstring(wchar_t i)
		{
			wostringstream oss;
			oss << i;
			return  oss.str();
		}
		size_t indexOf(vector<shared_ptr<State>> &v, State *s)
		{
			for (size_t i = 0; i < v.size();i++)
			{
				if (v[i].get() == s)
					return i;
			}
			return -1;
		}
		bool needEscap(wchar_t w)
		{
			switch (w)
			{
			case L'"':
			case L'\\':
				return true;
			default:
				return false;
			}
		}
		void PrintAutomatonToDotFile(wstring fileName, Automaton::Ref automaton)
		{
			FileWriter writer(fileName);
			wstring intbuf;

			writer.WriteString(L"digraph hierarchy {\n");
			writer.WriteString(L"rankdir = LR;\n"
							   L"size = \"8,5\"\n"
							   L"node[shape = circle];\n");

			for (int i = 0;i < automaton->states.size();i++)
			{
				State* state = automaton->states[i].get();
				intbuf = intToWstring(i);
				wstring lable = L"S" + intbuf;
				writer.WriteString(lable +L" [");
				if (automaton->startState == state)
				{
					
				}
				else if (state->finalState)
				{
					writer.WriteString(L"shape=doublecircle, ");
				}
				writer.WriteString(L"label=\""+ lable +L"\"");
				writer.WriteString(L"]\n");
			}
			for (int i = 0;i < automaton->states.size();i++)
			{
				State* state = automaton->states[i].get();
				intbuf = intToWstring(i);
				wstring sourceLable = L"S" + intbuf;

				for (int j = 0;j < state->transitions.size();j++)
				{
					Transition* transition = state->transitions[j];
					intbuf = intToWstring(indexOf(automaton->states, transition->target));
					wstring targetLable = L"S" + intbuf;

					writer.WriteString(sourceLable+ L"->"+targetLable);
					writer.WriteString(L" [");
					switch (transition->type)
					{
					case Transition::Chars:
						if (transition->range.begin == transition->range.end)
						{
							writer.WriteString(L"label=\"");
							if(needEscap(transition->range.begin))
								writer.WriteString(L"\\"+wcToWstring(transition->range.begin));
							else
								writer.WriteChar(transition->range.begin);
							writer.WriteString(L"\"");
							break;
						}
						writer.WriteString(L"label=\"");
						if (needEscap(transition->range.begin))
							writer.WriteString(L"\\" + wcToWstring(transition->range.begin));
						else
							writer.WriteChar(transition->range.begin);
						writer.WriteString(L" - ");
						if (needEscap(transition->range.end))
							writer.WriteString(L"\\" + wcToWstring(transition->range.end));
						else
							writer.WriteChar(transition->range.end);
						writer.WriteString(L"\"");
						break;
					case Transition::Epsilon:
						writer.WriteString(L"label=\"");
						writer.WriteString(L"ε");
						writer.WriteString(L"\"");
						break;
					case Transition::BeginString:
						writer.WriteString(L"label=\"");
						writer.WriteString(L"^");
						writer.WriteString(L"\"");
						break;
					case Transition::EndString:
						writer.WriteString(L"label=\"");
						writer.WriteString(L"$");
						writer.WriteString(L"\"");
						break;
					case Transition::Nop:
						writer.WriteString(L"label=\"");
						writer.WriteString(L"Nop");
						writer.WriteString(L"\"");
						break;
					}
					writer.WriteString(L" ]\n");
				}
			}
			writer.WriteString(L"}");
		}
		void PrintAutomaton(wstring fileName, Automaton::Ref automaton)
		{
			FileWriter writer(fileName);
			wstring intbuf;
			for (int i = 0;i<automaton->states.size();i++)
			{
				State* state = automaton->states[i].get();
				if (automaton->startState == state)
				{
					writer.WriteString(L"[START]");
				}
				if (state->finalState)
				{
					writer.WriteString(L"[FINISH]");
				}
				writer.WriteString(L"State<");
				intbuf = intToWstring(i);
				writer.WriteString(intbuf);
				writer.WriteLine(L">");
				for (int j = 0;j<state->transitions.size();j++)
				{
					Transition* transition = state->transitions[j];
					intbuf = intToWstring(indexOf(automaton->states,transition->target));
					writer.WriteString(L"    To State<");
					writer.WriteString(intbuf);
					writer.WriteString(L"> : ");
					switch (transition->type)
					{
					case Transition::Chars:
						writer.WriteString(L"<Char : ");
						writer.WriteString(intToWstring(transition->range.begin));
						writer.WriteString(L"[");
						writer.WriteChar(transition->range.begin);
						writer.WriteString(L"] - ");
						writer.WriteString(intToWstring(transition->range.end));
						writer.WriteString(L"[");
						writer.WriteChar(transition->range.end);
						writer.WriteLine(L"]>");
						break;
					case Transition::Epsilon:
						writer.WriteLine(L"<Epsilon>");
						break;
					case Transition::BeginString:
						writer.WriteLine(L"^");
						break;
					case Transition::EndString:
						writer.WriteLine(L"$");
						break;
					case Transition::Nop:
						writer.WriteLine(L"<Nop>");
						break;
					}
				}
			}
		}
		void PrintRegex(wstring name, wstring code)
		{
			RegexExpression::Ref regex = ParseRegexExpression(code);
			List subsets;
			Expression::Ref expression = regex->expression;
			map<State*, State*> nfaStateMap;
			Multimap<State*, State*> dfaStateMap;
			Automaton::Ref eNfa = expression->generateEpsilonNfa();
			PrintAutomaton(name + L".eNfa.txt", eNfa);
			Automaton::Ref nfa = EpsilonNfaToNfa(eNfa, epsilonChecker, nfaStateMap);
			PrintAutomaton(name + L".Nfa.txt", nfa);
			Automaton::Ref dfa = NfaToDfa(nfa, dfaStateMap);
			PrintAutomaton(name + L".Dfa.txt", dfa);

			PrintAutomatonToDotFile(name + L".eNfa.gv", eNfa);
			PrintAutomatonToDotFile(name + L".Nfa.gv", nfa);
			PrintAutomatonToDotFile(name + L".Dfa.gv", dfa);
		}

		TEST_METHOD(TestAutomaton)
		{
			PrintRegex(L"TestRegexabc", L"abc?");
			PrintRegex(L"TestRegexFullint", L"(/+|-)?/d+");
			PrintRegex(L"TestRegexFloat", L"(/+|-)?/d+(./d+)?");
			PrintRegex(L"TestRegexString", L"\"([^\\\\\"]|\\\\\\.)*\"");
			PrintRegex(L"TestRegexComment", L"///*([^*]|/*+[^*//])*/*+//");
		}



		void RunPureInterpretor(const wstring &pattern, const wstring &target,int start, int length)
		{
			Regex re(pattern);
			wstring rs;
			re.search(target, rs);
			bool cmp = true;
			RegexResult result = re.result_m;
			result.start == start ? cmp = true : cmp = false;
			result.length == length ? cmp = true : cmp = false;
			Assert::AreEqual(true,cmp);
			
			FileWriter writer(L"TestMatchResult.txt");
			writer.WriteString(rs);
		}
		TEST_METHOD(TestMatchHead)
		{
			
			RunPureInterpretor(L"/d", L"abcde12345abcde", 5, 1);
			RunPureInterpretor(L"/d", L"12345abcde", 0, 1);
			RunPureInterpretor(L"/d", L"vczh", -1, 0);

			RunPureInterpretor(L"(/+|-)?/d+", L"abcde12345abcde", 5, 5);
			RunPureInterpretor(L"(/+|-)?/d+", L"abcde+12345abcde", 5, 6);
			RunPureInterpretor(L"(/+|-)?/d+", L"abcde-12345abcde", 5, 6);
			RunPureInterpretor(L"(/+|-)?/d+", L"12345abcde", 0, 5);
			RunPureInterpretor(L"(/+|-)?/d+", L"+12345abcde", 0, 6);
			RunPureInterpretor(L"(/+|-)?/d+", L"-12345abcde", 0, 6);
			RunPureInterpretor(L"(/+|-)?/d+", L"-+vczh+-", -1, 0);

			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde12345abcde", 5, 5);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde+12345abcde", 5, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde-12345abcde", 5, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde12345.abcde", 5, 5);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde+12345.abcde", 5, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde-12345.abcde", 5, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde12345.54321abcde", 5, 11);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde+12345.54321abcde", 5, 12);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"abcde-12345.54321abcde", 5, 12);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"12345", 0, 5);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"+12345", 0, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"-12345", 0, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"12345.", 0, 5);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"+12345.", 0, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"-12345.", 0, 6);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"12345.54321", 0, 11);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"+12345.54321", 0, 12);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"-12345.54321", 0, 12);
			RunPureInterpretor(L"(/+|-)?/d+(./d+)?", L"-+vczh+-", -1, 0);

			RunPureInterpretor(L"\"([^\\\\\"]|\\\\\\.)*\"", L"vczh\"is\"genius", 4, 4);
			RunPureInterpretor(L"\"([^\\\\\"]|\\\\\\.)*\"", L"vczh\"i\\r\\ns\"genius", 4, 8);
			RunPureInterpretor(L"\"([^\\\\\"]|\\\\\\.)*\"", L"vczh is genius", -1, 0);

			RunPureInterpretor(L"///*([^*]|/*+[^*//])*/*+//", L"vczh/*is*/genius", 4, 6);
			RunPureInterpretor(L"///*([^*]|/*+[^*//])*/*+//", L"vczh/***is***/genius", 4, 10);
			RunPureInterpretor(L"///*([^*]|/*+[^*//])*/*+//", L"vczh is genius", -1, 0);
		}
	};
}