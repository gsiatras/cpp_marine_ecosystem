#ifndef ORGANISM_H_INCLUDED
#define ORGANISM_H_INCLUDED

#include <iostream>
#define map_size 25

using namespace std;

// oloi oi organismoi mas
class organism {
public:

static int counterBorn[10];

    organism(int a, float m, int mg, int id, float r)
    {
        age = a;
        megethos = m;
        rythmos = r;
        megisto_megethos = mg;
        i_d = id;
        htepw = 0;
    }

    //sunarthseis tupou GET kai SET
    int getAge() { return age; }

    void setAge(int a) { age=a; }

    int getId() { return i_d; }

    int getMegistoMegethos() { return megisto_megethos; }

    int getElaxistoMegethos() { return elaxisto_megethos; }

    float getMegethos() { return megethos; }

    void setMegethos(float m) { megethos = m; }

    float getRythmos() { return rythmos; }

    void setFlag(bool flg) { myflag = flg; }

    bool getFlag() { return myflag; }

    void setHave(float have1) { htepw = have1; }

    bool getHave() { return htepw; }

    void setfoodPerWeek(float fpw) { foodPerWeek = fpw; }

    float getfoodPerWeek() { return foodPerWeek; }

private:
    int age, i_d, trofh, megisto_megethos, elaxisto_megethos;
    bool myflag;
    float megethos, rythmos, foodPerWeek, htepw;

};

#endif
