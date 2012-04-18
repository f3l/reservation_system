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
}

void capplication::run()
{
	cmenu menu;
	clinked_list<croom*> theater(1); /* Create a linked list of rooms named theater */
	theater[0] = new croom();
	croom* current_room = theater[0]; /* We need a pointer for our different rooms */
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::print_room, "View Room"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::handout, "Sell Ticket"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::reserve, "Reserve Ticket"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::handout, "Hand out reserved ticket"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::release, "Cancel reservation"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::cancel, "Take back ticket"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::lock, "Make seat unavailable"));
	menu.add_entry(new cmenu_entry<croom>(current_room, &croom::unlock, "Make seat available"));
	menu.add_entry(new cmenu_entry<capplication>(this, &capplication::end_program, "Exit"));

	while(m_running)
		{
			menu.display();
			menu.select();
		}

	delete theater[0];
	return;
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
