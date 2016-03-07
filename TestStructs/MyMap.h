#pragma once


template <typename TKey, typename TValue>
class MyBinaryTree
{
protected:
	struct Node
	{
		Node(const TKey key, const TValue &value)
			: m_key(key)
			, m_value(value)
			, m_left(nullptr)
			, m_right(nullptr)
		{
		}
		TKey m_key;
		TValue m_value;
		Node *m_left;
		Node *m_right;
	};

	Node *m_root;
	size_t m_count;

	void destroy_tree()
	{
		inspect_each_node(m_root, 
			[this] (Node *node) 
			{
				free_node(node); 
			}
		);
	}

	template<typename TFunc>
	void inspect_each_node(Node *node, TFunc func)
	{
		if (node != nullptr)
		{
			inspect_each_node(node->m_left,  func);
			inspect_each_node(node->m_right, func);
			func(node);
		}
	}

	void free_node(Node *&node)
	{
		assert(m_count);
		delete node;
		node = nullptr;
		m_count--;
	}

	void insert_update(Node*& root, const TKey &key, const TValue &value)
	{
		if (!root)
		{
			root = new Node(key, value);
			m_count++;
		}
		else if (key == root->m_key)
		{
			// already exists - just update it
			root->m_value = value;
		}
		else if (key < root->m_key)
		{
			insert_update(root->m_left, key, value);
		}
		else
		{
			insert_update(root->m_right, key, value);
		}
	}

	Node * find_by_key(Node *node, const TKey &key)
	{
		if (!node)
		{
			return nullptr;
		}
		else if (key == node->m_key)
		{
			return node;
		}
		else if (key < node->m_key)
		{
			return find_by_key(node->m_left, key);
		}
		else
		{
			return find_by_key(node->m_right, key);
		}
	}

	Node * find_min(Node *node)
	{
		while (node && node->m_left != nullptr)
		{
			node = node->m_left;
		}
		return node;
	}

	Node * erase_node_by_key(Node *root, const TKey &key)
	{
		if (!root)
		{
			return nullptr;
		}
		else if (key < root->m_key)
		{
			root->m_left = erase_node_by_key(root->m_left, key)
		}
		else if (key > root->m_key)
		{
			root->m_right = erase_node_by_key(root->m_right, key);
		}
		else // it's a match
		{
			if (root->m_left == nullptr && root->m_right == nullptr)
			{
				// No children
				free_node(root);
			}
			else if (root->m_right && root->m_left == nullptr)
			{
				// one child on the right
				Node *temp = root;
				root = root->right;
				free_node(temp);
			}
			else if (root->m_left && root->m_right == nullptr)
			{
				// one child on the left
				Node *temp = root;
				root = root->m_left;
				free_node(temp);
			}
			else
			{
				// we have children on the left and right
				Node *temp = find_min(root->right);
				root->data = temp->data;
				root->right = erase_node_by_key(root->m_right, temp->m_key);
			}
		}
		return root;
	}

public:
	MyBinaryTree()
		: m_root(nullptr)
		, m_count(0)
	{}
	
	~MyBinaryTree()
	{
		destroy_tree();
		assert(m_count == 0);
	}

	size_t size() const
	{
		return m_count;
	}

	void set(const TKey &key, const TValue &value)
	{
		insert_update(m_root, key, value);
	}

	bool get(const TKey &key, TValue &value)
	{
		Node * finder = find_by_key(m_root, key);
		if (finder)
		{
			value = finder->m_value;
			return true;
		}
		return false;
	}

	bool contains(const TKey &key)
	{
		return nullptr != find_by_key(m_root, key);
	}

	void remove(const TKey &key)
	{
		erase_node_by_key(m_root, key);
	}

	template<typename TFunc>
	void iterate(TFunc func)
	{
		inspect_each_node(m_root, [&](Node *node) {
			func(node->m_key, node->m_value);
		});
	}

};


/*
	Learning all about Tries, basic US centeric alphabet
*/
class MyTries
{
	struct Node 
	{
		Node *m_children[26];
	};
public:

};