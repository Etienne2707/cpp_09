#ifndef BitcoinExchange_TM_FILENAME_EXT_UC
#define BitcoinExchange_TM_FILENAME_EXT_UC

#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <unistd.h>

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
    std::map<int,std::vector<std::string>> _map;
public:
    
    BitcoinExchange(char *file);
    BitcoinExchange(const BitcoinExchange & src);
    BitcoinExchange & operator=(const BitcoinExchange & rhs);
    ~BitcoinExchange();
    int set_data( void );
    int set_map( char *str );
    int check_format(std::string line,  std::vector<std::string>& value);
    std::string Get_Number(std::string line);
    void    print_mapXdata( void );
    int    date_exist(std::map<int, std::vector<std::string>>::iterator Mit );
    float   get_exchange_rate(int found);
    std::string get_close_date(std::map<int, std::vector<std::string>>::iterator Mit);
    std::string decreaseDate(std::string date);
    int	checkDay(std::string day);
    int	checkYear(std::string year);
    int	checkMonth(std::string month);
};

#endif