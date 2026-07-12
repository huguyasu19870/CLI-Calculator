#ifndef TEST_PROGRAM_H_INCLUDED
#define TEST_PROGRAM_H_INCLUDED
#include <string>
#include <array>
#include <chrono>
#include <algorithm>

class CalcTest{
public:
    void testValidation();
    void finalTestValidation();
    std::array<std::string, 10> simpleIntegerOperationTestCases(int testOps);
    std::array<int, 10> simpleIntegerOperationTestAnswer(int testOps);
    void incrementTestNum(){
        testNum++;
    };
    void clearTestNum(){
        testNum = 0;
    };
    void setTestNum(int input){
        testNum = input;
    }
    int getTestNum(){
        return testNum;
    };
    void incrementTestOps(){
        testOps++;
    };
    void clearTestOps(){
        testOps = 0;
    };
    void setTestOps(int input){
        testOps = input;
    };
    int getTestOps(){
        return testOps;
    };
    int getTestType(){
        return testType;
    }
    void incrementTestType(){
        testType++;
    }
    void setTestType(int input){
        testType = input;
    }
    std::array<bool, 10> getSimpleResultTempArray(){
        return simpleResultTempArray;
    };
    void setSimpleResultTempArray(std::array<bool, 10> inputArray){
        simpleResultTempArray = inputArray;
    };
    void clearSimpleResultTempArray(){
        simpleResultTempArray = {false, false, false, false, false};
    }
    void insertSimpleResultTempArray(bool resultInput, int index){
        simpleResultTempArray[index] = resultInput;
    }
    std::array<bool, 8> getSimpleResultArray(){
        return simpleResultArray;
    };
    void setSimpleResultArray(std::array<bool, 8> inputArray){
        simpleResultArray = inputArray;
    }
    void insertSimpleResultArray(bool resultInput, int index){
        simpleResultArray[index] = resultInput;
    }
    void setStartClock(){
        startTime = std::chrono::system_clock::now();
    }
    void setFinishClock(){
        finishTime = std::chrono::system_clock::now();
    }
    std::chrono::system_clock::time_point getStartClock(){
        return startTime;
    }
    std::chrono::system_clock::time_point getFinishClock(){
        return finishTime;
    }
private:
    int testNum = 0;
    int testOps = 0;
    /*
    testOps are similar to main's calcOps, which determines the operation of the calculation.
    Difference is that in testOps, multiplication and division, and addition and subtraction are assigned the different number.
    ------------------------------
    0 = Factorial
    1 = Exponent
    2 = Multiplication
    3 = Division
    4 = Addition
    5 = Subtraction
    6 = Comparison(Non calculation)
    7 = Comparison(With calculation)
    */
    int testType = 0;
    std::array<bool, 10> simpleResultTempArray = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<bool, 8> simpleResultArray = {0, 0, 0, 0, 0, 0, 0, 0};
    inline static std::chrono::system_clock::time_point startTime;
    inline static std::chrono::system_clock::time_point finishTime;
};

#endif // TEST_PROGRAM_H_INCLUDED
