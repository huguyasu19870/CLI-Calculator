#include <string>
#include <unordered_map>
#include <vector>
#include <climits>
#include <iostream>
#include <cstddef>
#include "input_cleaner.h"
#include "operation.h"

bool InputOrganization::isNumberComp(char &in){
    return (((in >= '0') && (in <= '9')) || (in == '.'));
}
bool InputOrganization::isMathOperator(char &in){
    return ((in == '!') || (in == '*') || (in == '+') || (in == '-') || (in == '/') || (in == '^'));
}
bool InputOrganization::isParenthesis(char &in){
    return ((in == '(') || (in == ')') || (in == '[') || (in == ']') || (in == '{') || (in == '}') || (in == '|'));
}
bool InputOrganization::isAlphabet(char &in){
    return (((in >= 'A') && (in == 'Z')) || ((in >= 'a') && (in <= 'z')));
}
bool InputOrganization::isComparisonOperator(char &in){
    return ((in == '<') || (in == '>') || (in == '=') || (in == '~'));
}

std::string InputOrganization::inputCleaner(std::string &input){
    std::string equationOutput = "";
    for(std::size_t i = 0; i < input.length(); i++){
        char currentLetter = input[i];
        //V1: If letter of input[i] is number or symbol used in mathematics, then add them into output string.
        if(InputOrganization::isNumberComp(currentLetter) || InputOrganization::isMathOperator(currentLetter) || InputOrganization::isComparisonOperator(currentLetter)){
            equationOutput += currentLetter;
        }
    }
    return equationOutput;
}

//Do I need this to be unordered map?
//No.
std::vector<std::string> InputOrganization::calculationSpecifier(std::string &input){
    std::vector<std::string> result;
    result.reserve((static_cast<int>(input.length()/2)));
    std::string tempEq = "";
    char currentLetter;
    char lastLetter;
    std::size_t locationKey = 0;
    bool hasComparison = false;
    for(std::size_t i = 0; i < input.length(); i++){
        if(input.length() != 0){
            tempEq.reserve(7);
            currentLetter = input[i];
            if(i == 0){
                lastLetter = 0;
            } else {
                lastLetter = input[i-1];
            }
            if(InputOrganization::isNumberComp(lastLetter)){
                if((!InputOrganization::isNumberComp(currentLetter)) && (currentLetter >= 32)){
                    result.push_back(tempEq);
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == '/'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.push_back(tempEq);
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == '<'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.push_back(tempEq);
                    tempEq = "";
                    InputOrganization::setComparisonLocation(locationKey);
                    InputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if(lastLetter == '>'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.push_back(tempEq);
                    tempEq = "";
                    InputOrganization::setComparisonLocation(locationKey);
                    InputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if(lastLetter == '~'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.push_back(tempEq);
                    tempEq = "";
                    InputOrganization::setComparisonLocation(locationKey);
                    InputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if((!InputOrganization::isNumberComp(lastLetter)) && (lastLetter >= 32)){
                if(InputOrganization::isNumberComp(currentLetter)){
                    result.push_back(tempEq);
                    tempEq = "";
                    locationKey++;
                } else if (InputOrganization::isComparisonOperator(currentLetter)){
                    result.push_back(tempEq);
                    tempEq = "";
                    InputOrganization::setComparisonLocation(locationKey);
                    InputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if((currentLetter == '+') || (currentLetter == '-')){
                if((InputOrganization::isMathOperator(lastLetter)) || (InputOrganization::isComparisonOperator(lastLetter)) || (InputOrganization::isParenthesis(lastLetter))){
                    result.push_back(tempEq);
                    tempEq = "";
                    if(InputOrganization::isComparisonOperator(lastLetter)){
                        InputOrganization::setComparisonLocation(locationKey);
                        InputOrganization::appendComparisonLocationList(locationKey);
                        hasComparison = true;
                    }
                    locationKey++;
                }
            } else if(InputOrganization::isComparisonOperator(currentLetter)){
                if(lastLetter == '!'){
                    result.push_back(tempEq);
                    tempEq = "";
                    locationKey++;
                }
            }
        }
        tempEq += currentLetter;
        if(i == input.length()-1){
            //Funny thing is that I was stuck in debug because I didn't write this if.
            //Apperantly, I have thought all about interaction between numbers and mathematical operators, but not when string ends.
            result.push_back(tempEq);
        }
    }
    if(!hasComparison){
        InputOrganization::setComparisonLocation(0);
    }
    std::vector<std::string> correctedResult;
    correctedResult.reserve(result.size());
    for(std::size_t i = 0; i < result.size(); i++){
        std::string currentCalc = result[i];
        int currentCalcLength = currentCalc.length();
        if(currentCalcLength > 1){
            if((currentCalc[0] == '*') && (currentCalc != "*-")){
                if((currentCalcLength % 2) == 0){
                    currentCalc = "^";
                } else {
                    currentCalc = "*";
                }
            } else if(currentCalc[0] == '<'){
                if((currentCalc != "<=") && (currentCalc != "=<")){
                    if(currentCalc.find("=") != std::string::npos){
                        currentCalc = "<=";
                    } else if(currentCalc.find("=") == std::string::npos){
                        currentCalc = "<";
                    }
                } else if(currentCalc == "=<"){
                    currentCalc = "<=";
                }
            } else if(currentCalc[0] == '>'){
                if((currentCalc != ">=") || (currentCalc != "=>")){
                    if(currentCalc.find("=") != std::string::npos){
                        currentCalc = ">=";
                    } else if(currentCalc.find("=") == std::string::npos){
                        currentCalc = ">";
                    }
                } else if(currentCalc == "=>"){
                    currentCalc = ">=";
                }
            } else if((currentCalc[0] == '+')&& (currentCalc != "+-")){
                currentCalc = "+";
            } else if((currentCalc[0] == '-') && (currentCalc != "--")){
                currentCalc = "-";
            } else if((currentCalc[0] == '/') && (currentCalc != "/-")){
                if(true){
                    currentCalc = "/";
                }
            } else if((currentCalc[0] == '^') && (currentCalc != "^-")){
                currentCalc = "^";
            } else if(currentCalc[0] == '='){
                currentCalc = "==";
            }
        }
        correctedResult.push_back(currentCalc);
    }
    return correctedResult;
}
