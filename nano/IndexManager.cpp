#include "IndexManager.hpp"

BPTreeKey::BPTreeKey() {
	keyLen = 0;
	intData = 0;
	floatData = 0.0f;
	charData[0] = '\0';
	type = DataType::UNDEFINED;
}

BPTreeKey::BPTreeKey(const BPTreeKey &key) {
	keyLen = key.keyLen;
	intData = key.intData;
	floatData = key.floatData;
	memcpy(charData, key.charData, keyLen);
	memcpy(rawData, key.rawData, 256);
	type = key.type;
}

BPTreeKey::BPTreeKey(const Attribute &attri) {
	keyLen = attri.length;
	intData = attri.intdata;
	floatData = attri.floatdata;
	memcpy(charData, attri.chardata, keyLen);
	memcpy(rawData, attri.rawdata, 256);
	switch (attri.type) {
	case DataType::INT:
		type = DataType::INT;
		break;

	case DataType::FLOAT:
		type = DataType::FLOAT;
		break;

	case DataType::CHAR:
		type = DataType::CHAR;
		break;

	default:
		type = DataType::UNDEFINED;
		break;
	}
}

BPTreeKey::~BPTreeKey() {
}

int BPTreeKey::getKeyDataLength() {
	switch (type) {
	case DataType::CHAR:
		return keyLen;
		break;

	case DataType::FLOAT:
		return sizeof(float);
		break;

	case DataType::INT:
		return sizeof(int);
		break;

	case DataType::UNDEFINED:
		return 0;
		break;

	default:
		break;
	}
	return 0;
}

int BPTreeKey::compare(const BPTreeKey &key) {
	assert(type == key.type);
	assert(type != DataType::UNDEFINED);
	switch (type) {
	case DataType::INT: {
		if (intData > key.intData)
			return 1;
		else if (intData == key.intData)
			return 0;
		else return -1;
		break;
	}

	case DataType::FLOAT: {
		if (floatData > key.floatData)
			return 1;
		else if (fabs(floatData - key.floatData) < 0.000001)
			return 0;
		else return -1;
		break;
	}

	case DataType::CHAR: {
		return strncmp(charData, key.charData, keyLen);
		break;
	}

	default:
		return 0;
		break;
	}
}

void BPTreeKey::convertToRawData() {
	switch (type) {
	case DataType::INT: {
		keyLen = sizeof(int);
		memcpy(rawData, &intData, keyLen);
		break;
	}

	case DataType::FLOAT: {
		keyLen = sizeof(float);
		memcpy(rawData, &floatData, keyLen);
		break;
	}

	case DataType::CHAR: {
		assert(keyLen >= 0);
		assert(keyLen <= 255);
		memcpy(rawData, charData, keyLen);
		break;
	}

	default:
		break;
	}
}

void BPTreeKey::parseFromRawData() {
	assert(type != DataType::UNDEFINED);
	keyLen = getKeyDataLength();
	switch (type) {
	case DataType::INT: {
		assert(keyLen == sizeof(int));
		memcpy(&intData, rawData, keyLen);
		break;
	}

	case DataType::FLOAT: {
		assert(keyLen == sizeof(float));
		memcpy(&floatData, rawData, keyLen);
		break;
	}

	case DataType::CHAR: {
		assert(keyLen >= 0);
		assert(keyLen <= 255);
		memcpy(charData, rawData, keyLen);
		break;
	}

	default:
		break;
	}
}

bool BPTreeKey::operator< (const BPTreeKey &key) {
	return compare(key) < 0;
}

bool BPTreeKey::operator==(const BPTreeKey &key) {
	return compare(key) == 0;
}

bool BPTreeKey::operator> (const BPTreeKey &key) {
	return compare(key) > 0;
}

bool BPTreeKey::operator>=(const BPTreeKey &key) {
	return (*this > key) || (*this == key);
}

int TreeItem::getEntryDataLength() {
	return sizeof(pagePointer) + key.getKeyDataLength();
}

void TreeNode::readNodeRawData() {
	BufferManager bufferManager;
	bufferManager.readPage(nodePage);
}

void TreeNode::writeNodeRawData() {
	BufferManager bufferManager;
	bufferManager.writePage(nodePage);
}

void TreeNode::convertToRawData() {
	char *cursor = nodePage.pageData;
	TreeNodeHead &nodeHeader = (TreeNodeHead&)(*cursor);

	nodeHeader.entryNumber = entryNumber;
	nodeHeader.keyDataLength = keyDataLength;
	nodeHeader.keyType = keyType;
	nodeHeader.parentNodePagePointer = parentNodePagePointer;
	nodeHeader.siblingNodePagePointer = siblingNodePagePointer;
	nodeHeader.nodeType = nodeType;

	cursor += sizeof(TreeNodeHead);

	for (int i = 0; i < entryNumber; ++i) {
		nodeEntries[i].key.convertToRawData();
		memcpy(cursor, nodeEntries[i].key.rawData, nodeEntries[i].key.getKeyDataLength());
		cursor += nodeEntries[i].key.getKeyDataLength();
		memcpy(cursor, &nodeEntries[i].pagePointer, sizeof(PageId));
		cursor += sizeof(PageId);
	}
}

void TreeNode::parseFromRawData() {
	char *cursor = nodePage.pageData;
	TreeNodeHead &nodeHeader = (TreeNodeHead&)(*nodePage.pageData);

	entryNumber = nodeHeader.entryNumber;
	keyDataLength = nodeHeader.keyDataLength;
	keyType = nodeHeader.keyType;
	parentNodePagePointer = nodeHeader.parentNodePagePointer;
	siblingNodePagePointer = nodeHeader.siblingNodePagePointer;
	nodeType = nodeHeader.nodeType;

	cursor += sizeof(TreeNodeHead);

	for (int i = 0; i < entryNumber; ++i) {
		nodeEntries[i].key.type = keyType;
		nodeEntries[i].key.keyLen = keyDataLength;
		memcpy(nodeEntries[i].key.rawData, cursor, nodeEntries[i].getEntryDataLength());
		nodeEntries[i].key.parseFromRawData();
		cursor += nodeEntries[i].key.getKeyDataLength();
		memcpy(&nodeEntries[i].pagePointer, cursor, sizeof(PageId));
		cursor += sizeof(PageId);
	}
}

void TreeNode::clearNode() {
	entryNumber = 1;
	parentNodePagePointer = UNDEFINEED_PAGE_NUM;
	siblingNodePagePointer = UNDEFINEED_PAGE_NUM;
}


bool TreeNode::isOverflow() {
	return getNodeRawDataLength() > PAGESIZE;
}

bool TreeNode::isUnderflow() {
	return getNodeRawDataLength() < (PAGESIZE / 2);
}

bool TreeNode::isLeaf() {
	return nodeType == BPTreeNodeType::BPTreeLeafNode;
}

bool TreeNode::isEmpty() {
	assert(entryNumber >= 0);
	return (entryNumber <= 1);
}

bool TreeNode::insertEntry(TreeItem entry) {
	assert(entry.key.type != DataType::UNDEFINED);
	int insertPoint;
	for (insertPoint = 0; insertPoint < entryNumber; ++insertPoint)
		if (nodeEntries[insertPoint].key > entry.key) break;
	return insertEntryAtIndex(entry, insertPoint);
}

bool TreeNode::deleteEntry(BPTreeKey key) {
	assert(key.type == keyType);
	int deletePoint;
	for (deletePoint = 1; deletePoint < entryNumber; ++deletePoint) {
		if (nodeEntries[deletePoint].key == key) break;
	}
	if (deletePoint == entryNumber) return false;
	return deleteEntryAtIndex(deletePoint);
}

bool TreeNode::insertEntryAtIndex(TreeItem entry, int index) {
	assert(index >= 0);
	assert(index <= entryNumber);
	for (int i = entryNumber - 1; i >= index; --i) {
		nodeEntries[i + 1] = nodeEntries[i];
	}
	nodeEntries[index] = entry;
	entryNumber++;
	return true;
}

bool TreeNode::deleteEntryAtIndex(int index) {
	assert(index >= 0);
	assert(index < entryNumber);
	for (int i = index; i < entryNumber; ++i) {
		nodeEntries[i] = nodeEntries[i + 1];
	}
	entryNumber--;
	return true;
}

int TreeNode::getNodeRawDataLength() {
	int accumulator = 0;

	accumulator += sizeof(TreeNodeHead);

	for (int i = 0; i < entryNumber; ++i) {
		accumulator += nodeEntries[i].getEntryDataLength();
	}

	return accumulator;
}

PageId TreeNode::getPagePointerForKey(BPTreeKey key) {
	assert(key.type != DataType::UNDEFINED);
	if (key < nodeEntries[1].key) return nodeEntries[0].pagePointer;
	else {
		for (int i = 1; i < entryNumber; i++)
			if (key >= nodeEntries[i].key)
				return nodeEntries[i].pagePointer;
	}
	assert(false); // pointer not found
	return nodeEntries[0].pagePointer;
}

void BPTree::updateParent(TreeNode node) {
	if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
		for (int i = 0; i < node.entryNumber; i++) {
			TreeNode tempNode;
			tempNode = getNodeAtPage(node.nodeEntries[i].pagePointer);
			tempNode.parentNodePagePointer = node.nodePage.pageIndex;
			tempNode.writeNode();
		}
	}
}

TreeNode BPTree::splitLeaveNode(TreeNode &node) {
	TreeNode newNode(createNode());
	Page tempPage = newNode.nodePage;
	newNode = node;
	newNode.nodePage = tempPage;
	node.siblingNodePagePointer = newNode.nodePage.pageIndex;

	int mid = node.entryNumber / 2;
	node.entryNumber = mid;

	for (int i = mid; i < newNode.entryNumber; ++i) {
		newNode.nodeEntries[i - mid + 1] = newNode.nodeEntries[i];
	}
	newNode.entryNumber -= mid - 1;
	return newNode;
}

TreeNode BPTree::splitInternalNode(TreeNode &node) {
	TreeNode newNode = createNode();
	Page tempPage = newNode.nodePage;
	newNode = node;
	newNode.nodePage = tempPage;
	node.siblingNodePagePointer = newNode.nodePage.pageIndex;

	int mid = node.entryNumber / 2;
	node.entryNumber = mid;

	for (int i = mid; i < newNode.entryNumber; ++i) {
		newNode.nodeEntries[i - mid] = newNode.nodeEntries[i];
	}
	newNode.entryNumber -= mid;
	return newNode;
}

TreeNode BPTree::createNode() {
	TreeNode node;
	node.nodeEntries[0].pagePointer = UNDEFINEED_PAGE_NUM;
	node.entryNumber = 1;
	node.keyDataLength = keyDataLength;
	node.keyType = keyType;
	node.parentNodePagePointer = UNDEFINEED_PAGE_NUM;
	node.siblingNodePagePointer = UNDEFINEED_PAGE_NUM;
	node.nodeType = BPTreeNodeType::BPTreeUndefinedNode;

	node.nodePage.tableName = tableName;
	node.nodePage.attributeName = attributeName;
	node.nodePage.pageType = PageType::IndexPage;
	BufferManager bufferManager;
	bufferManager.allocatePage(node.nodePage);
	return node;
}

bool BPTree::deleteNode(TreeNode &node) {
	BufferManager bufferManager;
	return bufferManager.deallocatePage(node.nodePage);
}

PageId BPTree::getLeadingPage() {
	return getLeadingPageAtNode(getNodeAtPage(ROOTPAGE));
}

PageId BPTree::getLeadingPageAtNode(TreeNode node) {
	assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
	assert(!node.isEmpty());
	if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
		return node.nodePage.pageIndex;
	}
	else {
		return getLeadingPageAtNode(getNodeAtPage(node.nodeEntries[0].pagePointer));
	}
}

TreeNode BPTree::getNodeAtPage(PageId pageIndex) {
	TreeNode node;
	node.nodePage.tableName = tableName;
	node.nodePage.attributeName = attributeName;
	node.nodePage.pageType = PageType::IndexPage;
	node.nodePage.pageIndex = pageIndex;
	node.readNode();
	return node;
}

bool BPTree::insertKeyPointerPair(BPTreeKey key, PageId pagePointer) {
	assert(key.type == keyType);
	assert(pagePointer != UNDEFINEED_PAGE_NUM);
	assert(key.keyLen == keyDataLength);
	TreeItem entry;
	entry.key = key;
	entry.pagePointer = pagePointer;
	return this->insertEntryIntoNode(entry, getNodeAtPage(ROOTPAGE));
}

bool BPTree::insertEntryIntoNode(TreeItem entry, TreeNode node) {
	assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
	if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
		if (entry.key < node.nodeEntries[1].key) {
			return this->insertEntryIntoNode(entry, getNodeAtPage(node.nodeEntries[0].pagePointer));
		}
		else {
			for (int i = node.entryNumber - 1; i > 0; --i) {
				if (entry.key >= node.nodeEntries[i].key) {
					return this->insertEntryIntoNode(entry, getNodeAtPage(node.nodeEntries[i].pagePointer));
				}
			}
		}
	}
	else if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
		node.insertEntry(entry);
		if (!node.isOverflow()) {
			node.writeNode();
			return true;
		}
		else {
			if (!isRoot(node)) {
				TreeNode newNode = splitLeaveNode(node);
				node.writeNode();
				updateParent(newNode);
				newNode.writeNode();
				TreeItem entry;
				entry.key = getMinKey(newNode);
				entry.pagePointer = newNode.nodePage.pageIndex;
				return updateEntryIntoNode(entry, getNodeAtPage(node.parentNodePagePointer));
			}
			else {
				TreeNode leftNode = createNode();
				Page tempPage = leftNode.nodePage;
				leftNode = node;
				leftNode.nodePage = tempPage;
				TreeNode rightNode = splitLeaveNode(leftNode);

				leftNode.parentNodePagePointer = node.nodePage.pageIndex;
				rightNode.parentNodePagePointer = node.nodePage.pageIndex;

				updateParent(leftNode);
				updateParent(rightNode);

				leftNode.writeNode();
				rightNode.writeNode();

				node.clearNode();
				node.entryNumber = 2;
				node.nodeEntries[0].pagePointer = leftNode.nodePage.pageIndex;
				node.nodeEntries[1].pagePointer = rightNode.nodePage.pageIndex;
				node.nodeEntries[1].key = getMinKey(rightNode);
				node.nodeType = BPTreeNodeType::BPTreeInternalNode;
				node.writeNode();
				return true;
			}
		}
	}
	assert(false); // Error
	return false;
}

bool BPTree::updateEntryIntoNode(TreeItem entry, TreeNode node) {
	assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
	node.insertEntry(entry);
	if (!node.isOverflow()) {
		node.writeNode();
		return true;
	}
	else {
		if (!isRoot(node)) {
			TreeNode newNode = splitInternalNode(node);
			node.writeNode();
			updateParent(newNode);
			newNode.writeNode();
			TreeItem entry;
			entry.key = getMinKey(newNode);
			entry.pagePointer = newNode.nodePage.pageIndex;
			return updateEntryIntoNode(entry, getNodeAtPage(node.parentNodePagePointer));
		}
		else {
			TreeNode leftNode = createNode();
			Page tempPage = leftNode.nodePage;
			leftNode = node;
			leftNode.nodePage = tempPage;
			TreeNode rightNode = splitInternalNode(leftNode);

			leftNode.parentNodePagePointer = node.nodePage.pageIndex;
			rightNode.parentNodePagePointer = node.nodePage.pageIndex;

			updateParent(leftNode);
			updateParent(rightNode);

			leftNode.writeNode();
			rightNode.writeNode();

			node.clearNode();
			node.entryNumber = 2;
			node.nodeEntries[0].pagePointer = leftNode.nodePage.pageIndex;
			node.nodeEntries[1].pagePointer = rightNode.nodePage.pageIndex;
			node.nodeEntries[1].key = getMinKey(rightNode);
			node.nodeType = BPTreeNodeType::BPTreeInternalNode;
			node.writeNode();
			return true;
		}
	}
	assert(false);
	return false;
}

bool BPTree::deleteKey(BPTreeKey key) {
	return deleteKeyInNode(key, getNodeAtPage(ROOTPAGE));
}

bool BPTree::deleteKeyInNode(BPTreeKey key, TreeNode node) {
	assert(key.keyLen == node.keyDataLength);
	assert(key.type == node.keyType);
	if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
		if (key < node.nodeEntries[1].key) {
			return deleteKeyInNode(key, getNodeAtPage(node.nodeEntries[0].pagePointer));
		}
		else {
			for (int i = node.entryNumber - 1; i > 0; --i) {
				if (key >= node.nodeEntries[i].key) {
					return deleteKeyInNode(key, getNodeAtPage(node.nodeEntries[i].pagePointer));
				}
			}
		}
	}
	else if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
		node.deleteEntry(key);
		node.writeNode();
		if (!node.isUnderflow()) {
			return true;
		}
		else {
			if (isRoot(node)) {
				return true; // Root node underflow do nothing
			}
			else {
				return handelUnderflowInChildNodeOfNodePage(getNodeAtPage(node.parentNodePagePointer), node.nodePage.pageIndex);
			}
		}
	}

	assert(false);
	return false;
}

bool BPTree::handelUnderflowInChildNodeOfNodePage(TreeNode node, PageId childPage) {
	assert(!node.isEmpty());
	assert(node.entryNumber >= 2);
	PageId siblingPage;
	if (childPage == node.nodeEntries[node.entryNumber - 1].pagePointer) {
		siblingPage = childPage;
		childPage = node.nodeEntries[node.entryNumber - 2].pagePointer;
	}
	else {
		siblingPage = getNodeAtPage(childPage).siblingNodePagePointer;
	}

	int childIndex = 0, siblingIndex = 0;
	for (int i = 0; i < node.entryNumber; ++i) {
		if (node.nodeEntries[i].pagePointer == childPage) childIndex = i;
		if (node.nodeEntries[i].pagePointer == siblingPage) siblingIndex = i;
	}

	TreeNode childNode = getNodeAtPage(childPage);
	TreeNode siblingNode = getNodeAtPage(siblingPage);

	if (childNode.nodeType == BPTreeNodeType::BPTreeInternalNode) {
		siblingNode.nodeEntries[0].key = getMinKey(getNodeAtPage(siblingNode.nodeEntries[0].pagePointer));

		int biggerLenghth = childNode.nodeEntries[0].getEntryDataLength() * int(ceil((double)(childNode.entryNumber + siblingNode.entryNumber) / 2.0)) + sizeof(TreeNodeHead);
		if (biggerLenghth < (PAGESIZE / 2)) { // 此时可以merge
			childNode.siblingNodePagePointer = siblingNode.siblingNodePagePointer;
			for (int i = childNode.entryNumber; i < childNode.entryNumber + siblingNode.entryNumber; ++i) {
				childNode.nodeEntries[i] = siblingNode.nodeEntries[i - childNode.entryNumber];
			}
			childNode.entryNumber += siblingNode.entryNumber; //merge 进childnode

			for (int i = siblingIndex; i < node.entryNumber; ++i)
				node.nodeEntries[i] = node.nodeEntries[i + 1];
			node.entryNumber--;
			node.writeNode();

			updateParent(childNode);
			childNode.writeNode();
			deleteNode(siblingNode);

			if (node.isUnderflow()) {
				if (isRoot(node)) {
					if (node.entryNumber == 1) {
						TreeNode tempNode = getNodeAtPage(node.nodeEntries[0].pagePointer);
						Page tempPage = node.nodePage;
						node = tempNode;
						node.nodePage = tempPage;
						updateParent(node);
						node.writeNode();
						deleteNode(tempNode);
						return true;
					}
					else {
						return true;
					}
				}
				else {
					return handelUnderflowInChildNodeOfNodePage(getNodeAtPage(node.parentNodePagePointer), node.nodePage.pageIndex);
				}
			}
			else {
				return true;
			}
		}
		else { // 此时需要 redistribute
			int tot = (childNode.entryNumber + siblingNode.entryNumber);
			int mid = tot / 2;
			TreeItem *entries = new TreeItem[tot];
			for (int i = 0; i < childNode.entryNumber; ++i)
				entries[i] = childNode.nodeEntries[i];
			for (int i = 0; i < siblingNode.entryNumber; ++i)
				entries[i + childNode.entryNumber] = siblingNode.nodeEntries[i];

			childNode.entryNumber = mid;
			siblingNode.entryNumber = tot - mid;

			for (int i = 0; i < childNode.entryNumber; ++i)
				childNode.nodeEntries[i] = entries[i];
			for (int i = 0; i < siblingNode.entryNumber; ++i)
				siblingNode.nodeEntries[i] = entries[i + childNode.entryNumber];

			updateParent(childNode);
			updateParent(siblingNode);

			childNode.writeNode();
			siblingNode.writeNode();

			node.nodeEntries[childIndex].key = getMinKey(childNode);
			node.nodeEntries[siblingIndex].key = getMinKey(siblingNode);
			node.writeNode();

			delete[] entries;
			return true;
		}
	}
	else {
		int biggerLenghth = childNode.nodeEntries[0].getEntryDataLength() * int(ceil((double)(childNode.entryNumber + siblingNode.entryNumber) / 2.0)) + sizeof(TreeNodeHead);
		if (biggerLenghth < (PAGESIZE / 2)) { // 此时可以merge
			childNode.siblingNodePagePointer = siblingNode.siblingNodePagePointer;
			for (int i = childNode.entryNumber; i < childNode.entryNumber + siblingNode.entryNumber - 1; ++i) {
				childNode.nodeEntries[i] = siblingNode.nodeEntries[i - childNode.entryNumber + 1];
			}
			childNode.entryNumber += siblingNode.entryNumber - 1; //merge 进childnode

			for (int i = siblingIndex; i < node.entryNumber; ++i)
				node.nodeEntries[i] = node.nodeEntries[i + 1];
			node.entryNumber--;
			node.writeNode();

			updateParent(childNode);
			childNode.writeNode();
			deleteNode(siblingNode);

			if (node.isUnderflow()) {
				if (isRoot(node)) {
					if (node.entryNumber == 1) {
						TreeNode tempNode = getNodeAtPage(node.nodeEntries[0].pagePointer);
						Page tempPage = node.nodePage;
						node = tempNode;
						node.nodePage = tempPage;
						updateParent(node);
						node.writeNode();
						deleteNode(tempNode);
						return true;
					}
					else {
						return true;
					}
				}
				else {
					return handelUnderflowInChildNodeOfNodePage(getNodeAtPage(node.parentNodePagePointer), node.nodePage.pageIndex);
				}
			}
			else {
				return true;
			}
		}
		else { // 此时需要 redistribute
			int tot = (childNode.entryNumber + siblingNode.entryNumber - 2);
			int mid = tot / 2;
			TreeItem *entries = new TreeItem[tot];
			for (int i = 1; i < childNode.entryNumber; ++i)
				entries[i - 1] = childNode.nodeEntries[i];
			for (int i = 1; i < siblingNode.entryNumber; ++i)
				entries[i + childNode.entryNumber - 2] = siblingNode.nodeEntries[i];

			childNode.entryNumber = mid;
			siblingNode.entryNumber = tot - mid;

			childNode.entryNumber++;
			siblingNode.entryNumber++;

			for (int i = 1; i < childNode.entryNumber; ++i)
				childNode.nodeEntries[i] = entries[i - 1];
			for (int i = 1; i < siblingNode.entryNumber; ++i)
				siblingNode.nodeEntries[i] = entries[i + childNode.entryNumber - 2];

			updateParent(childNode);
			updateParent(siblingNode);

			childNode.writeNode();
			siblingNode.writeNode();

			node.nodeEntries[childIndex].key = getMinKey(childNode);
			node.nodeEntries[siblingIndex].key = getMinKey(siblingNode);
			node.writeNode();

			delete[] entries;
			return true;
		}

	}
	assert(false);
	return false;
}

PageId BPTree::searchKeyForPagePointer(BPTreeKey key) {
	assert(key.type == keyType);
	assert(key.keyLen == keyDataLength);
	return searchKeyForPagePointerInNode(key, getNodeAtPage(ROOTPAGE));
}

PageId BPTree::searchKeyForPagePointerInNode(BPTreeKey key, TreeNode node) {
	assert(key.keyLen == node.keyDataLength);
	assert(key.type == node.keyType);
	if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
		for (int i = 0; i < node.entryNumber; ++i) {
			if (node.nodeEntries[i].key == key)
				return node.nodeEntries[i].pagePointer;
		}
	}
	else if (node.nodeType == BPTreeNodeType::BPTreeInternalNode) {
		if (key < node.nodeEntries[1].key) {
			return searchKeyForPagePointerInNode(key, getNodeAtPage(node.nodeEntries[0].pagePointer));
		}
		else {
			for (int i = node.entryNumber - 1; i > 0; --i) {
				if (key >= node.nodeEntries[i].key)
					return searchKeyForPagePointerInNode(key, getNodeAtPage(node.nodeEntries[i].pagePointer));
			}
		}
	}
	return UNDEFINEED_PAGE_NUM;
	assert(false); // Error
}

bool BPTree::isRoot(TreeNode node) {
	return node.nodePage.pageIndex == ROOTPAGE;
}

BPTreeKey BPTree::getMaxKey(TreeNode node) {
	assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
	assert(!node.isEmpty());
	if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
		return node.nodeEntries[node.entryNumber - 1].key;
	}
	else {
		return getMaxKey(getNodeAtPage(node.nodeEntries[node.entryNumber - 1].pagePointer));
	}
	assert(false); // Error
}

BPTreeKey BPTree::getMinKey(TreeNode node) {
	assert(node.nodeType != BPTreeNodeType::BPTreeUndefinedNode);
	assert(!node.isEmpty());
	if (node.nodeType == BPTreeNodeType::BPTreeLeafNode) {
		return node.nodeEntries[1].key;
	}
	else {
		return getMinKey(getNodeAtPage(node.nodeEntries[0].pagePointer));
	}
	assert(false); // Error
}
