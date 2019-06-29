#include "API.hpp"

bool API::insertRecord(SQLcommand sql)
{
	clock_t begin = clock();
	CatalogManager catalog;
	if (!catalog.tableExisted(sql.tableName)) {
		printf("Table %s doesn't exist! Insertion failed!\n", sql.tableName.c_str());
	}
	vector<Attribute> vec = catalog.tableInformation(sql.tableName);
	int i;
	if (vec.size() != sql.attrNum)
	{
		printf("Failed to insert record. Wrong number of attributes.\n");
		return 0;
	}

	for (i = 1; i <= sql.attrNum; i++)
	{
		if (vec[i - 1].type == DataType::CHAR)
		{
			if (sql.condCont[i].attrType != "CHAR")
			{
				printf("Failed to insert record. Wrong type of value.\n");
				return 0;
			}

			if (sql.condCont[i].attrValueStr.length() > vec[i - 1].length)
			{
				printf("Failed to insert record. Value is too long.\n");
				return 0;
			}
			memset(vec[i - 1].chardata, 0, vec[i - 1].length);
			memcpy(vec[i - 1].chardata, sql.condCont[i].attrValueStr.c_str(), sql.condCont[i].attrValueStr.length());
		}
		else
			if (vec[i - 1].type == DataType::FLOAT)
			{
				if (sql.condCont[i].attrType == "CHAR")
				{
					printf("Failed to insert record. Wrong type of value.\n");
					return 0;
				}
				if (sql.condCont[i].attrType == "INT") {
					vec[i - 1].floatdata = (float)sql.condCont[i].attrValueInt;
				}
				else {
					vec[i - 1].floatdata = sql.condCont[i].attrValueFlo;
				}
			}
			else
			{
				if (sql.condCont[i].attrType != "INT")
				{
					printf("Failed to insert record. Wrong type of value.\n");
					return 0;
				}
				vec[i - 1].intdata = sql.condCont[i].attrValueInt;
			}
	}

	Table table(sql.tableName);

	for (int i = 0; i < vec.size(); ++i) {
		if (catalog.attrUnique(sql.tableName, vec[i].attrName)) {
			if (catalog.indexNum(sql.tableName, vec[i].attrName) > 0) {
				BPTree *indexTree;
				if (vec[i].type == DataType::INT) {
					indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::INT, vec[i].length);
				}
				else if (vec[i].type == DataType::FLOAT) {
					indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::FLOAT, vec[i].length);
				}
				else {
					indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::CHAR, vec[i].length);
				}
				if ((*indexTree).searchKeyForPagePointer(vec[i]) != UNDEFINEED_PAGE_NUM) {
					printf("Conflict on attribute %s, this attribute should be unique!\n", vec[i].attrName.c_str());
					delete indexTree;
					return 0;
				}
				delete indexTree;
			}
			else {
				if (!table.scanEqual(i, vec[i]).empty()) {
					printf("Conflict on attribute %s, this attribute should be unique!\n", vec[i].attrName.c_str());
					return 0;
				}
			}
		}
	}


	PageId insertedPage = table.insertTuple(vec);

	for (int i = 0; i < vec.size(); ++i) {
		if (catalog.indexNum(sql.tableName, vec[i].attrName) > 0) {
			BPTree *indexTree;
			if (vec[i].type == DataType::INT) {
				indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::INT, vec[i].length);
			}
			else if (vec[i].type == DataType::FLOAT) {
				indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::FLOAT, vec[i].length);
			}
			else {
				indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::CHAR, vec[i].length);
			}
			(*indexTree).insertKeyPointerPair(vec[i], insertedPage);
			delete indexTree;
		}
	}

	printf("Command running time: %f second\n", (float)(clock() - begin) / CLOCKS_PER_SEC);
	return 1;
}

bool API::createTable(TableInfo tableInfo)
{
	clock_t begin = clock();
	CatalogManager catalog;
	catalog.insertTable(tableInfo);
	printf("Successfully created 1 table (%fs)\n", (float)(clock() - begin) / CLOCKS_PER_SEC);
	return 1;
}

bool API::dropIndex(SQLcommand sql)
{
	clock_t begin = clock();
	CatalogManager catalog;
	catalog.deleteIndex(sql.indexName);
	printf("Successfully deleted 1 index (%fs)\n", (float)(clock() - begin) / CLOCKS_PER_SEC);
	return 1;
}

bool API::createIndex(SQLcommand sql)
{
	clock_t begin = clock();
	CatalogManager catalog;
	if (catalog.insertIndex(sql.tableName, sql.attrName, sql.indexName))
	{
		if (catalog.indexNum(sql.tableName, sql.attrName) == 1) {
			Table table(sql.tableName);
			BPTree *indexTree;
			int i;
			auto vec = catalog.tableInformation(sql.tableName);
			for (i = 0; i < vec.size(); ++i) {
				if (vec[i].attrName == sql.attrName) break;
			}
			if (vec[i].type == DataType::INT) {
				indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::INT, vec[i].length);
			}
			else if (vec[i].type == DataType::FLOAT) {
				indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::FLOAT, vec[i].length);
			}
			else {
				indexTree = new BPTree(sql.tableName, vec[i].attrName, DataType::CHAR, vec[i].length);
			}
			for (auto itr : table.getAll(i)) {
				indexTree->insertKeyPointerPair(itr.first, itr.second);
			}
			delete indexTree;
		}
	}
	printf("Index %s created (%fs)\n", sql.indexName.c_str(), (float)(clock() - begin) / CLOCKS_PER_SEC);
	return 1;
}

bool API::dropTable(SQLcommand sql)
{
	clock_t begin = clock();
	CatalogManager catalog;
	catalog.dropTable(sql.tableName);
	printf("Table %s dropped (%fs)\n", sql.tableName.c_str(), (float)(clock() - begin) / CLOCKS_PER_SEC);
	return 1;
}

bool API::selectRecord(SQLcommand sql)
{
	clock_t begin = clock();
	CatalogManager cm;
	if (!cm.tableExisted(sql.tableName)) {
		printf("Table %s doesn't exist! Select failed!\n", sql.tableName.c_str());
		return 0;
	}

	vector<Attribute> conditionList;
	conditionList.clear();
	vector<string> relationList;
	relationList.clear();

	for (int i = 1; i <= sql.condNum; i++) {
		bool exist = false;
		for (auto attribute : cm.tableInformation(sql.tableName)) {
			if (attribute.attrName == sql.condCont[i].attrName) {
				exist = true;
				if (sql.condCont[i].attrType == "INT") {
					if (attribute.type == DataType::CHAR) {
						printf("In where clause, the argument provided for attribute %s doesn't match its type, select failed!\n", attribute.attrName.c_str());
						return 0;
					}
					else if (attribute.type == DataType::INT) {
						attribute.intdata = sql.condCont[i].attrValueInt;
					}
					else if (attribute.type == DataType::FLOAT) {
						attribute.floatdata = (float)sql.condCont[i].attrValueInt;
					}
				}
				else if (sql.condCont[i].attrType == "FLOAT") {
					if (attribute.type != DataType::FLOAT) {
						printf("In where clause, the argument provided for attribute %s doesn't match its type, select failed!\n", attribute.attrName.c_str());
						return 0;
					}
					attribute.floatdata = sql.condCont[i].attrValueFlo;
				}
				else if (sql.condCont[i].attrType == "CHAR") {
					if (attribute.type != DataType::CHAR) {
						printf("In where clause, the argument provided for attribute %s doesn't match its type, select failed!\n", attribute.attrName.c_str());
						return 0;
					}
					if (attribute.length < sql.condCont[i].attrValueStr.length()) {
						printf("In where clause, the argument provided for attribute %s is too long, select failed!\n", attribute.attrName.c_str());
						return 0;
					}
					memset(attribute.chardata, 0, attribute.length);
					memcpy(attribute.chardata, sql.condCont[i].attrValueStr.c_str(), sql.condCont[i].attrValueStr.length());
				}
				conditionList.push_back(attribute);
				relationList.push_back(sql.condCont[i].op);
			}
		}
		if (!exist) {
			printf("Attribute named %s doesn't exist! Select failed!\n", sql.condCont[i].attrName.c_str());
			return 0;
		}
	}

	vector<string> fmtstrs;
	Table table(sql.tableName);

	if (sql.condNum == 0) {
		auto result = table.getAll();
		if (result.size() == 0) {
			puts("Empty set.");
		}
		else {
			putchar('+');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int thislen;
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					thislen = max(10, attrlen);
					fmtstrs.push_back("%" + to_string(thislen) + "d");
				}
				else if (itr.type == DataType::CHAR) {
					thislen = max(itr.length, attrlen);
					fmtstrs.push_back("%" + to_string(thislen) + "s");
				}
				else {
					thislen = max(8, attrlen);
					fmtstrs.push_back("%" + to_string(thislen) + ".2f");
				}
				for (int i = 0; i < thislen; i++) {
					putchar('-');
				}
				putchar('+');
			}
			putchar('\n');
			putchar('|');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					attrlen = max(10, attrlen);
				}
				else if (itr.type == DataType::CHAR) {
					attrlen = max(itr.length, attrlen);
				}
				else {
					attrlen = max(8, attrlen);
				}
				printf("%*s", attrlen, itr.attrName.c_str());
				putchar('|');
			}
			putchar('\n');
			putchar('+');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int thislen;
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					thislen = max(10, attrlen);
				}
				else if (itr.type == DataType::CHAR) {
					thislen = max(itr.length, attrlen);
				}
				else {
					thislen = max(8, attrlen);
				}
				for (int i = 0; i < thislen; i++) {
					putchar('-');
				}
				putchar('+');
			}
			putchar('\n');
			for (auto itr : result) {
				table.printinfo(itr, fmtstrs);
			}
			printf("%zu rows selected (%fs)\n", result.size(), (float)(clock() - begin) / CLOCKS_PER_SEC);
		}
	}
	else {
		vector<PageId> result = table.getAll();

		for (int i = 0; i < conditionList.size(); ++i) {
			if ((relationList[i] == "=") && (cm.indexNum(sql.tableName, conditionList[i].attrName) > 0)) {
				BPTree *indexTree;
				if (conditionList[i].type == DataType::INT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::INT, conditionList[i].length);
				}
				else if (conditionList[i].type == DataType::FLOAT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::FLOAT, conditionList[i].length);
				}
				else {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::CHAR, conditionList[i].length);
				}
				auto searchResult = indexTree->searchKeyForPagePointer(conditionList[i]);
				if (searchResult != UNDEFINEED_PAGE_NUM) {
					result.clear();
					result.push_back(searchResult);
					break;
				}
				delete indexTree;
			}
		}

		for (int i = 0; i < conditionList.size(); ++i) {
			vector<PageId> nextResult;
			nextResult.clear();

			auto tableInfo = cm.tableInformation(sql.tableName);
			int attributeIndex;
			for (attributeIndex = 0; attributeIndex < tableInfo.size(); ++attributeIndex)
				if (tableInfo[attributeIndex].attrName == conditionList[i].attrName) break;

			if ((relationList[i] == "=") && (cm.indexNum(sql.tableName, conditionList[i].attrName) > 0)) {
				BPTree *indexTree;
				if (conditionList[i].type == DataType::INT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::INT, conditionList[i].length);
				}
				else if (conditionList[i].type == DataType::FLOAT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::FLOAT, conditionList[i].length);
				}
				else {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::CHAR, conditionList[i].length);
				}
				auto searchResult = indexTree->searchKeyForPagePointer(conditionList[i]);
				if (searchResult != UNDEFINEED_PAGE_NUM && find(result.begin(), result.end(), searchResult) != result.end())
					nextResult.push_back(searchResult);

				delete indexTree;
			}
			else {
				for (auto itr : result) {
					auto currentAttributes = table.getTupleAtPage(itr);
					bool ok = false;
					if (relationList[i] == "=") {
						if (conditionList[i] == currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == "<>") {
						if (conditionList[i] != currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == "<") {
						if (conditionList[i] > currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == "<=") {
						if (conditionList[i] >= currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == ">") {
						if (conditionList[i] < currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == ">=") {
						if (conditionList[i] <= currentAttributes[attributeIndex])
							ok = true;
					}
					if (ok)
						nextResult.push_back(itr);
				}
			}
			result = nextResult;
		}
		if (result.size() == 0) {
			puts("Empty set");
		}
		else {
			putchar('+');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int thislen;
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					thislen = max(10, attrlen);
					fmtstrs.push_back("%" + to_string(thislen) + "d");
				}
				else if (itr.type == DataType::CHAR) {
					thislen = max(itr.length, attrlen);
					fmtstrs.push_back("%" + to_string(thislen) + "s");
				}
				else {
					thislen = max(8, attrlen);
					fmtstrs.push_back("%" + to_string(thislen) + ".2f");
				}
				for (int i = 0; i < thislen; i++) {
					putchar('-');
				}
				putchar('+');
			}
			putchar('\n');
			putchar('|');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					attrlen = max(10, attrlen);
				}
				else if (itr.type == DataType::CHAR) {
					attrlen = max(itr.length, attrlen);
				}
				else {
					attrlen = max(8, attrlen);
				}
				printf("%*s", attrlen, itr.attrName.c_str());
				putchar('|');
			}
			putchar('\n');
			putchar('+');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int thislen;
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					thislen = max(10, attrlen);
				}
				else if (itr.type == DataType::CHAR) {
					thislen = max(itr.length, attrlen);
				}
				else {
					thislen = max(8, attrlen);
				}
				for (int i = 0; i < thislen; i++) {
					putchar('-');
				}
				putchar('+');
			}
			putchar('\n');
			for (auto itr : result) {
				table.printinfo(itr, fmtstrs);
			}
			putchar('+');
			for (auto itr : cm.tableInformation(sql.tableName)) {
				int thislen;
				int attrlen = (int)itr.attrName.length();
				if (itr.type == DataType::INT) {
					thislen = max(10, attrlen);
				}
				else if (itr.type == DataType::CHAR) {
					thislen = max(itr.length, attrlen);
				}
				else {
					thislen = max(8, attrlen);
				}
				for (int i = 0; i < thislen; i++) {
					putchar('-');
				}
				putchar('+');
			}
			putchar('\n');
			printf("%zu rows selected (%fs)\n", result.size(), (float)(clock() - begin) / CLOCKS_PER_SEC);
		}
	}
	return 1;
}

bool API::deleteRecord(SQLcommand sql)
{
	clock_t begin = clock();
	CatalogManager cm;
	if (!cm.tableExisted(sql.tableName)) {
		printf("Table %s doesn't exist! Select failed!\n", sql.tableName.c_str());
		return 0;
	}

	vector<Attribute> conditionList;
	conditionList.clear();
	vector<string> relationList;
	relationList.clear();

	for (int i = 1; i <= sql.condNum; i++) {
		bool exist = false;
		for (auto Attribute : cm.tableInformation(sql.tableName)) {
			if (Attribute.attrName == sql.condCont[i].attrName) {
				exist = true;
				if (sql.condCont[i].attrType == "INT") {
					if (Attribute.type == DataType::CHAR) {
						printf("In where clause, the argument provided for attribute %s doesn't match its type, delete failed!\n", Attribute.attrName.c_str());
						return 0;
					}
					else if (Attribute.type == DataType::INT) {
						Attribute.intdata = sql.condCont[i].attrValueInt;
					}
					else if (Attribute.type == DataType::FLOAT) {
						Attribute.floatdata = (float)sql.condCont[i].attrValueInt;
					}
				}
				else if (sql.condCont[i].attrType == "FLOAT") {
					if (Attribute.type != DataType::FLOAT) {
						printf("In where clause, the argument provided for attribute %s doesn't match its type, delete failed!\n", Attribute.attrName.c_str());
						return 0;
					}
					Attribute.floatdata = sql.condCont[i].attrValueFlo;
				}
				else if (sql.condCont[i].attrType == "CHAR") {
					if (Attribute.type != DataType::CHAR) {
						printf("In where clause, the argument provided for attribute %s doesn't match its type, delete failed!\n", Attribute.attrName.c_str());
						return 0;
					}
					if (Attribute.length < sql.condCont[i].attrValueStr.length()) {
						printf("In where clause, the argument provided for attribute %s is too long, delete failed!\n", Attribute.attrName.c_str());
						return 0;
					}
					memset(Attribute.chardata, 0, Attribute.length);
					memcpy(Attribute.chardata, sql.condCont[i].attrValueStr.c_str(), sql.condCont[i].attrValueStr.length());
				}
				conditionList.push_back(Attribute);
				relationList.push_back(sql.condCont[i].op);
			}
		}
		if (!exist) {
			printf("Attribute named %s doesn't exist! Delete failed!\n", sql.condCont[i].attrName.c_str());
			return 0;
		}
	}

	Table table(sql.tableName);

	vector<PageId> result = table.getAll();

	if (sql.condNum != 0) {
		for (int i = 0; i < conditionList.size(); ++i) {
			if ((relationList[i] == "=") && (cm.indexNum(sql.tableName, conditionList[i].attrName) > 0)) {
				BPTree *indexTree;
				if (conditionList[i].type == DataType::INT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::INT, conditionList[i].length);
				}
				else if (conditionList[i].type == DataType::FLOAT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::FLOAT, conditionList[i].length);
				}
				else {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::CHAR, conditionList[i].length);
				}
				auto searchResult = indexTree->searchKeyForPagePointer(conditionList[i]);
				if (searchResult != UNDEFINEED_PAGE_NUM) {
					result.clear();
					result.push_back(searchResult);
					break;
				}
				delete indexTree;
			}
		}

		for (int i = 0; i < conditionList.size(); ++i) {
			vector<PageId> nextResult;
			nextResult.clear();

			auto tableInfo = cm.tableInformation(sql.tableName);
			int attributeIndex;
			for (attributeIndex = 0; attributeIndex < tableInfo.size(); ++attributeIndex)
				if (tableInfo[attributeIndex].attrName == conditionList[i].attrName) break;

			if ((relationList[i] == "=") && (cm.indexNum(sql.tableName, conditionList[i].attrName) > 0)) {
				BPTree *indexTree;
				if (conditionList[i].type == DataType::INT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::INT, conditionList[i].length);
				}
				else if (conditionList[i].type == DataType::FLOAT) {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::FLOAT, conditionList[i].length);
				}
				else {
					indexTree = new BPTree(sql.tableName, conditionList[i].attrName, DataType::CHAR, conditionList[i].length);
				}
				auto searchResult = indexTree->searchKeyForPagePointer(conditionList[i]);
				if (searchResult != UNDEFINEED_PAGE_NUM && find(result.begin(), result.end(), searchResult) != result.end())
					nextResult.push_back(searchResult);

				delete indexTree;
			}
			else {
				for (auto itr : result) {
					auto currentAttributes = table.getTupleAtPage(itr);
					bool ok = false;
					if (relationList[i] == "=") {
						if (conditionList[i] == currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == "<>") {
						if (conditionList[i] != currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == "<") {
						if (conditionList[i] > currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == "<=") {
						if (conditionList[i] >= currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == ">") {
						if (conditionList[i] < currentAttributes[attributeIndex])
							ok = true;
					}
					else if (relationList[i] == ">=") {
						if (conditionList[i] <= currentAttributes[attributeIndex])
							ok = true;
					}
					if (ok)
						nextResult.push_back(itr);
				}
			}
			result = nextResult;
		}
	}

	if (!result.empty()) {
		auto tableInfo = cm.tableInformation(sql.tableName);
		for (auto attribute : cm.tableInformation(sql.tableName)) {
			if (cm.indexNum(sql.tableName, attribute.attrName) > 0) {
				int attributeIndex;
				for (attributeIndex = 0; attributeIndex < tableInfo.size(); ++attributeIndex)
					if (tableInfo[attributeIndex].attrName == attribute.attrName) break;

				BPTree *indexTree = nullptr;
				if (attribute.type == DataType::INT) {
					indexTree = new BPTree(sql.tableName, attribute.attrName, DataType::INT, attribute.length);
				}
				else if (attribute.type == DataType::FLOAT) {
					indexTree = new BPTree(sql.tableName, attribute.attrName, DataType::FLOAT, attribute.length);
				}
				else if (attribute.type == DataType::CHAR) {
					indexTree = new BPTree(sql.tableName, attribute.attrName, DataType::CHAR, attribute.length);
				}

				for (auto itr : result) {
					indexTree->deleteKey(table.getTupleAtPage(itr)[attributeIndex]);
				}

				delete indexTree;
			}
		}
		for (auto itr : result) {
			table.deleteTuple(itr);
		}
	}

	printf("Delete OK, %zu record deleted (%fs)\n", result.size(), (float)(clock() - begin) / CLOCKS_PER_SEC);

	return 1;
}
