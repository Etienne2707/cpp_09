#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <unistd.h>
#include <utility>
#include <string.h>
#include <deque>
const std::string red = "\033[0;31m";
const std::string green = "\033[1;32m";
const std::string yellow = "\033[1;33m";
const std::string cyan = "\033[0;36m";
const std::string magenta = "\033[0;35m";
const std::string reset = "\033[0m";


class PmergeMe
{
private:
    bool _isodd;
    int _odd;
public:
    PmergeMe(/* args */);
    PmergeMe(char **unsorted);
    ~PmergeMe();
    int     pmergeme(char **argv);
void    print_list(std::list<int> right);
std::list<int>  get_list(char **argv);
void    SortThePair(std::list<int>& list);
void    MergeSort(std::list<int>::iterator start, std::list<int>::iterator end);
void    Merge(std::list<int>::iterator start, std::list<int>::iterator middle ,std::list<int>::iterator end);
void   Check_Input(char **argv);
int	nextBlock(int n);
void binaryInsert(std::list<int>& X, std::list<int>::iterator end);


//DEQUE
void    MergeSort(std::deque<int>::iterator start, std::deque<int>::iterator end);
std::deque<int>  get_deque(char **argv);
void	binaryInsert(std::deque<int>& X, std::deque<int>::iterator end);
void    Merge(std::deque<int>::iterator start, std::deque<int>::iterator middle ,std::deque<int>::iterator end);
void    SortThePair(std::deque<int>& list);
void    print_deque(std::deque<int> right);

    class InputError : public std::exception
    {
    public:
            virtual const char * what() const throw();
    };



};







#endif