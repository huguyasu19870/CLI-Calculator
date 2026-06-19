#include <stdexcept>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include "operation.h"
#include "input_cleaner.h"
#include "calculation_Logic.h"

std::vector<std::string> CalculationLogic::calcLogic(std::vector<std::string> input){
    TypeConvert TypeConvert;
    inputOrganization inputOrganization;
    SimpleOperation SimpleOperation;
    unsigned long long int compLoc = inputOrganization.getComparisonLocation();
    bool isDoneProcessing = false;
    bool isFirstHalf;
    std::string currentCalc;
    unsigned long long int calcStep = 0;
    int calc1;
    int calc2;
    int calcTemp;
    CalculationLogic::setCalcOps(0);
    int calcOps = CalculationLogic::getCalcOps();
    //std::cout << "[Debug] function calcOps's variable compLoc is :" << compLoc << std::endl;
    //std::cout << "[Debug] function calcOps's variable calcStep is : " << calcStep << std::endl;
    //std::cout << "[Debug] function calcOps's variable calcOps is : " << calcOps << std::endl;
    isFirstHalf = calcStep < compLoc;
    while(!isDoneProcessing){
    startCalc:
        //I have tried to do smart thing and minimize the amount of calculation by doing some circus routine.
        //I was not that smart or knowledgeable, so I am brute-forcing the result out of this.

        //std::cout << "[Debug] function calcLogic's variable calcOps is : " << calcOps << std::endl;
        //std::cout << "[Debug] function calcLogic's variable calcStep is : " << calcStep << std::endl;
        if(calcStep >= input.size()){
            /*
            std::cout << "[Debug] function calcLogic's variable calcStep at oor is : " << calcStep << std::endl;
            std::cout << "[Debug] function calcLogic's variable calcOps at oor is : " << calcOps << std::endl;
            std::cout << "[Debug] function calcLogic's variable input's size at oor is : " << input.size() << std::endl;
            */
            break;
        }
        currentCalc = input.at(calcStep);
        #ifdef DEBUG
        std::cout << "[Debug] function calcLogic's variable currentCalc is: " << currentCalc << std::endl;
        #endif // DEBUG
        if((currentCalc == "!") && (calcOps == 0)){
            calcTemp = SimpleOperation.factorialOp(TypeConvert.letterToInt(input[calcStep-1]));
            input[calcStep-1] = std::to_string(calcTemp);
            input.erase(input.begin() + calcStep);
            if((isFirstHalf) || (compLoc == 0)){
                calcStep -= 1;
            } else {
                calcStep -= 2;
            }
        } else if((currentCalc == "^") && (calcOps == 1)){
            calc1 = TypeConvert.letterToInt(input[calcStep-1]);
            calc2 = TypeConvert.letterToInt(input[calcStep+1]);
            calcTemp = SimpleOperation.exponentOp(calc1, calc2);
            input[calcStep-1] = std::to_string(calcTemp);
            input.erase(input.begin() + calcStep);
            input.erase(input.begin() + calcStep);
            if((isFirstHalf) || (compLoc == 0)){
                calcStep -= 1;
            } else {
                calcStep -= 2;
            }
        } else if((calcOps == 2) && ((currentCalc == "*") || (currentCalc == "/"))){
            calc1 = TypeConvert.letterToInt(input[calcStep-1]);
            calc2 = TypeConvert.letterToInt(input[calcStep+1]);
            if(currentCalc == "*"){
                calcTemp = calc1 * calc2;
            } else if(currentCalc == "/"){
                if(calc2 == 0){
                    std::cout << "Attempted to Divide by Zero.";
                }
                calcTemp = calc1 / calc2;
            }
            input[calcStep-1] = std::to_string(calcTemp);
            input.erase(input.begin() + calcStep);
            input.erase(input.begin() + calcStep);
            if((isFirstHalf) || (compLoc == 0)){
                calcStep -= 1;
            } else {
                calcStep -= 2;
            }
        } else if((calcOps == 3) && ((currentCalc == "+") || (currentCalc == "-"))){
            calc1 = TypeConvert.letterToInt(input[calcStep-1]);
            calc2 = TypeConvert.letterToInt(input[calcStep+1]);
            if(currentCalc == "+"){
                calcTemp = calc1 + calc2;
            } else if(currentCalc == "-"){
                calcTemp = calc1 - calc2;
            }
            input[calcStep-1] = std::to_string(calcTemp);
            //std::cout << "[Debug] function calcLogic's input vector's at calcStep-1 is: " << input[calcStep-1] << std::endl;
            input.erase(input.begin() + calcStep);
            input.erase(input.begin() + calcStep);
            if((isFirstHalf) || (compLoc == 0)){
                calcStep -= 1;
            } else {
                calcStep -= 2;
            }
        }
        if((currentCalc == "<") || (currentCalc == "<=") || (currentCalc == ">") || (currentCalc == ">=") || (currentCalc == "~=") || (currentCalc == "=")){
            compLoc = calcStep;
        }
        //std::cout << "[Debug] function calcLogic's variable calcTemp is: " << calcTemp << std::endl;
        //std::cout << "[Debug] function calcLogic's variable isFirstHalf is: " << isFirstHalf << std::endl;
        //std::cout << "[Debug] function calcLogic's variable calcStep is: " << calcStep << std::endl;
        //std::cout << "[Debug] function calcLogic's variable compLoc is: " << compLoc<< std::endl;
        if(isFirstHalf && (calcStep == compLoc) && (calcOps < 3)){
            calcStep = 0;
            calcOps++;
            CalculationLogic::incrementCalcOps();
        } else if(isFirstHalf && (calcStep == compLoc) && (calcOps == 3)){
            isFirstHalf = false;
            calcOps = 0;
            CalculationLogic::setCalcOps(0);
        } else if((!isFirstHalf) && (calcStep >= (input.size()-1)) && (calcOps < 3)){
            calcStep = compLoc;
            calcOps++;
            CalculationLogic::incrementCalcOps();
        } else if((!isFirstHalf) && (calcStep >= (input.size()-1)) && (calcOps == 3)){
            isDoneProcessing = true;
            calcOps = 0;
            CalculationLogic::setCalcOps(0);
        }
        if(calcStep >= input.size()){
            isDoneProcessing = true;
        }
        if(isDoneProcessing && (compLoc != 0)){
            CalculationLogic::setCalcOps(4);
        }
        if((calcStep < ULLONG_MAX) && (input.size() > 1)){
            calcStep++;
        } else {
            break;
        }
    }
    #ifdef DEBUG
    std::cout << "[Debug] function calcLogic's first value of output is: " << input[0] << std::endl;
    if(input.size() >= 3){
        std::cout << "[Debug] function calcLogic's second value of output is: " << input[1] << std::endl;
        std::cout << "[Debug] function calcLogic's third value of output is: " << input[2] << std::endl;
    }
    #endif // DEBUG
    return input;
}

std::vector<std::string> CalculationLogic::singleComparisonLogic(std::vector<std::string> input){
    TypeConvert TypeConvert;
    std::vector<std::string> comparisonResult;
    comparisonResult.resize(4);
    int result1 = TypeConvert.letterToInt(input[0]);
    int result2 = TypeConvert.letterToInt(input[2]);
    std::string compOp = input[1];
    bool compResult;
    if(compOp == "<"){
        compResult = result1 < result2;
    } else if((compOp == "<=") || (compOp == "=<")){
        compResult = result1 <= result2;
    } else if(compOp == ">"){
        compResult = result1 > result2;
    } else if((compOp == ">=") || (compOp == "=>")){
        compResult = result1 >= result2;
    } else if((compOp == "=") || (compOp == "==")){
        compResult = result1 == result2;
    } else if(compOp == "!="){
        compResult = result1 != result2;
    } else if(compOp == "~="){
        int digits1 = input[0].length();
        int digits2 = input[2].length();
        int roudingDigit = digits2-1;
        if(roudingDigit > 0){
            compResult = ((digits2+(roudingDigit*5)) > digits1) && ((digits2-(roudingDigit*5)) < digits1);
        } else if(roudingDigit == 0){
            compResult = ((digits2+(0.5f)) > digits1) && ((digits2-(0.5f)) < digits1);
        }
    }
    comparisonResult[0] = std::to_string(result1);
    comparisonResult[2] = std::to_string(result2);
    comparisonResult[1] = compOp;
    comparisonResult[3] = std::to_string(static_cast<int>(compResult));
    return comparisonResult;
}
