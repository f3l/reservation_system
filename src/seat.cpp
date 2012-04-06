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

/*
 *  The routines for class seat from "seat.h"
 */

#include <iostream>
#include <string>
#include <limits>
using namespace std;

/* Get the declarations needed for this file */
#include "seat.h"

seat::seat()
{
	/* When a new room gets created, we need to set some information */
	name="\0";
	state=FREE;
}

/* Maybe there's need for some kind  of "print", but how (superseed <<?), and for which purposes?*/

seat_state seat::get_state() /*Returns the current state, as it is private*/
{
	return state;
}

void seat::lock()
{
	state=LOCKED;
}

void seat::unlock()
{
	/*
	 * we need to check, whether the chosen seat
	 * is in state LOCKED, only then we can FREE
	 * him with this function
	 */
	if(state==LOCKED)
		{
			state=FREE;
		}
	else
		{
			cout<<"The chosen seat isn't locked. Aborting"<<endl;
		}
}

void seat::reserve()
/* Reserve a place for a person, needs the name! */
{
	/* The usual input at first */
	/* The seat needs to be in state FREE */
	if(!(state==FREE))
		{
			cout<<"This seat is not reservable! Aborting."<<endl;
			return;
		}
	
	/* THEN ask for name and save in set new state */
	cout<<"For whom should the reservation take place?"<<endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
	getline(cin, name);
	state=RESERVED;
}
	
void seat::release(uint row,uint line) /*ROW and LINE as machine index, starting with 0*/
{
	/* The seat must be Reserved to get released */
	if( ! (state==RESERVED))
		{
			cout<<"Seat isn't releasable! Aborting."<<endl;
			return;
		}
	
	/* We need an affirmation, we do quite similar to as input */
	char affirm='n';
	while(true)
		{
			cout<<"Do you really want to release the reservation of"<<endl;
			cout<<"seat "<<line+1<<" in row "<<row+1<<endl;
			cout<<"currently reserved for"<<endl;
			cout<<name<<"? (y/N)"<<endl;
			cin>>affirm;
			switch(affirm)
				{
					/* If user doesn't affirm, we stop the routine */
				case 'N':
				case 'n':
					return;
					break;
					/* If he does, we release the seat and exit */
				case 'Y':
				case 'y':
					name="\0";
					state=FREE;
					return;
					break;
					/* Otherwise, we give it another try */
				}
		}
}

void seat::handout(uint row,uint line)
{
	/*
	 * This time, we check whether it is free or reserverd and instantly
	 * ask for verification in the later case
	 */
	if( state==RESERVED)
		{
			char affirm='n';
			while(true)
				{
					cout<<"Do you really want to hand out the reservation of"<<endl;
					cout<<"seat "<<line+1<<" in row "<<row+1<<endl;
					cout<<"currently reserved for"<<endl;
					cout<<name<<"? (y/N)"<<endl;
					cin>>affirm;
					
					/*
					 * We can't use a switch/case here, because we need
					 * break for exiting the while-loop
					 */
					if(affirm=='y' || affirm =='Y')
						{
							break;
						}
					else if(affirm=='n' || affirm =='N')
						{
							return;
						}
					else
						{
							cout<<"Invalid input!"<<endl;
						}
				}
		}
	if( (state==FREE) || (state=RESERVED))
		{
			state=HANDED;
			name="\0";
			cout<<"Done"<<endl;
		}
	else
		{
			cout<<"The seat is not available!"<<endl;
			return;
		}
}

/* Take back cards (almost the same as release) */
void seat::cancel(uint row, uint line)
{
	/* The seat must be HANDED to get released */
	if( ! (state==HANDED))
		{
			return;
		}
	
	/* We need an affirmation, we do quite similar to as input */
	char affirm='n';
	while(true)
		{
			cout<<"Do you really want to cancel the card for"<<endl;
			cout<<"seat "<<line+1<<" in row "<<row+1<<"? (y/N)"<<endl;
			cin>>affirm;
			switch(affirm)
				{
					/* If user doesn't affirm, we stop the routine */
				case 'N':
				case 'n':
					return;
					break;
					/* If he does, we release the seat and exit */
				case 'Y':
				case 'y':
					name="\0";
					state=FREE;
					cout<<"Done"<<endl;
					return;
					break;
					/* Otherwise, we give it another try */
				}
		}
}