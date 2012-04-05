/*
 *  Reservation System - A programm to manage rect-shaped seatings
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
#include "room.h"

void print_menu();
void end_programm();

/*
 * Creates a new cinema (or else) room with given seats per rows and rows,
 * and the provides a simple menu for actions like reservations etc.
 */

int main()
{
	room theater; /* Create new object game of type game */
	uint menu;
	while(true)
		{
			print_menu();
			cin>>menu;
			switch(menu)
				{
				case 1:
					theater.print_room();
					break;
					/* Internal, sell ticket and hand out reserved ticket are equal */
				case 2:
				case 4:
					theater.handout();
					break;
				case 3:
					theater.reserve();
					break;
				case 5:
					theater.release();
					break;
				case 6:
					theater.cancel();
					break;
				case 7:
					theater.lock();
					break;
				case 8:
					theater.unlock();
					break;
				case 0:
					end_programm();
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

void end_programm()
{
	char confirm='n';
	while(true)
		{
			cout<<"Do you really want to quit programms?(y/N)"<<endl;
			cout<<"Your room will be lost!"<<endl;
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
					exit(0);
					break;
				default:
					cout<<"Invalid Input!"<<endl;
					break;
				}
		}
}
