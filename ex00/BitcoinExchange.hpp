#ifndef DEF_BITCOINEXCHANGE
#define DEF_BITCOINEXCHANGE

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
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <ctime>

class BitcoinExchange
{
	public:
		BitcoinExchange(std::string const& filename, std::string const& input);
		BitcoinExchange(BitcoinExchange const& src);
		~BitcoinExchange();
		BitcoinExchange &operator=(BitcoinExchange const& src);

		void printData() const;

	private:
		std::map<std::string, float>_data;
		BitcoinExchange();

		bool checkDate(std::string const& date);
		bool loadData(std::string const& filename);
		void checkInput(std::string const& input);
		void calculBitcoin(std::string const& input);
};

#endif
