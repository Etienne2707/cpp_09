#include "PmergeMe.hpp"
#include <ctime>

PmergeMe::PmergeMe(/* args */)
{
    std::cout << yellow << "Default Constructor call" << std::endl;
}

PmergeMe::PmergeMe(char **unsorted) : _isodd(false), _odd(0)
{
    std::cout << yellow << "Parametric Constructor call" << std::endl;
    pmergeme(unsorted);
}


PmergeMe::~PmergeMe()
{
    std::cout << red << "Destructor call" << std::endl;
}

//LIST

std::list<int>  PmergeMe::get_list(char **argv)
{
    std::list<int> list;
    
    for (int i = 0;argv[i] != 0;i++)
    {
        int result = atoi(argv[i]);
        if (result < 0)
            throw PmergeMe::InputError();
        list.push_back(result);
    }
    return (list);
}

void    PmergeMe::print_list(std::list<int> right)
{
    std::list<int>::iterator rit;

    for (rit = right.begin();rit != right.end();rit++)
    {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
}

int	PmergeMe::nextBlock(int n)
{
	int	size = 2;
	int	prev = 2;
	int	tmp;

	for (int i = 1; i < n; i++)
	{
		tmp = size;
		size += prev * prev;
		prev = tmp;
	}
	return size;
}

void	PmergeMe::binaryInsert(std::list<int>& List, std::list<int>::iterator end)
{
	std::list<int>	tmp;
	std::list<int>::iterator	to_insert, range_end;
	std::list<int>::iterator	start = List.begin();

	tmp.push_back(*start);
	for (std::list<int>::iterator it = start; it != end; it++)
		tmp.push_back(*(++it));
	if (std::distance(start, end) < 2)
		return;
	std::advance(start, 2);

	range_end = tmp.begin();
	std::advance(range_end, 4);
	int blockSize = 2;
	for (int i = 1; std::distance(start, end) > blockSize * 2; i++)
	{
		to_insert = start;
		std::advance(to_insert, blockSize * 2);
		while (to_insert != start)
		{
			std::advance(to_insert, -2);
			tmp.insert(std::lower_bound(tmp.begin(), range_end, *to_insert), *to_insert);
			range_end--;
		}
		std::advance(start, blockSize * 2);
		std::advance(range_end, blockSize);
		blockSize = nextBlock(i);
		std::advance(range_end, blockSize);
	}
	to_insert = end;
	range_end = tmp.end();
	while (to_insert != start)
	{
		std::advance(to_insert, -2);
		tmp.insert(std::lower_bound(tmp.begin(), range_end, *to_insert), *to_insert);
		range_end--;
	}

	if (end != List.end())
		tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), *end), *end);
    to_insert = start;
    if (this->_isodd == true)
    {
		tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), this->_odd), this->_odd);
    }
	List.assign(tmp.begin(), tmp.end());
}


void    PmergeMe::Merge(std::list<int>::iterator start, std::list<int>::iterator middle ,std::list<int>::iterator end)
{
    std::list<int> mergedList;
    std::list<int>::iterator leftIter = start;
    std::list<int>::iterator rightIter = middle;
    
    while (leftIter != middle && rightIter != end) {
        if (*leftIter < *rightIter) {
            mergedList.push_back(*leftIter);
            leftIter++;
        } else {
            mergedList.push_back(*rightIter);
            rightIter++;
        }
    }
    
    mergedList.insert(mergedList.end(), leftIter, middle);
    mergedList.insert(mergedList.end(), rightIter, end);
    
    std::list<int>::iterator mergeIter = mergedList.begin();
    for (std::list<int>::iterator it = start; it != end; ++it, ++mergeIter) {
        *it = *mergeIter;
    }
}


void    PmergeMe::MergeSort(std::list<int>::iterator start, std::list<int>::iterator end)
{
    if (std::distance(start,end) <= 1) {return ;}
    
    std::list<int>::iterator middle = start;
    std::advance(middle, (std::distance(start, end) / 2));
    MergeSort(start,middle);
    MergeSort(middle,end);
    Merge(start,middle,end);
    
}

void    PmergeMe::SortThePair(std::list<int>& list)
{
    std::list<int>::iterator next;
    for (std::list<int>::iterator it = list.begin() ; it != list.end(); std::advance(it,2))
    {
        next = it;
        std::advance(next,1);
        if (*it > *next)
            std::iter_swap(it , next);
       
    }
}


//Deque

std::deque<int>  PmergeMe::get_deque(char **argv)
{
    std::deque<int> list;
    
    for (int i = 0;argv[i] != 0;i++)
    {
        int result = atoi(argv[i]);
        if (result < 0)
            throw PmergeMe::InputError();
        list.push_back(result);
    }
    return (list);
}

void    PmergeMe::print_deque(std::deque<int> right)
{
    std::deque<int>::iterator rit;

    for (rit = right.begin();rit != right.end();rit++)
    {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;
}

void	PmergeMe::binaryInsert(std::deque<int>& Deq, std::deque<int>::iterator end)
{
	std::deque<int>	tmp;
	std::deque<int>::iterator	to_insert;
	std::deque<int>::iterator	start = Deq.begin();

	tmp.push_back(*start);
	for (std::deque<int>::iterator it = start; it != end; it++)
		tmp.push_back(*(++it));
	if (std::distance(start, end) < 2)
		return;
	start += 2;
	int range_end = 4;
	int blockSize = 2;
	for (int i = 1; std::distance(start, end) > blockSize * 2; i++)
	{
		to_insert = start + blockSize * 2;
		while (to_insert != start)
		{
			std::advance(to_insert, -2);
			tmp.insert(std::lower_bound(tmp.begin(), tmp.begin() + range_end, *to_insert), *to_insert);
		}
		std::advance(start, blockSize * 2);
		range_end += blockSize;
		blockSize = nextBlock(i);
		range_end += blockSize;

	}
	to_insert = end;
	while (to_insert != start)
	{
		std::advance(to_insert, -2);
		tmp.insert(std::lower_bound(tmp.begin(), tmp.end() - range_end, *to_insert), *to_insert);
		range_end++;
	}

	if (end != Deq.end())
		tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), *end), *end);
    if (this->_isodd == true)
    {
		tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), this->_odd), this->_odd);
    }
	Deq.assign(tmp.begin(), tmp.end());
}


void    PmergeMe::Merge(std::deque<int>::iterator start, std::deque<int>::iterator middle ,std::deque<int>::iterator end)
{
    std::deque<int> mergedList;
    std::deque<int>::iterator leftIter = start;
    std::deque<int>::iterator rightIter = middle;
    
    while (leftIter != middle && rightIter != end) {
        if (*leftIter < *rightIter) {
            mergedList.push_back(*leftIter);
            leftIter++;
        } else {
            mergedList.push_back(*rightIter);
            rightIter++;
        }
    }

   // std::cout << "test : " ; print_deque(mergedList);
    
    mergedList.insert(mergedList.end(), leftIter, middle);
    mergedList.insert(mergedList.end(), rightIter, end);
    
    std::deque<int>::iterator mergeIter = mergedList.begin();
    for (std::deque<int>::iterator it = start; it != end; ++it, ++mergeIter) {
        *it = *mergeIter;
    }
}


void    PmergeMe::MergeSort(std::deque<int>::iterator start, std::deque<int>::iterator end)
{
    if (std::distance(start,end) <= 1) {return ;}
    
    std::deque<int>::iterator middle = start;
    std::advance(middle, (std::distance(start, end) / 2));
        MergeSort(start,middle);
    MergeSort(middle,end);
    Merge(start,middle,end);
    
}

void    PmergeMe::SortThePair(std::deque<int>& list)
{
    std::deque<int>::iterator next;
    for (std::deque<int>::iterator it = list.begin() ; it != list.end();)
    {
        next = it;
        std::advance(next,1);
        if (*it > *next)
            std::iter_swap(it , next);
        std::advance(it,2);
    }
}

//GLOBAL SCOPE

void    PmergeMe::Check_Input(char **argv)
{
    bool negative = false;
    bool positive = false;
    for (int i = 0; argv[i] != 0; i++)
    {
        int j = 0;
        if (argv[i][j] == '+')
            j++;
        while (argv[i][j] != '\0')
        {
            if (!std::isdigit(argv[i][j]))
                throw PmergeMe::InputError();
            j++;
        }
    }
}

const char * PmergeMe::InputError::what() const throw()
{
    return ("Input Error");
}

int     PmergeMe::pmergeme(char **argv)
{
    {
        clock_t start = clock();
        Check_Input(argv);
        std::list<int> list = get_list(argv);  
        std::cout << "List Before : ";print_list(list);
        if((list.size()) % 2 != 0)
        {
            this->_isodd = true; this->_odd = list.back() ; list.pop_back();
        }
        SortThePair(list);
        binaryInsert(list,list.end());
        MergeSort(list.begin(),list.end());
        clock_t end = clock();
        double duration = (double)(end-start) * 1000 / CLOCKS_PER_SEC;
        std::cout << "List After : " ;print_list(list);
        std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << duration <<  "ms" << std::endl;
    }

    {
        clock_t start = clock();

        std::deque<int> deque = get_deque(argv);
        std::cout << "List Before : ";print_deque(deque);
        if (this->_isodd == true)
            deque.pop_back();
        SortThePair(deque);
        binaryInsert(deque,deque.end());
        MergeSort(deque.begin(),deque.end());
        clock_t end = clock();
        double duration = (double)(end-start) * 1000 / CLOCKS_PER_SEC;
        std::cout << "List After : " ;print_deque(deque);
        std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << duration <<  "ms" << std::endl;

    }

    return 1;
}


