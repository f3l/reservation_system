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


	/* And need some initial values for our seats (seat->name="\0",seat->state=FREE) */
	for(uint i=0;i<rows;++i)
		{
			for(uint j=0;j<lines;++j)
				{
					seats[i][j].name="\0";
					seats[i][j].state=FREE;
				}
		}
}

void room::print_room()
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

					switch(seats[i][j].state)
						{
#ifndef _WIN32
							/* That's the code for UNIX-Type-terminals */
						case FREE:
							cout<<"\033[00;32m"<<"L|"<<"\033[0m"<<"\t"; /* green color */
							break;
						case RESERVED:
							cout<<"\033[01;32m"<<"L|"<<"\033[0m"<<"\t"; /* yellow color */
							break;
						case HANDED:
							cout<<"\033[033;31m"<<"LI"<<"\033[0m"<<"\t"; /* red color */
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
	seats[trow-1][tline-1].state=LOCKED;
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
	if( seats[trow][tline].state==LOCKED)
		{
			seats[trow][tline].state=FREE;
		}
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
	
	/* The seat needs to be in state FREE */
	if(!(seats[trow][tline].state==FREE))
		{
			cout<<"This seat is not reservable!"<<endl;
			return;
		}
	
	/* THEN ask for name and save in set new state */
	cout<<"For whom should the reservation take place?"<<endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
	getline(cin, seats[trow][tline].name);
	seats[trow][tline].state=RESERVED;
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
	
	/* The seat must be Reserved to get released */
	if( ! (seats[trow][tline].state==RESERVED))
		{
			return;
		}
	
	/* We need an affirmation, we do quite similar to as input */
	char affirm='n';
	while(true)
		{
			cout<<"Do you really want to release the reservation of"<<endl;
			cout<<"seat "<<tline<<" in row "<<trow<<endl;
			cout<<"currently reserved for"<<endl;
			cout<<seats[trow][tline].name<<"? (y/N)"<<endl;
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
					seats[trow][tline].name="\0";
					seats[trow][tline].state=FREE;
					return;
					break;
					/* Otherwise, we give it another try */
				}
		}
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
	
	/*
	 * This time, we check whether it is free or reserverd and instantly
	 * ask for verification in the later case
	 */
	if( seats[trow][tline].state==RESERVED)
		{
			char affirm='n';
			while(true)
				{
					cout<<"Do you really want to hand out the reservation of"<<endl;
					cout<<"seat "<<tline+1<<" in row "<<trow+1<<endl;
					cout<<"currently reserved for"<<endl;
					cout<<seats[trow][tline].name<<"? (y/N)"<<endl;
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
	if( (seats[trow][tline].state==FREE) || (seats[trow][tline].state=RESERVED))
		{
			seats[trow][tline].state=HANDED;
			seats[trow][tline].name="\0";
		}
	else
		{
			cout<<"The seat is not available!"<<endl;
			return;
		}
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
	if( ! (seats[trow][tline].state==HANDED))
		{
			return;
		}
	
	/* We need an affirmation, we do quite similar to as input */
	char affirm='n';
	while(true)
		{
			cout<<"Do you really want to cancel the card for"<<endl;
			cout<<"seat "<<tline<<" in row "<<trow<<endl;
			cout<<"currently reserved for"<<endl;
		       
			cout<<seats[trow][tline].name<<"? (y/N)"<<endl;
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
					seats[trow][tline].name="\0";
					seats[trow][tline].state=FREE;
					return;
					break;
					/* Otherwise, we give it another try */
				}
		}
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
