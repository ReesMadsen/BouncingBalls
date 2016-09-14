#include "Error.h"

void PrintError(ErrorType Error)
{
	if(Error==ShouldNeverBeHere)
	{
		//std::cout << "Error=Should Never Be Here" << std::endl;
	}
	else if(Error==UnderConstruction)
	{
		//std::cout << "Error=Under Construction" << std::endl;
	}
	else
	{
		//std::cout << "Error=Null Error" << std::endl;
	}
}