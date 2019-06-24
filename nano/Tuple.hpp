//
//  Tuple.hpp
//  MiniSQL
//
//  Created by jerry on 03/11/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef Tuple_hpp
#define Tuple_hpp

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "RecordPage.hpp"
#include "Attribute.hpp"
#include "BufferManager.hpp"
#include "CatalogManager.hpp"

using namespace std;

class Tuple{
public:
	Tuple()  {}
	~Tuple() {}

    void createlist(string);
	void createPage(string);
	void convertToRawData();
	void ParseFromRawData();

	RecordPage page;
	vector<Attribute> list;
};

#endif /* Tuple_hpp */
