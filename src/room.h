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
	
	for(uint i=0;i<lines;++i)
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
							/*case FREE:
							  system("color 1A");
							  cout<<"LI";
							  system(
							*/	
#endif
							/*default:
							  cout<<"Hier komm ich nicht an"<<endl;*/
						}
				}
			cout<<endl;
		}
}

void room::printname()
{
	int i=0;
	while(name[i])
		{
			cout<<name[i];
			++i;
		}
	cout<<endl;
}
