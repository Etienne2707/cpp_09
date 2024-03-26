#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(char *str)
{
    std::cout << yellow << "Parametric constructor call" << reset <<  std::endl;
    set_file(str);
    //set_data();
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

int BitcoinExchange::check_format(std::string line)
{
    std::string::iterator it;

    if (line.size() < 13)
        return (-1);
    for (it = line.begin(); it != line[4] ;)
}


int BitcoinExchange::set_file(char *str)
{
    std::ifstream inputFile(str);
    std::string line;
    std::string output;
    //int number;

    if (!inputFile.is_open())
    {
        std::cerr << red << "Erreur lors de l'ouverture du fichier." << reset << std::endl;
        return (-1);
    }
    while (std::getline(inputFile,line))
    {
        if (!check_format(line));
        for (std::string::iterator it=line.begin(); it!=line.end() && *it != '|'; ++it)
        {
            output += *it;
        }
    }
    std::cout << green << output << reset << std::endl;
    inputFile.close();
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
    std::cout << cyan << this->_data << reset << std::endl;
    inputFile.close();
    return (1);
}



BitcoinExchange::~BitcoinExchange()
{
    std::cout << red << "Default destructor call" << std::endl;
}