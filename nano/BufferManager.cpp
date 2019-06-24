#include "BufferManager.hpp"

map<string, FILE*> BufferManager::tableFileHandles;
map<pair<string, string>, FILE*> BufferManager::indexFileHandles;
map<string, FILE*> BufferManager::tableCatalogFileHandles;
map<pair<string, string>, FILE*> BufferManager::indexCalalogFileHandles;

const string BufferManager::recordFilesDirectory = ".\\RecordFiles";
const string BufferManager::indexFilesDirectory = ".\\IndexFiles";
const string BufferManager::recordCatalogFilesDirectory = ".\\RecordCatalogFiles";
const string BufferManager::indexCatalogFilesDirectory = ".\\IndexCatalogFiles";

Page BufferManager::cachePages[CACHECAPACITY];
bool BufferManager::pined[CACHECAPACITY];
bool BufferManager::isDirty[CACHECAPACITY];
int BufferManager::lruCounter[CACHECAPACITY];

void BufferManager::makeTwoPages(FILE* fp)
{ //如果文件太小将其扩充至两页
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) / PAGESIZE < 2)
    {
        char *pageBuffer = new char[PAGESIZE * 2];
        memset(pageBuffer, 0, PAGESIZE * 2);
        fwrite(pageBuffer, sizeof(char), PAGESIZE * 2, fp);
    }
}

string BufferManager::tableFilePath(string tableName)
{ //根据表名返回表文件路径
    return recordFilesDirectory + "\\" + tableName + ".db";
}

string BufferManager::indexFilePath(string tableName, string attributeName)
{ //根据表名和索引名返回索引文件路径
    return indexFilesDirectory + "\\" + tableName + "_" + attributeName + ".db";
}

string BufferManager::tableCatalogFilePath(string tableName)
{ //根据表名返回表目录文件路径
    return recordCatalogFilesDirectory + "\\" + tableName + ".db";
}

string BufferManager::indexCatalogFilePath(string tableName, string attributeName)
{ //根据表名和索引名返回索引目录文件路径
    return indexCatalogFilesDirectory + "\\" + tableName + "_" + attributeName + ".db";
}

bool BufferManager::closeTableFile(string tableName)
{ //关闭已打开的表文件
    if (tableFileHandles.find(tableName) == tableFileHandles.end())
        return false;
    FILE* fp = tableFileHandles[tableName];
    tableFileHandles.erase(tableName);
    if (fclose(fp) != -1)
        return true;
    return false;
}

bool BufferManager::closeIndexFile(string tableName, string attributeName)
{ //关闭已打开的索引文件
    auto indexPair = make_pair(tableName, attributeName);
    if (indexFileHandles.find(indexPair) == indexFileHandles.end())
        return false;
    FILE* fp = indexFileHandles[indexPair];
    indexFileHandles.erase(indexPair);
    if (fclose(fp) != -1)
        return true;
    return false;
}

bool BufferManager::closeTableCatalogFile(string tableName)
{ //关闭已打开的表目录文件
    if (tableCatalogFileHandles.find(tableName) == tableCatalogFileHandles.end())
    {
        return false;
    }
    FILE* fp = tableCatalogFileHandles[tableName];
    tableCatalogFileHandles.erase(tableName);
    if (fclose(fp) != -1)
        return true;
    return false;
}

bool BufferManager::closeIndexCatalogFile(string tableName, string attributeName)
{ //关闭已打开的索引目录文件
    auto indexPair = make_pair(tableName, attributeName);
    if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end())
    {
        return false;
    }
    FILE* fp = indexCalalogFileHandles[indexPair];
    indexCalalogFileHandles.erase(indexPair);
    if (fclose(fp) != -1)
        return true;
    return false;
}

bool BufferManager::tableFileIsExist(string tableName)
{ //检查该表文件是否存在
    auto filePath = tableFilePath(tableName);
    return access(filePath.c_str(), 0) != -1;
}

bool BufferManager::indexFileIsExist(string tableName, string attributeName)
{ //检查该索引文件是否存在
    auto filePath = indexFilePath(tableName, attributeName);
    return access(filePath.c_str(), 0) != -1;
}

bool BufferManager::tableCatalogFileIsExist(string tableName)
{ //检查该表目录文件是否存在
    auto filePath = tableCatalogFilePath(tableName);
    return access(filePath.c_str(), 0) != -1;
}

bool BufferManager::indexCatalogFileIsExist(string tableName, string attributeName)
{ //检查该索引目录文件是否存在
    auto filePath = indexCatalogFilePath(tableName, attributeName);
    return access(filePath.c_str(), 0) != -1;
}

bool BufferManager::openTableFile(string tableName)
{ //打开表文件
    string filePath = tableFilePath(tableName);
    if (tableFileHandles.find(tableName) == tableFileHandles.end())
    {
        FILE* fp = fopen(filePath.c_str(), "wb+");
        if (fp == NULL)
            return false;
        tableFileHandles[tableName] = fp;
        makeTwoPages(fp);
        return true;
    }
    cout << "File " << filePath << " "<< "already opened" << endl;
    return false;
}

bool BufferManager::openIndexFile(string tableName, string attributeName)
{ //打开索引文件
    auto indexPair = make_pair(tableName, attributeName);
    string filePath = indexFilePath(tableName, attributeName);
    if (indexFileHandles.find(indexPair) == indexFileHandles.end())
    {
        FILE* fp = fopen(filePath.c_str(), "wb+");
        if (fp == NULL)
            return false;
        indexFileHandles[indexPair] = fp;
        makeTwoPages(fp);
        return true;
    }
    cout << "File " << filePath << " "
         << "already opened" << endl;
    return false;
}

bool BufferManager::openTableCatalogFile(string tableName)
{ //打开表目录文件
    string filePath = tableCatalogFilePath(tableName);
    if (tableCatalogFileHandles.find(tableName) == tableCatalogFileHandles.end())
    {
        FILE* fp = fopen(filePath.c_str(),"wb+");
        if (fp == NULL)
            return false;
        tableCatalogFileHandles[tableName] = fp;
        makeTwoPages(fp);
        return true;
    }
    cout << "File " << filePath << " "
         << "already opened" << endl;
    return false;
}

bool BufferManager::openIndexCatalogFile(string tableName, string attributeName)
{ //打开索引目录文件
    auto indexPair = make_pair(tableName, attributeName);
    string filePath = indexCatalogFilePath(tableName, attributeName);
    if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end())
    {
        FILE* fp = fopen(filePath.c_str(),"wb+");
        if (fp == NULL)
            return false;
        indexCalalogFileHandles[indexPair] = fp;
        makeTwoPages(fp);
        return true;
    }
    cout << "File " << filePath << " "
         << "already opened" << endl;
    return false;
}

void BufferManager::pinPage(Page &page)
{ //锁定cache中的指定页
    for (int i = 0; i < CACHECAPACITY; ++i)
    {
        if (cachePages[i] == page)
        {
            pined[i] = true;
            break;
        }
    }
}

void BufferManager::unpinPage(Page &page)
{ //解锁cache中的指定页
    for (int i = 0; i < CACHECAPACITY; ++i)
    {
        if (cachePages[i] == page)
        {
            pined[i] = false;
            break;
        }
    }
}

void BufferManager::updateLRU(int index)
{ //更新lru
    for (int i = 0; i < CACHECAPACITY; ++i)
    {
        lruCounter[i]++;
        if (lruCounter[i] > LRUCOUNTERMAX)
            lruCounter[i] = LRUCOUNTERMAX;
    }
    lruCounter[index] = 0;
}

int BufferManager::getPageIndex(Page &page)
{ //返回该页在cache中的下标
    int retIndex = -1;
    for (int i = 0; i < CACHECAPACITY; ++i)
        if (cachePages[i] == page)
        {
            retIndex = i;
            break;
        }
    return retIndex;
}

int BufferManager::getInsteadCachePage()
{ //根据lru返回应该被替换的页的下标
    int retIndex = -1;
    int bigSaver = -1;
    for (int i = 0; i < CACHECAPACITY; ++i)
    {
        if ((!pined[i]) && (lruCounter[i] > bigSaver))
        {
            retIndex = i;
            bigSaver = lruCounter[i];
        }
    }
    return retIndex;
}

void BufferManager::writeBackAllCache()
{ //将cache中的所有页写回文件中
    for (int i = 0; i < CACHECAPACITY; ++i)
    {
        if (isDirty[i])
        {
            forceWritePage(cachePages[i]);
            isDirty[i] = false;
        }
        pined[i] = false;
        lruCounter[i] = 0;
    }
}
void BufferManager::clearCache()
{ //清空cache
    for (int i = 0; i < CACHECAPACITY; ++i)
    {
        cachePages[i].pageType = PageType::UndefinedPage;
        pined[i] = false;
        isDirty[i] = false;
        lruCounter[i] = 0;
    }
}

void BufferManager::checkPageFile(Page &page)
{   //将该页的filehandle指向对应的文件，并将该filehandle添加到
    //tablefilehandles中（如果不存在）
    assert(page.pageType != PageType::UndefinedPage);
    if(page.pageType ==  PageType::RecordPage)
    {
        assert(page.tableName != "");
        if (tableFileHandles.find(page.tableName) == tableFileHandles.end())
            assert(openTableFile(page.tableName) == true);
        page.fileHandle = tableFileHandles[page.tableName];
    }
    else if(page.pageType ==  PageType::IndexPage)
    {
        assert(page.tableName != "");
        assert(page.attributeName != "");
        auto indexPair = make_pair(page.tableName, page.attributeName);
        if (indexFileHandles.find(indexPair) == indexFileHandles.end())
            assert(openIndexFile(page.tableName, page.attributeName) == true);
        page.fileHandle = indexFileHandles[indexPair];
    }
    else if(page.pageType == PageType::RecordCatalogPage)
    {
        assert(page.tableName != "");
        if (tableCatalogFileHandles.find(page.tableName) == tableCatalogFileHandles.end())
            assert(openTableCatalogFile(page.tableName) == true);
        page.fileHandle = tableCatalogFileHandles[page.tableName];
    }
    else if(page.pageType == PageType::IndexCatalogPage)
    {
        auto indexPair = make_pair(page.tableName, page.attributeName);
        if (indexCalalogFileHandles.find(indexPair) == indexCalalogFileHandles.end())
            assert(openIndexCatalogFile(page.tableName, page.attributeName) == true);
        page.fileHandle = indexCalalogFileHandles[indexPair];
    }
}

bool BufferManager::deleteTableFile(string tableName)
{ //删除指定的表文件
    writeBackAllCache();
    clearCache();
    auto filePath = tableFilePath(tableName);
    tableFileHandles.erase(tableName);
    return remove(filePath.c_str()) != -1;
}

bool BufferManager::deleteIndexFile(string tableName, string attributeName)
{ //删除指定的索引文件
    writeBackAllCache();
    clearCache();
    auto filePath = indexFilePath(tableName, attributeName);
    indexFileHandles.erase(make_pair(tableName, attributeName));
    return remove(filePath.c_str()) != -1;
}

bool BufferManager::deleteTableCatalogFile(string tableName)
{ //删除指定的表目录文件
    writeBackAllCache();
    clearCache();
    auto filePath = tableCatalogFilePath(tableName);
    tableCatalogFileHandles.erase(tableName);
    return remove(filePath.c_str()) != -1;
}

bool BufferManager::deleteIndexCatalogFile(string tableName, string attributeName)
{ //删除指定的索引目录文件
    writeBackAllCache();
    clearCache();
    auto filePath = indexCatalogFilePath(tableName, attributeName);
    indexCalalogFileHandles.erase(make_pair(tableName, attributeName));
    return remove(filePath.c_str()) != -1;
}

PageIndexType BufferManager::tableFileTotalPages(string tableName)
{ //返回表文件的总页数
    Page page;
    page.tableName = tableName;
    page.pageType = PageType::RecordPage;
    checkPageFile(page);
    fseek(page.fileHandle, 0, SEEK_END);
    return ftell(page.fileHandle) / PAGESIZE;
}

PageIndexType BufferManager::indexFileTotalPages(string tableName, string attributeName)
{ //返回索引文件的总页数
    Page page;
    page.tableName = tableName;
    page.attributeName = attributeName;
    page.pageType = PageType::IndexPage;
    checkPageFile(page);
    fseek(page.fileHandle, 0, SEEK_END);
    return ftell(page.fileHandle) / PAGESIZE;
}

PageIndexType BufferManager::tableCatalogFileTotalPages(string tableName)
{ //返回表目录文件的总页数
    Page page;
    page.tableName = tableName;
    page.pageType = PageType::RecordCatalogPage;
    checkPageFile(page);
    fseek(page.fileHandle, 0, SEEK_END);
    return ftell(page.fileHandle) / PAGESIZE;
}

PageIndexType BufferManager::indexCatalogFileTotalPages(string tableName, string attributeName)
{ //返回索引目录文件的总页数
    Page page;
    page.tableName = tableName;
    page.attributeName = attributeName;
    page.pageType = PageType::IndexCatalogPage;
    checkPageFile(page);
    fseek(page.fileHandle, 0, SEEK_END);
    return ftell(page.fileHandle) / PAGESIZE;
}

bool BufferManager::readPage(Page &page)
{   //读取这一页的信息，如果这一页在cache中，读取并更新lru；
    //否则直接从文件中读取信息，然后根据lru替换cache中的某一页
    assert(page.pageType != PageType::UndefinedPage);
    assert(page.pageIndex != UNDEFINEED_PAGE_NUM);
    int pageIndex = getPageIndex(page);
    if (pageIndex == -1)
    {
        forceReadPage(page); // May cause bug
        pageIndex = getInsteadCachePage();
        if(pageIndex != -1)
        {
            if (isDirty[pageIndex])
            {
                isDirty[pageIndex] = false;
                forceWritePage(cachePages[pageIndex]);
            }
            cachePages[pageIndex] = page;
            updateLRU(pageIndex);
        }
        return true;
    }
    else
    {
        page = cachePages[pageIndex];
        updateLRU(pageIndex);
        return true;
    }
    assert(false);
    return false;
}

bool BufferManager::forceReadPage(Page &page)
{ //直接从文件中读取信息
    assert(page.pageType != PageType::UndefinedPage);
    assert(page.pageIndex != UNDEFINEED_PAGE_NUM);
    checkPageFile(page);
    fseek(page.fileHandle, page.pageIndex * PAGESIZE, SEEK_SET);
    return fread(page.pageData, sizeof(char), PAGESIZE, page.fileHandle) != -1;
}

bool BufferManager::writePage(Page &page)
{   //往这一页中写入，如果这一页在cache中，只需将这一页的isdirty置true，并更新lru；
    //否则直接写入对应的文件中，然后根据lru替换cache中的某一页
    //    return forceWritePage(page);
    assert(page.pageType != PageType::UndefinedPage);
    assert(page.pageIndex != UNDEFINEED_PAGE_NUM);
    int pageIndex = getPageIndex(page);
    if (pageIndex == -1)
    {
        forceWritePage(page); // May cause bug
        pageIndex = getInsteadCachePage();
        if(pageIndex != -1)
        {
            if (isDirty[pageIndex])
            {
                isDirty[pageIndex] = false;
                forceWritePage(cachePages[pageIndex]);
            }
            cachePages[pageIndex] = page;
            updateLRU(pageIndex);
        }
        return true;
    }
    else
    {
        cachePages[pageIndex] = page;
        isDirty[pageIndex] = true;
        updateLRU(pageIndex);
        return true;
    }
    assert(false);
    return false;
}

bool BufferManager::forceWritePage(Page &page)
{ //直接将该页数据写入对应文件中
    assert(page.pageType != PageType::UndefinedPage);
    assert(page.pageIndex != UNDEFINEED_PAGE_NUM);
    checkPageFile(page);
    fseek(page.fileHandle, page.pageIndex * PAGESIZE, SEEK_SET);
    return fwrite(page.pageData, sizeof(char), PAGESIZE, page.fileHandle) != -1;
}

void BufferManager::closeAllFiles()
{ //关闭所有打开的文件
    for (auto itr : tableFileHandles)
        assert(fclose(itr.second) != -1);

    for (auto itr : indexFileHandles)
        assert(fclose(itr.second) != -1);

    for (auto itr : tableCatalogFileHandles)
        assert(fclose(itr.second) != -1);

    for (auto itr : indexCalalogFileHandles)
        assert(fclose(itr.second) != -1);
}

bool BufferManager::allocatePage(Page &page)
{ //分配页号
    assert(page.pageType != PageType::UndefinedPage);
    checkPageFile(page);
    char pageBuffer[PAGESIZE];
    fseek(page.fileHandle, 0, SEEK_SET);
    fread(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);

    PageIndexType pageIndex = *((PageIndexType *)pageBuffer);
    if (pageIndex != 0)
    {
        fseek(page.fileHandle, pageIndex * PAGESIZE, SEEK_SET);
        fread(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);
        fseek(page.fileHandle, 0, SEEK_SET);
        fwrite(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);
    }
    else
    {
        fseek(page.fileHandle, 0, SEEK_END);
        pageIndex = ftell(page.fileHandle) / PAGESIZE;
        memset(pageBuffer, 0, PAGESIZE);
        fwrite(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);
    }

    page.pageIndex = pageIndex;
    return true;
}

bool BufferManager::deallocatePage(Page &page)
{ //回收页号
    assert(page.pageType != PageType::UndefinedPage);
    checkPageFile(page);

    char pageBuffer[PAGESIZE];
    fseek(page.fileHandle, 0, SEEK_SET);
    fread(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);

    fseek(page.fileHandle, page.pageIndex * PAGESIZE, SEEK_SET);
    fwrite(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);

    PageIndexType *pageIndex = (PageIndexType *)pageBuffer;
    *pageIndex = page.pageIndex;

    fseek(page.fileHandle, 0, SEEK_SET);
    fwrite(pageBuffer, sizeof(char), PAGESIZE, page.fileHandle);

    page.pageIndex = -1;

    return true;
}