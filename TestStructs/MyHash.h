#pragma once
#include <assert.h>
#include <stdint.h>
#include <string>

void MyHash_UnitTest();

/* 
	[kv]  [kv]  null  [kv]    array of nodes containing key,value,pointer to a linked list
	      |           |
	      [kv]        [kv]    if there is a collision, it is appended to the list
		  |
		  [kv]

*/
class MyHashTableOfStringsToStrings
{
protected:
	enum {
		//TABLE_SIZE = 2,     // Good for debugging
		TABLE_SIZE = 100,   // Good for production
	};

	struct Node 
	{
		std::string m_key;
		std::string m_value;
		Node *m_next;
		
		Node(const std::string &key, const std::string &value)
			: m_next(nullptr)
			, m_key(key)
			, m_value(value)
		{}
	};
	typedef Node * NodePtr;
	NodePtr m_hashTable[TABLE_SIZE];
	size_t m_count;

	NodePtr node_new(const std::string &key, const std::string &value)
	{
		m_count++;
		return new Node(key, value);
	}

	void node_free(NodePtr &node)
	{
		assert(m_count);
		m_count--;
		delete node;
		node = nullptr;
	}

	int GetBucketIndex(const std::string &key) const
	{
		// Naive: sum of all chars modulo table_size
		int result = 0;
		for (auto i : key)
		{
			result = (result + (int)i) % TABLE_SIZE;
		}
		return result;
	}

	Node * find_node(const std::string &key)
	{
		int bucket_index = GetBucketIndex(key);
		NodePtr walk = m_hashTable[bucket_index];
		while (walk)
		{
			if (walk->m_key == key)
			{
				return walk;
			}
			walk = walk->m_next;
		}
		return nullptr;
	}

	template<typename TFunc>
	void inspect_each_item(TFunc func)
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			int depth = 0;
			NodePtr node = m_hashTable[i];
			while (node)
			{
				func(i, depth++, node);
				node = node->m_next;
			}
		}
	}

public:

	MyHashTableOfStringsToStrings()
		: m_count(0)
	{
		memset(m_hashTable, 0, sizeof(m_hashTable));
	}

	~MyHashTableOfStringsToStrings()
	{
		for (int i = 0; i < TABLE_SIZE; i++)
		{
			NodePtr node = m_hashTable[i];
			while (node)
			{
				NodePtr temp = node;
				node = node->m_next;
				node_free(temp);
			}
		}
		assert(m_count == 0);
	}

	void Set(const std::string &key, const std::string &value)
	{
		int bucket_index = GetBucketIndex(key);

		// Create the bucket?
		if (!m_hashTable[bucket_index])
		{
			m_hashTable[bucket_index] = node_new(key, value);
			return;
		}

		// Walk the nodes until we find the same key or the end
		Node * walk = m_hashTable[bucket_index];
		while (walk)
		{
			if (walk->m_key == key)
			{
				// Update the existing value
				walk->m_value = value;
				break;
			}
			else
			if (walk->m_next == nullptr)
			{
				// This is the last node, add a new one
				walk->m_next = node_new(key, value);
				break;
			}
			else
			{
				// walk to the next node 
				walk = walk->m_next;
			}
		}
	}

	bool Lookup(const std::string &key, std::string &value)
	{
		NodePtr node = find_node(key);
		if (!node)
		{
			return false;
		}
		value = node->m_value;
		return true;
	}

	void dump()
	{
		printf("MaxBuckets: %d, Total Elements: %zd\n", TABLE_SIZE, m_count);
		inspect_each_item([](int bucket, int depth, Node* node) {
			printf("%2d %2d K:%s V:%s\n", bucket, depth, node->m_key.c_str(), node->m_value.c_str());
		});
	}
};
