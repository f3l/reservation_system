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

#ifndef MENU_DEFINED
#define MENU_DEFINED

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>

#include "tl_functions.h"

using namespace std;

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

class cmenu_entry : public imenu_entry
{
	private:
	function<void()> m_func;
	string m_name;
  
	protected:
	void do_action()
	{
		m_func();
		return;
	}
	string do_name() const
	{
		return m_name;
	}
 
	public:
	cmenu_entry(function<void()> func, string name)
	: m_func(func), m_name(name)
	{}
} ;

class cmenu
{
 protected:
	vector<imenu_entry*> m_entries;
	virtual void do_display()
	{
		for(auto entry = m_entries.begin(); entry != m_entries.end(); ++entry)
			{
				cout<<"("<<entry - m_entries.begin()<<") "<<(*entry)->name()<<endl;
			}
	}
	
	virtual void do_select()
	{
		unsigned int selection;
		do_input(selection);
		try
			{
				m_entries.at(selection)->action();
			}
		catch(out_of_range)
			{
				cout<<"Invalid menu entry!"<<endl;
			}
		return;
	}

	public:
	virtual ~cmenu()
	{
		for(auto current_entry : m_entries)
			delete current_entry;
	}
  
	void add_entry(imenu_entry *pentry)
	{
		m_entries.push_back(pentry);
	}
  
	void display() { do_display(); }
	void select() { do_select(); }
} ;


#endif
