#include "test_program.h"
#include <string>
#include <array>
#include <stdexcept>
#include <iostream>

std::array<std::string, 10> CalcTest::simpleIntegerOperationTestCases(int testOps){
    std::array<std::string, 10> additionCase = {"154320+412819", "-9845+15321", "1500000000+647483640", "-450000+-250000", "2147483640+5", "2000000000+-1500000000", "0+-1234567", "888888+-888888", "999999+1", "2147483645+-2"};
    std::array<std::string, 10> subtractionCase = {"2000000000-850500123", "1456789012-56789013", "2147483640-1000000000", "876543210-432109876", "1073741824-536870912", "999999999-123456789", "1500000000-750000000", "2100500000-100500000", "500000005-6", "1234567890-1234567880"};
    std::array<std::string, 10> multiplicationCase = {"45132*8204", "125000*4500", "12345*9876", "999999*2147", "55555*33333", "2000000*1050", "14285*7000", "67890*12345", "3141592*500", "46340*46340"};
    std::array<std::string, 10> divisionCase = {"142666137/6471", "1362033702/41466", "471087200/11104", "1174640214/28501", "364827670/8230", "1543934985/33745", "1715024259/44019", "1228789296/33732", "765788239/41441", "14376496/1013"};
    std::array<std::string, 10> exponentCase = {"3^5", "2^10", "7^4", "12^3", "5^6", "2^30", "6^5", "15^4", "4^9", "11^5"};
    std::array<std::string, 10> factorialCase = {"1!", "2!", "3!", "4!", "5!", "6!", "7!", "8!", "10!", "12!"};
    std::array<std::string, 10> simpleComparisonCase = {"-439262515 < 1446625053", "684101282 < 761020855", "1303488738 <= 1926658560", "-779116518 <= 685704327", "-1214867088 > -1613113628", "1995851392 > 71948606", "190510544 >= 1974795550", "1703630796 >= 234296320", "404775551 == -187336658", "-2129266502 == 831759369"};
    std::array<std::string, 10> calcComparisonCase = {"15*400+350 > 12*500-150", "-125*8+4500 < 250*4+2000", "850000/12 <= 120000-86000", "12^3+272 > 40*50", "5500/11+4500 == 100*50", "3^4*100 <= 15000-2300*3", "2^16 < 30000*2", "9999*5-5 > 100000/2", "5^6 > 4^7", "1500000000-800000000 < 350000*2000"};
    std::array<std::string, 10> result;
    switch(testOps){
    case 0:
        result = factorialCase;
        break;
    case 1:
        result = exponentCase;
        break;
    case 2:
        result = multiplicationCase;
        break;
    case 3:
        result = divisionCase;
        break;
    case 4:
        result = additionCase;
        break;
    case 5:
        result = subtractionCase;
        break;
    case 6:
        result = simpleComparisonCase;
        break;
    case 7:
        result = calcComparisonCase;
        break;
    }
    return result;
}
std::array<int, 10> CalcTest::simpleIntegerOperationTestAnswer(int testOps){
    std::array<int, 10> additionAnswer = {567139, 5476, 2147483640, -700000, 2147483645, 500000000, -1234567, 0, 1000000, 2147483643};
    std::array<int, 10> subtractionAnswer = {1149499877, 1399999999, 1147483640, 444433334, 536870912, 876543210, 750000000, 2000000000, 499999999, 10};
    std::array<int, 10> multiplicationAnswer = {370262928, 562500000, 121919220, 2146997853, 1851814815, 2100000000, 99995000, 838102050, 1570796000, 2147395600};
    std::array<int, 10> divisionAnswer = {22047, 32847, 42425, 41214, 44329, 45753, 38961, 36428, 18479, 14192};
    std::array<int, 10> exponentAnswer = {243, 1024, 2401, 1728, 15625, 1073741824, 7776, 50625, 262144, 161051};
    std::array<int, 10> factorialAnswer = {1, 2, 6, 24, 120, 720, 5040, 40320, 3628800, 479001600};
    std::array<int, 10> simpleComparisonAnswer = {1, 1, 1, 1, 1, 1, 0, 1, 0, 0};
    std::array<int, 10> calcComparisonAnswer = {1, 0, 0, 0, 1, 1, 0, 0, 0, 0};
    std::array<int, 10> result;
    switch(testOps){
    case 0:
        result = factorialAnswer;
        break;
    case 1:
        result = exponentAnswer;
        break;
    case 2:
        result = multiplicationAnswer;
        break;
    case 3:
        result = divisionAnswer;
        break;
    case 4:
        result = additionAnswer;
        break;
    case 5:
        result = subtractionAnswer;
        break;
    case 6:
        result = simpleComparisonAnswer;
        break;
    case 7:
        result = calcComparisonAnswer;
        break;
    }
    return result;
}

void CalcTest::finalTestValidation(){
    std::array<bool, 8> testResult = CalcTest::getSimpleResultArray();
    int falseDetect = -1;
    for(int i = 0; i < testResult.size(); i++){
        if(testResult[i] == false){
            falseDetect = i;
        }
    }
    std::string errorLoc;
    if(falseDetect == 0){
        errorLoc = "Factorial";
    } else if(falseDetect == 1){
        errorLoc = "Exponent";
    } else if(falseDetect == 2){
        errorLoc = "Multiplication";
    } else if(falseDetect == 3){
        errorLoc = "Division";
    } else if(falseDetect == 4){
        errorLoc = "Addition";
    } else if(falseDetect == 5){
        errorLoc = "Subtraction";
    } else if(falseDetect == 6){
        errorLoc = "Comparison";
    } else if(falseDetect == 7){
        errorLoc = "Calculation comparison";
    }
    if(falseDetect == -1){
        std::cout << "Test result green." << std::endl;
    } else {
        std::cout << "Test result red." << std::endl;
        std::cout << "Error tripped at " << errorLoc << std::endl;
    }
    CalcTest::setFinishClock();
    auto start = CalcTest::getStartClock();
    auto finish = CalcTest::getFinishClock();
    double elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count();
    std::cout << "Test Duration is " << elapsedTime << "ms." << std::endl;
}
