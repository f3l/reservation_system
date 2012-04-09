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


/* Include basic headers */
#include<iostream>
#include<cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

/* And own headers needed */

#include "application.h"
#include "room.h"
#include "linked_list.h"
#include "menu.h"

/*
 * Creates a new cinema (or else) room with given seats per rows and rows,
 * and the provides a simple menu for actions like reservations etc.
 */

application::application()
{
	m_running = 1;
}

void application::run()
{
	menu Menu;
	linked_list<room*> theater(1); /* Create a linked list of rooms named theater */
	theater[0]->content = new room();
	node<room*>* current_room=theater[0]; /*We need a pointer for our different rooms*/
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::print_room, "View Room"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::handout, "Sell Ticket"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::reserve, "Reserve Ticket"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::handout, "Hand out reserved ticket"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::release, "Cancel reservation"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::cancel, "Take back ticket"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::lock, "Make seat unavailable"));
	Menu.add_entry(new menu_entry<room>(current_room->content, &room::unlock, "Make seat available"));
	Menu.add_entry(new menu_entry<application>(this, &application::end_program, "Exit"));

	while(m_running)
	{
		Menu.display();
		Menu.select();
	}

	delete theater[0]->content;
	return;
}

/* Asks for verification, if succesfull terminates process */

void application::end_program()
{
	char confirm='n';
	while(true)
		{
			cout<<"Do you really want to quit program?(y/N)"<<endl;
			cout<<"Your rooms will be lost!"<<endl;
			cin>>confirm;
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
