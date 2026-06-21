#ifndef CALCULATION_LOGIC_H_INCLUDED
#define CALCULATION_LOGIC_H_INCLUDED
#include <vector>
#include <string>

class CalculationLogic{
public:
    std::vector<std::string> calcLogic(const std::vector<std::string> &input);
    std::vector<std::string> singleComparisonLogic(std::vector<std::string> input);
    int getCalcOps(){
        return calcOps;
    };
    void incrementCalcOps(){
        calcOps++;
    };
    void setCalcOps(int input){
        calcOps = input;
    };
private:
    int calcOps = 0;
    /*
    0 = Factorial
    1 = Exponent
    2 = Multiplication/Division
    3 = Addition/Subtraction
    4 = Comparison ; for now, maybe sent to -1, or maybe not need one to represent it.
    */
};

#endif // CALCULATION_LOGIC_H_INCLUDED
