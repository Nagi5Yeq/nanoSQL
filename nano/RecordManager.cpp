#include "RecordManager.hpp"

BufferManager  bm;

void RecordPage::updateNext(PageId next)
{
	memcpy(pageData, &next, sizeof(PageId));
}

void RecordPage::updatePrev(PageId before)
{
	memcpy(pageData + sizeof(PageId), &before, sizeof(PageId));
}

PageId RecordPage::getNext()
{
	PageId next;
	memcpy(&next, pageData, sizeof(PageId));
	return next;
}

PageId RecordPage::getPrev()
{
	PageId before;
	memcpy(&before, pageData + sizeof(PageId), sizeof(PageId));
	return before;
}

void Tuple::createList(string TableName)
{
	CatalogManager cm;
	list = cm.tableInformation(TableName);
}

void Tuple::createPage(string TableName)
{
	BufferManager bm;
	page.tableName = TableName;
	bm.allocatePage(page);
}

void Tuple::convertToRawData()
{
	assert(page.pageType != PageType::UndefinedPage);
	char *cursor = page.pageData;
	cursor += 2 * sizeof(PageId);

	for (unsigned int i = 0; i < list.size(); i++)
	{
		list[i].convertToRawData();
		memcpy(cursor, list[i].rawdata, list[i].getKeyDataLength());
		cursor += list[i].getKeyDataLength();
		assert(list[i].type != DataType::UNDEFINED);
	}
}

void Tuple::parseFromRawData()
{
	assert(page.pageType != PageType::UndefinedPage);
	char *cursor = page.pageData;
	cursor += 2 * sizeof(PageId);

	for (unsigned int i = 0; i < list.size(); i++)
	{
		memcpy(list[i].rawdata, cursor, list[i].getKeyDataLength());
		cursor += list[i].getKeyDataLength();
		list[i].parseFromRawData();
		assert(list[i].type != DataType::UNDEFINED);
	}
}

Table::Table(string name)
{
	TableName = name;
	RecordPage page;
	page.pageIndex = 1;
	page.tableName = name;
	bm.readPage(page);
	head = page.getNext();
	if (head == 0)
		head = UNDEFINEED_PAGE_NUM;


}

Table::~Table()
{
	RecordPage page;
	page.pageIndex = 1;
	page.tableName = TableName;
	bm.readPage(page);
	page.updateNext(head);
	bm.writePage(page);
}

PageId Table::insertTuple(vector<Attribute> list)
{
	Tuple tuple;
	tuple.list = list;
	tuple.createPage(TableName);

	tuple.page.updatePrev(1);
	tuple.page.updateNext(head);
	if (head != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.pageIndex = head;
		page.tableName = TableName;
		bm.readPage(page);
		page.updatePrev(tuple.page.pageIndex);
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

	PageId next = page.getNext();
	PageId before = page.getPrev();
	if (before == 1) {
		head = next;
	}
	if (next == UNDEFINEED_PAGE_NUM)
	{
		RecordPage beforepage;
		beforepage.pageIndex = before;
		beforepage.tableName = TableName;
		bm.readPage(beforepage);
		beforepage.updateNext(UNDEFINEED_PAGE_NUM);
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

		beforepage.updateNext(nextpage.pageIndex);
		nextpage.updatePrev(beforepage.pageIndex);

		bm.writePage(beforepage);
		bm.writePage(nextpage);
	}

	bm.deallocatePage(page);

}

vector<PageId> Table::scanEqual(int attrnum, Attribute attribute)
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
		tuple.createList(TableName);
		tuple.parseFromRawData();

		if (tuple.list[attrnum] == attribute)
			result.push_back(i);

		i = page.getNext();
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
		tuple.createList(TableName);
		tuple.parseFromRawData();

		if (tuple.list[attrnum] != attribute)
			result.push_back(i);

		i = page.getNext();
	}

	return result;
}

vector<PageId> Table::scanLess(int attrnum, Attribute attribute)
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
		tuple.createList(TableName);
		tuple.parseFromRawData();
		if (tuple.list[attrnum] < attribute)
			result.push_back(i);

		i = page.getNext();
	}

	return result;
}

vector<PageId> Table::scanGreater(int attrnum, Attribute attribute)
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
		tuple.createList(TableName);
		tuple.parseFromRawData();
		if (tuple.list[attrnum] > attribute)
			result.push_back(i);

		i = page.getNext();
	}

	return result;
}

vector<PageId> Table::scanLessEqual(int attrnum, Attribute attribute)
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
		tuple.createList(TableName);
		tuple.parseFromRawData();
		if (tuple.list[attrnum] <= attribute)
			result.push_back(i);

		i = page.getNext();
	}

	return result;
}

vector<PageId> Table::scanGreaterEqual(int attrnum, Attribute attribute)
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
		tuple.createList(TableName);
		tuple.parseFromRawData();
		if (tuple.list[attrnum] >= attribute)
			result.push_back(i);

		i = page.getNext();
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
		i = page.getNext();
	}

	return result;
}

vector<pair<Attribute, PageId>> Table::getAll(int attrnum)
{
	vector<pair<Attribute, PageId>> result;
	PageId i = head;
	while (i != UNDEFINEED_PAGE_NUM)
	{
		RecordPage page;
		page.tableName = TableName;
		page.pageIndex = i;
		bm.readPage(page);

		Tuple tuple;
		tuple.page = page;
		tuple.createList(TableName);
		tuple.parseFromRawData();
		pair<Attribute, PageId> p;
		p.first = tuple.list[attrnum];
		p.second = i;
		result.push_back(p);

		i = page.getNext();
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
	tuple.createList(TableName);
	tuple.parseFromRawData();

	return tuple.list;
}

void Table::printinfo(PageId index, vector<string> fmtstrs)
{
	RecordPage page;
	page.pageIndex = index;
	page.tableName = TableName;
	bm.readPage(page);

	Tuple tuple;
	tuple.page = page;
	tuple.createList(TableName);
	tuple.parseFromRawData();

	putchar('|');
	for (int i = 0; i < tuple.list.size(); i++)
	{
		switch (tuple.list[i].type)
		{
		case DataType::CHAR:
			printf(fmtstrs[i].c_str(), tuple.list[i].chardata);
			break;
		case DataType::FLOAT:
			printf(fmtstrs[i].c_str(), tuple.list[i].floatdata);
			break;
		case DataType::INT:
			printf(fmtstrs[i].c_str(), tuple.list[i].intdata);
			break;
		case DataType::UNDEFINED:;
		default:
			cout << "Type error!";
			break;
		}
		putchar('|');
	}
	cout << endl;

}
