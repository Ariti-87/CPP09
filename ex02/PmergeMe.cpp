#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(std::vector<int> & vec, std::list<int> & list) : _vec(vec), _list(list)
{

	jacobsthal();
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
	std::vector<int> tmp(vec);
	vec.clear();
	vec.push_back(_vecPairs[0].first); // insert First Min
	insertMax(vec, tmp);
	insertJacobsthal(vec);
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

void PmergeMe::insertMax(std::vector<int> & vec, std::vector<int> & tmp)
{
	std::vector<int>::iterator it = tmp.end() - 1;
	for (size_t i = 0; i < _vecPairs.size(); i++)
		vec.push_back(_vecPairs[i].second);
	if (tmp.size() % 2 == 1)
		vec.insert(std::upper_bound(vec.begin(),vec.end(), *it), *it); // Insert last if odd list
}

void PmergeMe::insertJacobsthal(std::vector<int> & vec)
{
	std::vector<int> tmpMin;
	for (size_t i = 1; i < _vecPairs.size(); i++)
		tmpMin.push_back(_vecPairs[i].first);
	std::vector< std::vector<int> >minGroups;
	minGroups.push_back(std::vector<int>());
	unsigned int groupIndex = 0;
	unsigned int groupSize = 0;
	for (size_t i = 0; i < tmpMin.size(); ++i)
	{
		if (groupIndex >= _jacobsthalGroup.size())
			break;
		if (groupSize == _jacobsthalGroup[groupIndex])
		{
			minGroups.push_back(std::vector<int>());
			groupIndex++;
			groupSize = 0;
		}
		minGroups.back().push_back(tmpMin[i]);
		groupSize++;
	}
	// for (size_t i = 0; i < minGroups.size(); ++i)
	// {
	// 	std::cout << "Groupe " << (i + 1) << ": ";
	// 	for (size_t j = 0; j < minGroups[i].size(); ++j)
	// 		std::cout << minGroups[i][j] << " ";
	// 	std::cout << std::endl;
	// }
	for (size_t i = 0; i < minGroups.size(); ++i)
	{
		for (std::vector<int>::reverse_iterator it = minGroups[i].rbegin(); it != minGroups[i].rend(); ++it)
			insertMin(vec, *it);
	}
}

void PmergeMe::insertMin(std::vector<int> & vec, int min)
{
	std::vector<int>::iterator endIt;
	std::vector<int>::iterator it;
	int max;
	for (int i = 0; _vecPairs[i].first != min; i++)
	{
		if (_vecPairs[i].first == min)
			max = _vecPairs[i].second;
	}
	endIt = find(vec.begin(), vec.end(), max);
	it = upper_bound(vec.begin(), endIt, min);
	vec.insert(it, min);
}

/////////////////////////////////////////// LIST //////////////////////////////////////////////

void PmergeMe::mergeInsert(std::list<int> & list)
{
	if (list.size() < 4)
	{
		list.sort();
		return;
	}
	addPairs(list);
	_listPairs.sort(comparePairsByMax);
	std::list<int> tmp(list);
	list.clear();
	list.push_back(_listPairs.front().first); // insert First Min
	insertMax(list, tmp);
	insertJacobsthal(list);
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

void PmergeMe::insertMax(std::list<int> & list, std::list<int> & tmp)
{
	std::list<int>::iterator it = tmp.end();
	if (tmp.size() % 2 == 1)
		it--;
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

void PmergeMe::insertJacobsthal(std::list<int> & list)
{
	std::list<int> tmpMin;
	for (std::list< std::pair<int, int> >::iterator it = _listPairs.begin(); it != _listPairs.end(); ++it)
	{
		if (it == _listPairs.begin())
			it++;
		tmpMin.push_back(it->first);
	}
	std::list< std::list<int> >minGroups;
	minGroups.push_back(std::list<int>());
	unsigned int groupIndex = 0;
	unsigned int groupSize = 0;
	for (std::list<int>::iterator it = tmpMin.begin(); it != tmpMin.end(); ++it)
	{
		if (groupIndex >= _jacobsthalGroup.size())
			break;
		if (groupSize == _jacobsthalGroup[groupIndex])
		{
			minGroups.push_back(std::list<int>());
			groupIndex++;
			groupSize = 0;
		}
		minGroups.back().push_back(*it);
		groupSize++;
	}

	for (std::list< std::list<int> >::iterator itGroup = minGroups.begin(); itGroup != minGroups.end(); ++itGroup)
	{
		for (std::list<int>::reverse_iterator it = itGroup->rbegin(); it != itGroup->rend(); ++it)
			insertMin(list, *it);
	}
}


void PmergeMe::insertMin(std::list<int> & list, int min)
{
	std::list< std::pair<int, int> >::const_iterator pairIt = _listPairs.begin();
	std::list<int>::iterator endIt;
	std::list<int>::iterator it;
	int max;
	while (pairIt->first != min)
	{
		pairIt++;
		if (pairIt->first == min)
			max = pairIt->second;
	}
	endIt = find(list.begin(), list.end(), max);
	it = upper_bound(list.begin(), endIt, min);
	list.insert(it, min);
}

/////////////////////////////////////////// AUTRE //////////////////////////////////////////////

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
	t = (clock() - t) * 1000000;
	std::cout << std::setprecision(2) << std::fixed << "Vector => Time to process a range of ";
	std::cout << vec.size() << " : " << (static_cast<double>(t)) / CLOCKS_PER_SEC << " us" << std::endl;

	t = clock();
	mergeInsert(list);
	// printPairs(_listPairs);
	std::cout << "list: ";
	printContainer(_list);
	t = (clock() - t) * 1000000;
	std::cout << "List => Time to process a range of ";
	std::cout << list.size() << " : " << (static_cast<double>(t)) / CLOCKS_PER_SEC << " us" << std::endl;
}

/////////////////////////////////////////// PRINT //////////////////////////////////////////////

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

/////////////////////////////////////////// JACOBSTHAL //////////////////////////////////////////////

int PmergeMe::jacobsthalSequence(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return (jacobsthalSequence(n - 1) + 2 * jacobsthalSequence(n - 2));
}

void PmergeMe::jacobsthal()
{
	int n = 30;
	std::vector<unsigned int> jacobsthalSeq(n);
	for (int i = 0; i < n; i++)
		jacobsthalSeq[i] = jacobsthalSequence(i);
	// std::cout << "La suite de Jacobsthal est : ";
	// for (int i = 0; i < n; ++i)
	// 	std::cout << jacobsthalSeq[i] << " ";
	// std::cout << std::endl;

	for (int i = 2; i < n - 1; i++)
		_jacobsthalGroup.push_back(jacobsthalSeq[i + 1] - jacobsthalSeq[i]);
	// std::cout << "Les groupes de Jacobsthal sont : ";
	// printContainer(_jacobsthalGroup);
}
