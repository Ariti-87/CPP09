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

		void printPairs(std::vector< std::pair<int, int> > const& pairs);
		void printPairs(std::list< std::pair<int, int> > const& pairs);

	private:
		std::vector<int> _vec;
		std::vector< std::pair<int, int> > _vecPairs;
		std::list<int> _list;
		std::list< std::pair<int, int> > _listPairs;
		std::vector<unsigned int> _jacobsthalGroup;

		PmergeMe();
		void mergeInsert(std::vector<int> & vec);
		void addPairs(std::vector<int> & vec);
		void insertMax(std::vector<int> & vec/* , std::vector<int> & tmp */);
		void insertMin(std::vector<int> & vec, int min);
		void insertJacobsthalMin(std::vector<int> & vec, std::vector<int> & tmp);

		void mergeInsert(std::list<int> & list);
		void addPairs(std::list<int> & list);
		void insertMax(std::list<int> & list/* , std::list<int> & tmp */);
		void insertMin(std::list<int> & list, int min);
		void insertJacobsthalMin(std::list<int> & list, std::list<int> & tmp);

		void printBeforeAndAfter(std::vector<int> & vec);
		void sortAndClock(std::vector<int> & vec, std::list<int> & list);

		void jacobsthal();
		int jacobsthalSequence(int n);
};

#endif

