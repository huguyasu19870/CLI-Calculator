#include "input_cleaner.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <climits>

std::string inputOrganization::inputCleaner(std::string input){
    std::string equationOutput = "";
    char currentLetter;
    for(unsigned long long int i = 0; i < input.length(); i++){
        currentLetter = input[i];
        //V1: If letter of input[i] is number or symbol used in mathematics, then add them into output string.
        switch(currentLetter){
        case 33:
        //case 40:
        //case 41:
        case 42:
        case 43:
        case 45:
        case 46:
        case 47:
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
        case 60:
        case 61:
        case 62:
        //case 91:
        //case 93:
        case 94:
        //case 123:
        //case 124:
        //case 125:
        case 126:
            equationOutput += currentLetter;
            break;
        }
        if(i == ULLONG_MAX){
            break;
        }
    }
    return equationOutput;
}

std::unordered_map<unsigned long long int, std::string> inputOrganization::calculationSpecifier(std::string input){
    std::unordered_map<unsigned long long int, std::string> result;
    std::string tempEq = "";
    char currentLetter;
    char lastLetter;
    unsigned long long int locationKey = 0;
    /*
    std::vector<unsigned long long int> exponentLocation;
    std::vector<unsigned long long int> factorialLocation;
    std::vector<unsigned long long int> muldivLocation;
    std::vector<unsigned long long int> addsubLocation;
    std::vector<unsigned long long int> mulLocation;
    std::vector<unsigned long long int> divLocation;
    std::vector<unsigned long long int> addLocation;
    std::vector<unsigned long long int> subLocation;*/
    for(unsigned long long int i = 0; i < input.length(); i++){
        if(input.length() != 0){
            currentLetter = input[i];
            if(i == 0){
                lastLetter = 0;
            } else {
                lastLetter = input[i-1];
            }
            if(((lastLetter >= 48) && (lastLetter <= 57))|| (lastLetter == 46)){
                //If last letter is number or period, and current letter is not, then add to map.
                if((currentLetter != 46) && (((currentLetter < 48) || (currentLetter > 57)))){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    locationKey++;
                }
            } else if(lastLetter == 47){
                //If last letter is slash sign and current letter is not equal sign, then add to map.
                if((currentLetter != 61) && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    locationKey++;
                }
            } else if(lastLetter == 60){
                //If last letter is smaller than sign and current letter is not equal sign, then add to map.
                if((currentLetter != 61) && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    locationKey++;
                }
            } else if(lastLetter == 62){
                //If last letter is larger than sign and current letter is not equal sign, then add to map.
                if((currentLetter != 61) && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    locationKey++;
                }
            } else if(lastLetter == 126){
                //If last letter is tilde and current letter is not equal sign, then add to map.
                if((currentLetter != 61) && (currentLetter >= 32)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";
                    inputOrganization::setComparisonLocation(locationKey);
                    locationKey++;
                }
            } else if((lastLetter != 46) && (((lastLetter < 48) && (lastLetter >= 32)) || (lastLetter > 57))){
                //If last letter is not a number or period and current letter is number, period, inequality sign, and equality sign, then add to map.
                if(((currentLetter >= 48) && (currentLetter <= 57))|| (currentLetter == 46)){
                    result.insert({locationKey, tempEq});/*
                    if(lastLetter == 94){
                        exponentLocation.push_back(locationKey);
                    } else if(lastLetter == 33){
                        factorialLocation.push_back(locationKey);
                    } else if((lastLetter == 42) || (lastLetter == 47)){
                        muldivLocation.push_back(locationKey);
                        if(lastLetter == 42){
                            mulLocation.push_back(locationKey);
                        } else {
                            divLocation.push_back(locationKey);
                        }
                    } else if((lastLetter == 43) || (lastLetter == 45)){
                        addsubLocation.push_back(locationKey);
                        if(lastLetter == 43){
                            addLocation.push_back(locationKey);
                        } else {
                            subLocation.push_back(locationKey);
                        }
                    } else */if((lastLetter == 60) || (lastLetter == 61) || (lastLetter == 62)){
                        inputOrganization::setComparisonLocation(locationKey);
                    }
                    tempEq = "";
                    locationKey++;
                }
            } else if((currentLetter == 43) || (currentLetter == 45)){
                //If current letter is plus or minus sign and last letter is mathematical operation, then add to map.
                if((lastLetter == 33) || (lastLetter == 42) || (lastLetter == 43) || (lastLetter == 45) || (lastLetter == 47) || (lastLetter == 61) || (lastLetter == 40) || (lastLetter == 41) || (lastLetter == 60) || (lastLetter == 62) || (lastLetter == 91) || (lastLetter == 93) || (lastLetter == 94) || (lastLetter == 123) || (lastLetter == 124) || (lastLetter == 125) || (lastLetter == 126)){
                    result.insert({locationKey, tempEq});
                    tempEq = "";/*
                    if(lastLetter == 94){
                        exponentLocation.push_back(locationKey);
                    } else if(lastLetter == 33){
                        factorialLocation.push_back(locationKey);
                    } else if((lastLetter == 42) || (lastLetter == 47)){
                        muldivLocation.push_back(locationKey);
                        if(lastLetter == 42){
                            mulLocation.push_back(locationKey);
                        } else {
                            divLocation.push_back(locationKey);
                        }
                    } else if((lastLetter == 43) || (lastLetter == 45)){
                        addsubLocation.push_back(locationKey);
                        if(lastLetter == 43){
                            addLocation.push_back(locationKey);
                        } else {
                            subLocation.push_back(locationKey);
                        }
                    } else */if((lastLetter == 60) || (lastLetter == 61) || (lastLetter == 62)){
                        inputOrganization::setComparisonLocation(locationKey);
                    }
                    locationKey++;
                }
            }
        }
        tempEq += currentLetter;
        if(i == ULLONG_MAX){
            result.insert({locationKey, tempEq});
            break;
        } else if(i == input.length()-1){
            result.insert({locationKey, tempEq});
        }
    }
    /*
    bool isDoneProcessing = false;
    unsigned long long int step = 0;
    unsigned long long int expLen = exponentLocation.size();
    unsigned long long int factLen = factorialLocation.size();
    unsigned long long int mulLen = muldivLocation.size();
    unsigned long long int addLen = addsubLocation.size();
    while(!isDoneProcessing){
        if(step < expLen){
            inputOrganization::appendOopLocation(step+factLen,exponentLocation[step]);
        }
        if(step < factLen){
            inputOrganization::appendOopLocation(step, factorialLocation[step]);
        }
        if(step < mulLen){
            inputOrganization::appendOopLocation(step+expLen+factLen, muldivLocation[step]);
        }
        if(step < addLen){
            inputOrganization::appendOopLocation(step+expLen+factLen+mulLen, addsubLocation[step]);
        }
        step++;
        if(step < (expLen+mulLen+addLen+factLen)){
            isDoneProcessing = true;
            break;
        }
        if((step+expLen+mulLen+addLen+factLen) == ULLONG_MAX){
            isDoneProcessing = true;
            break;
        }
    }
    */
    return result;
}
/*
std::vector<std::vector<unsigned long long int> > inputOrganization::operationLocator(std::string input){
    //I have no idea when I find the use for this function.
    std::vector<std::vector<unsigned long long int> > result;
    std::vector<unsigned long long int> factorialLocation;
    std::vector<unsigned long long int> openingParenthesis;
    std::vector<unsigned long long int> closingParenthesis;
    std::vector<unsigned long long int> openingBracket;
    std::vector<unsigned long long int> closingBracket;
    std::vector<unsigned long long int> openingCurvedBracket;
    std::vector<unsigned long long int> closingCurvedBracket;
    std::vector<unsigned long long int> exponentLocation;
    std::vector<unsigned long long int> multiplicationLocation;
    std::vector<unsigned long long int> divisionLocation;
    std::vector<unsigned long long int> additionLocation;
    std::vector<unsigned long long int> subtractionLocation;
    std::vector<unsigned long long int> verticleBar;
    std::vector<unsigned long long int> largerThanSign;
    std::vector<unsigned long long int> largerOrEqual;
    std::vector<unsigned long long int> equalSign;
    std::vector<unsigned long long int> notEqualSign;
    std::vector<unsigned long long int> approxEqual;
    std::vector<unsigned long long int> smallerThanSign;
    std::vector<unsigned long long int> smallerOrEqual;
    std::vector<unsigned long long int> skipVal;
    skipVal.resize(1);
    unsigned long long int skippedValue = 0;
    char currentLetter;
    bool skipNext = false;
    for(unsigned long long int i = 0; i < input.length(); i++){
        if(skipNext){
            skippedValue++;
            skipNext = false;
            continue;
        }
        currentLetter = input[i];
        switch(currentLetter){
        case 33:
            if(input[i+1] == 61){
            factorialLocation.push_back(i);
            break;
        case 40:
            openingParenthesis.push_back(i);
            break;
        case 41:
            closingParenthesis.push_back(i);
            break;
        case 42:
            multiplicationLocation.push_back(i);
            break;
        case 43:
            additionLocation.push_back(i);
            break;
        case 45:
            subtractionLocation.push_back(i);
            break;
        case 47:
            if(input[i+1] == 61){
                notEqualSign.push_back(i);
                skipNext = true;
            } else {
                divisionLocation.push_back(i);
            }
            break;
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
            skippedValue++;
            break;
        case 60:
            if(input[i+1] == 61){
                largerOrEqual.push_back(i);
                skipNext = true;
            } else {
                largerThanSign.push_back(i);
            }
            break;
        case 61:
            equalSign.push_back(i);
            break;
        case 62:
            if(input[i+1] == 61){
                smallerOrEqual.push_back(i);
                skipNext = true;
            } else {
                smallerThanSign.push_back(i);
            }
            break;
        case 91:
            openingBracket.push_back(i);
            break;
        case 93:
            closingBracket.push_back(i);
            break;
        case 94:
            exponentLocation.push_back(i);
            break;
        case 123:
            openingCurvedBracket.push_back(i);
            break;
        case 124:
            verticleBar.push_back(i);
            break;
        case 125:
            closingCurvedBracket.push_back(i);
            break;
        case 126:
            if(input[i+1] == 61){
                approxEqual.push_back(i);
                skipNext = true;
            } else {
                skippedValue++;
            }
            break;
        }
        if(i == ULLONG_MAX){
            break;
        }
    }
    }
    skipVal[0] = skippedValue;
    result.resize(20);
    result[0] = openingParenthesis;
    result[1] = closingParenthesis;
    result[2] = openingCurvedBracket;
    result[3] = closingCurvedBracket;
    result[4] = openingBracket;
    result[5] = closingBracket;
    result[6] = exponentLocation;
    result[7] = factorialLocation;
    result[8] = multiplicationLocation;
    result[9] = divisionLocation;
    result[10] = additionLocation;
    result[11] = subtractionLocation;
    result[12] = verticleBar;
    result[13] = equalSign;
    result[14] = approxEqual;
    result[15] = largerThanSign;
    result[16] = largerOrEqual;
    result[17] = smallerThanSign;
    result[18] = smallerOrEqual;
    result[19] = skipVal;
}
*/
