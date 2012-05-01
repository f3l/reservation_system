/*
 *  Reservation System - A program to manage rect-shaped seatings
 *  Copyright (C) 2012 Johannes Loher / Oliver Rümpelein
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact: jloher@gmx.net or oli_r@fg4f.de
 *  Get current code at <http://www.github.com/f3l/reservation_system>
 */

 /* Both the declaration and implementation are done in this file, because the use of templates requires this */

#ifndef LINKED_LIST_DEFINED
#define LINKED_LIST_DEFINED

#include <stdexcept>

/******************/
/*  Declaration   */
/******************/

template <class T> /* We need to declare this first, so node can have this as a friend :) */
class clinked_list;


/* Declaration of the node class */

template <class T>
class cnode
{
	friend class clinked_list<T>; /* Needed so that linked_list can write to private members of node */

public:
	T m_content;

	/* Getter functions */
	cnode<T> *next() { return m_pnext; }

	/* Normal functions */
	cnode();
	cnode(const T& content);
	virtual ~cnode();

private: 
	cnode<T> *m_pnext;
};

/* Declaration of the linked_list class */

template <class T>
class clinked_list
{
public:
	/* Getter funtions */
	T& first();
	T& last();
	unsigned int length() { return m_length; }

	/* Normal fuctions */
	clinked_list();
	clinked_list(unsigned int length);
	virtual ~clinked_list();
	virtual void append();
	virtual void append(const T& content);
	virtual void insert(unsigned int pos);
	virtual void insert(const T& content, unsigned int pos);
	virtual void remove(unsigned int pos);
	T& operator [] (unsigned int n);

private:
	cnode<T> *m_pfirst, *m_plast;
	unsigned int m_length;
};


/******************/
/* Implementation */
/******************/


/* Implementation of the node class */

template <class T>
cnode<T>::cnode() : m_pnext(0)
{

}

template <class T>
cnode<T>::cnode(const T& content) : m_content(content), m_pnext(0)
{

}

template <class T>
cnode<T>::~cnode()
{

}


/* Implementation of the linked_list class */

template <class T>
T& clinked_list<T>::first()
{
	if(!m_pfirst)
		throw std::out_of_range("element does not exist!");
	return m_pfirst->m_content;
}

template <class T>
T& clinked_list<T>::last()
{
	if(!m_plast)
		throw std::out_of_range("element does not exist!");
	return m_plast->m_content;
}

template <class T>
clinked_list<T>::clinked_list()
{
	m_length = 0;
	m_pfirst = 0;
	m_plast = 0;
}

template <class T>
clinked_list<T>::clinked_list(unsigned int length)
{
	m_length = length;
	m_pfirst = new cnode<T>;
	cnode<T> *pcurrent_node = m_pfirst;
	for(unsigned int i = 0; i < m_length - 1; i++)
		{
			pcurrent_node->m_pnext = new cnode<T>;
			pcurrent_node = pcurrent_node->m_pnext;
		}
	m_plast = pcurrent_node;
}

template <class T>
clinked_list<T>::~clinked_list()
{
	cnode<T> *pcurrent_node, *pprevious_node;
	pcurrent_node = m_pfirst;
	while(pcurrent_node)
		{
			pprevious_node = pcurrent_node;
			pcurrent_node = pcurrent_node->m_pnext;
			delete pprevious_node;
		}
}

template <class T>
void clinked_list<T>::append()
{
	cnode<T> *pnew_node = new cnode<T>;
	if(m_pfirst)
		{
			cnode<T> *pcurrent_node = m_pfirst;
			while(pcurrent_node->m_pnext)
				pcurrent_node = pcurrent_node->m_pnext;
			pcurrent_node->m_pnext = pnew_node;
		}
	else
		{
			m_pfirst = pnew_node;
		}
	m_plast = pnew_node;
	m_length++;
	return;
}

template <class T>
void clinked_list<T>::append(const T& content)
{
	cnode<T> *pnew_node = new cnode<T>(content);
	if(m_pfirst)
		{
			cnode<T> *pcurrent_node = m_pfirst;
			while(pcurrent_node->m_pnext)
				pcurrent_node = pcurrent_node->m_pnext;
			pcurrent_node->m_pnext = pnew_node;
		}
	else
		{
			m_pfirst = pnew_node;
		}
	m_plast = pnew_node;
	m_length++;
	return;
}

template <class T>
void clinked_list<T>::insert(unsigned int pos)
{
	cnode<T> *pnew_node = new cnode<T>;

	if(pos == 0) /* Create a new node at the start of the list and set m_pfirst to point to the new node */
		{
			pnew_node->m_pnext = m_pfirst;
			m_pfirst = pnew_node;
		}
	else /* Insert a node somewhere inside or at the end of the list */
		{
			cnode<T> *pcurrent_node = m_pfirst;
			for(unsigned int i = 0; i < pos - 1; i++)
				{
					if(pcurrent_node->m_pnext)
						pcurrent_node = pcurrent_node->m_pnext;
					else
						break;
				}
			pnew_node->m_pnext = pcurrent_node->m_pnext;
			pcurrent_node->m_pnext = pnew_node;
			if(m_plast == pcurrent_node)
				m_plast = pnew_node;
		}
	m_length++;

	return;
}

template <class T>
void clinked_list<T>::insert(const T& content, unsigned int pos)
{
	cnode<T> *pnew_node = new cnode<T>(content);

	if(pos == 0) /* Create a new node at the start of the list and set m_pfirst to point to the new node */
		{
			pnew_node->m_pnext = m_pfirst;
			m_pfirst = pnew_node;
		}
	else /* Insert a node somewhere inside or at the end of the list */
		{
			cnode<T> *pcurrent_node = m_pfirst;
			for(unsigned int i = 0; i < pos - 1; i++)
				{
					if(pcurrent_node->m_pnext)
						pcurrent_node = pcurrent_node->m_pnext;
					else
						break;
				}
			pnew_node->m_pnext = pcurrent_node->m_pnext;
			pcurrent_node->m_pnext = pnew_node;
			if(m_plast == pcurrent_node)
				m_plast = pnew_node;
		}
	m_length++;

	return;
}

template <class T>
void clinked_list<T>::remove(unsigned int pos)
{
	cnode<T> *ptemp, *pcurrent_node = m_pfirst;
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
						return;
				}
			ptemp = pcurrent_node->m_pnext;
			pcurrent_node->m_pnext = ptemp->m_pnext;
			if(m_plast == ptemp)
				m_plast = pcurrent_node;
			delete ptemp;
		}
	m_length--;
	return;
}

template <class T>
T& clinked_list<T>::operator [] (unsigned int n)
{
	cnode<T> *pcurrent_node = m_pfirst;
	if(!pcurrent_node)
		throw std::out_of_range("element does not exist!");
	for(unsigned int i = 0; i < n; i++)
		{
			if(pcurrent_node->m_pnext)
				pcurrent_node = pcurrent_node->m_pnext;
			else
				throw std::out_of_range("element does not exist!");
		}
	return pcurrent_node->m_content;
}

#endif