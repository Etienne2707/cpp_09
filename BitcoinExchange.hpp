#ifndef BitcoinExchange_TM_FILENAME_EXT_UC
#define BitcoinExchange_TM_FILENAME_EXT_UC

#include <fstream>
#include <iostream>
#include <map>
const std::string red = "\033[0;31m";
const std::string green = "\033[1;32m";
const std::string yellow = "\033[1;33m";
const std::string cyan = "\033[0;36m";
const std::string magenta = "\033[0;35m";
const std::string reset = "\033[0m";


class BitcoinExchange
{
private:
    BitcoinExchange();
    std::string _data;
    std::string _file;
    std::map<std::string,int>    _btc;
public:
    
    BitcoinExchange(char *file);
    BitcoinExchange(const BitcoinExchange & src);
    BitcoinExchange & operator=(const BitcoinExchange & rhs);
    ~BitcoinExchange();
    int set_data( void );
    int set_file( char *str );
    int check_format(std::string line);
};

#endif