#ifndef MENU_DEFINED
#define MENU_DEFINED

#include "linked_list.h"
#include <iostream>
#include <string>

class imenu_entry
{
	protected:
	virtual void do_action() = 0;
	virtual string do_get_name() const = 0;

	public:
	void action() { do_action(); }
	string get_name() const { return do_get_name(); }
	virtual ~imenu_entry(){}
} ;

template<typename T>
class menu_entry : public imenu_entry
{
	private:
	T *m_pobject;
	void (T::*m_pmethod)();
	string m_name;
  
	protected:
	void do_action()
	{
		(m_pobject->*m_pmethod)();
	}
	string do_get_name() const
	{
		return m_name;
	}
 
	public:
	menu_entry(T *pobject, void (T::*pmethod)(), string name)
	: m_pobject(pobject), m_pmethod(pmethod), m_name(name)
	{}
} ;

class menu
{
	protected:
	linked_list<imenu_entry*> m_entries;
	virtual void do_display()
	{
		for(unsigned int i = 0; i < m_entries.length(); i++)
		{
			std::cout<<"("<<i<<") "<<m_entries[i]->content->get_name()<<std::endl;
		}
	}

	virtual void do_select()
	{
		unsigned int selection;
		std::cin>>selection;
		if(selection<m_entries.length())
			m_entries[selection]->content->action();
		else
			std::cout<<"Invalid menu entry!"<<endl;
		return;
	}

	public:
	virtual ~menu()
	{
		for(unsigned int i = 0 ; i < m_entries.length(); i++)
		{
			if(m_entries[i]->content)
				delete m_entries[i]->content;
		}
	}
  
	void add_entry(imenu_entry *entry)
	{
		m_entries.append_node();
		m_entries.last()->content = entry;
	}
  
	void display() { do_display(); }
	void select() { do_select(); }
} ;


#endif
