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
 *  Contact: ghost91@gmx.de or oli_r@fg4f.de
 *  Get current code at <http://www.github.com/f3l/reservation_system>
 */

  /* Both the declaration and implementation are done in this file, because the use of templates requires this */

#ifndef MENU_DEFINED
#define MENU_DEFINED

#include "linked_list.h"
#include "functions.h"
#include <iostream>
#include <string>

class imenu_entry
{
	protected:
	virtual void do_action() = 0;
	virtual string do_name() const = 0;

	public:
	void action() { do_action(); }
	string name() const { return do_name(); }
	virtual ~imenu_entry(){}
} ;

template<typename T>
class cmenu_entry : public imenu_entry
{
	private:
	T *m_pobject;
	void (T::*m_pmethod)();
	string m_name;
  
	protected:
	void do_action()
	{
		(m_pobject->*m_pmethod)();
		return;
	}
	string do_name() const
	{
		return m_name;
	}
 
	public:
	cmenu_entry(T *pobject, void (T::*pmethod)(), string name)
	: m_pobject(pobject), m_pmethod(pmethod), m_name(name)
	{}
} ;

class cmenu
{
 protected:
	clinked_list<imenu_entry*> m_entries;
	virtual void do_display()
	{
		for(unsigned int i = 0; i < m_entries.length(); i++)
			{
				std::cout<<"("<<i<<") "<<m_entries[i]->m_content->name()<<std::endl;
			}
	}
	
	virtual void do_select()
	{
		unsigned int selection;
		do_input(selection);
		if(selection<m_entries.length())
			m_entries[selection]->m_content->action();
		else
			std::cout<<"Invalid menu entry!"<<endl;
		return;
	}

 private:	
	template<typename T>
		void do_input(T& input)
		{
			while(true)
				{
					std::cin>>input;
					if(cin.fail())
						{
							cout<<"Invalid Input!"<<endl;
							flush_stream(cin);
						}
					else
						{
							return;
						}
				}
		}

	public:
	virtual ~cmenu()
	{
		for(unsigned int i = 0 ; i < m_entries.length(); i++)
			{
				if(m_entries[i]->m_content)
					delete m_entries[i]->m_content;
			}
	}
  
	void add_entry(imenu_entry *pentry)
	{
		m_entries.append_node();
		m_entries.last()->m_content = pentry;
	}
  
	void display() { do_display(); }
	void select() { do_select(); }
} ;


#endif
