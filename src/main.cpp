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

void print_menu();
void end_programm();

/*
 * Creates a new cinema (or else) room with given seats per rows and rows,
 * and the provides a simple menu for actions like reservations etc.
 */

int main()
{
	room theater; /*Create new object game of type game*/
	uint menu;
	while(true)
		{
			print_menu();
			cin>>menu;
			switch(menu)
				{
				case 1:
					theater.print_room();
					break;
					/*Internal, sell ticket and hand out reserved ticket are equal*/
				case 2:
				case 4:
					theater.handout();
					break;
				case 3:
					theater.reserve();
					break;
				case 5:
					theater.release();
					break;
				case 6:
					theater.cancel();
					break;
				case 7:
					theater.lock();
					break;
				case 8:
					theater.unlock();
					break;
				case 0:
					end_programm();
					break;
				default:
					cout<<"Invalid Input"<<endl;
				}
		}
#ifndef __unix__
	system(halt);
#endif
	return 0;
}


/*prints main-menu (nothing more, nothing less)*/
void print_menu()
{
	cout<<"Possible choices:"<<endl;
	cout<<"(1) View room"<<endl;
	cout<<"(2) Sell ticket"<<endl;
	cout<<"(3) Reserve ticket"<<endl;
	cout<<"(4) Hand out reserved ticket"<<endl;
	cout<<"(5) Cancel reservation"<<endl;
	cout<<"(6) Take back ticket"<<endl;
	cout<<"(7) Make seat unavailable"<<endl;
	cout<<"(8) Make seat available"<<endl;
	cout<<"(0) Exit";
	cout<<endl<<"Your Choice?"<<endl;
	return;
}

/*asks for verification, if succesfull terminates process*/

void end_programm()
{
	char confirm='n';
	while(true)
		{
			cout<<"Do you really want to quit programms?(y/N)"<<endl;
			cout<<"Your room will be lost!"<<endl;
			cin>>confirm;
			switch(confirm)
				{
				case 'N':
				case 'n':
					return;
					break;
				case 'Y':
				case 'y':
					cout<<"Exiting"<<endl;
					exit(0);
					break;
				default:
					cout<<"Invalid Input!"<<endl;
					break;
				}
		}
}
