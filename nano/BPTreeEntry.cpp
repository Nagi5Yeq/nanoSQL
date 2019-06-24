//
//  BPTreeEntry.cpp
//  MiniSQL
//
//  Created by fan wu on 10/25/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#include "BPTreeEntry.hpp"

int BPTreeEntry::getEntryDataLength() {
    return sizeof(pagePointer) + key.getKeyDataLength();
}