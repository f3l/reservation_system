#include "functions.h"
#include <iostream>
#include <limits>

using namespace std;

istream &flush_stream(istream &in)
{
	in.clear();
	return in.ignore(numeric_limits<streamsize>::max(), '\n'), in;
}