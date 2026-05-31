#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
#include <vector>
#include <string>

class SimpleOperation{
public:
    int factorialOp(int a);
    int exponentOp(int a, int b);
};
class Comparison{
public:
};
class TypeConvert{
public:
    int letterToInt(const std::string &input);
    int letterToInt(const char &input);
};

#endif // OPERATION_H_INCLUDED
