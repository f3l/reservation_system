/*
 *  Reservation System - A program to manage rect-shaped seatings
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

#ifndef APPLICATION_DEFINED
#define APPLICATION_DEFINED

#include "room.h"
#include "menu.h"
#include "linked_list.h"

class capplication
{
private:
	int m_running, m_return_to_main_menu;
	cmenu m_main_menu;
	clinked_list<croom*> m_rooms;
	
public:
	capplication();
	~capplication();
	void run();
	void list_rooms();
	void add_room();
	void delete_room();
	void edit_room();
	void return_to_main_menu();
	void end_program();
};

#endif
