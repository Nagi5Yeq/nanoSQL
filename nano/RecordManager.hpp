#ifndef RecordManager_hpp
#define RecordManager_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <utility>
#include "CatalogManager.hpp"
#include "BufferManager.hpp"
#include "Attribute.hpp"

class RecordPage : public Page
{
public:
	RecordPage() { pageType = PageType::RecordPage; }
	~RecordPage() {};

	void updateNext(PageId);
	void updatePrev(PageId);
	PageId getNext();
	PageId getPrev();

};

class Tuple {
public:
	Tuple() {}
	~Tuple() {}

	void createList(string);
	void createPage(string);
	void convertToRawData();
	void parseFromRawData();

	RecordPage page;
	vector<Attribute> list;
};

class Table {
public:
	Table(string);
	~Table();

	PageId insertTuple(vector<Attribute>);
	void deleteTuple(PageId);

	vector<PageId> scanEqual(int, Attribute);
	vector<PageId> scanNotEqual(int, Attribute);
	vector<PageId> scanLess(int, Attribute);
	vector<PageId> scanGreater(int, Attribute);
	vector<PageId> scanLessEqual(int, Attribute);
	vector<PageId> scanGreaterEqual(int, Attribute);

	vector<PageId> getAll();
	vector<pair<Attribute, PageId>> getAll(int);
	vector<Attribute> getTupleAtPage(PageId);
	void printinfo(PageId, vector<string>);

	PageId head;
	string TableName;

};

#endif /* Table_hpp */
