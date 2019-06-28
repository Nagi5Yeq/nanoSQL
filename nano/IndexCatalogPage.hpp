#ifndef IndexCatalogPage_hpp
#define IndexCatalogPage_hpp

#include "Page.hpp"
#include <cstdio>

class IndexCatalogPage : public Page
{
public:
	int recordLimit;

	IndexCatalogPage() { pageType = PageType::IndexCatalogPage; pageIndex = 1; recordLimit = 10; }
	~IndexCatalogPage() {};
	int writeIndex(string, string, string);
	void deleteIndex(int);
	void writeInitialPage();
	void writeCont(int, string);
	int readPrevDel(int);
	string readIndexName(int);
	string readTableName(int);
	string readAttrName(int);
};


#endif /* IndexCatalogPage_hpp */

