#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "this program take 1 argument" << std::endl;
		return 1;
	}
	std::string input(argv[1]);
	BitcoinExchange Bitcoin("data.csv", input);
	// Bitcoin.printData();
	return 0;
}
