#include "BitcoinExchange.hpp"
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(char *str)
{
    std::cout << yellow << "Parametric constructor call" << reset <<  std::endl;
    set_map(str);
    set_data();
    print_mapXdata();
}


BitcoinExchange::BitcoinExchange(BitcoinExchange const & src)
{
    std::cout << yellow << "Copy constructeur called" <<  reset << std::endl;
    *this = src;
}

BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & src)
{
    std::cout << yellow << "Assigment operator call" << reset << std::endl;
    if (this == &src)
        return (*this);
    return (*this);
}

int BitcoinExchange::check_format(std::string line,  std::vector<std::string>& value)
{
    std::string::iterator it;
    std::string year;
    std::string month;
    std::string day;
    if (!line.compare("date | value"))
        return -1;
    if (line.size() < 13)
        return -1;
    for (it = line.begin(); it != line.begin() + 4; it++)
    {
        if (*it < '0' || *it > '9')
            return (-1);
        year += *it;
    }
    if (*it != '-')
        return (-1);
    *it++;
    while (it != line.begin() + 7)
    {
        if (*it < '0' || *it > '9')
            return (-1);
        month += *it;
        it++;
    }
    if (*it != '-')
        return (-1);
    *it++;
    while (it != line.begin() + 10)
    {
        if (*it < '0' || *it > '9')
            return (-1);
        day += *it;
        it++;
    }
    if (*it != ' ' && *(it + 1 ) != '|')
        return (-2);
    value.push_back(year), value.push_back(month), value.push_back(day);
    return 1;
}

float stringToFloat(const std::string& number) {
    return static_cast<float>(std::atof(number.c_str()));
}

std::string BitcoinExchange::Get_Number(std::string line)
{
    std::string::iterator it = line.begin();
    std::string number;
    bool dot_float = false;
    while(*it != '|')
        it++;
    it++;
    while(it != line.end() && *it == 32)
        it++;
    if (it == line.end())
        return ("-2");
    while(it != line.end())
    {
        if (*it == '.')
        {
            if (dot_float == true)
                return ("-2");
            dot_float = true;
        }
        if ((*it < '0' || *it > '9') && *it != '.')
            return ("-2");
        number += *it++;
    }
    if (stringToFloat(number) > 1000)
        return ("-3");
    return number;
}

int BitcoinExchange::set_map(char *str)
{
    std::ifstream inputFile(str);
    std::string line;
    std::string result;
    std::vector<std::string> value;
    int index = 1;

    if (!inputFile.is_open())
    {
        std::cerr << red << "Erreur lors de l'ouverture du fichier." << reset << std::endl;
        return (-1);
    }
    while (std::getline(inputFile,line))
    {
        if (check_format(line,value) == 1)
        {
            value.push_back(Get_Number(line));
            this->_map.insert(std::make_pair(index,value));
        }
        else
        {
            value.push_back(line);
            value.push_back("-1");
            this->_map.insert(std::make_pair(index,value));
        }
        value.clear();
        index++;
    }
    return (1);
}

int BitcoinExchange::set_data( void )
{
    std::ifstream inputFile("data.csv");
    std::string line;

    if (!inputFile.is_open())
    {
        std::cerr << red << "Erreur lors de l'ouverture du fichier." << reset << std::endl;
        return (-1);
    }
    while (std::getline(inputFile,line))
    {
        this->_data += line + "\n";
    }
    inputFile.close();
    return (1);
}

std::string BitcoinExchange::decreaseDate(std::string date)
{
	std::stringstream   s(date);
	std::string         year, month, day, concatenated;

	getline(s, year, '-');
	getline(s, month, '-');
	getline(s, day);
	int	y = atoi(year.c_str());
	int	m = atoi(month.c_str());
	int	d = atoi(day.c_str());
	if (d > 1)
		d--;
	else if (m > 1)
	{
		d = 31;
		m--;
	}
	else if (y > 2008)
	{
		d = 31;
		m = 12;
		y--;
	}
	std::stringstream conc;
	conc << y << '-' << std::setw(2) << std::setfill('0') << m << '-' << std::setw(2) << std::setfill('0') << d;
	concatenated = conc.str();
	return (concatenated);
}

float   BitcoinExchange::get_exchange_rate(int found)
{
    std::string exchange_rate;
    std::string::iterator it = this->_data.begin() + found;  
    std::string::iterator last;

   while (it != this->_data.end() && *it != ',')
        it++;
    last = it;
    while (last != this->_data.end() && *last != '\n')
        last++;
    exchange_rate = std::string(++it,last);
    return (stringToFloat(exchange_rate));
    
}

int	BitcoinExchange::checkYear(std::string year)
{
	int	y = atoi(year.c_str());

	if (y > 2022 || y < 2009)
	{
		std::cout << "Error: Year out of range => " << year << std::endl;
		return (-1);
	}
	return (0);
}

int	BitcoinExchange::checkMonth(std::string month)
{
	int	m = atoi(month.c_str());

	if (m > 12 || m < 1)
	{
		std::cout << "Error: Month out of range => " << month << std::endl;
		return (-1);
	}
	return (0);
}

int	BitcoinExchange::checkDay(std::string day)
{
	int	d = atoi(day.c_str());

	if (d > 31 || d < 1)
	{
		std::cout << "Error: Day out of range => " << day << std::endl;
		return (-1);
	}
	return (0);
}

int     BitcoinExchange::date_exist(std::map<int, std::vector<std::string>>::iterator Mit)
{
    std::string date;
    std::size_t found;

    date = Mit->second[0] + "-" + Mit->second[1] + "-" + Mit->second[2];
    if (checkYear(Mit->second[0]) == -1 || checkMonth(Mit->second[1]) == -1 || checkDay(Mit->second[2]) == -1)
        return (0);
    found = this->_data.find(date);
    if (found != std::string::npos)
    {
        float result = get_exchange_rate(found) * stringToFloat(Mit->second[3]);
        std::cout << green << date << " => " << std::fixed << std::setprecision(2) << Mit->second[3] << " = " << result << std::endl;
    }
    else
    {
        while (found == std::string::npos)
        {
            date = decreaseDate(date);
            found = this->_data.find(date);
        }
        std::cout << yellow << date << " => " << Mit->second[3] << " = " << get_exchange_rate(found) * stringToFloat(Mit->second[3]) << std::endl;

    }
    return (1);
}

void    BitcoinExchange::print_mapXdata( void )
{
    std::map<int,std::vector<std::string>>::iterator Mit;
    std::vector<std::string>::iterator Vit;

    for (Mit = this->_map.begin(); Mit != _map.end(); ++Mit) {
        Vit = Mit->second.begin();
        if (Vit + 1 != Mit->second.end() && stringToFloat(*(Vit + 1)) < 0) {
            std::cout << red << "Error: bad input => " << *Vit << std::endl;
        }
        else if (Vit + 3 != Mit->second.end() && stringToFloat(*(Vit + 3))  == -2) { //Ajouter si plus de 1000
            std::cout << red << "Error: not a positive number." << std::endl;
        }
        else if (Vit + 3 != Mit->second.end() && stringToFloat(*(Vit + 3)) == -3) { //Ajouter si plus de 1000
            std::cout << red << "Error: to large number." << std::endl;
        }
        else {
            date_exist(Mit);
        }
        
    }
}


BitcoinExchange::~BitcoinExchange()
{
    std::cout << red << "Default destructor call" << std::endl;
}