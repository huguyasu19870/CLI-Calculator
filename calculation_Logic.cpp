#include <stdexcept>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include "operation.h"
#include "input_cleaner.h"
#include "calculation_Logic.h"

std::vector<std::string> CalculationLogic::calcLogic(const std::vector<std::string> &input){
    TypeConvert TC;
    SimpleOperation SO;
    std::string currentCalc;
    int calcTemp;
    #ifdef DEBUG
        for(const auto& elem : input){
            std::cout << "[Debug] function calcLogic's input components is " << elem << std::endl;
        }
    #endif // DEBUG
    //std::cout << "[Debug] function calcOps's variable compLoc is :" << compLoc << std::endl;


    std::vector<std::string> inputVector = input;
    std::vector<std::string> tempVector;
    tempVector.reserve(input.size());
    auto factorialFind = std::find(inputVector.begin(), inputVector.end(), "!");
    #ifdef DEBUG
                std::cout << 0 << std::endl;
    #endif // DEBUG
    if(factorialFind != inputVector.end()){
        for(std::size_t i = 0; i < inputVector.size(); i++){
            /*
            #ifdef DEBUG
                std::cout << "fact " << i << '|' << inputVector[i]<< std::endl;
            #endif // DEBUG
            */
            currentCalc = inputVector[i];
            if(currentCalc == "!"){
                calcTemp = SO.factorialOp(TC.letterToInt(inputVector[i-1]));
                tempVector.push_back(std::to_string(calcTemp));
            } else {
                if(i+1 < inputVector.size()){
                    if(inputVector[i+1] != "!"){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == inputVector.size()-1){
                    if(inputVector[i] != "!"){
                        tempVector.push_back(inputVector[i]);
                    }
                }
            }
        }
        inputVector.swap(tempVector);
        tempVector.clear();
    }
    auto expFind = std::find(inputVector.begin(), inputVector.end(), "^");
    #ifdef DEBUG
        std::cout << 10 << std::endl;
    #endif // DEBUG
    if(expFind != inputVector.end()){
        for(std::size_t i = 0; i < inputVector.size(); i++){
            /*
            #ifdef DEBUG
                std::cout << "exp " << i << '|' << inputVector[i]<< std::endl;
            #endif // DEBUG
            */
            currentCalc = inputVector[i];
            if(currentCalc == "^"){
                calcTemp = SO.exponentOp(TC.letterToInt(inputVector[i-1]), TC.letterToInt(inputVector[i+1]));
                tempVector.push_back(std::to_string(calcTemp));
                i++;
            } else {
                if((i+1 < inputVector.size()) && (i != 0)){
                    if((inputVector[i-1] != "^") && (inputVector[i+1] != "^")){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == 0){
                    if(inputVector[i+1] != "^"){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == inputVector.size()-1){
                    if(inputVector[i-1] != "^"){
                        tempVector.push_back(inputVector[i]);
                    }
                }
            }
        }
        inputVector.swap(tempVector);
        tempVector.clear();
    }

    auto multiFind = std::find(inputVector.begin(), inputVector.end(), "*");
    auto divFind = std::find(inputVector.begin(), inputVector.end(), "/");
    #ifdef DEBUG
        std::cout << 20 << std::endl;
    #endif // DEBUG
    if((multiFind != inputVector.end()) || (divFind != inputVector.end())){
        for(std::size_t i = 0; i < inputVector.size(); i++){
            /*
            #ifdef DEBUG
                std::cout << "muldiv " << i << '|' << inputVector[i] << std::endl;
            #endif // DEBUG
            */
            currentCalc = inputVector[i];
            if(currentCalc == "*"){
                calcTemp = TC.letterToInt(inputVector[i-1]) * TC.letterToInt(inputVector[i+1]);
                tempVector.push_back(std::to_string(calcTemp));
                i++;
            } else if(currentCalc == "/"){
                try{
                    if(inputVector[i+1] == "0"){
                        throw std::invalid_argument("Division by zero is not defined.");
                    }
                    calcTemp = TC.letterToInt(inputVector[i-1]) / TC.letterToInt(inputVector[i+1]);
                } catch (const std::invalid_argument &e){
                    return (tempVector = {"$error", "ZeroDivision"});
                }
                tempVector.push_back(std::to_string(calcTemp));
                i++;
            } else {
                if((i+1 < inputVector.size()) && (i != 0)){
                    if((inputVector[i-1] != "*") && (inputVector[i-1] != "/") && (inputVector[i+1] != "*") && (inputVector[i+1] != "/")){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == 0){
                    if((inputVector[i+1] != "*") && (inputVector[i+1] != "/")){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == inputVector.size()-1){
                    if((inputVector[i-1] != "*") && (inputVector[i-1] != "/")){
                        tempVector.push_back(inputVector[i]);
                    }
                }
                if(i >= inputVector.size()){
                    break;
                }
            }
        }
        inputVector.swap(tempVector);
        tempVector.clear();
    }
    auto addFind = std::find(inputVector.begin(), inputVector.end(), "+");
    auto subFind = std::find(inputVector.begin(), inputVector.end(), "-");
    #ifdef DEBUG
        std::cout << 30 << std::endl;
    #endif // DEBUG
    if((addFind != inputVector.end()) || (subFind != inputVector.end())){
        for(std::size_t i = 0; i < inputVector.size(); i++){
            /*
            #ifdef DEBUG
                std::cout << "addsub " << i << '|' << inputVector[i]<< std::endl;
            #endif // DEBUG
            */
            currentCalc = inputVector[i];
            if(currentCalc == "+"){
                calcTemp = TC.letterToInt(inputVector[i-1]) + TC.letterToInt(inputVector[i+1]);
                tempVector.push_back(std::to_string(calcTemp));
                i++;
            } else if(currentCalc == "-"){
                calcTemp = TC.letterToInt(inputVector[i-1]) - TC.letterToInt(inputVector[i+1]);
                tempVector.push_back(std::to_string(calcTemp));
                i++;
            } else {
                if((i+1 < inputVector.size()) && (i != 0)){
                    if((inputVector[i-1] != "+") && (inputVector[i-1] != "-") && (inputVector[i+1] != "+") && (inputVector[i+1] != "-")){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == 0){
                    if((inputVector[i+1] != "+") && (inputVector[i+1] != "-")){
                        tempVector.push_back(inputVector[i]);
                    }
                } else if(i == inputVector.size()-1){
                    if((inputVector[i-1] != "+") && (inputVector[i-1] != "-")){
                        tempVector.push_back(inputVector[i]);
                    }
                }
            }
        }
        inputVector.swap(tempVector);
        tempVector.clear();
    }

    #ifdef DEBUG
        std::cout << 40 << std::endl;
    #endif // DEBUG
    return inputVector;
}

std::vector<std::string> CalculationLogic::singleComparisonLogic(std::vector<std::string> input){
    TypeConvert TC;
    std::vector<std::string> comparisonResult;
    comparisonResult.resize(4);
    int result1 = TC.letterToInt(input[0]);
    int result2 = TC.letterToInt(input[2]);
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
