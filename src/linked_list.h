#ifndef LINKED_LIST_DEFINED
#define LINKED_LIST_DEFINED


/******************/
/*  Declaration   */
/******************/

template <class T> /* We need to declare this first, so node can have this as a fried :) */
class linked_list;


/* Declaration of the node class */

template <class T>
class node
{
	friend class linked_list<T>; /* Needed so that linked_list can write to private members of node */

public:
	T content;

	/* Getter functions */
	node<T> *next() { return m_pnext; }

	/* Normal functions */
	node();
	virtual ~node();

private: 
	node<T> *m_pnext;
};

/* Declaration of the linked_list class */

template <class T>
class linked_list
{
public:
	/* Getter funtions */
	node<T> *first() { return m_pfirst; }
	node<T> *last() { return m_plast; }
	unsigned int length() { return m_length; }

	/* Normal fuctions */
	linked_list();
	linked_list(unsigned int length);
	virtual ~linked_list();
	virtual void append_node();
	virtual void insert_node(unsigned int pos);
	virtual void delete_node(unsigned int pos);
	node<T> *operator [] (unsigned int n);

private:
	node<T> *m_pfirst, *m_plast;
	unsigned int m_length;
};


/******************/
/* Implementation */
/******************/


/* Implementation of the node class */

template <class T>
node<T>::node()
{
	m_pnext = 0;
}

template <class T>
node<T>::~node()
{

}


/* Implementation of the linked_list class */

template <class T>
linked_list<T>::linked_list()
{
	m_length = 0;
}

template <class T>
linked_list<T>::linked_list(unsigned int length)
{
	m_length = length;
	m_pfirst = new node<T>;
	node<T> *pcurrent_node = m_pfirst;
	for(unsigned int i = 0; i < m_length - 1; i++)
	{
		pcurrent_node->m_pnext = new node<T>;
		pcurrent_node = pcurrent_node->m_pnext;
	}
	m_plast = pcurrent_node;
}

template <class T>
linked_list<T>::~linked_list()
{
	node<T> *pcurrent_node, *pprevious_node;
	pcurrent_node = m_pfirst;
	while(pcurrent_node)
	{
		pprevious_node = pcurrent_node;
		pcurrent_node = pcurrent_node->m_pnext;
		delete pprevious_node;
	}
}

template <class T>
void linked_list<T>::append_node()
{
	node<T> *pcurrent_node = m_pfirst;
	node<T> *pnew_node = new node<T>;
	while(pcurrent_node->m_pnext)
		pcurrent_node = pcurrent_node->m_pnext;
	pcurrent_node->m_pnext = pnew_node;
	m_length++;
	return;
}

template <class T>
void linked_list<T>::insert_node(unsigned int pos)
{
	node<T> *pnew_node = new node<T>;

	if(pos == 0) /* Create a new node at the start of the list and set m_pfirst to point to the new node */
	{
		pnew_node->m_pnext = m_pfirst;
		m_pfirst = pnew_node;
	}
	else /* Insert a node somewhere inside or at the end of the list */
	{
		node<T> *pcurrent_node = m_pfirst;
		for(unsigned int i = 0; i < pos - 1; i++)
		{
			if(pcurrent_node->m_pnext)
				pcurrent_node = pcurrent_node->m_pnext;
			else
				break;
		}
		pnew_node->m_pnext = pcurrent_node->m_pnext;
		pcurrent_node->m_pnext = pnew_node;
	}
	m_length++;

	return;
}

template <class T>
void linked_list<T>::delete_node(unsigned int pos)
{
	node<T> *ptemp, *pcurrent_node = m_pfirst;
	if(pos == 0) /* Delete the first node */
	{
		m_pfirst = pcurrent_node->m_pnext;
		delete pcurrent_node;
	}
	else /* Delete other nodes */
	{
		for(unsigned int i = 0; i < pos - 1; i++)
		{
			if(pcurrent_node->m_pnext)
				pcurrent_node = pcurrent_node->m_pnext;
			else
			{
				return;
			}
		}
		ptemp = pcurrent_node->m_pnext;
		pcurrent_node->m_pnext = ptemp->m_pnext;
		delete ptemp;
	}
	m_length--;
	return;
}

template <class T>
node<T> *linked_list<T>::operator [] (unsigned int n)
{
	node<T> *pcurrent_node = m_pfirst;
	for(unsigned int i = 0; i < n; i++)
	{
		if(pcurrent_node->m_pnext)
			pcurrent_node = pcurrent_node->m_pnext;
		else
			return 0;
	}
	return pcurrent_node;
}

#endif