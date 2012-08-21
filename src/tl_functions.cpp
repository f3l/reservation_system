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
 *  Contact: jloher@gmx.net or oli_r@fg4f.de
 *  Get current code at <http://www.github.com/f3l/reservation_system>
 */

 /* This file contains the implementations of the overloaded functions of the template functions defined in tl_functions.h */

#include <iostream>
#include <string>

#include "tl_functions.h"

using namespace std;


/* Overload the do_input() function to work correctly with C++ strings */
string& do_input(string& input, istream& in, ostream& out)
{
	getline(in, input); /* No flushing needed in this case, because getline() will remove everything until '\n' on it's own */
	return input;
}

/* Overload the do_input() function to work correctly with C-style strings */
char* do_input(char *input, unsigned int len, istream& in, ostream& out)
{
	in.get(input, len); /* Use get() instead of getline() so that the delimiter '\n' does not get removed and we can flush the stream safely */
	/* Flush the input stream */
	in.clear();
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	return input;
}