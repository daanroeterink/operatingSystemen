#ident	"@(#)NextFit.cc	2.1	AKK	20090208"
/** @file NextFit.cc
 * De implementatie van NextFit.
 */

#include "main.h"
#include "NextFit.h"


// Iemand vraagt om 'wanted' geheugen
Area  *NextFit::alloc(int wanted)
{
	require(wanted > 0);		// minstens "iets",
	require(wanted <= size);	// maar niet meer dan we kunnen hebben.

	updateStats();				// update resource map statistics

	// Search thru all available free areas
	Area  *ap = 0;
	ap = searcher(wanted);		// first attempt
	if (ap) {					// success ?
		return ap;
	}
	if (reclaim()) {			// could we reclaim fragmented areas
		ap = searcher(wanted);	// second attempt
		if (ap) {				// success ?
			return ap;
		}
	}
	// Alas, failed to allocate anything
	//dump();//DEBUG
	return 0;
}


// Application returns an area no longer needed
void	NextFit::free(Area *ap)
{
	require(ap != 0);
	if (cflag) {
		// EXPENSIVE: check for overlap with already registered free areas
		for (ALiterator  i = areas.begin() ; i != areas.end() ; ++i) {
			check(!ap->overlaps(*i));    // sanity check
		}
	}
	areas.push_back(ap);	// de lazy version
}


// ----- hulpfuncties -----

// Iemand vraagt om 'wanted' geheugen
Area  *NextFit::searcher(int wanted)
{
	require(wanted > 0);		// minstens "iets",
	require(wanted <= size);	// maar niet meer dan we kunnen hebben.

	// Search thru all available areas
	// start searching at the old cursor ...
	for (ALiterator  i = cursor ; i != areas.end() ; ++i) {
		Area  *ap = *i;					// Candidate item
		if (ap->getSize() >= wanted) {	// Large enough?
			// Yes, use this area
			cursor = areas.erase(i);	// remove this element from the freelist,
			// the next element becomes the new start-of-search cursor
			if (ap->getSize() > wanted) {		// larger than needed?
				Area  *rp = ap->split(wanted);	// split into two parts (updating sizes)
				areas.insert(cursor, rp);		// add remainder before cursor
			}
			return ap;
		}
	}
	// ... wrap around to beginning, search upto old cursor
	for (ALiterator  i = areas.begin(); i != cursor; ++i) {
		Area  *ap = *i;					// Candidate item
		if (ap->getSize() >= wanted) {	// Large enough?
			// Yes, use this area
			cursor = areas.erase(i);	// remove this element from the freelist
			// the next element becomes the new start-of-search cursor
			if (ap->getSize() > wanted) {		// larger than needed?
				Area  *rp = ap->split(wanted);	// split into two parts (updates sizes)
				areas.insert(cursor, rp);		// add remainder to freelist
			}
			return ap;
		}
	}
	return 0; // report failure
}


// Try to join fragmented freespace
bool	NextFit::reclaim()
{
	bool  changed = false;	// did we change anything ?

	// Sort resource map by area address
	areas.sort( Area::orderByAddress() );	// WARNING: expensive N*log(N) operation !

	// Search thru all available areas for matches
	ALiterator  i = areas.begin();
	Area  *ap = *i;				// the current candidate ...
	for (++i ; i != areas.end() ;) {
		Area  *bp = *i;			// ... match ap with ...
		if (bp->getBase() == (ap->getBase() + ap->getSize()))
		{
			// oke, bp matches ap ...
			ALiterator  next = areas.erase(i);	// remove bp from the list
			ap->join(bp);			// append area bp to ap (and destroy bp)
			++mergers;				// update statistics
			changed = true;			// yes we changed something
			i = next;				// revive the 'i' iterator
		} else {
			ap = bp;				// move on to next area
			++i;
		}
	}
	if (changed) {					// iff we have changed some area's the
		cursor = areas.begin();		// next search should start at the (new) front
	}
	++reclaims;						// update statistics
	return changed;
}

// vim:sw=4:ai:aw:ts=4:
