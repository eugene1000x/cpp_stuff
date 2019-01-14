
#ifndef EUGENEJONAS__CPP_STUFF__ERROR_HANDLING_H
#define EUGENEJONAS__CPP_STUFF__ERROR_HANDLING_H


#include <exception>


namespace eugenejonas::cpp_stuff
{


class ExpectedException: public std::exception
{
	//nothing
}

class UnexpectedException: public std::exception
{
	//nothing
}


}


#endif
