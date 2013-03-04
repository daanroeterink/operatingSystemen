#ident	"@(#)Allocator.cc	2.1	AKK	20090222"
/** @file Allocator.cc
 * De implementatie van Allocator.
 */

#include "main.h"		// common stuff
#include "Allocator.h"	// voor: class Allocator


// Define an allocator
Allocator::Allocator(bool cflag, const char *type)
	: cflag(cflag), type(type)
{
	require(type != 0);
	//std::cout << "Allocator type " << type << " gemaakt\n";//DEBUG
}


// Record how much memory we administrate
void Allocator::setSize(int new_size)
{
	require(new_size > 0);
	size = new_size;
	//std::cout << "Allocator geheugen op " << size << " eenheden ingesteld\n";//DEBUG
}


// vim:sw=4:ai:aw:ts=4:
