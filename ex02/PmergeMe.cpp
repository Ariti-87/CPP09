#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	std::cout << GREEN << "Default PmergeMe" << RESET << " has been created" << std::endl;
}

PmergeMe::PmergeMe(std::vector<int> & vec, std::list<int> & list) : _vec(vec), _list(list)
{
	printBeforeAndAfter(vec);
	sortAndClock(_vec, _list);
}

PmergeMe::PmergeMe(PmergeMe const& src) : _vec(src._vec), _list(src._list)
{
	std::cout << GREEN << "Copy PmergeMe " << RESET << " has been created" << std::endl;
}

PmergeMe::~PmergeMe()
{
	// std::cout << GREEN << "PmergeMe " << RESET << " has been destroyed" << std::endl;
}

PmergeMe & PmergeMe::operator=(PmergeMe const& src)
{
	if (this != &src)
	{
		_vec = src._vec;
		_list = src._list;
	}
	return *this;
}

void PmergeMe::printBeforeAndAfter(std::vector<int> & vec)
{
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
	mergeInsert(vec);
	_vecPairs.clear();
	std::cout << std::endl << "After: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

void PmergeMe::sortAndClock(std::vector<int> & vec, std::list<int> & list)
{
	clock_t t;

	t = clock();
	mergeInsert(vec);
	t = (clock() - t) * 1000000;
	std::cout << std::setprecision(2) << std::fixed << "Vector => Time to process a range of ";
	std::cout << vec.size() << " : " << ((float)t) / CLOCKS_PER_SEC << " us" << std::endl;

	t = clock();
	// mergeInsert(list);
	t = (clock() - t) * 1000000;
	std::cout << "List => Time to process a range of ";
	std::cout << list.size() << " : " << ((float)t) / CLOCKS_PER_SEC << " us" << std::endl;
}

void PmergeMe::mergeInsert(std::vector<int> & vec)
{
	sortPairs(vec);
	std::cout << "Pairs : ";
	printContainer(_vecPairs);
}

void PmergeMe::sortPairs(std::vector<int> & vec)
{
	if (vec.size() < 2)
	{
		_vecPairs.push_back(vec[0]);
		return ;
	}
	if (vec.size() == 2)
	{
		if(vec[0] > vec[1])
			std::swap(vec[0], vec[1]);
		_vecPairs.push_back(vec[0]);
		_vecPairs.push_back(vec[1]);
		return ;
	}
	std::vector<int>::iterator it = vec.begin() + 2;
	std::vector<int> left(vec.begin(), it);
	std::vector<int> right(it, vec.end());
	sortPairs(left);
	sortPairs(right);
}

void PmergeMe::sortPairsByMax()
{
	std::vector<int> tmp;
	tmp.push_back(_vecPairs[0]);
	tmp.push_back(_vecPairs[1]);
	std::vector<int>::iterator it = _vecPairs.begin() + 2;
	while (it != _vecPairs.end())
	{
		
	}

}

void PmergeMe::merge(std::vector<int>& vec, std::vector<int>& left, std::vector<int>& right) {
	std::vector<int>::iterator itLeft = left.begin();
	std::vector<int>::iterator itRight = right.begin();
	while (itLeft != left.end() && itRight != right.end()) {
		if (*itLeft < *itRight) {
			vec.push_back(*itLeft++);
		} else {
			vec.push_back(*itRight++);
		}
	}
	while (itLeft != left.end()) vec.push_back(*itLeft++);
	while (itRight != right.end()) vec.push_back(*itRight++);
}










void PmergeMe::mergeInsert(std::list<int> & list)
{
	if (list.size() < 2)
		return ;
	if (list.size() == 2)
	{
		if (list.front() > list.back())
			list.sort();
		std::cout << "final : ";
		printContainer(list);
		return ;
	}
	std::list<int> left;
	std::list<int>::iterator it = list.begin();
	for (int i = 0; i < 2; i++, it++)
		left.push_back(*it);
	std::list<int> right(it, list.end());

	std::cout << "left : ";
	printContainer(left);
	std::cout << "right : ";
	printContainer(right);

	mergeInsert(left);
	mergeInsert(right);

	list.clear();
	merge(list, left, right);
}

void PmergeMe::merge(std::list<int>& list, std::list<int>& left, std::list<int>& right) {
	std::list<int>::iterator itLeft = left.begin();
	std::list<int>::iterator itRight = right.begin();
	while (itLeft != left.end() && itRight != right.end()) {
		if (*itLeft < *itRight) {
			list.push_back(*itLeft++);
		} else {
			list.push_back(*itRight++);
		}
	}
	while (itLeft != left.end()) list.push_back(*itLeft++);
	while (itRight != right.end()) list.push_back(*itRight++);
}


// void PmergeMe::mergeInsert(std::vector<int> & vec)
// {
// 	if (vec.size() < 2)
// 		return ;
// 	if (vec.size() == 2)
// 	{
// 		if(vec[0] > vec[1])
// 			std::swap(vec[0], vec[1]);
// 		std::cout << "final : ";
// 		printContainer(vec);
// 		return ;
// 	}
// 	std::vector<int>::iterator paire = vec.begin() + 2;
// 	std::vector<int> left(vec.begin(), paire);
// 	std::vector<int> right(paire, vec.end());

// 	std::cout << "left : ";
// 	printContainer(left);
// 	std::cout << "right : ";
// 	printContainer(right);

// 	mergeInsert(left);
// 	mergeInsert(right);

// 	vec.clear();
// 	merge(vec, left, right);
// }

// void PmergeMe::merge(std::vector<int>& vec, std::vector<int>& left, std::vector<int>& right) {
// 	std::vector<int>::iterator itLeft = left.begin();
// 	std::vector<int>::iterator itRight = right.begin();
// 	while (itLeft != left.end() && itRight != right.end()) {
// 		if (*itLeft < *itRight) {
// 			vec.push_back(*itLeft++);
// 		} else {
// 			vec.push_back(*itRight++);
// 		}
// 	}
// 	while (itLeft != left.end()) vec.push_back(*itLeft++);
// 	while (itRight != right.end()) vec.push_back(*itRight++);
// }

// const long unsigned int jacobsthal[] = {
// 		2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
// 		2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
// 		1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
// 		178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
// 		11453246122, 22906492246, 45812984490, 91625968982, 183251937962,
// 		366503875926, 733007751850, 1466015503702, 2932031007402, 5864062014806,
// 		11728124029610, 23456248059222, 46912496118442, 93824992236886, 187649984473770,
// 		375299968947542, 750599937895082, 1501199875790165, 3002399751580331,
// 		6004799503160661, 12009599006321322, 24019198012642644, 48038396025285288,
// 		96076792050570576, 192153584101141152, 384307168202282304, 768614336404564608,
// 		1537228672809129216, 3074457345618258432, 6148914691236516864, 0};
