#ifndef INPUT_CLEANER_H_INCLUDED
#define INPUT_CLEANER_H_INCLUDED
#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>

class InputOrganization{
public:
    std::string inputCleaner(std::string &input);
    std::vector<std::string> calculationSpecifier(std::string &input);
    bool isNumberComp(char &input);
    bool isMathOperator(char &input);
    bool isComparisonOperator(char &input);
    bool isParenthesis(char &input);
    bool isAlphabet(char &input);
    unsigned long long int& getComparisonLocation(){
        return comparisonLocation;
    };
    void setComparisonLocation(unsigned long long int input){
        comparisonLocation = input;
    };
    std::vector<std::size_t>& getComparisonLocationList(){
        return comparisonLocationList;
    }
    void appendComparisonLocationList(std::size_t &input){
        comparisonLocationList.push_back(input);
    }
private:
    inline static unsigned long long int comparisonLocation = 0;
    inline static std::vector<std::size_t> comparisonLocationList;
};

#endif // INPUT_CLEANER_H_INCLUDED
