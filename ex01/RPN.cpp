#include "RPN.hpp"

RPN::RPN()
{
	std::cout << GREEN << "Default RPN" << RESET << " has been created" << std::endl;
}

RPN::RPN(RPN const& src) // A completer
{
	std::cout << GREEN << "Copy RPN " << RESET << " has been created" << std::endl;
}

RPN::~RPN()
{
	std::cout << GREEN << "RPN " << RESET << " has been destroyed" << std::endl;
}

RPN & RPN::operator=(RPN const& src)
{
	if (this != &src)
		// A completer
	return *this;
}

std::ostream &operator<<(std::ostream &o, RPN const& src)
{
	o << GREEN << "RPN ";// A completer
	o << RESET << std::endl;
	return o;
}

