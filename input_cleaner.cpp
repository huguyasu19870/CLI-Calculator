#include <string>
#include <unordered_map>
#include <vector>
#include <climits>
#include <iostream>
#include "input_cleaner.h"
#include "operation.h"

std::string inputOrganization::inputCleaner(std::string &input){
    std::string equationOutput = "";
    for(unsigned long long int i = 0; i < input.length(); i++){
        char currentLetter = input[i];
        //V1: If letter of input[i] is number or symbol used in mathematics, then add them into output string.
        switch(currentLetter){
        case 33:
        case 42:
        case 43:
        case 45:
        case 46:
        case 47:
        case 60:
        case 61:
        case 62:
        case 94:
        case 126:
        //case 40:
        //case 41:
        //case 91:
        //case 93:
        //case 123:
        //case 124:
        //case 125:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
            equationOutput += currentLetter;
            break;
        }
        if(i == ULLONG_MAX){
            break;
        }
    }
    return equationOutput;
}

//Do I need this to be unordered map?
std::unordered_map<unsigned long long int, std::string> inputOrganization::calculationSpecifier(std::string &input){
    std::unordered_map<unsigned long long int, std::string> result;
    std::string tempEq = "";
    char currentLetter;
    char lastLetter;
    unsigned long long int locationKey = 0;
    bool hasComparison = false;
    for(unsigned long long int i = 0; i < input.length(); i++){
        if(input.length() != 0){
            currentLetter = input[i];
            if(i == 0){
                lastLetter = 0;
            } else {
                lastLetter = input[i-1];
            }
            //I have no idea when I have programmed this variable, but origially (before fixing for github) it was apparently tempEq[something], which is just why.
            if(((lastLetter >= 48) && (lastLetter <= 57))|| (lastLetter == 46)){
                if((currentLetter != 46) && (((currentLetter < 48) || (currentLetter > 57)))){
                    //If last letter is number or period, and current letter is not, then add to map.
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == 47){
                if((currentLetter != 61) && (currentLetter >= 32)){
                    //If last letter is slash sign and current letter is not equal sign, then add to map.
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == 60){
                if((currentLetter != 61) && (currentLetter >= 32)){
                    //If last letter is smaller than sign and current letter is not equal sign, then add to map.
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if(lastLetter == 62){
                if((currentLetter != 61) && (currentLetter >= 32)){
                    //If last letter is larger than sign and current letter is not equal sign, then add to map.
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if(lastLetter == 126){
                if((currentLetter != 61) && (currentLetter >= 32)){
                    //If last letter is tilde and current letter is not equal sign, then add to map.
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if((lastLetter != 46) && (((lastLetter < 48) && (lastLetter >= 32)) || (lastLetter > 57))){
                //If last letter is not a number or period and current letter is number, period, inequality sign, and equality sign, then add to map.
                if(((currentLetter >= 48) && (currentLetter <= 57))|| (currentLetter == 46)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                } else if ((currentLetter == 60) || (currentLetter == 61) || (currentLetter == 62)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    hasComparison = true;
                    locationKey++;
                }
            } else if((currentLetter == 43) || (currentLetter == 45)){
                //If current letter is plus or minus sign and last letter is mathematical operation, then add to map.
                if((lastLetter == 33) || (lastLetter == 42) || (lastLetter == 43) || (lastLetter == 45) || (lastLetter == 47) || (lastLetter == 61) || (lastLetter == 40) || (lastLetter == 41) || (lastLetter == 60) || (lastLetter == 62) || (lastLetter == 91) || (lastLetter == 93) || (lastLetter == 94) || (lastLetter == 123) || (lastLetter == 124) || (lastLetter == 125) || (lastLetter == 126)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    if((lastLetter == 60) || (lastLetter == 61) || (lastLetter == 62)){
                        inputOrganization::setComparisonLocation(locationKey);
                        hasComparison = true;
                    }
                    locationKey++;
                }
            } else if((currentLetter == 60) || (currentLetter == 61) || (currentLetter == 62)){
                if(lastLetter == 33){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            }
        }
        tempEq += currentLetter;
        if(i == ULLONG_MAX){
            result.insert({locationKey, tempEq});
            break;
        } else if(i == input.length()-1){
            //Funny thing is that I was stuck in debug because I didn't write this if.
            //Apperantly, I have thought all about interaction between numbers and mathematical operators, but not when string ends.
            result.insert({locationKey, tempEq});
        }
    }
    if(!hasComparison){
        inputOrganization::setComparisonLocation(0);
    }
    /*
    unsigned long long int compLoc = inputOrganization::getComparisonLocation();
    int anotherComploc = CalcLogic.getCompLoc();
    std::cout << "[Debug] function calculationSpecifier's comparisonLocation is: " << compLoc << std::endl;
    std::cout << "[Debug] current class CalculationLogic's compLoc private variable is: " << anotherComploc << std::endl;
    */
    return result;
}

std::vector<std::string> inputOrganization::returnOrderedFormula(std::unordered_map<unsigned long long int, std::string> &input){
    std::vector<std::string> calcFlg2;
    calcFlg2.reserve(input.size());
    for(unsigned long long int i = 0; i < input.size(); i++){
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
        if(i == ULLONG_MAX){
            break;
        }
    }
    return calcFlg2;
}

