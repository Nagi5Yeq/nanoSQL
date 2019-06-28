#ifndef CatalogManager_hpp
#define CatalogManager_hpp

#include <cstdio>
#include <vector>
#include "BufferManager.hpp"
#include "TableInfo.hpp"
#include "Attribute.hpp"
#include <string>
using namespace std;

class CatalogManager
{
public:
	CatalogManager() {};
	~CatalogManager() {};
	void insertTable(TableInfo);
	void dropTable(string);
	bool tableExisted(string);
	int attrType(string, string);
	bool attrUnique(string, string);
	string primaryKey(string);
	bool indexExisted(string);
	bool attrExisted(string, string);
	string indexLocation(string);
	bool insertIndex(string, string, string);
	void deleteIndex(string);
	int indexNum(string, string);
	vector<Attribute> tableInformation(string);
};

#endif /* CatalogManager_hpp */
