#pragma once
#ifndef	__NextFit_h__
#define	__NextFit_h__	2.1
#ident	"@(#)NextFit.h	2.1	AKK	20090208"

/** @file NextFit.h
 *  @brief The class that implements the lazy version of the NextFit algorithm.
 *  @author R.A.Akkersdijk@saxion.nl
 *  @version 2.1	2009/02/08
 */

#include "Fitter.h"

/// @class NextFit
/// Het NextFit algorithme gebruikt het eerste
/// bruikbare gebied in de resource map.
class	NextFit : public Fitter
{

public:

	explicit	// see: http://en.cppreference.com/w/cpp/language/explicit
	/// @param cflag	initial status of check-mode
	/// @param type		name of this algorithm (default=NextFit)
	NextFit(bool cflag, const char *type = "NextFit (lazy)")
		: Fitter(cflag, type) { cursor = areas.begin(); }

	/// Ask for an area of at least 'wanted' units
	/// @returns	An area or 0 if not enough freespace available
	Area	*alloc(int wanted);

	/// The application returns an area to freespace
	/// @param ap	The area returned to free space
	void	free(Area *ap);

protected:

	ALiterator	  cursor;		///< remembers where we stopped searching last time

	Area 	*searcher(int);		///< tries to find some room
	bool	reclaim();			///< tries to merge adjacent areas

};

#endif	/*NextFit_h*/
// vim:sw=4:ai:aw:ts=4:
