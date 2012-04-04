/* 
 * Provides a class for reservation in a rectangle-shaped room.
 * To see how it works, and what it provides, see /doc/classes
 *
 * @ghost91: You probalby want to change the call of malloc()
 * in the constructor to one of new, but i couldn't manage
 * it that way.
 */

typedef unsigned int uint; /*We will need many unsignes ints*/

/*A seat can have the states "free","reserved","handed" or "locked" (e.g. seat broken or doesn't exist)*/
enum seat_state{FREE,RESERVED,HANDED,LOCKED};

/* A seat consists of an enum seat_state and
 * a string for the name of the person who
 * reserved it.
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
	//print_room();
private:
	uint rows;
	uint lines;
	char name[32];
	//	seat **seats;
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

	/*We need a 2-dimensional dynamical array of seats*/
	seat **seats;  
	seats=(seat**)malloc(rows*sizeof(seat*));
//	seats = new *seats[rows];
	for(uint i=0;i<lines;++i)
		{
			seats[i]=(seat*)malloc(lines*sizeof(seat));
		}
	
}
