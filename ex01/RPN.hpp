#ifndef DEF_RPN
#define DEF_RPN

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define VIOLET "\033[35m"
#define GREEN "\033[32m"
#define LGREEN "\033[92m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define BLACK "\033[30m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"

#include <iostream>
#include <stack>
#include <climits>
#include <cctype>

class RPN
{
	public:
		RPN(std::string const& input);
		RPN(RPN const& src);
		~RPN();
		RPN &operator=(RPN const& src);

	private:
		std::stack<int> _stack;
		RPN();
		bool checkInput(std::string const& input);
		void calculRPN(std::string const& input);
};

#endif

