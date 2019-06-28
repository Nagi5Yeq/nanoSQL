//
//  BPTree.hpp
//  MiniSQL
//
//  Created by fan wu on 10/29/15.
//  Copyright © 2015 Fan Wu. All rights reserved.
//

#ifndef BPTree_hpp
#define BPTree_hpp

#include "BPTreeKey.hpp"
#include "BPTreeEntry.hpp"
#include "BPTreeNode.hpp"
#include "BufferManager.hpp"
#include "Global.h"
#include "Page.hpp"
#include <string>

using namespace std;

class BPTree {
public:
    BPTree(string tableName, string attributeName, DataType keyType, int keyDataLength) {
        assert(tableName != "");
        assert(attributeName != "");
        this->tableName = tableName;
        this->attributeName = attributeName;
        this->keyType = keyType;
        this->keyDataLength = keyDataLength;
        BPTreeNode node(getNodeAtPage(ROOTPAGE));
        if (node.nodeType == BPTreeNodeType::BPTreeUndefinedNode) {
            node.nodeEntries[0].pagePointer = UNDEFINEED_PAGE_NUM;
            node.entryNumber = 1;
            node.keyDataLength = keyDataLength;
            node.keyType = keyType;
            node.parentNodePagePointer = UNDEFINEED_PAGE_NUM;
            node.siblingNodePagePointer = UNDEFINEED_PAGE_NUM;
            node.nodeType = BPTreeNodeType::BPTreeLeafNode;
            node.writeNode();
            // 当索引文件第一次被访问，初始化Root节点
        }
    }
    
    ~BPTree() {}
    
    BPTreeNode          splitLeaveNode(BPTreeNode &node);
    BPTreeNode          splitInternalNode(BPTreeNode &node);
    BPTreeNode          createNode();
    bool                deleteNode(BPTreeNode &node);
    
    PageId       getLeadingPage();
    PageId       getLeadingPageAtNode(BPTreeNode node);
    
    BPTreeNode          getNodeAtPage(PageId pageIndex);
    
    void                updateParent(BPTreeNode node);
    
    bool                insertKeyPointerPair(BPTreeKey key, PageId pagePointer);
    bool                insertEntryIntoNode(BPTreeEntry entry, BPTreeNode node);
    bool                updateEntryIntoNode(BPTreeEntry entry, BPTreeNode node);
    
    bool                deleteKey(BPTreeKey key);
    bool                deleteKeyInNode(BPTreeKey key, BPTreeNode node);
    bool                handelUnderflowInChildNodeOfNodePage(BPTreeNode node, PageId childPage);
    
    
    PageId       searchKeyForPagePointer(BPTreeKey key);
    PageId       searchKeyForPagePointerInNode(BPTreeKey key, BPTreeNode node);
    
    bool                isRoot(BPTreeNode node);
    
    BPTreeKey           getMaxKey(BPTreeNode node);
    BPTreeKey           getMinKey(BPTreeNode node);
    
    string              tableName;
    string              attributeName;
    DataType       keyType;
    int                 keyDataLength;
};

#endif /* BPTree_hpp */
