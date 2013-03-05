#pragma once
#ifndef	__McKarel_h__
#define	__McKarel_h__	0.000001 Alpha Beta Charlie Edition
#ident	"@(#)McKarel.h	0.000001 Alpha Beta Charlie Edition"


#include <math.h>
#include <vector>
#include "main.h"
#include "Allocator.h"

#define AREASIZE 16

class McKarel : public Allocator
{

private:

    vector<Area*> *administratie;
    int* areaByteSize;

public :


    McKarel(bool cflag);

    ~McKarel();

    void SetSize(int wantedSize);

    Area *alloc(int wanted);	///< Application vraagt om geheugen
    void  free(Area *);			///< Application geeft een Area weer terug aan geheugenbeheer
    void  report();				///< Report performance statistics
    Area *searcher(int wanted);    ///< Search for empty area

    int getClosestQuadratic(int wanted);
};

#endif
