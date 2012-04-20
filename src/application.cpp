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


/* Include basic headers */
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#ifdef _WIN32
	#include <windows.h>
#endif

/* And own headers needed */
#include "application.h"
#include "room.h"
#include "menu.h"
#include "linked_list.h"
#include "tl_functions.h"

using namespace std;

/*
 * Creates the first cinema (or else) room with given seats per rows and rows,
 * and then provides a simple menu for actions like reservations, etc.
 */

capplication::capplication()
{
	m_running = 1;
	m_room_edit_mode = 0;
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::list_rooms, "List rooms"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::add_room, "Add a room"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::edit_room, "Edit a room"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::delete_room, "Delete a room"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::end_program, "Quit"));
}

capplication::~capplication()
{
	for(unsigned int i = 0; i < m_rooms.length(); i++)
		if(m_rooms[i])
			delete m_rooms[i];
}

void capplication::run()
{
	while(m_running)
		{
			m_main_menu.display();
			m_main_menu.select();
		}
	return;
}

void capplication::list_rooms()
{
	for(unsigned int i; i < m_rooms.length(); i++)
		if(m_rooms[i])
			cout<<i+1<<": "<<m_rooms[i]->name()<<endl;
	return;
}

void capplication::add_room()
{
	m_rooms.append();
	m_rooms.last() = new croom;
	return;
}

void capplication::edit_room()
{
	unsigned int selection = 0;
	do
		{
			cout<<"Please enter the number of the room you want to edit! (Enter 0 to abbort)"<<endl;
			do_input(selection);
			if(selection == 0)
				return;
			try
				{
					m_pcurrent_room = m_rooms[selection-1];
				}
			catch(...)
				{
					m_pcurrent_room = 0;
				}
			if(!m_pcurrent_room)
				cout<<"There is no room corresponding to the number you entered."<<endl;
		}
	while(!m_pcurrent_room);
	cmenu room_menu;
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::print, "View Room"));
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::handout, "Sell Ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::reserve, "Reserve Ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::handout, "Hand out reserved ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::release, "Cancel reservation"));
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::cancel, "Take back ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(m_pcurrent_room, &croom::lock, "Make seat unavailable"));
	room_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::exit_room_edit, "Return to main menu"));

	m_room_edit_mode = 1;
	while(m_room_edit_mode)
		{
			room_menu.display();
			room_menu.select();
		}
	return;
}

void capplication::delete_room()
{
	unsigned int selection = 0;
	do
		{
			cout<<"Please enter the number of the room you want to delete! (Enter 0 to abbort)"<<endl;
			do_input(selection);
			if(selection == 0)
				return;
			try
				{
					m_pcurrent_room = m_rooms[selection-1];
				}
			catch(...)
				{
					m_pcurrent_room = 0;
				}
			if(!m_pcurrent_room)
				cout<<"There is no room corresponding to the number you entered."<<endl;
		}
	while(!m_pcurrent_room);
	delete m_pcurrent_room;
	m_rooms.remove(selection-1);
	return;
}

void capplication::exit_room_edit()
{
	m_room_edit_mode = 0;
}

/* Asks for verification, if succesfull terminates process */

void capplication::end_program()
{
	char confirm = 'n';
	while(true)
		{
			cout<<"Do you really want to quit program?(y/N)"<<endl;
			cout<<"Your rooms will be lost!"<<endl;
			
			do_input(confirm);
			switch(confirm)
				{
				case 'N':
				case 'n':
					return;
					break;
				case 'Y':
				case 'y':
					cout<<"Exiting"<<endl;
					m_running = 0;
					return;
					break;
				default:
					cout<<"Invalid Input!"<<endl;
					cin.clear();
					cin.ignore();
					break;
				}
		}
}
