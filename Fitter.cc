#ident	"@(#)Fitter.cc	2.1	AKK	20090208"
/** @file Fitter.cc
 * De implementatie van de Fitter baseclass.
 */

#include <cmath>		// for: sqrt(3) [needs -lm]
#include "ansi.h"		// ansi color codes

#include "Fitter.h"


Fitter::Fitter(bool cflag, const char *type)
	: Allocator(cflag, type)
	, reclaims(0), mergers(0)
	, qcnt(0), qsum(0), qsum2(0)
{
}


// Initializes how much memory we own
void  Fitter::setSize(int new_size)
{
	require(new_size > 0);					// must be a meaningfull value
	require(areas.empty());					// prevent changing the size when the freelist is nonempty
	Allocator::setSize(new_size);			// inform the Allocator baseclass about the new size
	areas.push_back(new Area(0, new_size));	// and create the first free area (i.e. "all")
	reclaims = mergers = 0;					// clear the statistics
	qcnt = qsum = qsum2 = 0;				// and these too
}


// Clean up dead stuff
Fitter::~Fitter()
{
	while (!areas.empty()) {
		Area  *ap = areas.front();
		areas.pop_front();
		delete ap;
	}
}


// Update statistics
void	Fitter::updateStats()
{
	++qcnt;									// number of 'alloc's
	qsum  += areas.size();					// length of resource map
	qsum2 += (areas.size() * areas.size());	// same: squared
}


// Report statistics
void	Fitter::report()
{
	std::cout << type << ": " << reclaims << " reclaims, " << mergers << " mergers\n";

	require(qcnt > 0);			// prevent divide-thru-zero
	double	avg = qsum / qcnt;	// calculate the average resource map length

	require(qcnt > 1);			// prevent divide-thru-zero
	double	stdev				// calculate the standard deviation
		= sqrt(
			  (qsum2 / (qcnt - 1))
			  -
			  (qcnt / (qcnt - 1)) * (((qsum / qcnt) * (qsum / qcnt)))
		  );
	// also see: http://en.wikipedia.org/wiki/Standard_deviation
	std::cout << type << ": average " << avg << " areas, stdev " << stdev << " areas\n";
	// Assuming a normal distribution, then:
	// 68% of the time the map length will be avg +/- stdev		[one-sigma]
	// 95% of the time the map length will be avg +/- (2*stdev)	[two-sigma]
	// 99.7% of the time it will be within 3-sigma
}


// Print the current freelist for debugging
void	Fitter::dump()
{
	std::cerr << AC_BLUE << type << "::areas";
	for (ALiterator  i = areas.begin() ; i != areas.end() ; ++i) {
		std::cerr << ' ' << **i;
	}
	std::cerr << AA_RESET << std::endl;
}

// vim:sw=4:ai:aw:ts=4:
