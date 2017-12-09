#pragma once
#include <string>
#include <memory.h>
namespace tl
{
	using namespace std;
	class Exception
	{
	public:
		Exception(const wstring& message_ = wstring(L""));

		const wstring& GetMessage()const; // 这种返回值就避免了拷贝，而且合法

	protected:
		wstring message;
	};

	class ArgumentException : public Exception
	{
	protected:
		wstring function;
		wstring name;
	public:
		ArgumentException(const wstring& message_, const wstring& function_,
						  const wstring& name_);

		const wstring& GetFunction();
		const wstring& GetName();
	};

	class ParsingException : public Exception
	{
	protected:
		int position;
		wstring	expression;

	public:
		ParsingException(const wstring& message_, const wstring& expression_, int position_);

		const wstring&	GetExpression()const;
		int	GetPosition()const;
	};
}