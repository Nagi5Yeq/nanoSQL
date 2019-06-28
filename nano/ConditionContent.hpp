#ifndef ConditionContent_hpp
#define ConditionContent_hpp

#include <cstdio>
#include <string>
using namespace std;

class ConditionContent
{
public:
    string attrName;
    string attrValueStr;
    int attrValueInt;
    float attrValueFlo;
    string attrType;
    string op;
};

#endif /* ConditionContent_hpp */
