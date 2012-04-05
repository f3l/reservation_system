/* 
 * Provides a class for reservation in a rectangle-shaped room.
 * To see how it works, and what it provides, see /doc/classes
 * MAYBE we can do the ijnput in an external function with
 * pointers/refs (we'll do that later)
 * Same with reserved-affirmation
 */
#include <iostream>
#ifndef __unix__
#include<windows.h>
#endif
typedef unsigned int uint; /*We will need many unsignes ints*/

/*A seat can have the states "free","reserved","handed" or "locked" (e.g. seat broken or doesn't exist)*/
enum seat_state{FREE,RESERVED,HANDED,LOCKED};

/* A seat consists of an enum seat_state and
 * a string for the name of the person who
 * reserved it. (Only set in this secific case)
 */
struct seat
{
	seat_state state;
	char name[64];
};
	


class room
{
public:

	room();
	void print_room();
	void lock();
	void unlock();
	void reserve();
	void release();
	void handout();
	void cancel();

	void printname();

	/*
	 * Important: check whether an option is allowed!
	 * The states in which you can perform an action are:
	 * lock(): each
	 * unlock(): LOCKED
	 * reserve(): FREE
	 * release(): RESERVED
	 * handout(): FREE, RESERVED (later with check)
	 * cancel(): LOCKED (Does almost the same as release(), but with another verification
	 */


private:
	uint rows;
	uint lines;

	/* We need a 2-dimensional array of seats, with "seats" being its "initial pointer"*/
	seat **seats;
	
	char name[32];
	uint seat_input(uint&, uint&);
};

room::room()
{
	/*When a new room gets created, we need some basic information about it*/
	cout<<"Name the room:"<<endl;
	cin.getline(name,31);
	cout<<"How many rows does the room have?"<<endl;
	cin>>rows;
	cout<<"How many seats per row?"<<endl;
	cin>>lines;
	
	/*We need to create a real dynamic array for seats*/
	seats=new seat*[rows];
	
	for(uint i=0;i<rows;++i)
		{
			seats[i]=new seat[lines];
		}


	/*And need some initial values for our seats (seat->name[0]=0,seat->state=FREE)*/
	for(uint i=0;i<rows;++i)
		{
			for(uint j=0;j<lines;++j)
				{
					seats[i][j].name[0]=0;
					seats[i][j].state=FREE;
				}
		}
}

void room::print_room()
{
	/*At first we need a line of numbers for the LINES, above, there's the room name*/
	printname();
	for(uint i=0;i<lines;++i)
		{
			cout<<"\t"<<i+1;
		}
	cout<<endl;
	
	/*Then, we give out each line seperatly (Number of row - Seats, later with color, if possible)*/
	for(uint i=0;i<rows;++i)
		{
			cout<<i+1<<"\t";
			for(uint j=0;j<lines;j++)
				{
#ifndef __unix__
					HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

					// Remember how things were when we started
					CONSOLE_SCREEN_BUFFER_INFO csbi;
					GetConsoleScreenBufferInfo( hstdout, &csbi );
#endif

					switch(seats[i][j].state)
						{
#ifdef __unix__
							/*That's the code for UNIX-Type-terminals*/
						case FREE:
							cout<<"\033[00;32m"<<"L|"<<"\033[0m"<<"\t";
							break;
						case RESERVED:
							cout<<"\033[033;32m"<<"L|"<<"\033[0m"<<"\t";
							break;
						case HANDED:
							cout<<"\033[033;31m"<<"LI"<<"\033[0m"<<"\t";
							break;
						case LOCKED:
							cout<<"\t";
							break;
#endif
#ifndef __unix__
							/*and here's the one for other systems (WIN)*/
						case FREE:
							SetConsoleTextAttribute( hstdout, 0x0A);
							cout<<"L|"<<"\t";
							break;
						case RESERVED:
							SetConsoleTextAttribute( hstdout, 0x0E);
							cout<<"L|"<<"\t";
							break;
						case HANDED:
							SetConsoleTextAttribute( hstdout, 0x0C);
							cout<<"L|"<<"\t";
							break;
						case LOCKED:
							cout<<"\t";
							break;
#endif
						}
#ifndef __unix__
				SetConsoleTextAttribute( hstdout, csbi.wAttributes );
#endif
				}
			cout<<endl;
		}
}

void room::printname()
{
	/*Print the name of the room (e.g. each character till "\0")*/
	for(int i=0;name[i];++i)
		{
			cout<<name[i];
		}
	cout<<endl;
}

void room::lock()
{
	/*we need temporary variables*/
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
	/*Get the data we need for unlocking (as above)*/
	uint trow;
	uint tline;
	cout<<"Unlock Seat"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}


	/*In this case, it's more efficient to first calculate our "machine"-indexes*/
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
/*reserve a place for a person, needs the name!*/
{
	/*the usual input at first*/
	uint trow;
	uint tline;
	cout<<"Reserve Seat"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/*In this case, it's more efficient to first calculate our "machine"-indexes*/
	trow-=1;
	tline-=1;
	
	/*The seat needs to be in state FREE*/
	if(!(seats[trow][tline].state==FREE))
		{
			cout<<"This seat is not reservable!"<<endl;
			return;
		}
	
	/*THEN ask for name and save in set new state*/
	
	cout<<"For whom should the reservation take place?"<<endl;
	fflush(stdin);
	cin.getline(seats[trow][tline].name,63);
	seats[trow][tline].state=RESERVED;
}
	
void room::release()
{
	/*the usual input at first*/
	uint trow;
	uint tline;
	cout<<"Cancel reservation"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/*In this case, it's more efficient to first calculate our "machine"-indexes*/
	trow-=1;
	tline-=1;
	
	/*The seat must be Reserved to get released*/
	if( ! (seats[trow][tline].state==RESERVED))
		{
			return;
		}
	
	/*We need an affirmation, we do quite similar to as input*/
	char affirm='n';
	while(true)
		{
			cout<<"Do you really want to release the reservation of"<<endl;
			cout<<"seat "<<tline<<" in row "<<trow<<endl;
			cout<<"currently reserved for"<<endl;
			for(int i=0;seats[trow][tline].name[i];++i)
				{
					cout<<seats[trow][tline].name[i];
				}
			cout<<"? (y/N)"<<endl;
			cin>>affirm;
			switch(affirm)
				{
					/*If user doesn't affirm, we stop the routine*/
				case 'N':
				case 'n':
					return;
					break;
					/*If he does, we release the seat and exit*/
				case 'Y':
				case 'y':
					seats[trow][tline].name[0]=0;
					seats[trow][tline].state=FREE;
					return;
					break;
					/*Otherwise, we give it another try*/
				}
		}
}

void room::handout()
{
	/*usual input*/
	uint trow;
	uint tline;
	cout<<"Hand out ticket"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/*In this case, it's more efficient to first calculate our "machine"-indexes*/
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
					cout<<"seat "<<tline<<" in row "<<trow<<endl;
					cout<<"currently reserved for"<<endl;
					for(int i=0;seats[trow][tline].name[i];++i)
						{
							cout<<seats[trow][tline].name[i];
						}
					cout<<"? (y/N)"<<endl;
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
			seats[trow][tline].name[0]=0;
		}
	else
		{
			cout<<"The seat is not available!"<<endl;
			return;
		}
}

/*Take back cards (almost the same as release)*/
void room::cancel()
{
	/*the usual input at first*/
	uint trow;
	uint tline;
	cout<<"Cancel bought cards"<<endl;
	if(seat_input(trow,tline))
		{
			return;
		}

	/*In this case, it's more efficient to first calculate our "machine"-indexes*/
	trow-=1;
	tline-=1;
	
	/*The seat must be HANDED to get released*/
	if( ! (seats[trow][tline].state==HANDED))
		{
			return;
		}
	
	/*We need an affirmation, we do quite similar to as input*/
	char affirm='n';
	while(true)
		{
			cout<<"Do you really want to cancel the card for"<<endl;
			cout<<"seat "<<tline<<" in row "<<trow<<endl;
			cout<<"currently reserved for"<<endl;
			for(int i=0;seats[trow][tline].name[i];++i)
				{
					cout<<seats[trow][tline].name[i];
				}
			cout<<"? (y/N)"<<endl;
			cin>>affirm;
			switch(affirm)
				{
					/*If user doesn't affirm, we stop the routine*/
				case 'N':
				case 'n':
					return;
					break;
					/*If he does, we release the seat and exit*/
				case 'Y':
				case 'y':
					seats[trow][tline].name[0]=0;
					seats[trow][tline].state=FREE;
					return;
					break;
					/*Otherwise, we give it another try*/
				}
		}
}


uint room::seat_input(uint& row, uint& line) /*Asks user for the row/line he wants to choose*/
{
	while(true)
		{
			cout<<"Which sea? (row,line)\n(0 to cancel)"<<endl;
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
