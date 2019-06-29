#ifndef IndexManager_hpp
#define IndexManager_hpp

#include "Attribute.hpp"
#include "BufferManager.hpp"
#include "Global.hpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

using namespace std;

static const int MAXCHARLENGTH = 256;

enum class BPTreeNodeType {
	BPTreeUndefinedNode = 0,
	BPTreeInternalNode,
	BPTreeLeafNode
};

class BPTreeKey {
public:
	BPTreeKey();
	BPTreeKey(const BPTreeKey &key);
	BPTreeKey(const Attribute &attri);
	~BPTreeKey();

	int compare(const BPTreeKey &key);
	int getKeyDataLength();
	void convertToRawData();
	void parseFromRawData();

	bool operator<  (const BPTreeKey &key);
	bool operator== (const BPTreeKey &key);
	bool operator>  (const BPTreeKey &key);
	bool operator>= (const BPTreeKey &key);

	DataType   type;
	char            charData[256];
	char            rawData[256];
	int             intData;
	float           floatData;
	int             keyLen;
};

class TreeItem {
public:

	TreeItem() {}
	~TreeItem() {}

	TreeItem(const TreeItem &entry) {
		key = entry.key;
		pagePointer = entry.pagePointer;
	}

	int getEntryDataLength();

	BPTreeKey       key;
	PageId   pagePointer;
};

struct TreeNodeHead {
	int             entryNumber;
	int             keyDataLength;
	DataType   keyType;
	PageId   parentNodePagePointer;
	PageId   siblingNodePagePointer;
	BPTreeNodeType  nodeType;
};

class TreeNode {
public:
	explicit TreeNode() {
		nodeEntries = new TreeItem[1024];
		entryNumber = 1; //第一个entry只会用指针部分
		keyDataLength = 0;
		keyType = DataType::UNDEFINED;
		parentNodePagePointer = UNDEFINEED_PAGE_NUM;
		siblingNodePagePointer = UNDEFINEED_PAGE_NUM;
		nodeType = BPTreeNodeType::BPTreeUndefinedNode;
	}

	TreeNode(const TreeNode &node) {
		nodeEntries = new TreeItem[1024];
		entryNumber = node.entryNumber;
		keyDataLength = node.keyDataLength;
		keyType = node.keyType;
		parentNodePagePointer = node.parentNodePagePointer;
		siblingNodePagePointer = node.siblingNodePagePointer;
		nodePage = node.nodePage;
		nodeType = node.nodeType;
		for (int i = 0; i < entryNumber; ++i)
			nodeEntries[i] = node.nodeEntries[i];
	}
	~TreeNode() {
		if (nodeEntries != NULL) delete[] nodeEntries;
		nodeEntries = NULL;
	}

	TreeNode& operator=(const TreeNode &node) {
		entryNumber = node.entryNumber;
		keyDataLength = node.keyDataLength;
		keyType = node.keyType;
		parentNodePagePointer = node.parentNodePagePointer;
		siblingNodePagePointer = node.siblingNodePagePointer;
		nodePage = node.nodePage;
		nodeType = node.nodeType;
		for (int i = 0; i < entryNumber; ++i)
			nodeEntries[i] = node.nodeEntries[i];
		return *this;
	}


	void readNodeRawData();
	void writeNodeRawData();

	void convertToRawData();
	void parseFromRawData();

	void readNode() {
		readNodeRawData();
		parseFromRawData();
	}
	void writeNode() {
		convertToRawData();
		writeNodeRawData();
	}

	void clearNode();

	bool isOverflow();
	bool isUnderflow();
	bool isLeaf();
	bool isEmpty();

	bool insertEntry(TreeItem entry);
	bool deleteEntry(BPTreeKey key);

	bool insertEntryAtIndex(TreeItem entry, int index);
	bool deleteEntryAtIndex(int index);

	int getNodeRawDataLength();

	PageId   getPagePointerForKey(BPTreeKey key);

	TreeItem *nodeEntries;
	int entryNumber;
	int keyDataLength;
	DataType keyType;
	PageId parentNodePagePointer;
	PageId siblingNodePagePointer;
	Page nodePage;
	BPTreeNodeType  nodeType;
};

class BPTree {
public:
	BPTree(string tableName, string attributeName, DataType keyType, int keyDataLength) {
		assert(tableName != "");
		assert(attributeName != "");
		this->tableName = tableName;
		this->attributeName = attributeName;
		this->keyType = keyType;
		this->keyDataLength = keyDataLength;
		TreeNode node(getNodeAtPage(ROOTPAGE));
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

	TreeNode          splitLeaveNode(TreeNode &node);
	TreeNode          splitInternalNode(TreeNode &node);
	TreeNode          createNode();
	bool                deleteNode(TreeNode &node);

	PageId       getLeadingPage();
	PageId       getLeadingPageAtNode(TreeNode node);

	TreeNode          getNodeAtPage(PageId pageIndex);

	void                updateParent(TreeNode node);

	bool                insertKeyPointerPair(BPTreeKey key, PageId pagePointer);
	bool                insertEntryIntoNode(TreeItem entry, TreeNode node);
	bool                updateEntryIntoNode(TreeItem entry, TreeNode node);

	bool                deleteKey(BPTreeKey key);
	bool                deleteKeyInNode(BPTreeKey key, TreeNode node);
	bool                handelUnderflowInChildNodeOfNodePage(TreeNode node, PageId childPage);


	PageId       searchKeyForPagePointer(BPTreeKey key);
	PageId       searchKeyForPagePointerInNode(BPTreeKey key, TreeNode node);

	bool                isRoot(TreeNode node);

	BPTreeKey           getMaxKey(TreeNode node);
	BPTreeKey           getMinKey(TreeNode node);

	string              tableName;
	string              attributeName;
	DataType       keyType;
	int                 keyDataLength;
};

#endif /* BPTree_hpp */
