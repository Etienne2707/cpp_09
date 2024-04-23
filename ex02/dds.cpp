std::deque<int>  PmergeMe::get_list(char **argv)
{
    std::deque<int> list;
    
    for (int i = 0;argv[i] != 0;i++)
    {
        list.push_back(atoi(argv[i]));
    }
    return (list);
}

void    PmergeMe::print_list(std::deque<int> right)
{
    std::deque<int>::iterator rit;

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

void	PmergeMe::binaryInsert(std::deque<int>& X, std::deque<int>::iterator end)
{
	std::deque<int>	S;
	std::deque<int>::iterator	to_insert, range_end;
	std::deque<int>::iterator	start = X.begin();
	int	blockSize;

	S.push_back(*start);
	for (std::deque<int>::iterator it = start; it != end; it++)
		S.push_back(*(++it));
	if (std::distance(start, end) < 2)
		return;
	std::advance(start, 2);

	range_end = S.begin();
	std::advance(range_end, 4);
	blockSize = 2;
	for (int i = 1; std::distance(start, end) > blockSize * 2; i++)
	{
		to_insert = start;
		std::advance(to_insert, blockSize * 2);
		while (to_insert != start)
		{
			std::advance(to_insert, -2);
			S.insert(std::lower_bound(S.begin(), range_end, *to_insert), *to_insert);
			range_end--;
		}
		std::advance(start, blockSize * 2);
		std::advance(range_end, blockSize);
		blockSize = nextBlock(i);
		std::advance(range_end, blockSize);
	}
	to_insert = end;
	range_end = S.end();
	while (to_insert != start)
	{
		std::advance(to_insert, -2);
		S.insert(std::lower_bound(S.begin(), range_end, *to_insert), *to_insert);
		range_end--;
	}

	if (end != X.end())
		S.insert(std::lower_bound(S.begin(), S.end(), *end), *end);
	X.assign(S.begin(), S.end());
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
    //std::cout << "Distance :" << (std::distance(start, end) / 2) << std::endl;
    MergeSort(start,middle);
    MergeSort(middle,end);
    //std::cout << "Start =" << *start << "Middle : " << *middle << "End :" << *end << std::endl;
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