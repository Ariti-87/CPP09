#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "this program take 1 argument" << std::endl;
		return 1;
	}
	std::string input(argv[1]);
	RPN rpn(input);
	return 0;
}
