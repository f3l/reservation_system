/* 
 * Provides a class for reservation in a rectangle-shaped room.
 * To see how it works, and what it provides, see /doc/classes
 * MAYBE we can do the ijnput in an external function with
 * pointers/refs (we'll do that later)
 * Same with reserved-affirmation
 */

#include <string>

using namespace std;

typedef unsigned int uint; /* We will need many unsignes ints */

/* A seat can have the states "free","reserved","handed" or "locked" (e.g. seat broken or doesn't exist) */
enum seat_state{FREE,RESERVED,HANDED,LOCKED};

/* A seat consists of an enum seat_state and
 * a string for the name of the person who
 * reserved it. (Only set in this secific case)
 */
struct seat
{
	seat_state state;
	string name;
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

	/* We need a 2-dimensional array of seats, with "seats" being its "initial pointer" */
	seat **seats;
	
	string name;
	uint seat_input(uint&, uint&);
};
