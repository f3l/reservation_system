/* 
 * Provides a class for reservation in a rectangle-shaped room.
 * To see how it works, and what it provides, see /doc/classes
 */

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
	void printname();
	
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
							/*do some crazy shit with color*/
							cout<<"L|"<<\t;
							/*reset crazy shit with color*/
							break;
						case RESERVED:
							/*do some crazy shit with color*/
							cout<<"L|"<<\t;
							/*reset crazy shit with color*/
							break;
						case HANDED:
							/*do some crazy shit with color*/
							cout<<"L|"<<\t;
							/*reset crazy shit with color*/
							break;
						case LOCKED:
							/*do some crazy shit with color*/
							cout<<"L|"<<\t;
							break;
#endif
						}
				}
			cout<<endl;
		}
}

void room::printname()
{
	/*Print the name of the room (e.g. each character till "\0")*/
	int i=0;
	while(name[i])
		{
			cout<<name[i];
			++i;
		}
	cout<<endl;
}

void room::lock()
{
	/*we need temporary variables*/
	uint trow;
	uint tline;
	while(true)
		/*We're waiting for some input, and we won't continue 'till we get valid values*/
		{
			cout<<"Which seat should get locked? (row, line)\n(Give 0 if you want to cancel)"<<endl;
			cin>>trow;
			if(trow==0)
				{
					cout<<"Cancelled by User request"<<endl;
					return;
				}
			cin>>tline;
			if(tline==0)
				{
					cout<<"Cancelled by User request"<<endl;
					return;
				}
			
			if(trow<=rows && tline<=lines)
				{
					break;
				}
			else
				{
					cout<<"Invalid input, please repeat";
				}
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
	while(true)
		{
			cout<<"Which seat should get unlocked? (row,line)\n(0 to cancel)"<<endl;
			cin>>trow;
			if(trow == 0)
				{
					cout<<"Canceled by user request"<<endl;
					return;
				}
			cin>>tline;
			if(tline == 0)
				{
					cout<<"Canceled by user request"<<endl;
					return;
				}
			if(trow<=rows && tline<=lines)
				{
					break;
				}
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
