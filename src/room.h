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
 * Definitionof a class for reservation in a rectangle-shaped room.
 * To see how it works, and what it provides, see /doc/classes
 */

/* Developement-information:
 * - seperate object "seat" and calls
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
