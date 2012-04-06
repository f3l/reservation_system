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
 * Definition of a class for reservation in a rectangle-shaped room.
 * To see how it works, and what it provides, see /doc/classes
 */

#include <string>
using namespace std;

#include "seat.h" /*We need our seat-class*/

typedef unsigned int uint; /* We will need many unsignes ints */

class room
{
public:

	room();
	room(uint number_of_rows, uint number_of_lines, string room_name);
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
