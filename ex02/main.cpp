#include "PmergeMe.hpp"

int main(int ac , char **argv)
{
    if (ac < 2)
        return (1);
    argv += 1;
    try
    {
        PmergeMe test(argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (1);
}