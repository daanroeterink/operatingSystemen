#include "McKarel.h"

McKarel::McKarel(bool cflag)
    : Allocator(cflag, "MCKarel")
{
    administratie = new vector<Area*>*[AREASIZE]();
    areaByteSize  = new int[AREASIZE]();
    for(int i=0; i < AREASIZE; i++)
    {
        administratie[i] = new vector<Area*>();
    }
}

McKarel::~McKarel()
{
}


void McKarel::SetSize(int wantedSize)
{
    require(size > 0);
    size = wantedSize;
    Allocator::setSize(wantedSize);
}

Area *McKarel::alloc(int wanted)
{
    require(wanted > 0);		// has to be "something",
    require(wanted <= size);	// but not more than can exist

    Area  *ap = 0;
    ap = searcher(wanted);		// first attempt
    if(ap)  					    // success ?
    {
        return ap;
    }
    else
    {
        return 0;
    }
}

void McKarel::free(Area *)
{

}

void    McKarel::report()
{

}

Area *McKarel::searcher(int wanted)
{
    if(wanted > (size/16))
    {
        //todo
    }
    else
    {
        for(int i =0; i < AREASIZE; i++)
        {
            if(areaByteSize[i] == 0)
            {
                areaByteSize[i] = wanted;
                vector<Area*>* areaVector = administratie[i];
                //Check if there is still room in this classroom
                if(ceil(((areaVector->size()+1)* areaByteSize[i])) > (size / AREASIZE))
                {
                    Area* ap = new Area((i*size/AREASIZE),wanted);
                    areaVector->push_back(ap);
                    return ap;
                }
            }
        }
    }
    return 0;
}

