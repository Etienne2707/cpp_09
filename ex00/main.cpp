#include "BitcoinExchange.hpp"


int main(int ac, char **argv)
{
    if (ac != 2)
        return (-1);
    BitcoinExchange test(argv[1]);

}