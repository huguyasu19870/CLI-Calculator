#include <stdexcept>
#include "operation.h"

int SimpleOperation::factorialOp(int a){
    bool isInputNegative = false;
    if(a == 0){
        return 1;
    } else if(a < 0){
        a *= -1;
        isInputNegative = true;
    }
    int result = 1;
    for(int i = a; i > 0; i--){
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
        for(int i = 0; i < b; i++){
            result *= a;
        }
    } else if(b < 0){
        throw std::invalid_argument("Negative Exponent is not supported");
    }
    return result;
}

int TypeConvert::letterToInt(std::string &input){
    return std::stoi(input);
}
int TypeConvert::letterToInt(char &i){
    int result;
    if(i == '0'){
        result = 0;
    } else if(i == '1'){
        result = 1;
    } else if(i == '2'){
        result = 2;
    } else if(i == '3'){
        result = 3;
    } else if(i == '4'){
        result = 4;
    } else if(i == '5'){
        result = 5;
    } else if(i == '6'){
        result = 6;
    } else if(i == '7'){
        result = 7;
    } else if(i == '8'){
        result = 8;
    } else if(i == '9'){
        result = 9;
    } else {
        result = -1;
    }
    return result;
}
