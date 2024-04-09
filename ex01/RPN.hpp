#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <string>
const std::string red = "\033[0;31m";
const std::string green = "\033[1;32m";
const std::string yellow = "\033[1;33m";
const std::string cyan = "\033[0;36m";
const std::string magenta = "\033[0;35m";
const std::string reset = "\033[0m";\

class RPN
{
private:
    RPN();
    std::string _expression;
    std::stack<int> _rpn;
    int _index;
public:
    RPN(char *str);
    ~RPN();
    int    StartRPN( void );
    int    StackCalculate( std::string::iterator & it );
    int Calculate(int first , int second , std::string::iterator & it );
};

#endif
