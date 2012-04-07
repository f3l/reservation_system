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
/*#include "seat.h"*/
#include "room.h"
#include "linked_list.h"

void print_menu();
int end_program();

/*
 * Creates a new cinema (or else) room with given seats per rows and rows,
 * and the provides a simple menu for actions like reservations etc.
 */

int main()
{
	linked_list<room*> theater(1); /* Create a linked list of rooms named theater */
	theater[0]->content = new room();
	node<room*>* current_room=theater[0]; /*We need a pointer for our different rooms*/

	uint menu;
	while(true)
		{
			print_menu();
			cin>>menu;
			switch(menu)
				{
				case 1:
					current_room->content->print_room();
					break;
					/* Internal, sell ticket and hand out reserved ticket are equal */
				case 2:
				case 4:
					current_room->content->handout();
					break;
				case 3:
					current_room->content->reserve();
					break;
				case 5:
					current_room->content->release();
					break;
				case 6:
					current_room->content->cancel();
					break;
				case 7:
					current_room->content->lock();
					break;
				case 8:
					current_room->content->unlock();
					break;
				case 0:
					if(end_program())
						{
							for(unsigned int i = 0; i < theater.length(); i++)	
								delete theater[i]->content;
							exit(0);
						}
					break;
				default:
					cout<<"Invalid Input"<<endl;
				}
		}
	return 0;
}


/* Prints main-menu (nothing more, nothing less) */
void print_menu()
{
	cout<<"Possible choices:"<<endl;
	cout<<"(1) View room"<<endl;
	cout<<"(2) Sell ticket"<<endl;
	cout<<"(3) Reserve ticket"<<endl;
	cout<<"(4) Hand out reserved ticket"<<endl;
	cout<<"(5) Cancel reservation"<<endl;
	cout<<"(6) Take back ticket"<<endl;
	cout<<"(7) Make seat unavailable"<<endl;
	cout<<"(8) Make seat available"<<endl;
	cout<<"(0) Exit";
	cout<<endl<<"Your Choice?"<<endl;
	return;
}

/* Asks for verification, if succesfull terminates process */

int end_program()
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
					return 0;
					break;
				case 'Y':
				case 'y':
					cout<<"Exiting"<<endl;
					return 1;
					break;
				default:
					cout<<"Invalid Input!"<<endl;
					break;
				}
		}
}
