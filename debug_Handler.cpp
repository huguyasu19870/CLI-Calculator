#include <array>
#include <vector>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <string>
#include "debug_Handler.h"

void DebugArea::selectDebugMode(DebugSources input, bool mode){
    bool isDebugModeOn = DebugArea::getDebugMode();
    if(!isDebugModeOn){
        std::cout << "Debug modes is not on!" << std::endl;
        return;
    }
    uint8_t position = static_cast<uint8_t>(input);
    DebugArea::debugCategory[position] = mode;
}
void DebugArea::operationDebugMode(OperationDebugTarget input, bool mode){
    bool isDebugModeOn = DebugArea::getDebugMode();
    if(!isDebugModeOn){
        std::cout << "Debug modes is not on!" << std::endl;
        return;
    }
    uint8_t position = static_cast<uint8_t>(input);
    DebugArea::operationDebugCategory[position] = mode;
}
void DebugArea::calcLogicDebugMode(CalcLogicDebugTarget input, bool mode){
    bool isDebugModeOn = DebugArea::getDebugMode();
    if(!isDebugModeOn){
        std::cout << "Debug modes is not on!" << std::endl;
        return;
    }
    uint8_t position = static_cast<uint8_t>(input);
    DebugArea::calcLogicDebugCategory[position] = mode;
}
void DebugArea::askDebugMode(bool askDetail){
    bool shouldEnd = false;
    std::string inputValue;
    int switchValue;
    int detailValue;
    while(!shouldEnd){
        std::cout << "Select the file to enable debug statement." << std::endl;
        for(int i = 0; i < InvDebugSources.size(); i++){
            std::cout << (i+1) << ":" << InvDebugSources[i] << std::endl;
        }
        std::cin >> inputValue;
        try{
            switchValue = std::stoi(inputValue);
        } catch(std::invalid_argument &e){
            bool isDone = false;
            for(int i = 0; i < InvDebugSources.size(); i++){
                if((inputValue == InvDebugSources[i])){
                    switchValue = i;
                    isDone = true;
                    break;
                }
            }
            if(!isDone){
                std::cout << "Input is incorrect. Try again." << std::endl;
                continue;
            }
        }
        if((!switchValue <= InvDebugSources.size()) && (switchValue < 1)){
            std::cout << "Input is incorrect. Try again." << std::endl;
        } else {
            shouldEnd = true;
        }
    }
    if(askDetail){
        shouldEnd = false;
    }
    while(!shouldEnd){
        std::cout << "Select position to enable debug statement." << std::endl;
        switch(switchValue){
        case 1:
            for(int i = 0; i < InvMainSources.size(); i++){
                std::cout << (i+1) << ":" << InvMainSources[i] << std::endl;
            }
            break;
        case 2:
            for(int i = 0; i < InvOperationDebugTarget.size(); i++){
                std::cout << (i+1) << ":" << InvOperationDebugTarget[i] << std::endl;
            }
            break;
        case 3:
            for(int i = 0; i < InvInputCleanerDebugTarget.size(); i++){
                std::cout << (i+1) << ":" << InvInputCleanerDebugTarget[i] << std::endl;
            }
            break;
        case 4:
            for(int i = 0; i < InvCalcLogicDebugTarget.size(); i++){
                std::cout << (i+1) << ":" << InvCalcLogicDebugTarget[i] << std::endl;
            }
            break;
        case 5:
            for(int i = 0; i < InvTestCalcDebugTarget.size(); i++){
                std::cout << (i+1) << ":" << InvTestCalcDebugTarget[i] << std::endl;
            }
            break;
        }
        std::cin >> inputValue;
        try{
            detailValue = std::stoi(inputValue);
        } catch(std::invalid_argument &e){
            std::string comparisonStr;
            bool isDone = false;
            switch(switchValue){
            case 1:
                for(int i = 0; i < InvMainSources.size(); i++){
                    if(inputValue == InvMainSources[i]){
                        detailValue = i;
                        isDone = true;
                        break;
                    }
                }
                break;
            case 2:
                for(int i = 0; i < InvOperationDebugTarget.size(); i++){
                    if(inputValue == InvOperationDebugTarget[i]){
                        detailValue = i;
                        isDone = true;
                        break;
                    }
                }
                break;
            case 3:
                for(int i = 0; i < InvInputCleanerDebugTarget.size(); i++){
                    if(inputValue == InvInputCleanerDebugTarget[i]){
                        detailValue = i;
                        isDone = true;
                        break;
                    }
                }
                break;
            case 4:
                for(int i = 0; i < InvCalcLogicDebugTarget.size(); i++){
                    if(inputValue == InvCalcLogicDebugTarget[i]){
                        detailValue = i;
                        isDone = true;
                        break;
                    }
                }
                break;
            case 5:
                for(int i = 0; i < InvTestCalcDebugTarget.size(); i++){
                    if(inputValue == InvTestCalcDebugTarget[i]){
                        detailValue = i;
                        isDone = true;
                        break;
                    }
                }
                break;
            }
            if(!isDone){
                std::cout << "Input is incorrect. Try again." << std::endl;
                continue;
            }
        }
        if((detailValue < 1) || (detailValue >= maxCategoryLength)){
            std::cout << "Input  is incorrect. Try again." << std::endl;
        } else {
            shouldEnd = true;
        }
    }
    switch(switchValue){
    case 1:
        DebugArea::selectDebugMode(DebugSources::Main, true);
        break;
    case 2:
        DebugArea::selectDebugMode(DebugSources::Operation, true);
        if(askDetail){
            switch(detailValue){
            case 1:
                DebugArea::operationDebugMode(OperationDebugTarget::Factorial, true);
                break;
            case 2:
                DebugArea::operationDebugMode(OperationDebugTarget::Exponent, true);
                break;
            }
        }
        break;
    case 3:
        DebugArea::selectDebugMode(DebugSources::InputCleaner, true);
        break;
    case 4:
        DebugArea::selectDebugMode(DebugSources::CalcLogic, true);
        if(askDetail){
            switch(detailValue){
            case 1:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::CalcLogicInput, true);
                break;
            case 2:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::FactorialLoopBegin, true);
                break;
            case 3:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::FactorialLoopInput, true);
                break;
            case 4:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::ExponentLoopBegin, true);
                break;
            case 5:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::ExponentLoopInput, true);
                break;
            case 6:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::MulDivLoopBegin, true);
                break;
            case 7:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::MulDivLoopInput, true);
                break;
            case 8:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::AddSubLoopBegin, true);
                break;
            case 9:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::AddSubLoopInput, true);
                break;
            case 10:
                DebugArea::calcLogicDebugMode(CalcLogicDebugTarget::CalcLoopEnd, true);
                break;
            }
        }
        break;
    case 5:
        DebugArea::selectDebugMode(DebugSources::TestProgram, true);
        break;
    }
}
void DebugArea::confirmDebugMode(){
    bool isDebugModeOn = DebugArea::getDebugMode();
    if(!isDebugModeOn){
        std::array<bool, 5> mainArray;
        std::fill(mainArray.begin(),mainArray.end(),false);
        DebugArea::debugCategory.swap(mainArray);
        std::vector<bool> opArray;
        opArray.resize(operationDebugCategory.size());
        std::fill(opArray.begin(),opArray.end(),false);
        DebugArea::operationDebugCategory.swap(opArray);
        std::vector<bool> clArray;
        clArray.resize(calcLogicDebugCategory.size());
        std::fill(clArray.begin(),clArray.end(),false);
        DebugArea::calcLogicDebugCategory.swap(clArray);
    } else {
        bool isCategorySelected = std::find(DebugArea::debugCategory.begin(), DebugArea::debugCategory.end(), true) != DebugArea::debugCategory.end();
        bool isOperationCategorySelected = std::find(DebugArea::operationDebugCategory.begin(), DebugArea::operationDebugCategory.end(), true) != DebugArea::operationDebugCategory.end();
        bool isCalcLogicCategorySelected = std::find(DebugArea::calcLogicDebugCategory.begin(), DebugArea::calcLogicDebugCategory.end(), true) != DebugArea::calcLogicDebugCategory.end();
        bool isSubCategorySelected = isOperationCategorySelected || isCalcLogicCategorySelected;
        bool isAnySelected = isCategorySelected || isOperationCategorySelected || isCalcLogicCategorySelected;
        if(!isAnySelected){
            std::array<bool,5> mainArray;
            std::fill(mainArray.begin(),mainArray.end(),true);
            DebugArea::debugCategory.swap(mainArray);
            std::vector<bool> opArray;
            opArray.resize(operationDebugCategory.size());
            std::fill(opArray.begin(),opArray.end(),true);
            DebugArea::operationDebugCategory.swap(opArray);
            std::vector<bool> clArray;
            clArray.resize(calcLogicDebugCategory.size());
            std::fill(clArray.begin(),clArray.end(),true);
            DebugArea::calcLogicDebugCategory.swap(clArray);
        } else {
            if(!isSubCategorySelected){
                for(int i = 0; i < DebugArea::debugCategory.size(); i++){
                    if(DebugArea::debugCategory[i] == true){
                        std::vector<bool> opArray;
                        std::vector<bool> clArray;
                        switch(i){
                        case static_cast<uint8_t>(DebugSources::Operation):
                            std::fill(opArray.begin(),opArray.end(),true);
                            DebugArea::operationDebugCategory.swap(opArray);
                            break;
                        case static_cast<uint8_t>(DebugSources::CalcLogic):
                            std::fill(clArray.begin(),clArray.end(),true);
                            DebugArea::calcLogicDebugCategory.swap(clArray);
                            break;
                        }
                    }
                }
            }
        }
    }
}
