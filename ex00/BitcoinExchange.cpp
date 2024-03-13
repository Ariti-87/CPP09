#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << GREEN << "Default BitcoinExchange" << RESET << " has been created" << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string const& filename, std::string const& input)
{
	std::cout << GREEN << "BitcoinExchange" << RESET << " has been created" << std::endl;
	if (loadData(filename))
		calculBitcoin(input);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& src) : _data(src._data)
{
	std::cout << GREEN << "Copy BitcoinExchange " << RESET << " has been created" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << GREEN << "BitcoinExchange " << RESET << " has been destroyed" << std::endl;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const& src)
{
	if (this != &src)
		_data = src._data;
	return *this;
}

bool BitcoinExchange::loadData(std::string const& filename)
{
	std::ifstream inFile(filename.c_str());
	std::string line;
	if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".csv")
	{
		std::cerr << "Error Data is not in .csv format" << std::endl;
		return false;
	}
	if (!inFile)
	{
		std::cerr << "Error opening Data file" << std::endl;
		return false;
	}
	if (!std::getline(inFile, line))
	{
		std::cerr << "Empty Data" << std::endl;
		return false;
	}
	while (std::getline(inFile, line))
	{
		std::istringstream iss(line);
		std::string date;
		std::string valueStr;
		if (std::getline(iss, date, ',') && std::getline(iss, valueStr))
		{
			float value;
			std::stringstream ss(valueStr);
			ss >> value;
			_data[date] = value;
		}
	}
	return true;
}

void BitcoinExchange::calculBitcoin(std::string const& input)
{
	std::ifstream inputStream(input.c_str());
	std::string line;
	if (!inputStream)
	{
		std::cerr << "Error opening input file" << std::endl;
		return ;
	}
	if (!std::getline(inputStream, line))
	{
		std::cerr << "Empty Input : " << input << std::endl;
		return;
	}
	while (std::getline(inputStream, line))
		checkInput(line);
}

void BitcoinExchange::printData() const
{
	std::map<std::string, float>::const_iterator it;
	for (it = _data.begin(); it != _data.end(); it++)
	{
		if (it->second == 0)
		{
			std::cout << "Key : " << it->first << " | " << "Value : " << it->second << std::endl;
		}
		else
		{
			std::cout << std::setprecision(2) << std::fixed;
			std::cout << "Key : " << it->first << " | " << "Value : " << it->second << std::endl;
		}
	}
}

bool BitcoinExchange::checkDate(std::string const& date)
{
	struct tm tm = {};
	if (strptime(date.c_str(), "%Y-%m-%d", &tm) == NULL)
		return false;
	// Correction of strptime
	int monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// Adjustment for leap years
	if (tm.tm_year % 4 == 0 && (tm.tm_year % 100 != 0 || tm.tm_year % 400 == 0) && tm.tm_mon == 1)
		monthlen[1] = 29;
	// Testing
	if (tm.tm_mday > monthlen[tm.tm_mon])
		return false;
	return true;
}

void BitcoinExchange::checkInput(std::string const& input)
{
		std::istringstream iss(input);
		std::string date;
		std::string sep;
		float value;
		std::map<std::string, float>::const_iterator it;
		std::map<std::string, float>::const_iterator it2;

		if (!(iss >> date))
		{
			std::cout << "Error: Date not found" << std::endl;
			return;
		}
		// std::cout << date << std::endl;
		if (!checkDate(date) || date.size() != 10 || date[9] == '|')
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return;
		}
		if (!(iss >> sep) || !(iss >> value))
		{
			std::cout << "Error: Value not found" << std::endl;
			return;
		}
		if (!iss.eof())
		{
			std::cout << "Error: Multiples values" << std::endl;
			return;
		}
		// std::cout << value << std::endl;
		if (value < 0)
		{
			std::cout << "Error: not a positive number" << std::endl;
			return ;
		}
		if (value > 1000)
		{
			std::cout << "Error: too large a number" << std::endl;
			return ;
		}
		it = _data.find(date);
		it2 = _data.lower_bound(date);
		if (it != _data.end())
		{
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
			return;
		}
		if (it2 == _data.begin())
		{
			std::cout << "First date, Data not available" << std::endl;
			return;
		}
		std::cout << date << " => " << value << " = " << value * (--it2)->second << std::endl;
}



