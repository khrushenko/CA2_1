#ifndef _BINARY_TREE_
#define _BINARY_TREE_

#include "IKeysComparer.h"
#include "BinaryTreeNode.h"
#include <queue>

using namespace std;

template <typename TKey, typename TValue>
class BinaryTree {
	IKeysComparer<TKey> * comparer;
	BinaryTreeNode<TKey, TValue> * rootNode;

public:
	BinaryTree(IKeysComparer<TKey> * comparer) {
		this->comparer = comparer;
		rootNode = 0;
	}

	~BinaryTree() {
		delete rootNode;
	}

	bool ContainsKey(const TKey & key) const {
		return FindNodeForKey(key) != 0;
	}

	bool Remove(const TKey & key) {
		BinaryTreeNode<TKey, TValue> * nodeToRemove = FindNodeForKey(key);
		if(nodeToRemove == 0)
			return false;
		queue<BinaryTreeNode<TKey, TValue> *> nodesQueue;
		if(nodeToRemove->LeftChildNode() != 0)
			nodesQueue.push(nodeToRemove->LeftChildNode());
		if(nodeToRemove->RightChildNode() != 0)
			nodesQueue.push(nodeToRemove->RightChildNode());
		BinaryTreeNode<TKey, TValue> * parentNode = nodeToRemove->Parent();
		if(parentNode != 0)
			parentNode->ChildNodeToNull(parentNode->LeftChildNode() == nodeToRemove);
		else
			rootNode = 0;
		while(!nodesQueue.empty()) {
			BinaryTreeNode<TKey, TValue> * node = nodesQueue.front();
			InsertIntoNode(parentNode, node->Key(), node->Value(), true);
			if(node->LeftChildNode() != 0)
				nodesQueue.push(node->LeftChildNode());
			if(node->RightChildNode() != 0)
				nodesQueue.push(node->RightChildNode());
			nodesQueue.pop();
		}
		delete nodeToRemove;
		return true;
	}

	bool InsertIfNotExists(const TKey & key, const TValue & value) {
		return InsertIntoNode(0, key, value, false);
	}

	bool InsertAnyway(const TKey & key, const TValue & value) {
		return InsertIntoNode(0, key, value, true);
	}

	bool TryGetValue(const TKey & key, TValue * outValue) const {
		BinaryTreeNode<TKey, TValue> * node = FindNodeForKey(key);
		if(node == 0)
			return false;
		(* outValue) = node->Value();
		return true;
	}

private:
	BinaryTreeNode<TKey, TValue> * FindNodeForKey(const TKey & key) const {
		BinaryTreeNode<TKey, TValue> * currentNode = rootNode;
		while(currentNode != 0) {
			int compareResult = comparer->Compare(key, currentNode->Key());
			if(compareResult == 0)
				return currentNode;
			else if(compareResult < 0)
				currentNode = currentNode->LeftChildNode();
			else
				currentNode = currentNode->RightChildNode();
		}
		return currentNode;
	}

	bool InsertIntoNode(BinaryTreeNode<TKey, TValue> * node, const TKey & key, const TValue & value, bool insertAnyway) {
		if(node == 0) {
			if(rootNode == 0) {
				rootNode = new BinaryTreeNode<TKey, TValue>(0, key, value);
				return !insertAnyway;
			}
			node = rootNode;
		}
		if(comparer->Compare(key, node->Key()) == 0) {
			if(insertAnyway)
				node->SetValue(value);
			return insertAnyway;
		}
		bool leftNodeNeeded = comparer->Compare(key, node->Key()) < 0;
		BinaryTreeNode<TKey, TValue> * targetNode = (leftNodeNeeded ? node->LeftChildNode() : node->RightChildNode());
		if(targetNode != 0)
			return InsertIntoNode(targetNode, key, value, insertAnyway);
		node->CreateChildNode(leftNodeNeeded, key, value);
		return !insertAnyway;
	}
};

#endif
