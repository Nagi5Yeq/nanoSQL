#ifndef BufferManager_hpp
#define BufferManager_hpp

#include "Global.h"
#include "Page.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <string>
#include <map>
#include <io.h>
#include <utility>
#include <iostream>
#include <string>
#include <direct.h>

using namespace std;

class BufferManager
{
private:
	bool checkisdir(const char* path) {
		DWORD result;
		result = GetFileAttributesA(path);
		return (result != INVALID_FILE_ATTRIBUTES && result == FILE_ATTRIBUTE_DIRECTORY);
	}
public:
	BufferManager()
	{

		if (!checkisdir(recordFilesDirectory.c_str()))
		{
			mkdir(recordFilesDirectory.c_str());
		}
		if (!checkisdir(indexFilesDirectory.c_str()))
		{
			mkdir(indexFilesDirectory.c_str());
		}
		if (!checkisdir(recordCatalogFilesDirectory.c_str()))
		{
			mkdir(recordCatalogFilesDirectory.c_str());
		}
		if (!checkisdir(indexCatalogFilesDirectory.c_str()))
		{
			mkdir(indexCatalogFilesDirectory.c_str());
		}
		// 初始化存放文件的文件夹，根据表名以及索引键建立文件
	}

	bool openTableFile(string tableName);
	bool openIndexFile(string tableName, string attributeName);
	bool openTableCatalogFile(string tableName);
	bool openIndexCatalogFile(string tableName, string attributeName);

	void makeTwoPages(FILE *fp);

	bool closeTableFile(string tableName);
	bool closeIndexFile(string tableName, string attributeName);
	bool closeTableCatalogFile(string tableName);
	bool closeIndexCatalogFile(string tableName, string attributeName);

	bool tableFileIsExist(string tableName);
	bool indexFileIsExist(string tableName, string attributeName);
	bool tableCatalogFileIsExist(string tableName);
	bool indexCatalogFileIsExist(string tableName, string attributeName);

	bool deleteTableFile(string tableName);
	bool deleteIndexFile(string tableName, string attributeName);
	bool deleteTableCatalogFile(string tableName);
	bool deleteIndexCatalogFile(string tableName, string attributeName);

	PageIndexType tableFileTotalPages(string tableName);
	PageIndexType indexFileTotalPages(string tableName, string attributeName);
	PageIndexType tableCatalogFileTotalPages(string tableName);
	PageIndexType indexCatalogFileTotalPages(string tableName, string attributeName);

	inline string tableFilePath(string tableName);
	inline string indexFilePath(string tableName, string attributeName);
	inline string tableCatalogFilePath(string tableName);
	inline string indexCatalogFilePath(string tableName, string attributeName);

	bool readPage(Page &page);
	bool forceReadPage(Page &page);
	bool writePage(Page &page);
	bool forceWritePage(Page &page);
	bool allocatePage(Page &page);
	bool deallocatePage(Page &page);

	void checkPageFile(Page &page);

	void closeAllFiles();

	void pinPage(Page &page);
	void unpinPage(Page &page);
	void updateLRU(int index);
	int getPageIndex(Page &page);
	int getInsteadCachePage();
	void writeBackAllCache();

	void clearCache();

	static map<string, FILE*> tableFileHandles;
	static map<pair<string, string>, FILE*> indexFileHandles;
	static map<string, FILE*> tableCatalogFileHandles;
	static map<pair<string, string>, FILE*> indexCalalogFileHandles;

	static const string recordFilesDirectory;
	static const string indexFilesDirectory;
	static const string recordCatalogFilesDirectory;
	static const string indexCatalogFilesDirectory;

	static Page cachePages[CACHECAPACITY];
	static bool pined[CACHECAPACITY];
	static bool isDirty[CACHECAPACITY];
	static int lruCounter[CACHECAPACITY];
};

#endif /* BufferManager_hpp */
