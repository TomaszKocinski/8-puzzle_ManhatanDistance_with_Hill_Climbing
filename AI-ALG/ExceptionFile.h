#pragma once
#include <exception>
struct MoreThanOneLocalMin :public std::exception{
	const char * what() const throw ();
};