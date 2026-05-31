#ifndef TEST_PROGRAM_H_INCLUDED
#define TEST_PROGRAM_H_INCLUDED
#include <string>
#include <array>

class calcTest{
public:
    void testValidation();
    void finalTestValidation();
    std::array<std::string, 5> simpleIntegerOperationTestCases(int testOps);
    std::array<int, 5> simpleIntegerOperationTestAnswer(int testOps);
    std::array<bool, 5> simpleIntegerComparisonTestAnswer(int testOps);
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
    std::array<bool, 5> getSimpleResultTempArray(){
        return simpleResultTempArray;
    };
    void setSimpleResultTempArray(std::array<bool, 5> inputArray){
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
    std::array<bool, 5> simpleResultTempArray = {0, 0, 0, 0, 0};
    std::array<bool, 8> simpleResultArray = {0, 0, 0, 0, 0, 0, 0, 0};
};

#endif // TEST_PROGRAM_H_INCLUDED
