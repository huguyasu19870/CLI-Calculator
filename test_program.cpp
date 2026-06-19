#include "test_program.h"
#include <string>
#include <array>
#include <stdexcept>
#include <iostream>

std::array<std::string, 5> calcTest::simpleIntegerOperationTestCases(int testOps){
    std::array<std::string, 5> additionCase = {"2+2", "75+96", "279+338", "6789+1245","27985+75831"};
    std::array<std::string, 5> subtractionCase = {"7-6","10-24","305-208","5780-3489","70935-64325"};
    std::array<std::string, 5> multiplicationCase = {"3*8", "13*75", "706*973", "4608*6703", "10937*43795"};
    std::array<std::string, 5> divisionCase = {"6/2", "35/5", "288/4", "5075/5", "59732/2"};
    std::array<std::string, 5> exponentCase = {"4^2", "20^3", "243^3", "3876^2", "10342^2"};
    std::array<std::string, 5> factorialCase = {"2!", "4!", "7!", "10!", "12!"};
    std::array<std::string, 5> simpleComparisonCase = {"7<9", "75<=42", "94>150", "76>=37", "2778=377"};
    std::array<std::string, 5> calcComparisonCase = {"7+6<9*6", "16*27<=7!", "24^7>273*102", "6!>=75*30", "1783+1094=73*25"};
    std::array<std::string, 5> result;
    switch(testOps){
    case 0:
        result = factorialCase;
        break;
    case 1:
        result = exponentCase;
        break;
    case 2:
        result = multiplicationCase;
        break;
    case 3:
        result = divisionCase;
        break;
    case 4:
        result = additionCase;
        break;
    case 5:
        result = subtractionCase;
        break;
    case 6:
        result = simpleComparisonCase;
        break;
    case 7:
        result = calcComparisonCase;
        break;
    }
    return result;
}
std::array<int, 5> calcTest::simpleIntegerOperationTestAnswer(int testOps){
    std::array<int, 5> additionAnswer = {4,171, 617, 8034,103816};
    std::array<int, 5> subtractionAnswer = {1, -14, 97, 2291, 6610};
    std::array<int, 5> multiplicationAnswer = {24, 975, 686938, 30887424, 478985915};
    std::array<int, 5> divisionAnswer = {3, 7, 72, 1015, 29866};
    std::array<int, 5> exponentAnswer = {16, 8000, 14348907, 15023376, 106956964};
    std::array<int, 5> factorialAnswer = {2, 24, 5040, 3628800, 479001600};
    std::array<int, 5> simpleComparisonAnswer = {1, 0, 0, 1, 0};
    std::array<int, 5> calcComparisonAnswer = {1, 1, 1, 0, 0};
    std::array<int, 5> result;
    switch(testOps){
    case 0:
        result = factorialAnswer;
        break;
    case 1:
        result = exponentAnswer;
        break;
    case 2:
        result = multiplicationAnswer;
        break;
    case 3:
        result = divisionAnswer;
        break;
    case 4:
        result = additionAnswer;
        break;
    case 5:
        result = subtractionAnswer;
        break;
    case 6:
        result = simpleComparisonAnswer;
        break;
    case 7:
        result = calcComparisonAnswer;
        break;
    }
    return result;
}

std::array<bool, 5> calcTest::simpleIntegerComparisonTestAnswer(int testOps){
    std::array<bool, 5> simpleComparisonAnswer = {true, false, false, true, false};
    std::array<bool, 5> calcComparisonAnswer = {false, false, false, true, false};
    std::array<bool, 5> result;
    switch(testOps){
    case 6:
        result = simpleComparisonAnswer;
        break;
    case 7:
        result = calcComparisonAnswer;
        break;
    }
    return result;
}

void calcTest::finalTestValidation(){
    std::array<bool, 8> testResult = calcTest::getSimpleResultArray();
    int falseDetect = -1;
    for(int i = 0; i < testResult.size(); i++){
        if(testResult[i] == false){
            falseDetect = i;
        }
    }
    std::string errorLoc;
    if(falseDetect == 0){
        errorLoc = "Factorial";
    } else if(falseDetect == 1){
        errorLoc = "Exponent";
    } else if(falseDetect == 2){
        errorLoc = "Multiplication";
    } else if(falseDetect == 3){
        errorLoc = "Division";
    } else if(falseDetect == 4){
        errorLoc = "Addition";
    } else if(falseDetect == 5){
        errorLoc = "Subtraction";
    } else if(falseDetect == 6){
        errorLoc = "Comparison";
    } else if(falseDetect == 7){
        errorLoc = "Calculation comparison";
    }
    if(falseDetect == -1){
        std::cout << "Test result green." << std::endl;
    } else {
        std::cout << "Test result red." << std::endl;
        std::cout << "Error trippied at " << errorLoc << std::endl;
    }
    calcTest::setFinishClock();
    auto start = calcTest::getStartClock();
    auto finish = calcTest::getFinishClock();
    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    std::cout << "Test Duration is " << elapsedTime << "ms." << std::endl;
}
