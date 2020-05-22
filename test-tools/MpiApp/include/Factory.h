#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "CommIntf.h"
#include "MpiComm.h"
#include <iostream>

using namespace std;

class Factory 
{
    public:
	//Factory method 
        static CommIntf *Create(CommType type); 
};

CommIntf* Factory::Create(CommType type)
{
    if(type == MPI) {
        cout << "Creating MPI Interface object.." << endl;	    
        return new MpiComm; 
    } else if(type == MP) {
        cout << "Creating MP Interface object.." << endl;
	//return new MPComm;
        return nullptr;
    } else {
        cout << "Invalid CommType specified.Cannot create object!! " << endl;
	return nullptr;
    }
}

#endif
