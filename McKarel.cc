#include "McKarel.h"

McKarel::McKarel(bool cflag)
    : Allocator(cflag, "MCKarel")
{
    administratie = new vector<Area*>[AREASIZE]();
    areaByteSize  = new int[AREASIZE]();
    for(int i=0; i < AREASIZE; i++)
    {
       areaByteSize[i] = -1;
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

void McKarel::free(Area* ap)
{
    int room = ap->getBase() / (size / AREASIZE);
      //cout << "freeing 2 room: " << room << "baseaddress: "<< ap->getBase() << endl;
    if(room != 0)
        room --;
    administratie[room].push_back(ap);
    if((administratie[room].size() * areaByteSize[room]) == (size/AREASIZE)) {
        areaByteSize[room] = -1;
    }
}

void    McKarel::report()
{

}

Area *McKarel::searcher(int wanted)
{
    //cout << "Wanted:" <<wanted << " - "  << size/AREASIZE << endl;
    int tweemacht = getClosestQuadratic(wanted);

    if(tweemacht > (size/AREASIZE))
    {
        cout << "Bigger than one room " << endl;
    }
    else
    {
        for(int i =0; i < AREASIZE; i++)
        {
            if(areaByteSize[i] == tweemacht && administratie[i].size() > 0)
            {
                 cout << "Existing Area" << endl;


                Area* retAP = administratie[i].back();
                administratie[i].pop_back();
                return retAP;
            }
            else if(areaByteSize[i] == -1)
            {
                areaByteSize[i] = tweemacht;

                 cout << "Emtpy Area" << endl;

                while(tweemacht * 2 < size/AREASIZE) {
                    Area* ap = new Area((i*(size/AREASIZE) + (tweemacht * administratie[i].size())),tweemacht);
                    cout << *ap << endl;
                    administratie[i].push_back(ap);
                    tweemacht += tweemacht;
                }

                   cout << "Emtpy Area 2" << endl;

                Area* retAP = administratie[i].back();
                administratie[i].pop_back();
                return retAP;
            }
            cout << "Fout" << endl;
        }
    }
    return 0;
}

int McKarel::getClosestQuadratic(int wanted)
{
    int closestQuadratic = 1;
    while(closestQuadratic < wanted)
    {
        closestQuadratic *= 2;
    }
    return closestQuadratic;
}
