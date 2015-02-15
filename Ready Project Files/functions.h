#ifndef  _FUNCTIONS_H
#define _FUNCTIONS_H

#include "organism.h"
#include "plangkton.h"
#include "nonplanktonic.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

using namespace std;

// dhmiourgia kai arxikopoihsh metavlhtwn kai pinakwn
organism* world[map_size][map_size];

int counterClock=0, idrand=0, randNewZwopl=0, neworgan, x=0, y=0, xNullAnap=0, yNullAnap=0, randMove=0, x1=0, y1=0, randAnapar=0, xbackup , ybackup, flagNets=0;
float inputAddPolution, polutionSize, polutionSize1, increasingMegethos=0, decreasingMegethos=0, molusmeno_megethos;
bool checkIfNull=false; // flag gia thn anaparagwgh
bool beginFlag = false; // flag gia an exei 3ekinhsei to game

int counterFoodPerWeek[8] = {0,0,0,0,0,0,0,0};
int counterAlive[10]={0,0,0,0,0,0,0,0,0,0};
int counterDeath[11]={0,0,0,0,0,0,0,0,0,0,0};
int counterAge[11]={0,0,0,0,0,0,0,0,0,0,0};
int FoodPerWeek[8] = {0,0,0,0,0,0,0,0};
int avgFoodPerWeek[8] = {0,0,0,0,0,0,0,0};
int organism::counterBorn[]={0,0,0,0,0,0,0,0,0,0};

int maxSizeOrganism[8]={150,35,80,30,39,11,5,5};
int minSizeOrganism[8]={81,15,40,10,12,6,1,1};
int maxAgeOrganism[8]={150,120,140,110,130,100,90,90};
float haveToEatArray[8]={0.16,0.14,0.12,0.10,0.08,0.06,0.04,0.02};
float growRate[8]={0.16,0.14,0.12,0.10,0.08,0.06,0.04,0.02};
float counterMegethos[11]={0,0,0,0,0,0,0,0,0,0,0};

// gia ton titlo
char temp[150];
char temp1[100];

// sunarthsh gia ta dixtua.
int myNets(int x1, int y1, int x2, int y2, organism* world[map_size][map_size])
{
    srand ( time(NULL) );
    for(int i=x1; i<x2+1; i++)
    {
        for(int j=y1; j<y2+1; j++)
        {
            int randomDelete = rand()%(100);
            if (randomDelete > 9) world[i][j] = NULL; //random 10% gia delete sta dixtua
        }
    }
    return 5; // sunexish tou programmatos
}

// sunarthsh gia th molunsh
int myPolution(int x1, int y1, int x2, int y2, float inputAddPolution, organism* world[map_size][map_size])
{
    inputAddPolution = inputAddPolution / 100; // diairesh me to 100 gia na exoume to pososto
    polutionSize = inputAddPolution * map_size; // antistoixish tou posostou me to xarth mas

    polutionSize = polutionSize + 0.1; // stroggulopoihsh gia oriakh timh 0.9 = 1
    polutionSize1 = (int)polutionSize; // apomakrunsh akeraiou merous afou exoume kelia

    //if(polutionSize1>map_size) polutionSize1 = map_size;
    if ((y2-y1) !=0 ) return 3;

    if (inputAddPolution > 1) return 4;

    return 5; // h douleia gia tis meiwseis ginetai sta "grafika" gia meiwsh twn "for"
}

//eisagwgh kai "anaparagwgh" futoplagkton
void newPhyto()
{
    srand ( time(NULL) );
    for(int i=0; i<map_size; i++)
    {
        y=map_size-1;
        x=rand()%(map_size);
        world[x][y] = (organism *) new phytoplankton(0, 0, 40, 8);
    }
}

//dhmiourgia tou pinaka random me stoixeia
void setMap()
{
    srand ( time(NULL) );
    for(int i=0; i<map_size; i++)
    {
        for(int j=0; j<map_size; j++)
        {
            x=rand()%(map_size);
            y=rand()%(map_size-1);
            idrand = rand()%(9);

            if (world[x][y] == NULL)
            {
                if (idrand == 0) world[x][y] = (organism *) new shark(0, minSizeOrganism[0], maxSizeOrganism[0], 0, growRate[0]);
                if (idrand == 1) world[x][y] = (organism *) new dolphin(0, minSizeOrganism[1], maxSizeOrganism[1], 1, growRate[1]);
                if (idrand == 2) world[x][y] = (organism *) new mullet(0, minSizeOrganism[2], maxSizeOrganism[2], 2, growRate[2]);
                if (idrand == 3) world[x][y] = (organism *) new bream(0, minSizeOrganism[3], maxSizeOrganism[3], 3, growRate[3]);
                if (idrand == 4) world[x][y] = (organism *) new octopus(0, minSizeOrganism[4], maxSizeOrganism[4], 4, growRate[4] );
                if (idrand == 5) world[x][y] = (organism *) new sardine(0, minSizeOrganism[5], maxSizeOrganism[5], 5, growRate[5]);
                if (idrand == 6) world[x][y] = (organism *) new fry(0, minSizeOrganism[6], maxSizeOrganism[6], 6, growRate[6]);
                if (idrand == 7) world[x][y] = (organism *) new mussel(0, minSizeOrganism[7], maxSizeOrganism[7], 7, growRate[7]);
                if (idrand == 8) world[x][y] = (organism *) new zooplankton(0, 1, 150, 9);
            }
        }
    }
    newPhyto();
}

// set flags analoga to "flg"
void setAllFlags(bool flg)
{
    for(int i=0; i<map_size; i++)
        for(int j=0; j<map_size; j++)
            if(world[i][j] != NULL)
                world[i][j] ->setFlag(flg);
}

// set th metavlhth foodPerWeek 0 -> gia arxikopoihsh
void setSetFoodPerWeek()
{
    for(int i=0; i<map_size; i++)
        for(int j=0; j<map_size; j++)
            if(world[i][j] != NULL)
                world[i][j]->setfoodPerWeek(0);
}

// ka8arismos tou xarth
void clearMap()
{
    for(int i=0; i<map_size; i++)
        for(int j=0; j<map_size; j++)
            world[i][j]=NULL;
}

//au3hsh hlikias gia ka8e stoixeio
void increaseAge()
{
    for(int x=0; x<map_size; x++)
        for(int y=0; y<map_size; y++)
            if(world[x][y] != NULL)
                world[x][y]->setAge(world[x][y]->getAge() +1);
}

// elegxos 8anatou apo mikro mege8os kai apo megisth hlikia
// logw mikrhs hlikias sthn arxh ka8e psariou einai pi8ano na mhn epiviwsei giauto dinoume eukairia na prospa8hsei na faei
// to futoplagkton kai to zwoplagkton den 8ewroume oti mporoun na mhn epiviwsoun logw mege8ous h hlikias. einai mikroorganismoi. o 8anatos egkeitai sto fagwma tous apo kapoio psari.
void deathCheck()
{
    for(int x=0; x<map_size; x++)
        for(int y=0; y<map_size; y++)
            if(world[x][y] != NULL)
                if (((world[x][y]->getMegethos() < 0) && (world[x][y]->getAge()>5)) || (world[x][y]->getAge() > maxAgeOrganism[world[x][y]->getId()]))
                    world[x][y]=NULL;
}

// dhmiourgia organismou apo ton xrhsth
void newOrganismGraphs(int newOrganismId, int handleAdd[3], int xClicked, int yClicked)
{
    // an o xrhsths valei 999 se kapoio attribute sto input na fortw8ei to default
    for(int i=0; i<3; i++)
    {
        if(handleAdd[i] == 999)
        {
            if(i=0) handleAdd[0] = 0;
            else if(i=1) handleAdd[1] = minSizeOrganism[newOrganismId];
            else if(i=2) handleAdd[2] = growRate[newOrganismId];
        }
    }

    // analoga to id pou epilexthke dhmiourgeitai k o antistoixos organismos
    switch(newOrganismId)
    {
        case 0: world[xClicked][yClicked] = (organism*) new shark(handleAdd[0], handleAdd[1], maxSizeOrganism[0], newOrganismId, handleAdd[2]);
                break;

        case 1: world[xClicked][yClicked] = (organism*) new dolphin(handleAdd[0], handleAdd[1], maxSizeOrganism[1], newOrganismId, handleAdd[2]);
                break;

        case 2: world[xClicked][yClicked] = (organism*) new mullet(handleAdd[0], handleAdd[1], maxSizeOrganism[2], newOrganismId, handleAdd[2]);
                break;

        case 3: world[xClicked][yClicked] = (organism*) new bream(handleAdd[0], handleAdd[1], maxSizeOrganism[3], newOrganismId, handleAdd[2]);
                break;

        case 4: world[xClicked][yClicked] = (organism*) new octopus(handleAdd[0], handleAdd[1], maxSizeOrganism[4], newOrganismId, handleAdd[2]);
                break;

        case 5: world[xClicked][yClicked] = (organism*) new sardine(handleAdd[0], handleAdd[1], maxSizeOrganism[5], newOrganismId, handleAdd[2]);
                break;

        case 6: world[xClicked][yClicked] = (organism*) new fry(handleAdd[0], handleAdd[1], maxSizeOrganism[6], newOrganismId, handleAdd[2]);
                break;

        case 7: world[xClicked][yClicked] = (organism*) new mussel(handleAdd[0], handleAdd[1], maxSizeOrganism[7], newOrganismId, handleAdd[2]);
                break;

        case 8: world[xClicked][yClicked] = (organism*) new phytoplankton(handleAdd[0], handleAdd[1], 40, newOrganismId);
                break;

        case 9: world[xClicked][yClicked] = (organism*) new zooplankton(handleAdd[0], handleAdd[1], 150, newOrganismId);
                break;
    }
}

// random keli "epistrofhs" elegxou gia tis sunarthseis MOVE kai EAT -> to keli pou 8a tsekaristei dhdalh, me random tropo
void aboutMove_Eat(int x, int y)
{
    randMove=rand()%(8);
    switch (randMove)
        {
            case 0: x1=x+1;
                    y1=y;
                    break;

            case 1: x1=x+1;
                    y1=y+1;
                    break;

            case 2: x1=x;
                    y1=y + 1;
                    break;

            case 3: x1=x-1;
                    y1=y+1;
                    break;

            case 4: x1=x-1;
                    y1=y;
                    break;

            case 5: x1=x-1;
                    y1 = y-1;
                    break;

            case 6: x1=x;
                    y1=y-1;
                    break;

            case 7: x1=x+1;
                    y1=y-1;
        }
    if (x1 >= map_size || x1 < 0) x1=x;
    if (y1 >= map_size || y1 < 0) y1=y;
}

//kinhsh twn organismwn
void move()
{
    srand ( time(NULL) );
    for(int x=0; x<map_size; x++)
    {
        for(int y=0; y<map_size; y++)
        {
            // to keli pou 8a tsekaristei
            aboutMove_Eat(x,y);
            if (world[x][y] != NULL)
            {
                // an den einai futoplagkton
                if (world[x][y]->getId() != 8)
                {
                    // an to next keli einai null kai egw (x, y) exw flag 1 (mporw na kinh8w), proxwraw kai kanw to flag mou 0.
                    if ((world[x1][y1] == NULL) && (world[x][y]->getFlag()))
                    {
                        world[x][y]->setFlag(false);
                        swap(world[x][y], world[x1][y1]);
                    }
                }
            }
        }
    }
}

//omoia me thn aboutMove_Eat
void aboutReproduction(int i)
{
    switch (i)
    {
        case 0: x1=x+1;
                y1=y;
                break;

        case 1: x1=x+1;
                y1=y+1;
                break;

        case 2: x1=x;
                y1=y + 1;
                break;

        case 3: x1=x-1;
                y1=y+1;
                break;

        case 4: x1=x-1;
                y1=y;
                break;

        case 5: x1=x-1;
                y1 = y-1;
                break;

        case 6: x1=x;
                y1=y-1;
                break;

        case 7: x1=x+1;
                y1=y-1;
    }
    if (x1 >= map_size || x1 < 0) x1=x;
    if (y1 >= map_size || y1 < 0) y1=y;
}

//anaparagwgh
void reproduction()
{
    srand ( time(NULL) );
    for(int x=0; x<map_size; x++)
    {
        for(int y=0; y<map_size; y++)
        {
            // an den eimai NULL
            if( world[x][y] != NULL)
            {
                //krataw ta x, y (mou) gia th sunexeia
                xbackup = x;
                ybackup = y;
                if ( world[x][y]->getFlag() ) // an to flag mou einai 1
                {
                    randAnapar=rand()%(10);
                    if (randAnapar > 1) // pi8anothta 80%
                    {
                        for (int i=0; i<8; i++)
                        {
                            //seiriakos elegxos twn keliwn
                            aboutReproduction(i);
                            // ean to (x1,y1) einai NULL
                            if (world[x1][y1] == NULL) //to teleutaio keli pou vre8hke eleu8ero kai energopoihsh tou flag oti uparxei keno keli gia anapargwgh
                            {
                                checkIfNull=true;
                                xNullAnap=x1;
                                yNullAnap=y1;
                            }


                            if (world[x1][y1] != NULL)
                            {
                                // ean to (x1,y1) DEN einai NULL KAI to (x1,y1) exei to idio ID me emena (xbackup, ybackup) ALLA den uparxei free keli
                                // tote allazoume tous rolous kai tsekaroume ta kelia gurw apo ton deutero organismo.
                                if ((world[x1][y1]->getId() == world[xbackup][ybackup]->getId()) && checkIfNull==false)
                                {
                                    for (int i=0; i<8; i++)
                                    {
                                        x=x1;
                                        y=y1;
                                        if ( world[x][y]->getFlag() )
                                        {
                                            aboutReproduction(i);
                                            if (world[x1][y1] == NULL)
                                            {
                                                checkIfNull=true;
                                                xNullAnap=x1;
                                                yNullAnap=y1;
                                            }
                                        }
                                    }
                                }

                                // ean to (x1,y1) DEN einai NULL KAI to (x1,y1) exei to idio ID me emena (xbackup, ybackup) KAI uparxei free keli
                                // tote dhmiourgia neou organsimou sto keno keli analoga to id pou uphrxe
                                // kai make to flag tou false wste o "mikros" na mn summetexei sthn anaparagwgh
                                if ((world[x1][y1]->getId() == world[xbackup][ybackup]->getId()) && checkIfNull==true)
                                {
                                    if (world[xbackup][ybackup]->getId() == 0)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new shark(0, minSizeOrganism[0], maxSizeOrganism[0], 0, growRate[0]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 1)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new dolphin(0, minSizeOrganism[1], maxSizeOrganism[1], 1, growRate[1]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 2)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new mullet(0, minSizeOrganism[2], maxSizeOrganism[2], 2, growRate[2]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 3)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new bream(0, minSizeOrganism[3], maxSizeOrganism[3], 3, growRate[3]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 4)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new octopus(0, minSizeOrganism[4], maxSizeOrganism[4], 4, growRate[4]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 5)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new sardine(0, minSizeOrganism[5], maxSizeOrganism[5], 5, growRate[5]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 6)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new fry(0, minSizeOrganism[6], maxSizeOrganism[6], 6, growRate[6]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                    else if (world[xbackup][ybackup]->getId() == 7)
                                    {
                                        world[xNullAnap][yNullAnap] = (organism *) new mussel(0, minSizeOrganism[7], maxSizeOrganism[7], 7, growRate[7]);
                                        world[xNullAnap][yNullAnap] -> setFlag(false);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// au3hsh mege8ous tou zwoplagkton
void increaseSizeZoo()
{
    for(int x=0; x<map_size; x++)
    {
        for(int y=0; y<map_size; y++)
        {
            if(world[x][y] != NULL)
            {
                if (world[x][y]->getId()==9)
                {
                    increasingMegethos = 1.15 * (world[x][y]->getMegethos()); // dld au3hsh mege8ous tou ka8e fora +15% (glitwnontas thn pros8esh tou paliou + to 15%)
                    world[x][y]->setMegethos(increasingMegethos);
                }
            }
        }
    }
}

// random wisagwgh new zwoplagkton
void newZoo()
{
    srand ( time(NULL) );
    for(int x=0; x<map_size; x++)
    {
        for(int y=0; y<map_size; y++)
        {
            randNewZwopl=rand()%(40);
            if(randNewZwopl == 1) // 1 sta 40 = 2.5 %
                if(world[x][y] == NULL)
                    world[x][y] = (organism *) new zooplankton(0, 1, 150, 9);
        }
    }
}

// fagwma organismwn
void eat()
{
    srand ( time(NULL) );
    for(int x=0; x<map_size; x++)
    {
        for(int y=0; y<map_size; y++)
        {
            int randEat=rand()%(10);
            if(randEat > 5)   // 40%
            {

                if (world[x][y] != NULL)
                {
                    // an den eimai NULL kai dn eimai futo/zwoplagtkon
                    if ((world[x][y]->getId() != 9) && (world[x][y]->getId() != 8))
                    {
                        aboutMove_Eat(x,y);
                        if (world[x1][y1] != NULL)
                        {
                            // elegxos mege8wn kai id an einai futo/zwoplagkton
                            if ((world[x1][y1]->getMegethos() < world[x][y]->getMegethos()) || (world[x1][y1]->getId() == 9) || (world[x1][y1]->getId() == 8))
                            {
                                increasingMegethos = (world[x][y]->getRythmos()) * (world[x1][y1]->getMegethos()); // ru8mos mou * mege8os tou
                                world[x][y]->setMegethos(world[x][y]->getMegethos() + increasingMegethos); // oso eixa + auto pou efaga
                                world[x1][y1] = NULL; // afou efaga ton allo 8a ginei NULL
                                swap(world[x][y], world[x1][y1]); // swap us -> paw sth 8esh tou
                                world[x1][y1]->setfoodPerWeek(world[x1][y1]->getfoodPerWeek() + increasingMegethos); // food per week -> oso eixa + auto pou efaga
                            }
                            else // na meiw8ei to mege8os mou
                            {
                                decreasingMegethos = (world[x][y]->getRythmos()) * (world[x][y]->getMegethos());
                                world[x][y]->setMegethos(world[x][y]->getMegethos() - decreasingMegethos);
                            }
                        }
                    }
                }
            }
        }
    }
}

/*
void haveToEatPerWeek(int xClicked, int yClicked)
{
    float tempTemp = world[xClicked][yClicked]->getMegethos() - ((world[xClicked][yClicked]->getMegethos()) * (haveToEatArray[world[xClicked][yClicked]->getId()]));

    for (int x=0; x<1; x++)
        tempTemp = tempTemp - (tempTemp * (haveToEatArray[world[xClicked][yClicked]->getId()])); // poso 8a einai k kala meta apo 1 vdomada 6 + 1 apo panw.

    if (1)//tempTemp < world[xClicked][yClicked]->getElaxistoMegethos())
    {
        world[xClicked][yClicked]->setHave(55); //world[xClicked][yClicked]->getElaxistoMegethos() - tempTemp + 55);
        cout<<"mphke"<<endl;
    }
    else
    {
        world[xClicked][yClicked]->setHave(44); // dn xreiazetai - peri8wrio gia na mh faei
        cout<<"dn mphke"<<endl;
    }

}
*/

//mhdenismos tou "food per week" ka8e psariou ka8e 7 clocks (7 meres)
void handleWeek(int counterClock)
{
    for(int x=0; x<map_size; x++)
        for(int y=0; y<map_size; y++)
            if ((world[x][y] != NULL) && (counterClock%7 == 0))
                 world[x][y]->setfoodPerWeek(0);
}

// sunarthsh gia katametrhsh twn alive organismwn
void CheckForAlive()
{
    for(int i=0; i<map_size; i++)
    {
        for(int j=0; j<map_size; j++)
        {
            if(world[i][j]!=NULL)
            {
                if((world[i][j]->getId()) == 0) counterAlive[0]++;
                else if((world[i][j]->getId()) == 1) counterAlive[1]++;
                else if((world[i][j]->getId()) == 2) counterAlive[2]++;
                else if((world[i][j]->getId()) == 3) counterAlive[3]++;
                else if((world[i][j]->getId()) == 4) counterAlive[4]++;
                else if((world[i][j]->getId()) == 5) counterAlive[5]++;
                else if((world[i][j]->getId()) == 6) counterAlive[6]++;
                else if((world[i][j]->getId()) == 7) counterAlive[7]++;
                else if((world[i][j]->getId()) == 8) counterAlive[8]++;
                else if((world[i][j]->getId()) == 9) counterAlive[9]++;
            }
        }
    }
}

// antistoixish tou world me ton worldGraph
void myDraw(organism* world[map_size][map_size], int worldGraph[map_size][map_size])
{
    for(int i=0; i<map_size; i++)
    {
        for (int j=0; j<map_size; j++)
        {
            if (world[i][j] != NULL)
                worldGraph[i][j] = world[i][j]->getId();
            else worldGraph[i][j] = -1;
        }
    }
}

//sunarthsh gia to restart ths prosomoiwshs
void restart()
{
    counterClock=0; // mhdenismos rologiou
    clearMap(); //set ta kelia NULL
    setMap(); //eisagwgh random stoixeiwn ston pinaka
    setAllFlags(true); //set ta flags twn keliwn pou periexoun organismous true
    setSetFoodPerWeek(); // set to FoodPerWeek ka8e organismou 0
    beginFlag = false; // flag ekkinhshs 0
    strcpy( temp1, "Simulation Restarted.");
    SDL_WM_SetCaption(temp1, " "); //set caption.
}

#endif

