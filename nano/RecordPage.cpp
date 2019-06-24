//
//  CatalogPage.cpp
//  MiniSQL
//
//  Created by jerry on 15/10/25.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#include "RecordPage.hpp"

void RecordPage::writenext(PageIndexType next)
{
	memcpy(pageData, &next, sizeof(PageIndexType));
}

void RecordPage::writebefore(PageIndexType before)
{
	memcpy(pageData + sizeof(PageIndexType), &before, sizeof(PageIndexType));
}

PageIndexType RecordPage::readnext()
{
	PageIndexType next;
	memcpy(&next, pageData, sizeof(PageIndexType));
	return next;
}

PageIndexType RecordPage::readbefore()
{
	PageIndexType before;
	memcpy(&before, pageData + sizeof(PageIndexType), sizeof(PageIndexType));
	return before;
}
