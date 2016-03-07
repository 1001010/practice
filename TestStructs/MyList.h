#pragma once

#include <assert.h>

/*
	Implements List collection classes

	Only usefull to me as coding practice. You realy shouldn't use it for anything. STL is much better
*/


// Test everything in this file
void MyList_UnitTest();

// Individual collection unit tests
void MyStack_UnitTest();
void MyDoubleLinkedList_UnitTest();


/*
	List based collection classes
*/
template <typename TData>
class MyStack
{
protected:
	struct Node 
	{
		Node(const TData &data, Node *next)
			: m_data(data)
			, m_next(next)
		{}
		TData m_data;
		Node *m_next;
	};

	typedef Node* NodePtr;

	NodePtr m_root;
	size_t m_count;

public:
	MyStack()
		: m_root(nullptr)
		, m_count(0)
	{}

	~MyStack()
	{
		NodePtr walk = m_root;
		NodePtr temp = nullptr;
		while (walk) {
			temp = walk;
			walk = walk->m_next;
			delete temp;
		}
	}

	void Push(const TData &data)
	{
		m_root = new Node(data, m_root);
		m_count++;
	}

	bool Pop(TData &data)
	{
		if (!m_root)
		{
			return false;
		}

		if (!m_count)
		{
			assert(!"BUG we have a root but our count is zero?");
			return false;
		}

		data = m_root->m_data;
		m_count--;

		NodePtr temp = m_root;
		m_root = m_root->m_next;

		delete temp;
		return true;
	}

	size_t Size() const
	{
		return m_count;
	}

	bool Validate() const
	{
		NodePtr walk = m_root;
		size_t counted = 0;
		while (walk)
		{
			counted++;
			if (counted > m_count)
			{
				assert(!"The count is too small");
				return false;
			}
			walk = walk->m_next;
		}
		if (counted != m_count)
		{
			assert(!"The count is off");
			return false;
		}
		return true;
	}

	bool FindValueNPositionsFromTheTail(TData &data, size_t count)
	{
		NodePtr node = m_root;

		if (count >= m_count || !node)
		{
			return false;
		}

		// n element pointer array that we fill and wrap around
		// [10][20][30]
		// once it wraps, the next position will contain N elements from the end

		size_t buffer_count = count + 1;
		NodePtr *history = new NodePtr[buffer_count];
		memset(history, 0, sizeof(history));

		size_t position = 0;
		while (node) 
		{
			history[position++ % buffer_count] = node;
			node = node->m_next;
		}

		bool result = false;
		if (position >= buffer_count)
		{
			data = (history[position % buffer_count])->m_data;
			result = true;
		}

		delete[] history;
		return result;
	}

	bool FindValueNPositionsFromTheHead(TData &data, size_t count)
	{
		if (count >= m_count || !m_root)
		{
			return false;
		}

		NodePtr node = m_root;
		for (size_t index = 0; index < count; index++)
		{
			if (node->m_next) 
			{
				node = node->m_next;
			}
			else 
			{
				assert(!"m_count is broken");
				return false;
			}
		}

		if (!node)
		{
			assert(!"node should be valid");
			return false;
		}

		data = node->m_data;
		return true;
	}
};


template <typename TData>
class MyDoubleLinkedList
{
protected:
	struct Node
	{
		Node(const TData &data, Node *prev, Node *next)
			: m_data(data)
			, m_prev(prev)
			, m_next(next)
		{
		}
		TData m_data;
		Node *m_next;
		Node *m_prev;
	};

	typedef Node* NodePtr;

	NodePtr m_root;
	size_t m_count;

	NodePtr FindLastNode()
	{
		NodePtr walk = m_root;
		while (walk && walk->m_next)
		{
			walk = walk->m_next;
		}
		return walk;
	}

public:
	MyDoubleLinkedList()
		: m_root(nullptr)
		, m_count(0)
	{}

	~MyDoubleLinkedList()
	{
		NodePtr walk = m_root;
		NodePtr temp = nullptr;
		while (walk)
		{
			temp = walk;
			walk = walk->m_next;
			delete temp;
		}
	}

	void PushHead(const TData &data)
	{
		m_count++;
		NodePtr node = new Node(data, nullptr, m_root);
		if (m_root)
		{
			m_root->m_prev = node;
		}
		m_root = node;
	}

	void PushTail(const TData &data)
	{
		m_count++;
		if (m_root)
		{
			NodePtr last = FindLastNode();
			last->m_next = new Node(data, last, nullptr);
		}
		else
		{
			m_root = new Node(data, nullptr, nullptr);
		}
	}

	bool PopHead(TData &data)
	{
		if (!m_root)
		{
			return false;
		}

		if (!m_count)
		{
			assert(!"BUG we have a root but our count is zero?");
			return false;
		}

		NodePtr temp = m_root;
		data = temp->m_data;

		m_root = m_root->m_next;
		if (m_root)
		{
			m_root->m_prev = nullptr;
		}

		delete temp;
		m_count--;
		return true;
	}

	bool PopTail(TData &data)
	{
		NodePtr last = FindLastNode();
		if (!last)
		{
			return false;
		}

		if (!m_count)
		{
			assert(!"BUG we have a node but our count is zero?");
			return false;
		}

		data = last->m_data;

		if (m_root == last)
		{
			m_root = nullptr;
		}
		else
		{
			last->m_prev->m_next = nullptr;
		}

		delete last;
		m_count--;
		return true;
	}

	size_t Size() const
	{
		return m_count;
	}

	bool Validate() const
	{
		if ((!m_count && m_root) || (m_count && !m_root))
		{
			assert(!"BUG: mismatch of empty count or empty root ");
			return false;
		}

		NodePtr walk = m_root;
		NodePtr last = nullptr;
		int counted = 0;
		while (walk)
		{
			counted++;
			if (counted > (int)m_count)
			{
				assert(!"The m_count is too small");
				return false;
			}
			if (walk->m_prev != last)
			{
				assert(!"m_prev is not pointing back to the prev node");
				return false;
			}
			last = walk;
			walk = walk->m_next;
		}
		if (counted != (int)m_count)
		{
			assert(!"The count is off");
			return false;
		}

		return true;
	}
};
