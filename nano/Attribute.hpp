﻿#ifndef Attribute_hpp
#define Attribute_hpp

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "Global.hpp"

using namespace std;

class Attribute {
public:
	Attribute();
	Attribute(const Attribute &attr);
	~Attribute();

	int compare(const Attribute &attr);
	int getKeyDataLength();
	void convertToRawData();
	void parseFromRawData();

	bool operator <  (const Attribute &attr);
	bool operator == (const Attribute &attr);
	bool operator != (const Attribute &attr);
	bool operator >  (const Attribute &attr);
	bool operator <= (const Attribute &attr);
	bool operator >= (const Attribute &attr);

	DataType 	type;
	int 			length;
	int 			intdata;
	float 			floatdata;
	char 			chardata[256];
	char 			rawdata[256];
	string          attrName;
};

#endif /* Attribute_hpp */
