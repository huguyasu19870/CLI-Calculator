#include <stdexcept>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include "operation.h"
#include "input_cleaner.h"

int SimpleOperation::factorialOp(int a){
    //std::cout << "[Debug] function factorialOp's variable a is: " << a << std::endl;
    bool isInputNegative = false;
    if(a == 0){
        return 1;
        //If input of a factorial is zero, then return one.
        //And if input of a factorial is negative, revert the sign to positive and note the operation.
    } else if(a < 0){
        a *= -1;
        isInputNegative = true;
    }

    int result = a;
    for(int i = (a - 1); i > 0; i--){
        result *= i;
    }
    if(isInputNegative){
        result *= -1;
    }
    return result;
}
int SimpleOperation::exponentOp(int a, int b){
    if(b == 0){
        return 1;
    }
    int result = a;
    if(b > 0){
        for(int i = 0; i < b-1; i++){
            result *= a;
        }
    } else if(b < 0){
        throw std::invalid_argument("Negative Exponent is not supported");
    }
    return result;
}

int TypeConvert::letterToInt(const std::string &input){
    if(input.length() == 1){
        return TypeConvert::letterToInt(input[0]);
    } else{
        return std::stoi(input);
    }
}
int TypeConvert::letterToInt(const char &i){
    int result = static_cast<int>(i - '0');
    if((result < 48) && (result > 57)){
        result = -1;
    }
    return result;
}
