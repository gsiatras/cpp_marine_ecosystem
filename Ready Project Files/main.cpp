#include "Play.h"

using namespace std;



void myClock(float mytime, Game game) //KOMPLE
{
    clock_t start_time;
    start_time = clock () + mytime * CLOCKS_PER_SEC;
    while (clock() < start_time)
    {
        //game.HandleEvents(world);
    }
}

void printGameSpeed()
{
    itoa( speed*1000, temp, 10);
    strcat( temp1, ". Game speed is: " );
    strcat( temp1, temp );
    strcat( temp1, " ms." );
    SDL_WM_SetCaption(temp1, "  ");
}

int main(int argc, char* argv[])
{
	Game game;

    long start = clock();

    clearMap(); //set ta kelia NULL
    setMap(); //eisagwgh random stoixeiwn ston pinaka
    setAllFlags(true); //set ta flags twn keliwn pou periexoun organismous true
    setSetFoodPerWeek(); // set to FoodPerWeek ka8e organismou 0

    strcpy( temp1, "Welcome to the simulation");
    game.Init( temp1 ,800,800,32,false);
	game.ChangeState(MenuState::Instance());
	printGameSpeed();

    myDraw(world, worldGraph); // draw ton random pinaka gia thn arxh.

	while(game.Running())
	{
		game.HandleEvents(world);

        if((beginFlag) && (game.getPause())) // an exei 3ekinhsei to game kai einai paused
        {
            itoa( counterClock, temp, 10);
            strcpy( temp1, "The simulation is paused on day: ");
            strcat( temp1, temp );

            printGameSpeed();
        }

        if(( clock() - start) >= (speed * CLOCKS_PER_SEC )) // mexri na mpei sth loop exoume ka8usterhsh.
        {
            if( !game.getPause() )
            {
                beginFlag = true; // flag oti to game 3ekinhse

                counterClock++;
                //myClock(speed, game); // ka8usterhsh programmatos

                //set ton titlo tou para8urou
                itoa( counterClock, temp, 10);
                strcpy( temp1, "The simulation is running. It is on day: ");
                strcat( temp1, temp );

                printGameSpeed();

                //********************GAMEPLAY**********************//
                increaseAge(); // au3hsh hlikiwn
                move(); // kinhsh organismwn
                setAllFlags(true); // flags gia kapoies xrhseis
                eat();
                handleWeek(counterClock); // elegxos gia thn katanalwsh ana evdomada
                reproduction(); // anaparagwgh psariwn
                setAllFlags(true);


                newPhyto(); // eisagwgh (anaparagwgh logw nerou) futoplagkton
                newZoo(); // omoia gia zwoplagkton
                increaseSizeZoo(); // au3hsh mege8ous zwoplagkton
                // ---------------  // au3hsh mege8ous futoplagkton
                deathCheck();

            }
            start = clock();
        }

        myDraw(world, worldGraph); //antistoixish tou real pinaka me ta grafika.
        if( game.getRender() )// Just to render only once at every STATE except PlayState !!
        {
            game.Draw(worldGraph); // draw ton pinaka twn grafikwn
        }
	}
	game.Clean();

	return 0;
}

