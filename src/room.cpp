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
 *  The routines for class room from "room.h"
 */

#include <iostream>
#include <string>
#include <limits>

/* We need some windows specific stuff if we want to be able to set colors in windows */
#ifdef _WIN32
	#include<windows.h>
#endif

/* Get the declarations needed for this file */
#include "room.h"

using namespace std;

room::room()
{
	/* When a new room gets created, we need some basic information about it */
	cout<<"Name the room:"<<endl;
	getline(cin, name);
	cout<<"How many rows does the room have?"<<endl;
	cin>>rows;
	cout<<"How many seats per row?"<<endl;
	cin>>lines;
	
	/* We need to create a real dynamic array for seats */
	seats=new seat*[rows];
	
	for(uint i=0;i<rows;++i)
		{
			seats[i]=new seat[lines];
		}
}

room::room(uint number_of_rows, uint number_of_lines, string room_name)
{
	name = room_name;
	rows = number_of_rows;
	lines = number_of_lines;
	
	/* We need to create a real dynamic array for seats */
	seats=new seat*[rows];
	
	for(uint i=0;i<rows;++i)
		{
			seats[i]=new seat[lines];
		}


	for(uint i=0;i<rows;++i)
		{
			seats[i]=new seat[lines];
		}
}

void room::print_room()
/*
 * Maybe we can split output into seats? wel'll see
 * that when basic routines are implemented
 */
{
	/* At first we need a line of numbers for the LINES, above, there's the room name */
	cout<<name<<endl;
	for(uint i=0;i<lines;++i)
		{
			cout<<"\t"<<i+1;
		}
	cout<<endl;
	
	/* Then, we give out each line seperatly (Number of row - Seats, later with color, if possible) */
	for(uint i=0;i<rows;++i)
		{
			cout<<i+1<<"\t";
			for(uint j=0;j<lines;j++)
				{
#ifdef _WIN32
					HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

					/* Remember how things were when we started */
					CONSOLE_SCREEN_BUFFER_INFO csbi;
					GetConsoleScreenBufferInfo( hstdout, &csbi );
#endif

					switch(seats[i][j].get_state())
						{
#ifndef _WIN32
							/* That's the code for UNIX-Type-terminals */
						case FREE:
							cout<<"\033[1;32m"<<"L|"<<"\033[0m"<<"\t"; /* green color */
							break;
						case RESERVED:
							cout<<"\033[1;33m"<<"L|"<<"\033[0m"<<"\t"; /* yellow color */
							break;
						case HANDED:
							cout<<"\033[1;31m"<<"L|"<<"\033[0m"<<"\t"; /* red color */
							break;
						case LOCKED:
							cout<<"\t";
							break;
#endif
#ifdef _WIN32
							/* and here's the one for other systems (WIN) */
						case FREE:
							SetConsoleTextAttribute( hstdout, 0x0A); /* green color */
							cout<<"L|"<<"\t";
							break;
						case RESERVED:
							SetConsoleTextAttribute( hstdout, 0x0E); /* yellow color */
							cout<<"L|"<<"\t";
							break;
						case HANDED:
							SetConsoleTextAttribute( hstdout, 0x0C); /* red color */
							cout<<"L|"<<"\t";
							break;
						case LOCKED:
							cout<<"\t";
							break;
#endif
						}
#ifdef _WIN32
				SetConsoleTextAttribute( hstdout, csbi.wAttributes );
#endif
				}
			cout<<endl;
		}
}

void room::lock()
{
	/* We need temporary variables */
	uint trow;
	uint tline;
	cout<<"Lock Seat"<<endl;
	/*
	 * If user wants to cancel, end routine
	 * (seat_input returns False if input is succesful)
	 */
	if(seat_input(trow,tline))
		{
			return;
		}

	/*
	 * Humans start count with one, programm with zero, therefore we need to decrement the input
	 * by one to reach the seat
	 */
	seats[trow-1][tline-1].lock();
}

void room::unlock()
{
	/* Get the data we need for unlocking (as above) */
	uint trow;
	uint tline;
	cout<<"Unlock Seat"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}


	/* In this case, it's more efficient to first calculate our "machine"-indexes */
	trow-=1;
	tline-=1;
	
	/*
	 * then we need to check, whether the chosen seat
	 * is in state LOCKED, only then we can FREE him
	 * with this function
	 */
	seats[trow][tline].unlock();
}

void room::reserve()
/* Reserve a place for a person, needs the name! */
{
	/* The usual input at first */
	uint trow;
	uint tline;
	cout<<"Reserve Seat"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/* In this case, it's more efficient to first calculate our "machine"-indexes */
	trow-=1;
	tline-=1;
	
	/* Then call the seats routine */
	seats[trow][tline].reserve();
}
	
void room::release()
{
	/* The usual input at first */
	uint trow;
	uint tline;
	cout<<"Cancel reservation"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/* In this case, it's more efficient to first calculate our "machine"-indexes */
	trow-=1;
	tline-=1;
	
	seats[trow][tline].release(trow,tline);
}


void room::handout()
{
	/* Usual input */
	uint trow;
	uint tline;
	cout<<"Hand out ticket"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/* In this case, it's more efficient to first calculate our "machine"-indexes */
	trow-=1;
	tline-=1;
	
	seats[trow][tline].handout(trow,tline);
}

/* Take back cards (almost the same as release) */
void room::cancel()
{
	/* The usual input at first */
	uint trow;
	uint tline;
	cout<<"Cancel bought cards"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/* In this case, it's more efficient to first calculate our "machine"-indexes */
	trow-=1;
	tline-=1;
	
	/* The seat must be HANDED to get released */
	seats[trow][tline].cancel(trow,tline);
}


uint room::seat_input(uint& row, uint& line) /* Asks user for the row/line he wants to choose */
{
	while(true)
		{
			cout<<"Which seat? (row,line)\n(0 to cancel)"<<endl;
			cin>>row;
			if(row == 0)
				{
					cout<<"Canceled by user request"<<endl;
					return 1;
				}
			cin>>line;
			if(line == 0)
				{
					cout<<"Canceled by user request"<<endl;
					return 1;
				}
			if(row<=rows && line<=lines)
				{
					break;
				}
		}
	return 0;
}
