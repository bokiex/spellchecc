#include "stdafx.h"

namespace help
{
	// converts an ascii char to an int
	// c: char to convert
	//
	// returns the appropriate integer
	int getIndex(char c)
	{
		int i = c - 'a';
		return i;
	}
}
