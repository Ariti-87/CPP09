#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

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
{}

PmergeMe & PmergeMe::operator=(PmergeMe const& src)
{
	if (this != &src)
	{
		_vec = src._vec;
		_list = src._list;
	}
	return *this;
}

/////////////////////////////////////////// VECTOR //////////////////////////////////////////////

static bool comparePairsByMax(std::pair<int, int> const& a, std::pair<int, int> const& b)
{
	return a.second < b.second;
}

void PmergeMe::mergeInsert(std::vector<int> & vec)
{
	addPairs(vec);
	std::sort(_vecPairs.begin(), _vecPairs.end(), comparePairsByMax);
	insertMax(vec);
	for (size_t i = 1; i < _vecPairs.size(); i++)
		insertMin(vec, i);
}

void PmergeMe::addPairs(std::vector<int> & vec)
{
	if (vec.size() < 2)
		return ;
	if (vec.size() == 2)
	{
		if(vec[0] > vec[1])
			std::swap(vec[0], vec[1]);
		_vecPairs.push_back(std::make_pair(vec[0], vec[1]));
		return ;
	}
	std::vector<int>::iterator it = vec.begin() + 2;
	std::vector<int> left(vec.begin(), it);
	std::vector<int> right(it, vec.end());
	addPairs(left);
	addPairs(right);
}

void PmergeMe::insertMax(std::vector<int> & vec)
{
	std::vector<int> tmp(vec);
	std::vector<int>::iterator it = tmp.end() - 1;
	vec.clear();
	// vec.push_back(_vecPairs[0].first); // insert First Min
	for (size_t i = 0; i < _vecPairs.size(); i++)
		vec.push_back(_vecPairs[i].second);
	if (tmp.size() % 2 == 1)
		vec.insert(std::upper_bound(vec.begin(),vec.end(), *it), *it); // Insert last if odd list
}

void PmergeMe::insertMin(std::vector<int> & vec, size_t i)
{
	std::vector<int>::iterator endIt = vec.begin();
	std::vector<int>::iterator it;
	int index = 0;
	while (_vecPairs[i].second != vec[index])
	{
		index++;
		endIt++;
	}
	it = upper_bound(vec.begin(), endIt, _vecPairs[i].first);
	vec.insert(it, _vecPairs[i].first);
}

/////////////////////////////////////////// LIST //////////////////////////////////////////////

void PmergeMe::mergeInsert(std::list<int> & list)
{
	addPairs(list);
	_listPairs.sort(comparePairsByMax);
	insertMax(list);
	for (size_t i = 1; i < _listPairs.size(); i++)
		insertMin(list, i);
}

void PmergeMe::addPairs(std::list<int> & list)
{
	if (list.size() < 2)
		return ;
	if (list.size() == 2)
	{
		if (list.front() > list.back())
			std::swap(list.front(), list.back());
		_listPairs.push_back(std::make_pair(list.front(), list.back()));
		return ;
	}
	std::list<int> left;
	std::list<int>::iterator it = list.begin();
	for (int i = 0; i < 2; i++, it++)
		left.push_back(*it);
	std::list<int> right(it, list.end());
	addPairs(left);
	addPairs(right);
}

void PmergeMe::insertMax(std::list<int> & list)
{
	std::list<int> tmp(list);
	std::list<int>::iterator it = tmp.end();
	list.clear();
	if (tmp.size() % 2 == 1)
		it--;
	list.push_back(_listPairs.front().first); // insert First Min
	for (std::list< std::pair<int, int> >::iterator pairIt = _listPairs.begin(); pairIt != _listPairs.end(); ++pairIt)
		list.push_back(pairIt->second);
	if (tmp.size() % 2 == 1)
	{
		std::list<int>::iterator insertPos = list.begin();
		while (insertPos != list.end() && *insertPos < *it)
			++insertPos;
		list.insert(insertPos, *it); // Insert last if odd list
	}
}

void PmergeMe::insertMin(std::list<int> & list, size_t i)
{
	std::list< std::pair<int, int> >::const_iterator pairIt = _listPairs.begin();
	std::advance(pairIt, i);
	std::list<int>::iterator endIt = list.begin();
	std::list<int>::iterator it;
	int index = 0;
	while (pairIt->second != *endIt)
	{
		index++;
		endIt++;
	}
	it = upper_bound(list.begin(), endIt, pairIt->first);
	list.insert(it, pairIt->first);
}

/////////////////////////////////////////// LIST //////////////////////////////////////////////

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
	std::cout << '\n' << std::endl;
}

void PmergeMe::sortAndClock(std::vector<int> & vec, std::list<int> & list)
{
	clock_t t;

	t = clock();
	mergeInsert(vec);
	// printPairs(_vecPairs);
	// std::cout << "container -> vector : ";
	// printContainer(_vec);
	t = (clock() - t) * 1000000;
	std::cout << std::setprecision(2) << std::fixed << "Vector => Time to process a range of ";
	std::cout << vec.size() << " : " << (static_cast<double>(t)) / CLOCKS_PER_SEC << " us" << std::endl;

	t = clock();
	mergeInsert(list);
	// printPairs(_listPairs);
	// std::cout << "container -> list : ";
	// printContainer(_list);
	t = (clock() - t) * 1000000;
	std::cout << "List => Time to process a range of ";
	std::cout << list.size() << " : " << (static_cast<double>(t)) / CLOCKS_PER_SEC << " us" << std::endl;
}

void PmergeMe::printPairs(std::vector< std::pair<int, int> > const& pairs)
{
	for (size_t i = 0; i < pairs.size(); ++i)
		std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ")" << std::endl;
}

void PmergeMe::printPairs(std::list< std::pair<int, int> > const& pairs)
{
	for (std::list< std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
}

template <typename Container>
void PmergeMe::printContainer(Container const& container) const
{
	for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
