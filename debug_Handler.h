#ifndef DEBUG_HANDLER_H_INCLUDED
#define DEBUG_HANDLER_H_INCLUDED
#include <array>
#include <cstdint>
#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <algorithm>

enum class DebugSources : uint8_t{
    Main = 0,
    Operation = 1,
    InputCleaner = 2,
    CalcLogic = 3,
    TestProgram = 4
};
enum class OperationDebugTarget : uint8_t{
    Factorial = 0,
    Exponent = 1
};
enum class CalcLogicDebugTarget : uint8_t{
    CalcLogicInput = 0,
    FactorialLoopBegin = 1,
    ExponentLoopBegin = 3,
    MulDivLoopBegin = 5,
    AddSubLoopBegin = 7,
    FactorialLoopInput = 2,
    ExponentLoopInput = 4,
    MulDivLoopInput = 6,
    AddSubLoopInput = 8,
    CalcLoopEnd = 9
};

class DebugArea{
public:
    void enableDebugMode(){
        debugMode = true;
    }
    void disableDebugMode(){
        debugMode = false;
    }
    void confirmDebugMode();
    void askDebugMode(bool askDetail);
    void selectDebugMode(DebugSources input, bool mode);
    void operationDebugMode(OperationDebugTarget input, bool mode);
    void calcLogicDebugMode(CalcLogicDebugTarget input, bool mode);
    bool getDebugMode(){
        return debugMode;
    }
    std::array<std::vector<bool>, 5> getTotalList (){
        return totalList;
    }
    std::array<std::string,5> InvDebugSources = {"Main", "Operation","InputCleaner","CalcLogic","TestProgram"};
    std::vector<std::string> InvMainSources = {"Null"};
    std::vector<std::string> InvOperationDebugTarget = {"Factorial","Exponent"};
    std::vector<std::string> InvInputCleanerDebugTarget = {"Null"};
    std::vector<std::string> InvCalcLogicDebugTarget = {"CalcLogicInput","FactorialLoopBegin","FactorialLoopInput","ExponentLoopBegin","ExponentLoopInput","MulDivLoopBegin","MulDivLoopInput","AddSubLoopBegin","AddSubLoopInput","CalcLoopEnd"};
    std::vector<std::string> InvTestCalcDebugTarget = {"Null"};
    std::array<std::vector<std::string>,5> InvDebugTargetList = {InvMainSources, InvOperationDebugTarget, InvInputCleanerDebugTarget,InvCalcLogicDebugTarget,InvTestCalcDebugTarget};
    inline static std::array<bool, 5> debugCategory = {false, false, false, false, false};
private:
    inline static bool debugMode = false;
    inline static std::vector<bool> mainDebugCategory;
    inline static std::vector<bool> operationDebugCategory = {false, false};
    inline static std::vector<bool> inputCleanerDebugCategory;
    inline static std::vector<bool> calcLogicDebugCategory = {false, false, false, false, false, false, false, false, false, false};
    inline static std::vector<bool> testProgramDebugCategory;
    inline static std::array<std::vector<bool>, 5> totalList = {mainDebugCategory, operationDebugCategory, inputCleanerDebugCategory, calcLogicDebugCategory, testProgramDebugCategory};
    inline static std::vector<int> categorySize = {mainDebugCategory.size(),operationDebugCategory.size(),inputCleanerDebugCategory.size(),calcLogicDebugCategory.size(),testProgramDebugCategory.size()};
    inline static int maxCategoryLength = 10;
};

template<typename E, typename V>
class FlexibleVariableCout{
public:
    void variableDebugOutput(DebugSources category, E subCategory, V input){
        DebugArea DA;
        std::array<std::vector<bool>, 5> totalList = DA.getTotalList();
        uint8_t categoryPosition = static_cast<uint8_t>(category);
        uint8_t subCategoryPosition = static_cast<uint8_t>(subCategory);
        bool isCategoryDebugEnabled = DA.debugCategory[categoryPosition];
        bool isSubCategoryDebugEnabled = totalList[categoryPosition][subCategoryPosition];
        if(!isCategoryDebugEnabled && !isSubCategoryDebugEnabled){
            return;
        } else {
            std::string file = DA.InvDebugSources[categoryPosition];
            std::string location = DA.InvDebugTargetList[categoryPosition][subCategoryPosition];
            std::cout << "[Debug]  The " << file << "'s variable at " << location << " is " << input << "." << std::endl;
        }
    }
    void iterableDebugOutput(DebugSources category, E subCategory, V input){
        DebugArea DA;
        std::array<std::vector<bool>, 5> totalList = DA.getTotalList();
        uint8_t categoryPosition = static_cast<uint8_t>(category);
        uint8_t subCategoryPosition = static_cast<uint8_t>(subCategory);
        bool isCategoryDebugEnabled = DA.debugCategory[categoryPosition];
        bool isSubCategoryDebugEnabled = totalList[categoryPosition][subCategoryPosition];
        if(!isCategoryDebugEnabled && !isSubCategoryDebugEnabled){
            return;
        } else {
            std::string file = DA.InvDebugSources[categoryPosition];
            std::string location = DA.InvDebugTargetList[categoryPosition][subCategoryPosition];
            for(int i = 0; i < input.size(); i++){
                std::cout << "[Debug]  The " << file << "'s iterative variable at " << location << " is " << input[i] << " at index " << i << "." << std::endl;
            }
        }
    }
};

#endif // DEBUG_HANDLER_H_INCLUDED
