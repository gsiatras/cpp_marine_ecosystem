#ifndef PLAGKTON_H_INCLUDED
#define PLAGKTON_H_INCLUDED

#include "organism.h"

class plagkton:public organism {

public:
    plagkton(int a, float m, int mg, int id):organism(a, m, mg, id, 0)
    { }

private:
};

class phytoplankton:public plagkton{
public:
    phytoplankton(int a, float m, int mg, int id):plagkton(a, m, mg, id)
    {
       counterBorn[8]++;
    }

private:

};

class zooplankton:public plagkton{
public:
    zooplankton(int a, float m, int mg, int id):plagkton(a, m, mg, id)
    {
        counterBorn[9]++;
    }
private:
};


#endif
