//
//  Table.cpp
//  MiniSQL
//
//  Created by jerry on 03/11/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "Table.hpp"

BufferManager  bm;

Table::Table(string name)
{
	TableName = name;
	RecordPage page;
	page.pageIndex = 1;
	page.tableName = name;
	bm.readPage(page);
	head = page.readnext();
	if(head == 0)
        head = UNDEFINEED_PAGE_NUM;


}

Table::~Table()
{
	RecordPage page;
	page.pageIndex = 1;
	page.tableName = TableName;
	bm.readPage(page);
	page.writenext(head);
	bm.writePage(page);
}

PageId Table::insertTuple(vector<Attribute> list)
{
	Tuple tuple;
    tuple.list = list;
	tuple.createPage(TableName);

	tuple.page.writebefore(1);
	tuple.page.writenext(head);
	if(head != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.pageIndex = head;
		page.tableName = TableName;
		bm.readPage(page);
		page.writebefore(tuple.page.pageIndex);
        bm.writePage(page);
	}
	head = tuple.page.pageIndex;
	tuple.convertToRawData();
	bm.writePage(tuple.page);

	return tuple.page.pageIndex;
}

void Table::deleteTuple(PageId index)
{
	RecordPage page;
	page.pageIndex = index;
	page.tableName = TableName;
	bm.readPage(page);

	PageId next = page.readnext();
	PageId before = page.readbefore();
    if (before == 1) {
        head = next;
    }
	if(next == UNDEFINEED_PAGE_NUM)
	{
		RecordPage beforepage;
		beforepage.pageIndex = before;
		beforepage.tableName = TableName;
		bm.readPage(beforepage);
		beforepage.writenext(UNDEFINEED_PAGE_NUM);
		bm.writePage(beforepage);
	}
	else
	{
		RecordPage nextpage;
		nextpage.pageIndex = next;
		nextpage.tableName = TableName;
		bm.readPage(nextpage);
		RecordPage beforepage;
		beforepage.pageIndex = before;
		beforepage.tableName = TableName;
		bm.readPage(beforepage);

		beforepage.writenext(nextpage.pageIndex);
		nextpage.writebefore(beforepage.pageIndex);

		bm.writePage(beforepage);
		bm.writePage(nextpage);
	}

	bm.deallocatePage(page);

}

vector<PageId> Table::scanEqual(int attrnum, Attribute attribute)
{
	vector<PageId> result;
	PageId i = head;

	while(i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();

		if(tuple.list[attrnum] == attribute)
			result.push_back(i);

		i = page.readnext();
	}

	return result;
}

vector<PageId> Table::scanNotEqual(int attrnum, Attribute attribute)
{
	vector<PageId> result;
	PageId i = head;

	while (i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();

		if (tuple.list[attrnum] != attribute)
			result.push_back(i);

		i = page.readnext();
	}

	return result;
}

vector<PageId> Table::scanLess(int attrnum, Attribute attribute)
{
	vector<PageId> result;
	PageId i = head;
	while(i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();
		if(tuple.list[attrnum] < attribute)
			result.push_back(i);

		i = page.readnext();
	}

	return result;
}

vector<PageId> Table::scanGreater(int attrnum, Attribute attribute)
{
	vector<PageId> result;
	PageId i = head;
	while(i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();
		if(tuple.list[attrnum] > attribute)
			result.push_back(i);

		i = page.readnext();
	}

	return result;
}

vector<PageId> Table::scanLessEqual(int attrnum, Attribute attribute)
{
	vector<PageId> result;
	PageId i = head;
	while(i != UNDEFINEED_PAGE_NUM)
	{

		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();
		if(tuple.list[attrnum] <= attribute)
			result.push_back(i);

		i = page.readnext();
	}

	return result;
}

vector<PageId> Table::scanGreaterEqual(int attrnum, Attribute attribute)
{
	vector<PageId> result;
	PageId i = head;
	while(i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();
		if(tuple.list[attrnum] >= attribute)
			result.push_back(i);

		i = page.readnext();
	}

	return result;
}

vector<PageId> Table::getAll()
{
	vector<PageId> result;
	PageId i = head;
	while (i != UNDEFINEED_PAGE_NUM)
	{
		result.push_back(i);

		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);		
		i = page.readnext();
	}

	return result;
}

vector<pair<Attribute, PageId>> Table::getAll(int attrnum)
{
	vector<pair<Attribute, PageId>> result;
	PageId i = head;
	while(i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createlist(TableName);
		tuple.ParseFromRawData();
		pair<Attribute, PageId> p;
		p.first = tuple.list[attrnum];
		p.second = i;
		result.push_back(p);

		i = page.readnext();
	}

	return result;
}

vector<Attribute> Table::getTupleAtPage(PageId num)
{
	RecordPage page;
	page.tableName = TableName;
	page.pageIndex = num;
	bm.readPage(page);

	Tuple tuple;
	tuple.page = page;
	tuple.createlist(TableName);
	tuple.ParseFromRawData();

	return tuple.list;
}

void Table::printinfo(PageId index)
{
    RecordPage page;
    page.pageIndex = index;
    page.tableName = TableName;
    bm.readPage(page);

    Tuple tuple;
    tuple.page = page;
    tuple.createlist(TableName);
    tuple.ParseFromRawData();

    for(int i = 0; i < tuple.list.size(); i++)
    {
        switch(tuple.list[i].type)
        {
        case DataType::CHAR:
            for (int j = 0; j < tuple.list[i].length; j++)
                cout << tuple.list[i].chardata[j];
            break;
        case DataType::FLOAT:
            printf("%.2f", tuple.list[i].floatdata);
            break;
        case DataType::INT:
            cout << tuple.list[i].intdata;
            break;
        case DataType::UNDEFINED:;
        default:
            cout << "Type error!" ;
            break;
        }
        cout << "\t\t\t";
    }
    cout << endl;

}
