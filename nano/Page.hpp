//
//  Page.hpp
//  MiniSQL
//
//  Created by fan wu on 10/16/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef Page_hpp
#define Page_hpp

#include "Global.h"
#include <cstring>
#include <string>

using namespace std;

enum class PageType {
    UndefinedPage,
    RecordPage,
    IndexPage,
    RecordCatalogPage,
    IndexCatalogPage
};

class Page {
public:
    Page() {
        tableName = "";
        attributeName = "";
        pageType = PageType::UndefinedPage;
        pageIndex = -1;
        fileHandle = NULL;
        memset(pageData, 0, PAGESIZE);
    }
    
    Page(const Page &page) {
        this->tableName = page.tableName;
        this->attributeName = page.attributeName;
        this->pageType = page.pageType;
        this->pageIndex = page.pageIndex;
        fileHandle = page.fileHandle;
        memcpy(this->pageData, page.pageData, PAGESIZE);
    }
    
    ~Page() {
    }
    
    bool operator==(const Page& page) {
        return (this->attributeName == page.attributeName) && (this->tableName == page.tableName) && (this->pageType == page.pageType) && (this->pageIndex == page.pageIndex);
    }
    
    string          tableName;
    string          attributeName;
    PageType        pageType;
    PageId   pageIndex;
    FILE*           fileHandle;
    char            pageData[PAGESIZE];
};

#endif /* Page_hpp */
