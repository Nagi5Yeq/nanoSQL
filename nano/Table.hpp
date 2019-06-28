//
//  Table.hpp
//  MiniSQL
//
//  Created by jerry on 03/11/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

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

class Table{
public:
	Table(string);
	~Table();

	PageId insertTuple(vector<Attribute>);				//参数：插入的Tuple的Attribute组成的vector 返回：插入page的PageIndex
	void deleteTuple(PageId);							//参数：所删除的Page的页号

	vector<PageId> scanEqual(int , Attribute);			//参数：第几个属性，所需比较的参数组成的Attribute
	vector<PageId> scanNotEqual(int, Attribute);			//返回：由页号所组成的vector
	vector<PageId> scanLess(int , Attribute);
	vector<PageId> scanGreater(int , Attribute);
	vector<PageId> scanLessEqual(int , Attribute);
	vector<PageId> scanGreaterEqual(int , Attribute);

	vector<PageId> getAll();								//参数：无	返回：所有在这个表中的page的页号
	vector<pair<Attribute, PageId>> getAll(int);			//参数：第几个属性 返回：由Attribute和页号所组成的pair的vector
	vector<Attribute> getTupleAtPage(PageId);			//参数：页号 返回：这一页的所有的Attribute所组成的vector

    void printinfo(PageId); 

	PageId head;
	string TableName;

};

#endif /* Table_hpp */
