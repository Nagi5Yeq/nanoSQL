#ifndef Global_h
#define Global_h

#include "assert.h"

enum class DataType {
	UNDEFINED,
	INT,
	FLOAT,
	CHAR
};

typedef int PageId;
const int MAXPATHDEEPTH = 100;
const int PAGESIZE = 4096 * sizeof(char);
const int NODESIZE = 1024;
const PageId ROOTPAGE = 1;
const PageId UNDEFINEED_PAGE_NUM = -1;
const int CACHECAPACITY = 10;
const int LRUCOUNTERMAX = 2000000000;

#endif