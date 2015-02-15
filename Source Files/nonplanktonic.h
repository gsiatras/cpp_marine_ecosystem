#ifndef NONPLANKTONIC_H_INCLUDED
#define NONPLANKTONIC_H_INCLUDED

#include "organism.h"

class nonplanktonic:public organism{
public:
    nonplanktonic(int a, float m,  int mg, int id, float r):organism(a, m, mg, id, r)
    { }
private:
};

class shark:public nonplanktonic{
public:

    shark(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
       counterBorn[0]++;
    }

protected:
};

class dolphin:public nonplanktonic{
public:
    dolphin(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
        counterBorn[1]++;
    }

private:
};

class mullet:public nonplanktonic{
public:
    mullet(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
        counterBorn[2]++;
    }
private:
};

class bream:public nonplanktonic{
public:
    bream(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
        counterBorn[3]++;
    }
private:
};

class octopus:public nonplanktonic{
public:
    octopus(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
        counterBorn[4]++;
    }

private:
};

class sardine:public nonplanktonic{
public:
    sardine(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
       counterBorn[5]++;
    }
private:
};

class fry:public nonplanktonic{
public:
    fry(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
       counterBorn[6]++;
    }

private:
};

class mussel:public nonplanktonic{
public:
    mussel(int a, float m, int mg, int id, float r):nonplanktonic(a, m, mg, id, r)
    {
       counterBorn[7]++;
    }

private:
};


#endif
