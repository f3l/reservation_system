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

#ifndef TL_FUNCTIONS
#define TL_FUNCTIONS

#include <iostream>
#include <limits>

using namespace std;

template<class T>
T& do_input(T& input, istream& in = cin, ostream& out = cout)
{
	while(true)
		{
			in>>input;
			if(in.fail())
				{
					out<<"Invalid Input!"<<endl;

					/* Flush the input stream */
					in.clear();
					in.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			else
				{
					/* Flush the input stream */
					in.clear();
					in.ignore(numeric_limits<streamsize>::max(), '\n');
					return input;
				}
		}
}

/* Overloaded functions of do_input are implemented in tl_functions.cpp */
string& do_input(string& input, istream& in = cin, ostream& out = cout);
char* do_input(char *input, unsigned int len, istream& in = cin, ostream& out = cout);


#endif
