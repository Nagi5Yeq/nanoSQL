#ifndef Table_hpp
#define Table_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <utility>
#include "BufferManager.hpp"
#include "Attribute.hpp"
#include "RecordPage.hpp"
#include "Tuple.hpp"

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
	void printinfo(PageId);

	PageId head;
	string TableName;

};

#endif /* Table_hpp */
