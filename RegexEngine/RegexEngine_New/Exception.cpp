#include "Exception.h"


namespace tl
{

	Exception::Exception(const wstring & message_)
		: message(message_)
	{
	}

	const wstring & Exception::GetMessage()const
	{
		return message;
	}



	ArgumentException::ArgumentException(const wstring & message_, const wstring & function_,
										 const wstring & name_)
		: Exception(message_)
		, function(function_)
		, name(name_)
	{
	}

	const wstring & ArgumentException::GetFunction()
	{
		return function;
	}

	const wstring & ArgumentException::GetName()
	{
		return name;
	}





	ParsingException::ParsingException(const wstring& _message, 
									   const wstring& _expression, int _position)
		:Exception(_message)
		, expression(_expression)
		, position(_position)
	{
	}

	const wstring& ParsingException::GetExpression()const
	{
		return expression;
	}

	int ParsingException::GetPosition()const
	{
		return position;
	}

}