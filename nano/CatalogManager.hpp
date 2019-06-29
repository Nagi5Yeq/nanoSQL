#ifndef CatalogManager_hpp
#define CatalogManager_hpp

#include <cstdio>
#include <vector>
#include "BufferManager.hpp"
#include "Global.hpp"
#include "Attribute.hpp"
#include <string>
using namespace std;

class TableInfo
{
public:
	TableInfo() { attrNum = 0; primaryKey = ""; primaryKeyLoc = 0; }
	int attrNum;
	string tableName;
	string attrName[MAXATTRNUM];
	string attrType[MAXATTRNUM];
	string attrIndex[MAXATTRNUM];
	char attrUnique[MAXATTRNUM];
	string primaryKey;
	int primaryKeyLoc;
	void reset() { attrNum = 0; primaryKey = ""; primaryKeyLoc = 0; }
};

class CatalogPage : public Page
{
public:
	CatalogPage() { pageType = PageType::RecordCatalogPage; pageIndex = 1; }
	~CatalogPage() {};
	void writeAttr(int, string);
	string readAttrName(int);
	string readAttrType(int);
	string readAttrIndex(int);
	char readAttrUnique(int);
	int readAttrIndexNum(int);
	void modifyAttrIndexNum(int, int);
};

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
