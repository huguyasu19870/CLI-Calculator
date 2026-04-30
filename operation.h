#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

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
    int letterToInt(std::string &input);
    int letterToInt(char &input);
};

#endif // OPERATION_H_INCLUDED
