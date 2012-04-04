/*Include basic libraries*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#ifndef __unix__
#include<windows.h>
#endif
using namespace std;

/*And own objects*/
#include "room.h"

/*
 * Creates a new cinema (or else) room with given seats per rows and rows,
 * and the provides a simple menu for actions like reservations etc.
 */

int main()
{
	room theater; /*Create new object game of type game*/
	theater.print_room();
	theater.lock();
	theater.print_room();
	return 0;
}
