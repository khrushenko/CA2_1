#ifndef _TREE_NODE_
#define _TREE_NODE_

template <typename TKey, typename TValue>
class BinaryTreeNode {
	TKey key;
	TValue value;
	BinaryTreeNode<TKey, TValue> * parentNode;
	BinaryTreeNode<TKey, TValue> * leftChildNode;
	BinaryTreeNode<TKey, TValue> * rightChildNode;

public:
	BinaryTreeNode(BinaryTreeNode<TKey, TValue> * parentNode, const TKey & key, const TValue & value) {
		this->parentNode = parentNode;
		this->key = key;
		this->value = value;
		this->leftChildNode = this->rightChildNode = 0;
	}

	~BinaryTreeNode() {
		delete leftChildNode;
		delete rightChildNode;
	}

	virtual BinaryTreeNode<TKey, TValue> * CreateLeftChildNode(const TKey & key, const TValue & value) {
		return CreateChildNode(true, key, value);
	}

	virtual BinaryTreeNode<TKey, TValue> * CreateRightChildNode(const TKey & key, const TValue & value) {
		return CreateChildNode(false, key, value);
	}

	virtual BinaryTreeNode<TKey, TValue> * CreateChildNode(bool createLeftChild, const TKey & key, const TValue & value) {
		BinaryTreeNode<TKey, TValue> * childNode = new BinaryTreeNode<TKey, TValue>(this, key, value);
		BinaryTreeNode<TKey, TValue> ** targetField = createLeftChild ? (& leftChildNode) : (& rightChildNode);
		if((* targetField) != 0)
			delete (* targetField);
		(* targetField) = childNode;
		return childNode;
	}

	virtual BinaryTreeNode<TKey, TValue> * LeftChildNode() const {
		return leftChildNode;
	}

	virtual BinaryTreeNode<TKey, TValue> * RightChildNode() const {
		return rightChildNode;
	}

	void ChildNodeToNull(bool leftNodeToNull) {
		BinaryTreeNode<TKey, TValue> ** targetField = (leftNodeToNull ? & leftChildNode : & rightChildNode);
		(* targetField) = 0;
	}

	virtual TKey Key() const {
		return key;
	}

	virtual TValue Value() const {
		return value;
	}

	virtual BinaryTreeNode<TKey, TValue> * Parent() const {
		return parentNode;
	}

	virtual void SetValue(const TValue & value) {
		this->value = value;
	}
};

#endif
