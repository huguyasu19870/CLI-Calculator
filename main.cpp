#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <thread>
#include <chrono>
#include "main.h"
#include "operation.h"
#include "input_cleaner.h"

int main()
{
    inputOrganization inputOrganization;
    TypeConvert TypeConvert;
    SimpleOperation SimpleOperation;
    std::string inputValue;
emptyInput:
    std::cout << "Please input the equation." << std::endl;
    std::cin >> inputValue;
    if(inputValue.empty()){
        std::cout << "Provided input was empty." << std::endl;
        goto emptyInput;
    }
    inputValue = inputOrganization.inputCleaner(inputValue);
    if(inputValue.empty()){
        std::cout << "Provided input resolved into empty." << std::endl;
        goto emptyInput;
    }
    inputValue = inputOrganization.inputCleaner(inputValue);

    std::unordered_map<unsigned long long int, std::string> calcFlg = inputOrganization.calculationSpecifier(inputValue);
    bool isDoneProcessing = false;
    unsigned long long int calcStep = 0;
    int result1;
    int result2;
    int result;
    int calc1;
    int calc2;
    int calcTemp;
    std::string currentCalc;
    bool isFirstHalf;
//    std::unordered_map<unsigned long long int, unsigned long long int> location = inputOrganization.getOopLocation();
    unsigned long long int compLoc = inputOrganization.getComparisonLocation();
//    unsigned long long int delCount = 0;
    std::vector<std::string> calcFlg2;
    calcFlg2.reserve(calcFlg.size());
    for(unsigned long long int i = 0; i < calcFlg.size(); i++){
        calcFlg2.push_back(calcFlg.at(i));
        if(i == ULLONG_MAX){
            break;
        }
    }
    int calcOps = 0;
    /*
    0 = Factorial
    1 = Exponent
    2 = Multiplication/Division
    3 = Addition/Subtraction
    4 = Comparison ; for now, maybe sent to -1, or maybe not need one to represent it.
    */
    while(!isDoneProcessing){
        //I have tried to do smart thing and minimize the amount of calculation by doing some circus routine.
        //I was not that smart or knowledgeable, so I am brute-forcing the result out of this.
        isFirstHalf = calcStep < compLoc;
        currentCalc = calcFlg2[calcStep];
        /*
        try{
            calcPhase = location.at(calcStep);
            currentCalc = calcFlg.at(calcPhase);
        } catch (std::out_of_range){
            std::cout << "Attempted access to out of range unordered map element." << std::endl;
            std::cout << "Please contact the nearest software developer." << std::endl;
        }
        */
        if((currentCalc == "!") && (calcOps == 0)){
            calcTemp = SimpleOperation.factorialOp(TypeConvert.letterToInt(calcFlg2[calcStep-1]));
            calcFlg2[calcStep-1] = std::to_string(calcTemp);
            calcFlg2.erase(calcFlg2.begin() + calcStep);
            calcStep -= 1;
        } else if((currentCalc == "^") && (calcOps == 1)){
            calc1 = TypeConvert.letterToInt(calcFlg2[calcStep-1]);
            calc2 = TypeConvert.letterToInt(calcFlg2[calcStep+1]);
            calcTemp = SimpleOperation.exponentOp(calc1, calc2);
            calcFlg2[calcStep-1] = std::to_string(calcTemp);
            calcFlg2.erase(calcFlg2.begin() + calcStep, calcFlg2.begin() + calcStep+1);
            calcStep -= 1;
        } else if((calcOps == 2) && ((currentCalc == "*") || (currentCalc == "/"))){
            calc1 = TypeConvert.letterToInt(calcFlg2[calcStep-1]);
            calc2 = TypeConvert.letterToInt(calcFlg2[calcStep+1]);
            if(currentCalc == "*"){
                calcTemp = calc1 * calc2;
            } else if(currentCalc == "/"){
                calcTemp = calc1 / calc2;
            }
            calcFlg2[calcStep-1] = std::to_string(calcTemp);
            calcFlg2.erase(calcFlg2.begin() + calcStep, calcFlg2.begin() + calcStep+1);
            calcStep -= 1;
        } else if((calcOps == 3) && ((currentCalc == "+") || (currentCalc == "-"))){
            calc1 = TypeConvert.letterToInt(calcFlg2[calcStep-1]);
            calc2 = TypeConvert.letterToInt(calcFlg2[calcStep+1]);
            if(currentCalc == "+"){
                calcTemp = calc1 + calc2;
            } else if(currentCalc == "-"){
                calcTemp = calc1 - calc2;
            }
            calcFlg2[calcStep-1] = std::to_string(calcTemp);
            calcFlg2.erase(calcFlg2.begin() + calcStep, calcFlg2.begin() + calcStep+1);
            calcStep -= 1;
        }
        if(isFirstHalf && (calcStep == compLoc) && (calcOps < 3)){
            calcStep = 0;
            calcOps++;
        } else if(isFirstHalf && (calcStep == compLoc) && (calcOps == 3)){
            isFirstHalf = false;
            calcOps = 0;
        } else if((!isFirstHalf) && (calcStep == (calcFlg2.size()-1)) && (calcOps < 3)){
            calcStep = compLoc;
            calcOps++;
        } else if((!isFirstHalf) && (calcStep == (calcFlg2.size()-1)) && (calcOps == 3)){
            isDoneProcessing = true;
        }
        if((isDoneProcessing == true) && (compLoc != 0)){
            calcOps = 4;
        }
        if(calcStep < ULLONG_MAX){
            calcStep++;
        } else {
            break;
        }
    }
    if(calcOps == 4){
        std::string compOp = calcFlg2[1];
        result1 = TypeConvert.letterToInt(calcFlg2[0]);
        result2 = TypeConvert.letterToInt(calcFlg2[2]);
        bool compResult;
        if(compOp == "<"){
            compResult = result1 < result2;
        } else if((compOp == "<=")){
            compResult = result1 <= result2;
        } else if(compOp == ">"){
            compResult = result1 > result2;
        } else if((compOp == ">=")){
            compResult = result1 >= result2;
        } else if(compOp == "="){
            compResult = result1 == result2;
        } else if(compOp == "!="){
            compResult = result1 != result2;
        } else if(compOp == "~="){
            int digits1 = calcFlg2[0].length();
            int digits2 = calcFlg2[2].length();
            int roudingDigit = digits2-1;
            if(roudingDigit > 0){
                compResult = ((digits2+(roudingDigit*5)) > digits1) && ((digits2-(roudingDigit*5)) < digits1);
            } else if(roudingDigit == 0){
                compResult = ((digits2+(0.5f)) > digits1) && ((digits2-(0.5f)) < digits1);
            }
        }
        std::cout << "Result of comparison" << inputValue << " is simplified to" << std::endl;
        std::cout << result1 << compOp << result2 << std::endl;
        std::cout << "Which is " << compResult << std::endl;
    } else {
        result = TypeConvert.letterToInt(calcFlg2[0]);
        std::cout << "Result of " << inputValue << " is" << std::endl << result << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}
