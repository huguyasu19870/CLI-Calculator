#include <string>
#include <unordered_map>
#include <vector>
#include <climits>
#include <iostream>
#include <cstddef>
#include "input_cleaner.h"
#include "operation.h"

bool inputOrganization::isNumberComp(char &in){
    return (((in >= '0') && (in <= '9')) || (in == '.'));
}
bool inputOrganization::isMathOperator(char &in){
    return ((in == '!') || (in == '*') || (in == '+') || (in == '-') || (in == '/') || (in == '^'));
}
bool inputOrganization::isParenthesis(char &in){
    return ((in == '(') || (in == ')') || (in == '[') || (in == ']') || (in == '{') || (in == '}') || (in == '|'));
}
bool inputOrganization::isAlphabet(char &in){
    return (((in >= 'A') && (in == 'Z')) || ((in >= 'a') && (in <= 'z')));
}
bool inputOrganization::isComparisonOperator(char &in){
    return ((in == '<') || (in == '>') || (in == '=') || (in == '~'));
}

std::string inputOrganization::inputCleaner(std::string &input){
    std::string equationOutput = "";
    for(std::size_t i = 0; i < input.length(); i++){
        char currentLetter = input[i];
        //V1: If letter of input[i] is number or symbol used in mathematics, then add them into output string.
        if(inputOrganization::isNumberComp(currentLetter) || inputOrganization::isMathOperator(currentLetter) || inputOrganization::isComparisonOperator(currentLetter)){
            equationOutput += currentLetter;
        }
    }
    return equationOutput;
}

//Do I need this to be unordered map?
std::unordered_map<std::size_t, std::string> inputOrganization::calculationSpecifier(std::string &input){
    std::unordered_map<std::size_t, std::string> result;
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
            if(inputOrganization::isNumberComp(lastLetter)){
                if((!inputOrganization::isNumberComp(currentLetter)) && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == '/'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == '<'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    inputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if(lastLetter == '>'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    inputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if(lastLetter == '~'){
                if((currentLetter != '=') && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    inputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if((!inputOrganization::isNumberComp(lastLetter)) && (lastLetter >= 32)){
                if(inputOrganization::isNumberComp(currentLetter)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                } else if (inputOrganization::isComparisonOperator(currentLetter)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    inputOrganization::appendComparisonLocationList(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if((currentLetter == '+') || (currentLetter == '-')){
                if((inputOrganization::isMathOperator(lastLetter)) || (inputOrganization::isComparisonOperator(lastLetter)) || (inputOrganization::isParenthesis(lastLetter))){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    if(inputOrganization::isComparisonOperator(lastLetter)){
                        inputOrganization::setComparisonLocation(locationKey);
                        inputOrganization::appendComparisonLocationList(locationKey);
                        hasComparison = true;
                    }
                    locationKey++;
                }
            } else if(inputOrganization::isComparisonOperator(currentLetter)){
                if(lastLetter == '!'){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            }
        }
        tempEq += currentLetter;
        if(i == input.length()-1){
            //Funny thing is that I was stuck in debug because I didn't write this if.
            //Apperantly, I have thought all about interaction between numbers and mathematical operators, but not when string ends.
            result.insert({locationKey, tempEq});
        }
    }
    if(!hasComparison){
        inputOrganization::setComparisonLocation(0);
    }
    return result;
}

std::vector<std::string> inputOrganization::returnOrderedFormula(std::unordered_map<std::size_t, std::string> &input){
    std::vector<std::string> calcFlg2;
    calcFlg2.reserve(input.size());
    for(std::size_t i = 0; i < input.size(); i++){
        std::string temp = input.at(i);
        int tempLen = temp.length();
        if(temp[0] == '*'){
            if((tempLen == 2) && (temp == "**")){
                temp = "^";
            } else {
                temp = "*";
            }
        } else if(temp[0] == '<'){
            if((temp != "<") && (temp != "<=") && (temp != "=<")){
                if((tempLen > 2) && (temp.find("=") != std::string::npos)){
                    temp = "<=";
                } else if((tempLen > 2) && (temp.find("=") == std::string::npos)){
                    temp = "<";
                }
            }
        } else if(temp[0] == '>'){
            if((temp != ">") && (temp != ">=") && (temp != "=>")){
                if((tempLen > 2) && (temp.find("=") != std::string::npos)){
                    temp = ">=";
                } else if((tempLen > 2) && (temp.find("=") == std::string::npos)){
                    temp = ">";
                }
            }
        } else if((temp[0] == '+') && (tempLen > 1)){
            temp = "+";
        } else if((temp[0] == '-') && (tempLen > 1)){
            temp = "-";
        } else if((temp[0] == '/') && (tempLen > 1)){
            temp = "/";
        } else if((temp[0] == '^') && (tempLen > 1)){
            temp = "^";
        } else if((temp[0] == '=') && (tempLen > 2)){
            temp = "==";
        }
        calcFlg2.push_back(temp);
    }
    return calcFlg2;
}

