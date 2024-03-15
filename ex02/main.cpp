#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "this program works with 2 argument min" << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::list<int> list;
	for (int i = 1; i < argc; i++)
	{
		int nb = atoi(argv[i]);
		if (nb < 0)
		{
			std::cerr << "this program works with positive numbers only" << std::endl;
			return 1;
		}
		vec.push_back(nb);
		list.push_back(nb);
	}
	PmergeMe vl(vec, list);
	return 0;
}
