#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <thread>
#include <chrono>
#include <array>
#include <algorithm>
#include <cstddef>
#include "main.h"
#include "operation.h"
#include "input_cleaner.h"
#include "test_program.h"
#include "calculation_Logic.h"

int main()
{
    InputOrganization inOrg;
    TypeConvert TC;
    CalculationLogic CL;
    CalcTest CT;

    std::string inputValue;
    bool debugMode = false;
    bool testMode = false;
    bool shouldEnd = false;
    #ifdef DEBUG
        debugMode = true;
    #endif // DEBUG
reInput:
    std::cout << "Please input the equation." << std::endl;
    std::cout << "If you want to end this program, type \"Quit \" or \"Exit\"." << std::endl;
    std::cin >> inputValue;
    if(inputValue.empty()){
        std::cout << "Provided input was empty." << std::endl;
        goto reInput;
    } else if((inputValue == "exit") || (inputValue == "Exit") || (inputValue == "quit") || (inputValue == "Quit")){
        std::cout << "Exit command received.";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        shouldEnd = true;
        return 0;
    } else if((inputValue == "test") || (inputValue == "Test")){
        CT.setStartClock();
        testMode = true;
        goto testInit;
    }
    inputValue = inOrg.inputCleaner(inputValue);
    if(inputValue.empty()){
        std::cout << "Provided input resolved into empty." << std::endl;
        goto reInput;
    }
    inputValue = inOrg.inputCleaner(inputValue);
    //Above codes essentially captures the programming into while loop if input is empty.


    if(false){
nullOutput:
            std::cout << "Variable testPhase pointed outside of array range." << std::endl;
            return 1;
        }
testInit:
    if(testMode){
        int testOp = CT.getTestOps();
        int testPhase = CT.getTestNum();
        int testType = CT.getTestType();
        std::array<std::string, 5> testArray;
        if(testType == 0){
            testArray = CT.simpleIntegerOperationTestCases(testOp);
        }
        inputValue = testArray[testPhase];
    }
    std::unordered_map<std::size_t, std::string> calcFlg = inOrg.calculationSpecifier(inputValue);
//    std::unordered_map<unsigned long long int, unsigned long long int> location = inOrg.getOopLocation();
//    unsigned long long int delCount = 0;
    std::vector<std::string> calcFlg2 = inOrg.returnOrderedFormula(calcFlg);
    for(int i = 0; i < calcFlg2.size(); i++){
        std::string elem = calcFlg2[i];
        //std::cout << "[Debug] function main's elements of calcFlg2 is: " << elem << std::endl;
        if((elem == "<") || (elem == ">") || (elem == "=") || (elem == "~=") || (elem == ">=") || (elem == "<=")){
            inOrg.setComparisonLocation(i);
        }
    }
    int result1;
    int result2;
    int result;
    calcFlg2 = CL.calcLogic(calcFlg2);
    if(calcFlg2[0] == "null"){
        goto nullOutput;
    } else if(calcFlg2[0] == "$error"){
        if(calcFlg2[1] == "ZeroDivision"){
            std::cout << "Division by Zero happened." << std::endl;
            goto reInput;
        }
    }
    int calcOps = CL.getCalcOps();
    //std::cout << "[Debug] main function's variable calcOps is: " << calcOps << std::endl;

    if((calcOps == 4) && (!testMode)){
        std::vector<std::string> comparisonResultVector = CL.singleComparisonLogic(calcFlg2);
        std::string compOp = comparisonResultVector[1];
        result1 = TC.letterToInt(comparisonResultVector[0]);
        result2 = TC.letterToInt(comparisonResultVector[2]);
        bool compResult = static_cast<bool>(TC.letterToInt(comparisonResultVector[3]));
        std::string stringCompResult;
        if(compResult){
            stringCompResult = "true";
        } else {
            stringCompResult = "false";
        }
        std::cout << "Result of comparison " << inputValue << " is simplified to" << std::endl;
        std::cout << result1 << compOp << result2 << std::endl;
        std::cout << "Which is " << stringCompResult << std::endl << std::endl;
    } else if(!testMode) {
        result = TC.letterToInt(calcFlg2[0]);
        std::cout << "Result of " << inputValue << " is" << std::endl << result << std::endl << std::endl;
    } else {
        int testOp = CT.getTestOps();
        int testPhase = CT.getTestNum();
        int testType = CT.getTestType();
        std::string testResult = calcFlg2[0];
        if(testType == 0){
            std::array<int, 5> answerArray = CT.simpleIntegerOperationTestAnswer(testOp);
            int expTestResult = answerArray[testPhase];
            int actualTestResult;
            if(testOp < 6){
                actualTestResult = TC.letterToInt(calcFlg2[0]);
            } else if(testOp >= 6){
                std::vector<std::string> comparisonFullResult = CL.singleComparisonLogic(calcFlg2);
                actualTestResult = TC.letterToInt(comparisonFullResult[3]);
            }
            bool isResultEqual = expTestResult == actualTestResult;
            CT.insertSimpleResultTempArray(isResultEqual, testPhase);
            CT.incrementTestNum();
            testPhase++;
            if(testPhase == answerArray.size()){
                std::array<bool, 5> resultArray = CT.getSimpleResultTempArray();
                bool hasNegative = false;
                for(const bool& elem: resultArray){
                    if(!elem){
                        hasNegative = true;
                        break;
                    }
                }
                if(hasNegative){
                    CT.insertSimpleResultArray(false, testOp);
                } else {
                    CT.insertSimpleResultArray(true, testOp);
                }
                CT.setTestNum(0);
                CT.incrementTestOps();
                testOp++;
            }
            std::string comparisonResultString;
            if(isResultEqual){
                comparisonResultString = "true";
            } else {
                comparisonResultString = "false";
            }
            std::cout << "Test question is " << inputValue << "." << std::endl;
            std::cout << "Test question resolved to " << actualTestResult << "." << std::endl;
            std::cout << "Expected result is " << expTestResult << "." << std::endl;
            std::cout << "Which is " << comparisonResultString << "." << std::endl;
            std::cout << std::endl;
            if(testOp == 8){
                goto endTest;
            }

        }
        goto testInit;
    }
    if(!shouldEnd){
        goto reInput;
    }
    if(testMode){
endTest:
        CT.finalTestValidation();
    }
    return 0;
}
