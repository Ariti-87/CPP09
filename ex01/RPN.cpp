#include "RPN.hpp"

RPN::RPN()
{
	std::cout << GREEN << "Default RPN" << RESET << " has been created" << std::endl;
}

RPN::RPN(std::string const& input)
{
	// std::cout << GREEN << "RPN" << RESET << " has been created" << std::endl;
	if (checkInput(input))
		calculRPN(input);
}

RPN::RPN(RPN const& src) : _stack(src._stack)
{
	std::cout << GREEN << "Copy RPN " << RESET << " has been created" << std::endl;
}

RPN::~RPN()
{
	// std::cout << GREEN << "RPN " << RESET << " has been destroyed" << std::endl;
}

RPN & RPN::operator=(RPN const& src)
{
	if (this != &src)
		_stack = src._stack;
	return *this;
}

void RPN::calculRPN(std::string const& input)
{
	for (std::string::const_iterator it = input.begin(); it != input.end(); it++)
	{
		if (*it == '+' || *it == '-' || *it == '*' || *it == '/' )
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error: the first two elements of the stack must be numbers" << std::endl;
				return ;
			}
			int value = _stack.top();
			// std::cout << "valeur 1 : " << value << std::endl;
			_stack.pop();
			int value2 = _stack.top();
			_stack.pop();
			// std::cout << "valeur 2 : " << value2 << std::endl;
			switch (*it)
			{
				case '+':
				{
					if (value > INT_MAX - value2)
					{
						std::cerr << "Error: Int overflow " << std::endl;
						return ;
					}
					_stack.push(value2 + value); break;
				}
				case '-':
				{
					if (value2 < INT_MIN + value)
					{
						std::cerr << "Error: Int overflow " << std::endl;
						return ;
					}
					_stack.push(value2 - value); break;
				}
				case '*':
				{
					if (value && value2 > INT_MAX / value)
					{
						std::cerr << "Error: Int overflow " << std::endl;
						return ;
					}
					_stack.push(value2 * value); break;
				}
				case '/':
				{
					if (value == 0)
					{
						std::cerr << "Error: Division by zero" << std::endl;
						return ;
					}
					_stack.push(value2 / value); break;
				}
			}
			// std::cout << *it << std::endl;
			// std::cout << _stack.top() << std::endl;
		}
		else
		{
			if (*it == ' ')
				continue;
			else
				_stack.push(*it - '0');
		}
	}
	if (_stack.size() != 1)
	{
		std::cerr << "Error: invalid input format, for n number you need n-1 operators" << std::endl;
		return ;
	}
	std::cout << _stack.top() << std::endl;
}

bool RPN::checkInput(std::string const& input)
{
	for (unsigned long i = 0; i < input.length(); i++)
	{
		if (i % 2 == 1)
		{
			if (input[i] != ' ')
			{
				std::cerr << "Error: invalid input format, space expected" << std::endl;
				return false;
			}
		}
		else
		{
			if (isdigit(input[i]))
				continue;
			else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
				continue;
			else
			{
				std::cerr << "Error: invalid input format, digit/operator expected" << std::endl;
				return false;
			}
		}
	}
	return true;
}
