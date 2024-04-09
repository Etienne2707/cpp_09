#include "RPN.hpp"

RPN::RPN(/* args */)
{
    std::cout << yellow << "Parametric constructor call" << reset << std::endl;
}

RPN::RPN(char *str) : _index(0)
{
    std::cout << yellow << "Parametric constructor call" << reset << std::endl;
    this->_expression = str;
    StartRPN();
}



int ERR()
{
    std::cout << red << "Wrong Input !" << std::endl;
    return (-1);
}

int RPN::Calculate(int first , int second , std::string::iterator & it)
{
    if (*it == '*')
        return (first * second);
    if (*it == '/')
        return (first / second);
    if (*it == '-')
        return (first - second);
    if (*it == '+')
        return (first + second);
    return (-1);
}

int    RPN::StackCalculate(std::string::iterator & it)
{
    int first;
    int second;
    int result = 0 ;
    if (*it >= '0' && *it <= '9')
    {
        int num = *it - '0';
        this->_rpn.push(num);
        this->_index++;
    }
    else if (*it == '+' ||  *it == '-' ||  *it == '/' ||  *it == '*')
    {
        if (this->_index < 2)
        {
            std::cout << _index << std::endl;
            return ERR();
        }
        second = this->_rpn.top();
        this->_rpn.pop();
        first = this->_rpn.top();
        this->_rpn.pop();
        std::cout << yellow << first << *it  << second << std::endl;
        this->_rpn.push(Calculate(first,second,it));
        this->_index++;
    }
    return (result);

}

int    RPN::StartRPN( void )
{
    std::string::iterator it = this->_expression.begin();

    while (it != this->_expression.end())
    {
        if ((*it < '0' || *it > '9' ) && *it != '+' &&  *it != '-' &&  *it != '/' &&  *it != '*' && *it != 32)
        {
            std::cout << (int)*it << std::endl;
            return ERR();
        }
        else if (*it == 32)
            it++;
        else if (*(it + 1) != 32 && it + 1 != this->_expression.end())
        {
            return ERR();
        }
        else
        {
            StackCalculate(it);
            it++;
        }
          
    }
    std::cout << this->_rpn.top() << std::endl;
    return (1);
}

RPN::~RPN()
{
    std::cout << red << "Default constructor call" << std::endl;
}


