#ifndef DEF_PMERGEME
#define DEF_PMERGEME

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
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <list>

class PmergeMe
{
	public:
		PmergeMe(std::vector<int> & vec, std::list<int> & list);
		PmergeMe(PmergeMe const& src);
		~PmergeMe();
		PmergeMe &operator=(PmergeMe const& src);

		template <typename Container>
		void printContainer(Container const& container) const;

	private:
		std::vector<int> _vec;
		std::vector<int> _vecPairs;
		std::list<int> _list;

		PmergeMe();
		void merge(std::vector<int>& vec, std::vector<int>& left, std::vector<int>& right);
		void mergeInsert(std::vector<int> & vec);
		void sortPairs(std::vector<int> & vec);
		void sortPairsByMax();

		void merge(std::list<int>& list, std::list<int>& left, std::list<int>& right);
		void mergeInsert(std::list<int> & list);

		void printBeforeAndAfter(std::vector<int> & vec);
		void sortAndClock(std::vector<int> & vec, std::list<int> & list);
};

template <typename Container>
void PmergeMe::printContainer(const Container& container) const
{
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

#endif

