#ifndef Global_hpp
#define Global_hpp

#include <iostream>
#include <cstring>
#include <string>
#include "assert.h"
using namespace std;

enum class DataType {
	UNDEFINED,
	INT,
	FLOAT,
	CHAR
};

enum class PageType {
	UndefinedPage,
	RecordPage,
	IndexPage,
	RecordCatalogPage,
	IndexCatalogPage
};

typedef int PageId;
const int MAXPATHDEEPTH = 100;
const int MAXATTRNUM = 32;
const int PAGESIZE = 4096 * sizeof(char);
const int NODESIZE = 1024;
const PageId ROOTPAGE = 1;
const PageId UNDEFINEED_PAGE_NUM = -1;
const int CACHECAPACITY = 10;
const int LRUCOUNTERMAX = 2000000000;

class Page {
public:
	Page() {
		tableName = "";
		attributeName = "";
		pageType = PageType::UndefinedPage;
		pageIndex = -1;
		fileHandle = NULL;
		memset(pageData, 0, PAGESIZE);
	}

	Page(const Page &page) {
		this->tableName = page.tableName;
		this->attributeName = page.attributeName;
		this->pageType = page.pageType;
		this->pageIndex = page.pageIndex;
		fileHandle = page.fileHandle;
		memcpy(this->pageData, page.pageData, PAGESIZE);
	}

	~Page() {
	}

	bool operator==(const Page& page) {
		return (this->attributeName == page.attributeName) && (this->tableName == page.tableName) && (this->pageType == page.pageType) && (this->pageIndex == page.pageIndex);
	}

	string          tableName;
	string          attributeName;
	PageType        pageType;
	PageId          pageIndex;
	FILE*           fileHandle;
	char            pageData[PAGESIZE];
};

#endif