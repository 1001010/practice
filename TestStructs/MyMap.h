#pragma once

#include <stdint.h>
#include <assert.h>
#include <iostream>

void MyMap_UnitTest();

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

	typedef Node * NodePtr;

	NodePtr m_root;
	size_t m_count;

	void destroy_tree()
	{
		inspect_each_node(m_root, 
			[this] (NodePtr node)
			{
				free_node(node); 
			},
			true
		);
	}

	template<typename TFunc>
	void inspect_each_node(NodePtr node, TFunc func, bool children_first)
	{
		if (node != nullptr)
		{
			if (children_first)
			{
				// good for deleting child nodes safely
				inspect_each_node(node->m_left,  func, children_first);
				inspect_each_node(node->m_right, func, children_first);
				func(node);
			}
			else
			{
				// good for debug dumps
				func(node);
				inspect_each_node(node->m_left,  func, children_first);
				inspect_each_node(node->m_right, func, children_first);
			}
		}
	}

	void free_node(NodePtr &node)
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

	NodePtr find_by_key(NodePtr node, const TKey &key)
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

	NodePtr find_min(NodePtr node)
	{
		while (node && node->m_left != nullptr)
		{
			node = node->m_left;
		}
		return node;
	}

	NodePtr erase_node_by_key(NodePtr node, const TKey &key)
	{
		if (!node)
		{
			return nullptr;
		}
		else if (key < node->m_key)
		{
			node->m_left = erase_node_by_key(node->m_left, key);
		}
		else if (key > node->m_key)
		{
			node->m_right = erase_node_by_key(node->m_right, key);
		}
		else // it's a match
		{
			if (node->m_left == nullptr && node->m_right == nullptr)
			{
				// No children
				free_node(node);
			}
			else if (node->m_right && node->m_left == nullptr)
			{
				// one child on the right
				NodePtr temp = node;
				node = node->m_right;
				free_node(temp);
			}
			else if (node->m_left && node->m_right == nullptr)
			{
				// one child on the left
				NodePtr temp = node;
				node = node->m_left;
				free_node(temp);
			}
			else
			{
				// we have children on the left and right
				/*
				  node
				 /    \
				L      R
				      / \
				   RL1   RR1
				*/
				// find the lowest value on the right side to replace node with
				NodePtr temp = find_min(node->m_right);
				assert(temp->m_left == nullptr);
				node->m_key   = temp->m_key;
				node->m_value = temp->m_value;
				node->m_right = erase_node_by_key(node->m_right, temp->m_key);
			}
		}
		return node;
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
		NodePtr finder = find_by_key(m_root, key);
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
		m_root = erase_node_by_key(m_root, key);
	}

	template<typename TFunc>
	void iterate(TFunc func)
	{
		inspect_each_node(m_root, [&](NodePtr node) {
			func(node->m_key, node->m_value);
		}, false);
	}

	void dump()
	{
		printf("\n");
		inspect_each_node(m_root, [&](NodePtr node) {
			
			// memory addresses!
			printf("%p <- %p -> %p",
				node->m_left,
				node,
				node->m_right);
			
			if (std::is_same<TKey, int>::value)
			{
				// pretty print the ints
				printf(" | %3d <- %3d -> %3d",
					node->m_left  ? node->m_left->m_key  : -1,
					node->m_key,
					node->m_right ? node->m_right->m_key : -1);
			}
			printf("\n");
		}, false);
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