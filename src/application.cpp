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
 * Provides a simple menu to create, edit and delete rooms.
 * When editing a room, you have the option to make reservations etc. 
 */

capplication::capplication() : m_running(1), m_return_to_main_menu(1)
{
	/* Add the menuetries for the main menu*/
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::list_rooms, "List rooms"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::add_room, "Add a room"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::edit_room, "Edit a room"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::delete_room, "Delete a room"));
	m_main_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::end_program, "Quit"));
}

capplication::~capplication()
{
	/* Free the memory of all rooms that are available */
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
	for(unsigned int i = 0; i < m_rooms.length(); i++)
		if(m_rooms[i])
			cout<<i+1<<": "<<m_rooms[i]->name()<<endl;
	return;
}

void capplication::add_room()
{
	m_rooms.append(new croom);
	return;
}

void capplication::edit_room()
{
	unsigned int selection = 0;
	croom* pcurrent_room;
	/* Loop until we got a valid selection or until the user abborted */
	do
		{
			cout<<"Please enter the number of the room you want to edit! (Enter 0 to abbort)"<<endl;
			do_input(selection);
			if(selection == 0)
				return;
			/* We need a try/catch clock here, because clinked_list throws an exception, if the element we want to access does not exist */
			try
				{
					pcurrent_room = m_rooms[selection-1];
				}
			catch(out_of_range)
				{
					pcurrent_room = 0;
				}
			if(!pcurrent_room)
				cout<<"There is no room corresponding to the number you entered."<<endl;
		}
	while(!pcurrent_room);

	/* Create the room menu */
	cmenu room_menu;
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::print, "View Room"));
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::handout, "Sell Ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::reserve, "Reserve Ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::handout, "Hand out reserved ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::release, "Cancel reservation"));
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::cancel, "Take back ticket"));
	room_menu.add_entry(new cmenu_entry<croom>(pcurrent_room, &croom::lock, "Make seat unavailable"));
	room_menu.add_entry(new cmenu_entry<capplication>(this, &capplication::return_to_main_menu, "Return to main menu"));

	/* Show the room menu and select entries from it as long as we are not returning to the main menu */
	m_return_to_main_menu = 0;
	while(!m_return_to_main_menu)
		{
			room_menu.display();
			room_menu.select();
		}
	return;
}

void capplication::delete_room()
{
	unsigned int selection = 0;
	croom* pcurrent_room;
	/* Loop until we got a valid selection or until the user abborted */
	do
		{
			cout<<"Please enter the number of the room you want to delete! (Enter 0 to abbort)"<<endl;
			do_input(selection);
			if(selection == 0)
				return;
			/* We need a try/catch clock here, because clinked_list throws an exception, if the element we want to access does not exist */
			try
				{
					pcurrent_room = m_rooms[selection-1];
				}
			catch(out_of_range)
				{
					pcurrent_room = 0;
				}
			if(!pcurrent_room)
				cout<<"There is no room corresponding to the number you entered."<<endl;
		}
	while(!pcurrent_room);

	delete pcurrent_room;			/* Free the memory of the room we want to delete */
	m_rooms.remove(selection-1);	/* Remove the room from the linked list */
	return;
}

void capplication::return_to_main_menu()
{
	/* Return to main menu */
	m_return_to_main_menu = 1;
}

/* Asks for verification, if succesfull terminates process */

void capplication::end_program()
{
	char confirm = 'n';
	while(true)
		{
			cout<<"Do you really want to quit the program?(y/N)"<<endl;
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
					break;
				}
		}
}
