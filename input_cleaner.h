#ifndef INPUT_CLEANER_H_INCLUDED
#define INPUT_CLEANER_H_INCLUDED
#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>

class InputOrganization{
public:
    std::string inputCleaner(std::string &input);
    std::unordered_map<std::size_t, std::string> calculationSpecifier(std::string &input);
    std::vector<std::vector<std::size_t> > operationLocator(std::string input);
    std::vector<std::string> returnOrderedFormula(std::unordered_map<std::size_t, std::string> &input);
    bool isNumberComp(char &input);
    bool isMathOperator(char &input);
    bool isComparisonOperator(char &input);
    bool isParenthesis(char &input);
    bool isAlphabet(char &input);
    /*
    std::unordered_map<unsigned long long int, unsigned long long int> getOopLocation(){
        return const &oopLocation;
    };
    void appendOopLocation(unsigned long long int a, unsigned long long int b){
        oopLocation.insert({a,b});
    };*/
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
    //std::unordered_map<unsigned long long int, unsigned long long int> oopLocation;
    inline static unsigned long long int comparisonLocation = 0;
    inline static std::vector<std::size_t> comparisonLocationList;
};

#endif // INPUT_CLEANER_H_INCLUDED
