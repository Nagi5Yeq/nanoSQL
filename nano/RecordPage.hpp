//
//  RecordPage.hpp
//  MiniSQL
//
//  Created by jerry on 15/10/25.
//  Copyright © 2015年 Fan Wu. All rights reserved.
//

#ifndef RecordPage_hpp
#define RecordPage_hpp

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Page.hpp"
using namespace std;

class RecordPage: public Page
{
public:
    RecordPage(){pageType = PageType::RecordPage;}
    ~RecordPage(){};
	
	void writenext(PageId);
	void writebefore(PageId);
	PageId readnext();
	PageId readbefore();

};

#endif /* RecordPage_hpp */
