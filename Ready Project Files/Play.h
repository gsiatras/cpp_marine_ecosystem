#ifndef  _PLAY_H
#define _PLAY_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <iostream>
#include <string>
#include <sstream>

#include "HelpState.h"
#include "functions.h"
#include "Ssprite.h"
#include "GameGamestate.h"

int worldGraph[map_size][map_size];
int polutionFlag, polutionFlag1, netsFlag=1, xClicked, yClicked, x2, y2, x3, y3, x4, y4, var11;
float speed = 0.75;

TTF_Font *font = NULL;
SDL_Color textColor = { 255, 255, 255 };

string str = "";

SDL_Surface *text;
SDL_Surface *text1;

SDL_Surface* messageInfo; // gia tis sunarthseis
bool flag1;
bool flag3 = true; //


char *s = new char[50];

char *tmp1 = new char[50];

char *info = new char[25];
char *info1 = new char[25];
//***********************************************************


//************************* INPUT ***************************
int myInput(SDL_Event event, Game *game, int worldGraph[map_size][map_size])
{
    std::string temp = str; // copy to arxiko string gia elegxo sth sunexeia

    if( str.length() <= 16 )//If the string less than maximum size
    {
        if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )  //If the key is a number
            str += (char)event.key.keysym.unicode;

        if( ( event.key.keysym.unicode >= (Uint16)',' ) && ( event.key.keysym.unicode <= (Uint16)'-' )) // if the key is , or -
            str += (char)event.key.keysym.unicode;

        //if ( event.key.keysym.unicode <= (Uint16)' ' ) // den douleuei to backspace
        //   str += (char)event.key.keysym.unicode;
    }

    if (event.key.keysym.sym == SDLK_RETURN)
        return 2; // path8hke enter, move to next step

    //If backspace was pressed and the string isn't blank
    if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
    {
        //Remove a character from the end
        str.erase( str.length() - 1 );
    }

    if( str != temp ) //If the string was changed
    {
        SDL_FreeSurface( text );
        game->setRender( true );
        text = TTF_RenderText_Solid( font, str.c_str(), textColor );
    }

    return 1; // dn phre to input. 3ana pali.
}
//****************************************************************************************




/* examples:
INIT()
TTF_Init(); // init font
font = TTF_OpenFont( "comic.ttf", 22 ); // load font
SomeSprite = NULL; // make the sprite null
SomeSprite = Sprite::Load("Some.png"); // load image


CLEAN()
// free surfaces and fonts
SDL_FreeSurface(SomeSprite); // free surface
TTF_CloseFont( font ); // close font


*/


//******************************* AddNetsState *******************************************
class AddNetsState : public GameState
{
    public:
        void Init();
        void Clean();

        void Pause();
        void Resume();

        void HandleEvents(Game* game, organism *world[map_size][map_size]);
        void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size] );

		// Implement Singleton Pattern
		static AddNetsState* Instance()
		{
			return &m_AddNetsState;
		}

   protected:
		AddNetsState() {}

    private:
        static AddNetsState m_AddNetsState;

        SDL_Surface* addNetsSprite;
        SDL_Surface* Surf_nets;
};

AddNetsState AddNetsState::m_AddNetsState;

void AddNetsState::Update(Game* game)
{
}

void AddNetsState::Init()
{
    TTF_Init(); // init font
    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

    addNetsSprite = NULL; // make the sprite null
	addNetsSprite = Sprite::Load("img/nets1.png"); // load image
	Surf_nets=NULL;
	Surf_nets=Sprite::Load("img/nets.png");

	printf("AddNetsState Init Successful\n");
}

void AddNetsState::Clean() // free surfaces and fonts
{
    SDL_FreeSurface(addNetsSprite);
    SDL_FreeSurface(Surf_nets);
    TTF_CloseFont( font );
}

void AddNetsState::Pause()
{
	printf("AddNetsState Paused\n");
}

void AddNetsState::Resume()
{
	printf("AddNetsState Resumed\n");
}

void AddNetsState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
                    case SDLK_SPACE:
                        game->PopState(game); // epistrofh sto prohgoumeno state me to SPACE
                        break;

                    case SDLK_ESCAPE: // quit me to ESCAPE
                        game->Quit();
                        break;
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(netsFlag == 1) // gia to 1o klik
                {
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            // pixels / 32 gia na exoume to keli
                            x1 = event.button.x / 32;
                            y1 = event.button.y / 32;
                            netsFlag=2; // go to next step
                    }
                    break;
                }

                if(netsFlag==2) // 2o klik
                {
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            // pixels / 32 gia na exoume to keli
                            x2 = event.button.x / 32;
                            y2 = event.button.y / 32;
                            netsFlag = myNets(x1,y1,x2,y2,world); // analoga ti epistrafei sunexizetai to programma.
                    }
                    break;
                }

                if(netsFlag==5) // ean htan ola ok (dhlhadh 5)
                {
                    game->setRender( true );
                     // +1 sta x y logw tou akeraiou ths diaireshs gia to keli.
                    for(int i=x1; i<x2+1; i++)
                    {
                        for(int j=y1; j<y2+1; j++)
                        {
                            Sprite::Draw( game->GetScreen(), Surf_nets, i*32, j*32 );
                        }
                    }
                    netsFlag=0; // na mhn paei se kanena vhma.
                }
            break;
        }
    }
}

void AddNetsState::Draw(Game* game, int worldGraph[map_size][map_size])
{
    Sprite::Draw(game->GetScreen(), addNetsSprite, 0, 0); // draw to background
    messageInfo = TTF_RenderText_Solid(font, "Welcome to nets. Make 2 clicks to add them. Press Space to go back.", textColor);
    Sprite::Draw( game->GetScreen(), messageInfo, 0, 750);
    SDL_Flip(game->GetScreen());
    game->setRender( false );
}
//****************************************************************************************


//************************ AddPolutionState **********************************************
class AddPolutionState : public GameState
{
    public:
        void Init();
        void Clean();

        void Pause();
        void Resume();

        void HandleEvents(Game* game, organism *world[map_size][map_size]);
        void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size] );

		// Implement Singleton Pattern
		static AddPolutionState* Instance()
		{
			return &m_AddPolutionState;
		}

   protected:
		AddPolutionState() {}

    private:
        static AddPolutionState m_AddPolutionState;

        SDL_Surface* addPolutionSprite;
        SDL_Surface* message0;
        SDL_Surface* messageErr;

        SDL_Surface* message2;
        SDL_Surface* messageFin;
        SDL_Surface* Surf_polution;

        SDL_Surface* addTranspSprite;
        bool flagDraw;

};

AddPolutionState AddPolutionState::m_AddPolutionState;


void AddPolutionState::Update(Game* game)
{
}

void AddPolutionState::Init()
{
    flagDraw = true;

	addPolutionSprite = NULL;
	addPolutionSprite = Sprite::Load("img/addpolution.png");
	message0 = NULL;
	messageErr = NULL;

	message2 = NULL;
	messageFin = NULL;
	text = NULL;

	Surf_polution=NULL;
	Surf_polution=Sprite::Load("img/Polution.png");

	addTranspSprite = NULL;
	addTranspSprite = Sprite::Load("img/PolutionTransp.png");



    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

	printf("AddPolutionState Init Successful\n");
}

void AddPolutionState::Clean()
{
        SDL_FreeSurface(addPolutionSprite);
        SDL_FreeSurface(message0);
        SDL_FreeSurface(messageErr);
        SDL_FreeSurface(message2);
        SDL_FreeSurface(messageFin);
        SDL_FreeSurface(Surf_polution);
        SDL_FreeSurface(addTranspSprite);

        SDL_FreeSurface(text);
        TTF_CloseFont( font );
}

void AddPolutionState::Pause()
{
	printf("AddPolutionState Paused\n");
}

void AddPolutionState::Resume()
{
	printf("AddPolutionState Resumed\n");
}

void AddPolutionState::Draw(Game* game, int worldGraph[map_size][map_size])
{
    if(flagDraw)
    {
        Sprite::Draw(game->GetScreen(), addPolutionSprite, 0, 0); // draw gia mia fora to background
        message0 = TTF_RenderText_Solid(font, "Enter the % for the polution:", textColor);
        Sprite::Draw( game->GetScreen(), message0, 240, 700);
    }
    flagDraw = false;

    Sprite::Draw( game->GetScreen(), addTranspSprite, 0, 0);
    Sprite::Draw( game->GetScreen(), text, 370, 724);
    Sprite::Draw( game->GetScreen(), messageErr, 230, 766);
    Sprite::Draw( game->GetScreen(), message2, 200, 744);
    Sprite::Draw( game->GetScreen(), messageFin, 150, 766);

    SDL_Flip(game->GetScreen());
    game->setRender( false );
}

void AddPolutionState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        game->Quit();
                        break;

                    case SDLK_SPACE:
                        game->PopState(game);
                        break;
                }
                // otan polutionFlag1  = 0 tote eimaste sto keyboard. if polutionFlag1 = 1 eimaste sto mouse.
                if ( polutionFlag1 == 0)
                {
                    if(var11 == 1) // 1o vhma
                    {
                        //game->setRender( true );
                        messageErr = NULL;
                        var11 = myInput(event, game, worldGraph); // an epistrafei 2 sunexizei kanonika
                    }

                    else if(var11 == 2)
                    {
                        // apo8hkeush input tou xrhsth (pososto)
                        int handleAddPolution[1] = {0};
                        copy(str.begin(), str.end(), info);
                        info[str.size()] ='\0';
                        handleAddPolution[0] = atoi(info);
                        inputAddPolution = handleAddPolution[0];

                        game->setRender( true );
                        message2 = TTF_RenderText_Solid(font, "Now, click where you want to put them.", textColor);
                        polutionFlag1 = 1; // na fugei gia ta clicks
                        polutionFlag = 1;   // na mpei sto 1o vhma twn click
                        var11 = 0;  // (asfaleia) kanena vhma gia to keyboard
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
            if ( polutionFlag1 == 1)
            {
                if(polutionFlag == 1) // 1o vhma sto mouse.
                {
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            // pixels / 32 gia na exoume to keli
                            x1 = event.button.x / 32;
                            y1 = event.button.y / 32;
                            polutionFlag=2; // next click/ step

                    }
                    break;

                }

                if(polutionFlag==2)
                {
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            // pixels / 32 gia na exoume to keli
                            x2 = event.button.x / 32;
                            y2 = event.button.y / 32;
                            polutionFlag = myPolution(x1, y1, x2, y2, inputAddPolution, world); // omoia me th molunsh, analoga thn epistrefomenh timh sunexizetai o kwdikas
                    }
                    break;

                }

                if(polutionFlag==3)
                {
                    game->setRender( true );
                    message2 = NULL;
                    messageErr = TTF_RenderText_Solid(font, "Wrong coordinates. Click again.", textColor); // la8os y
                    //epistrofh sto 1o click
                    polutionFlag = 1;
                }

                if (polutionFlag == 4)
                {
                    game->setRender( true );
                    messageErr = TTF_RenderText_Solid(font, "You have entered >100%. Enter again.", textColor); // la8os keyb input
                    // swsth metavash sto keyboard
                    str = "";
                    polutionFlag1 = 0;
                    var11 = 1;
                }

                if (polutionFlag==5)
                {
                    game->setRender( true );
                    messageErr = NULL;

                    messageFin = TTF_RenderText_Solid(font, "You have added Polution. Press Space to go back.", textColor); // ola ok

                    for(int i=x1; i<x2 + 1; i++) // +1 logw akeraias timhs tou click
                    {
                        for(int j=y1; j<y1 + polutionSize1; j++)
                        {
                            Sprite::Draw( game->GetScreen(), Surf_polution, i*32, j*32 );

                            if(world[i][j] != NULL)
                            {
                                molusmeno_megethos = (inputAddPolution/200) * (world[i][j]->getMegethos()); // /200 = /2 (sto miso) * /100 (gia to pososto)
                                world[i][j]->setMegethos(world[i][j]->getMegethos() - molusmeno_megethos);
                            }
                        }
                    }
                    polutionFlag1=0;
                }
            }
            break;
		}
	}
}
//****************************************************************************************


//******************************* AddState ***********************************************
class AddState : public GameState
{
    public:
		void Init();
		void Clean();

		void Pause();
		void Resume();

		void HandleEvents(Game* game, organism *world[map_size][map_size]);
		void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size] );

		// Implement Singleton Pattern
		static AddState* Instance()
		{
			return &m_AddState;
		}

    protected:
		AddState() {}

    private:
        static AddState m_AddState;

        SDL_Surface* addSprite;
        SDL_Surface* addSpriteTransp;
        SDL_Surface* message0;
        SDL_Surface* message1;
        SDL_Surface* message2;
        SDL_Surface* message3;
};

AddState AddState::m_AddState;

void AddState::Init()
{
    message0 = NULL;
    message1 = NULL;
    message2 = NULL;
    message3 = NULL;
    text=NULL;

    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

    addSprite = NULL;
	addSprite = Sprite::Load("img/addstate.png");

    addSpriteTransp = NULL;
    addSpriteTransp = Sprite::Load("img/transp.png");
	printf("Addstate Init Successful\n");
}

void AddState::Clean()
{
    SDL_FreeSurface(addSprite);
    SDL_FreeSurface(addSpriteTransp);
    SDL_FreeSurface(message0);
    SDL_FreeSurface(message1);
    SDL_FreeSurface(message2);
    SDL_FreeSurface(message3);
    SDL_FreeSurface(text);
    TTF_CloseFont( font );
}

void AddState::Update(Game* game)
{
}

void AddState::Pause()
{
	printf("AddState Paused\n");
}

void AddState::Resume()
{
	printf("AddState Resumed\n");
}

void AddState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;
	static int var1 = 0;
    static int newOrganismId = 0;

	if (SDL_PollEvent(&event))
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;

            case SDL_KEYDOWN:
                    if (var1==0)
                    {
                        switch( event.key.keysym.sym )
                        {
                            case SDLK_ESCAPE:
                                game->Quit();
                                break;

                            case SDLK_SPACE:
                                game->PopState(game);
                                break;
                            // analoga to case tupwnei antistoixo mhnuma, zwgrafizetai mia fora( setRender) kai to var1 dinei th sunexeia ston kwdika
                            // krateitai backup sto newOrganismId to id pou epilex8hke
                            case SDLK_0:
                                message0 = TTF_RenderText_Solid(font, "You have chosen shark.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 0;
                                break;

                            case SDLK_1:
                                message0 = TTF_RenderText_Solid(font, "You have chosen dolphin.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 1;
                                break;

                            case SDLK_2:
                                message0 = TTF_RenderText_Solid(font, "You have chosen mullet.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 2;
                                break;

                            case SDLK_3:
                                message0 = TTF_RenderText_Solid(font, "You have chosen bream.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 3;
                                break;

                            case SDLK_4:
                                message0 = TTF_RenderText_Solid(font, "You have chosen octapus.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 4;
                                break;

                            case SDLK_5:
                                message0 = TTF_RenderText_Solid(font, "You have chosen sardine.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 5;
                                break;

                            case SDLK_6:
                                message0 = TTF_RenderText_Solid(font, "You have chosen fry.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 6;
                                break;

                            case SDLK_7:
                                message0 = TTF_RenderText_Solid(font, "You have chosen mussel.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 7;
                                break;

                            case SDLK_8:
                                message0 = TTF_RenderText_Solid(font, "You have chosen phytoplankton.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 8;
                                break;

                            case SDLK_9:
                                message0 = TTF_RenderText_Solid(font, "You have chosen zooplankton.", textColor);
                                message3 = TTF_RenderText_Solid(font, "Now give its attributes.", textColor);
                                game->setRender( true );
                                var1=1;
                                newOrganismId = 9;
                                break;
                        }
                    }
                    else if(var1 == 1) // na parei to input
                    {
                        var1 = myInput(event, game, worldGraph);
                    }
                    else if(var1 == 2)
                    {
                        //xwrismos twn input tou xrhsth
                        int handleAdd[3] = {0,0,0}; // pinakas gia ta 3 strings
                        copy(str.begin(), str.end(), info);
                        info[str.size()] ='\0';
                        info1 = strtok (info, ",- "); //seperate strings with , or -
                        handleAdd[0] = atoi(info1);
                        for (int i = 1; i < 3 && info1 != NULL; i++)
                        {
                            info1= strtok(NULL, ",- ");
                            handleAdd[i] = atoi(info1); //ka8e keli pairnei to spasmeno string
                        }

                        newOrganismGraphs(newOrganismId, handleAdd, xClicked, yClicked);

                        message2 = TTF_RenderText_Solid(font, "You have added a new fish. Press Space to go back.", textColor);
                        game->setRender( true );
                        var1 = 0;
                    }
                    break;
		}
}

void AddState::Draw(Game* game, int worldGraph[map_size][map_size])
{
    //zwgrafizontai ta parakatw mia fora
    if (flag3)
    {
        Sprite::Draw(game->GetScreen(), addSprite, 0, 0);
        message1 = TTF_RenderText_Solid( font, "Press 0 for shark." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 10);
        message1 = TTF_RenderText_Solid( font, "Press 1 for dolphin." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 32);
        message1 = TTF_RenderText_Solid( font, "Press 2 for mullet." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 54);
        message1 = TTF_RenderText_Solid( font, "Press 3 for bream" , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 76);
        message1 = TTF_RenderText_Solid( font, "Press 4 for octapus.", textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 98);
        message1 = TTF_RenderText_Solid( font, "Press 5 for sardine." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 120);
        message1 = TTF_RenderText_Solid( font,"Press 6 for fry." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 142);
        message1 = TTF_RenderText_Solid( font,"Press 7 for mussel." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 164);
        message1 = TTF_RenderText_Solid( font, "Press 8 for phytoplankton." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 186);
        message1 = TTF_RenderText_Solid( font, "Press 9 for zooplankton." , textColor );
        Sprite::Draw( game->GetScreen(), message1, 10, 208);
        message1 = TTF_RenderText_Solid(font, "About the input: You give its age, its size and its growth rate with commas", textColor);
        Sprite::Draw( game->GetScreen(), message1, 10, 252);
        message1 = TTF_RenderText_Solid(font, "or dashes between them. If you enter 999 to an attribure, it's like you", textColor);
        Sprite::Draw( game->GetScreen(), message1, 10, 274);
        message1 = TTF_RenderText_Solid(font, "entered the default value for it.", textColor);
        Sprite::Draw( game->GetScreen(), message1, 10, 296);

    }
    flag3 = false;

    Sprite::Draw( game->GetScreen(), addSpriteTransp, 0, 0);
    Sprite::Draw( game->GetScreen(), message0, 10, 318);
    Sprite::Draw( game->GetScreen(), message3, 10, 350);
    Sprite::Draw( game->GetScreen(), text, 10, 372);
    Sprite::Draw( game->GetScreen(), message2, 10, 400);

    SDL_Flip(game->GetScreen());
    game->setRender(false);
}
//****************************************************************************************


//************************ GeneralInfoState **********************************************
class GeneralInfoState : public GameState
{
    public:
        void Init();
        void Clean();

        void Pause();
        void Resume();

        void HandleEvents(Game* game, organism *world[map_size][map_size]);
        void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size] );

		// Implement Singleton Pattern
		static GeneralInfoState* Instance()
		{
			return &m_GeneralInfoState;
		}

    protected:
		GeneralInfoState() {}

    private:
        static GeneralInfoState m_GeneralInfoState;

        SDL_Surface* GeneralInfoSprite;
};

GeneralInfoState GeneralInfoState::m_GeneralInfoState;

void GeneralInfoState::Update(Game* game)
{
}

// stis parakatw sunarthseis ginontai elegxoi gia ka8e eidos pou anaferetai sto onoma ths sunarthshs
// kai uparxei elegxos gia la8os xeirismo otan den uparxei alive kapoio eidos organismou (-1)
void deathStat(Game* game, int counterAlive[10])
{
    for (int i=0; i<10; i++)
    {
        counterDeath[i] = organism::counterBorn[i] - counterAlive[i];
        counterDeath[10] = counterDeath[10] + counterDeath[i];
    }

    for (int i=0; i<10; i++)
        counterDeath[i] = counterDeath[i] * 100 / counterDeath[10] ;

    strcpy( s, "Death rate of: ");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 274);

    strcpy( s, "   Sharks: ");
    itoa(counterDeath[0], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 296);

    strcpy( s, "   Dolphins = ");
    itoa(counterDeath[1], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 318);

    strcpy( s, "   Mullets = ");
    itoa(counterDeath[2], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 340);

    strcpy( s, "   Breams = ");
    itoa(counterDeath[3], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 362);

    strcpy( s, "   Octopuses = ");
    itoa(counterDeath[4], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 384);

    strcpy( s, "   Sardines = ");
    itoa(counterDeath[5], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 406);

    strcpy( s, "   Fry = ");
    itoa(counterDeath[6], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 428);

    strcpy( s, "   Mussels = ");
    itoa(counterDeath[7], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 450);

    strcpy( s, "   Phytoplankton = ");
    itoa(counterDeath[8], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 472);

    strcpy( s, "   Zooplankton = ");
    itoa(counterDeath[9], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 494);

    SDL_Flip(game->GetScreen());
}

void ageStat(Game* game, int counterAlive[10]) // check if it works
{
    for(int i=0; i<map_size; i++)
    {
        for(int j=0; j<map_size; j++)
        {
            if(world[i][j]!=NULL)
            {
                if((world[i][j]->getId()) == 0) counterAge[0] = counterAge[0] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 1) counterAge[1] = counterAge[1] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 2) counterAge[2] = counterAge[2] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 3) counterAge[3] = counterAge[3] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 4) counterAge[4] = counterAge[4] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 5) counterAge[5] = counterAge[5] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 6) counterAge[6] = counterAge[6] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 7) counterAge[7] = counterAge[7] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 8) counterAge[8] = counterAge[8] + world[i][j]->getAge();
                else if((world[i][j]->getId()) == 9) counterAge[9] = counterAge[9] + world[i][j]->getAge();
            }
        }
    }

    for (int i=0; i<10; i++)
    {
        if (counterAlive[i] == 0) counterAge[i] = -1;
        else counterAge[i] = counterAge[i]*100 / counterAlive[i];
    }

    strcpy( s, "Average age of: ");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 472);

    strcpy( s, "   Sharks: ");
    itoa(counterAge[0], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 494);

    strcpy( s, "   Dolhpins: ");
    itoa(counterAge[1], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 516);

    strcpy( s, "   Mullets: ");
    itoa(counterAge[2], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 538);

    strcpy( s, "   Breams: ");
    itoa(counterAge[3], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 560);

    strcpy( s, "   Octopuses: ");
    itoa(counterAge[4], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 582);

    strcpy( s, "   Sardines: ");
    itoa(counterAge[5], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 604);

    strcpy( s, "   Fry: ");
    itoa(counterAge[6], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 626);

    strcpy( s, "   Mussels: ");
    itoa(counterAge[7], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 648);

    strcpy( s, "   Phytoplankton: ");
    itoa(counterAge[8], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 670);

    strcpy( s, "   Zooplankton: ");
    itoa(counterAge[9], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 692);
}

void MOmege8os(Game* game, int counterAlive[10]) // check if it works
{
    for(int i=0; i<map_size; i++)
    {
        for(int j=0; j<map_size; j++)
        {
            if(world[i][j]!=NULL)
            {
                if((world[i][j]->getId()) == 0) counterMegethos[0] = counterMegethos[0] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 1) counterMegethos[1] = counterMegethos[1] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 2) counterMegethos[2] = counterMegethos[2] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 3) counterMegethos[3] = counterMegethos[3] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 4) counterMegethos[4] = counterMegethos[4] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 5) counterMegethos[5] = counterMegethos[5] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 6) counterMegethos[6] = counterMegethos[6] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 7) counterMegethos[7] = counterMegethos[7] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 8) counterMegethos[8] = counterMegethos[8] + world[i][j]->getMegethos();
                else if((world[i][j]->getId()) == 9) counterMegethos[9] = counterMegethos[9] + world[i][j]->getMegethos();
            }
        }
    }

    for (int i=0; i<10; i++)
    {
        if(counterAlive[i] == 0) counterMegethos[i] = -1;
        else counterMegethos[i] = counterMegethos[i]*100 / counterAlive[i] ;
    }

    strcpy( s, "Average size of: ");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 10);

    strcpy( s, "   Sharks = ");
    itoa(counterMegethos[0], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 32);

    strcpy( s, "   Dolphins = ");
    itoa(counterMegethos[1], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 54);

    strcpy( s, "   Mullets = ");
    itoa(counterMegethos[2], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 76);

    strcpy( s, "   Breams = ");
    itoa(counterMegethos[3], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 98);

    strcpy( s, "   Octopuses = ");
    itoa(counterMegethos[4], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 120);

    strcpy( s, "   Sardines = ");
    itoa(counterMegethos[5], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 142);

    strcpy( s, "   Marides =");
    itoa(counterMegethos[6], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 164);

    strcpy( s, "   Mussels = ");
    itoa(counterMegethos[7], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 186);

    strcpy( s, "   Phytoplankton = ");
    itoa(counterMegethos[8], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 208);

    strcpy( s, "   Zooplankton = ");
    itoa(counterMegethos[9], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 400, 230);

    SDL_Flip(game->GetScreen());
}

void aliveFunc(Game* game, int counterAlive[10])
{
    strcpy( s, "Alive: Sharks = ");
    itoa(counterAlive[0], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 10);

    strcpy( s, "   Dolhpins = ");
    itoa(counterAlive[1], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 32);

    strcpy( s, "   Mullets = ");
    itoa(counterAlive[2], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 54);

    strcpy( s, "   Breams = ");
    itoa(counterAlive[3], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 76);

    strcpy( s, "   Octopuses = ");
    itoa(counterAlive[4], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 98);

    strcpy( s, "   Sardines = ");
    itoa(counterAlive[5], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 120);

    strcpy( s, "   Marides = ");
    itoa(counterAlive[6], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 142);

    strcpy( s, "   Mussels = ");
    itoa(counterAlive[7], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 164);

    strcpy( s, "   Phytoplankton = ");
    itoa(counterAlive[8], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 186);

    strcpy( s, "   Zooplankton = ");
    itoa(counterAlive[9], tmp1 ,10);
    strcat( s, tmp1);
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 208);

    SDL_Flip(game->GetScreen());
}

void averageFoodPerWeek(organism* world[map_size][map_size], int counterAlive[10], int avgFoodPerWeek[8], int FoodPerWeek[8], Game* game) // check if it works
{
    for(int i=0; i<map_size; i++)
    {
        for(int j=0; j<map_size; j++)
        {
            if(world[i][j] != NULL)
            {
                if((world[i][j]->getId()) == 0) FoodPerWeek[0] = FoodPerWeek[0] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 1) FoodPerWeek[1] = FoodPerWeek[1] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 2) FoodPerWeek[2] = FoodPerWeek[2] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 3) FoodPerWeek[3] = FoodPerWeek[3] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 4) FoodPerWeek[4] = FoodPerWeek[4] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 5) FoodPerWeek[5] = FoodPerWeek[5] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 6) FoodPerWeek[6] = FoodPerWeek[6] + world[i][j]->getfoodPerWeek();
                else if((world[i][j]->getId()) == 7) FoodPerWeek[7] = FoodPerWeek[7] + world[i][j]->getfoodPerWeek();
            }
        }
    }

    for (int i=0; i<8; i++)
    {
        if(counterAlive[i] == 0) avgFoodPerWeek[i] = -1;
        else avgFoodPerWeek[i] = FoodPerWeek[i]*100 / counterAlive[i];
    }

    strcpy( s, "Average Food Per Week of:");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 252);

    strcpy( s, "   Sharks = ");
    itoa(avgFoodPerWeek[0], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 274);

    strcpy( s, "   Dolphins = ");
    itoa(avgFoodPerWeek[1], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 296);

    strcpy( s, "   Mullets = ");
    itoa(avgFoodPerWeek[2], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 318);

    strcpy( s, "   Breams = ");
    itoa(avgFoodPerWeek[3], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 340);

    strcpy( s, "   Octopuses = ");
    itoa(avgFoodPerWeek[4], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 362);

    strcpy( s, "   Sardines = ");
    itoa(avgFoodPerWeek[5], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 384);

    strcpy( s, "   Fry = ");
    itoa(avgFoodPerWeek[6], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo,10, 406);

    strcpy( s, "   Mussels = ");
    itoa(avgFoodPerWeek[7], tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    messageInfo = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), messageInfo, 10, 428);

    SDL_Flip(game->GetScreen());
}

void GeneralInfoState::Draw(Game* game, int worldGraph[map_size][map_size])
{
    Sprite::Draw(game->GetScreen(), GeneralInfoSprite, 0, 0);

    // den xrhsimopoioume koinh LOOP gia ton upologismo giati 8eloume na uparxei kapoia ane3arthsia twn sunarthsewn
    CheckForAlive();
    ageStat(game, counterAlive);
    aliveFunc(game, counterAlive);
    deathStat(game, counterAlive);
    MOmege8os(game, counterAlive);
    averageFoodPerWeek(world, counterAlive, avgFoodPerWeek, FoodPerWeek, game);

    game->setRender(false);
}

void GeneralInfoState::Init()
{
	GeneralInfoSprite = NULL;
	GeneralInfoSprite = Sprite::Load("img/GeneralInfoState.png");
	TTF_Init();
    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

	printf("GeneralInfoState Init Successful\n");
}

void GeneralInfoState::Clean()
{
        SDL_FreeSurface(GeneralInfoSprite);
        SDL_FreeSurface(messageInfo);
        TTF_CloseFont( font );
}

void GeneralInfoState::Pause()
{
	printf("GeneralInfoState Paused\n");
}

void GeneralInfoState::Resume()
{
	printf("GeneralInfoState Resumed\n");
}

void GeneralInfoState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				    case SDLK_ESCAPE:
                        game->Quit();
                        break;

                    case SDLK_SPACE:
                        game->PopState(game);
                        break;
                }
            break;
        }
    }
}
//****************************************************************************************


//******************************* Print Info State ***************************************
class PrintInfoState : public GameState
{
    public:
        void Init();
        void Clean();

        void Pause();
        void Resume();

        void HandleEvents(Game* game, organism *world[map_size][map_size]);
        void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size] );

		// Implement Singleton Pattern
		static PrintInfoState* Instance()
		{
			return &m_PrintInfoState;
		}

   protected:
		PrintInfoState() {}

    private:
        static PrintInfoState m_PrintInfoState;

        SDL_Surface* PrintInfoSprite;
        SDL_Surface* message0;
};
PrintInfoState PrintInfoState::m_PrintInfoState;

void PrintInfoState::Update(Game* game)
{
}

void PrintInfoState::Draw(Game* game, int worldGraph[map_size][map_size])
{
    Sprite::Draw(game->GetScreen(), PrintInfoSprite, 0, 0);

    // emfanish eidous kai statistikwn gia ton epilegmeno organismo me sunarthseis get
    char *kind = new char[40];

    if((world[xClicked][yClicked]->getId()) == 0) kind="You have selected a shark.";
    else if((world[xClicked][yClicked]->getId()) == 1) kind="You have selected a dolphin.";
    else if((world[xClicked][yClicked]->getId()) == 2) kind="You have selected a mullet.";
    else if((world[xClicked][yClicked]->getId()) == 3) kind="You have selected a bream.";
    else if((world[xClicked][yClicked]->getId()) == 4) kind="You have selected an octapus.";
    else if((world[xClicked][yClicked]->getId()) == 5) kind="You have selected a sardin.";
    else if((world[xClicked][yClicked]->getId()) == 6) kind="You have selected a fry.";
    else if((world[xClicked][yClicked]->getId()) == 7) kind="You have selected a mussel.";
    else if((world[xClicked][yClicked]->getId()) == 8) kind="You have selected a phytoplankton";
    else if((world[xClicked][yClicked]->getId()) == 9) kind="You have selected a zooplankton.";

    message0 = TTF_RenderText_Solid( font, kind, textColor );
    Sprite::Draw( game->GetScreen(), message0, 10, 10);

    strcpy( s, "Its age is: ");
    int tmp = world[xClicked][yClicked]->getAge();
    itoa(tmp, tmp1 ,10);
    strcat( s, tmp1);
    message0 = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), message0, 10, 32);

    strcpy( s, "Its size is: ");
    tmp = (world[xClicked][yClicked]->getMegethos())*100;
    itoa(tmp, tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    message0 = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), message0, 10, 54);

    strcpy( s, "Its growth rate is: ");
    tmp = (world[xClicked][yClicked]->getRythmos())*100;
    itoa(tmp, tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    message0 = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), message0, 10, 76);

    strcpy( s, "Its food per week is: ");
    tmp = (world[xClicked][yClicked]->getfoodPerWeek())*100;
    itoa(tmp, tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    message0 = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), message0, 10, 98);

    // check gia thn vdomada HAVE TO EAT
    float tempTemp = world[xClicked][yClicked]->getMegethos() - ((world[xClicked][yClicked]->getMegethos()) * (haveToEatArray[world[xClicked][yClicked]->getId()]));
    for (int x=0; x<6; x++)
        tempTemp = tempTemp - (tempTemp * (haveToEatArray[world[xClicked][yClicked]->getId()])); // poso 8a einai k kala meta apo 1 vdomada 6 + 1 apo panw.

    if (tempTemp < world[xClicked][yClicked]->getElaxistoMegethos()) tempTemp = (world[xClicked][yClicked]->getElaxistoMegethos() - tempTemp + 1); // h diafora oso einai + 1 wste na ta kataferei
    else tempTemp = 0; // dn xreiazetai - peri8wrio gia na mh faei

    strcpy( s, "It has to eat per week: ");
    tmp = tempTemp*100;
    itoa(tmp, tmp1 ,10);
    strcat( s, tmp1);
    strcat( s, "%.");
    message0 = TTF_RenderText_Solid( font, s, textColor );
    Sprite::Draw( game->GetScreen(), message0, 10, 120);

    SDL_Flip(game->GetScreen());
    game->setRender(false);
}

void PrintInfoState::Init()
{
	PrintInfoSprite = NULL;
	PrintInfoSprite = Sprite::Load("img/GeneralInfoState.png");

	message0 = NULL;

	TTF_Init();
    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

	printf("PrintInfoState Init Successful\n");
}

void PrintInfoState::Clean()
{
        SDL_FreeSurface(PrintInfoSprite);
        SDL_FreeSurface(message0);
        TTF_CloseFont( font );
}

void PrintInfoState::Pause()
{
	printf("PrintInfoState Paused\n");
}

void PrintInfoState::Resume()
{
	printf("PrintInfoState Resumed\n");
}

void PrintInfoState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				    case SDLK_ESCAPE:
                        game->Quit();
                        break;

                    case SDLK_SPACE:
                        game->PopState(game);
                        break;
                }
            break;
        }
    }
}
//****************************************************************************************


//************************* PLAY STATE ***************************************************
class PlayState : public GameState
{
	public:
		void Init();
		void Clean();

		void Pause();
		void Resume();

		void HandleEvents(Game* game, organism *world[map_size][map_size]);
		void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size] );

		// Implement Singleton Pattern
		static PlayState* Instance()
		{
			return &m_PlayState;
		}

        void setPause( bool pause ){    this->pause = pause;  }
        bool getPause(){    return this->pause;  }

        bool getRender() { return therender; }
        void setRender(bool therender) { this-> therender = therender;}

    protected:
		PlayState() {}

	private:
		static PlayState m_PlayState;

        bool pause;
        bool therender;

		SDL_Surface* playSprite;

        SDL_Surface* Surf_karxarias;
        SDL_Surface* Surf_delfini;
        SDL_Surface* Surf_kefalos;
        SDL_Surface* Surf_tsipoura;
        SDL_Surface* Surf_xtapodi;
        SDL_Surface* Surf_sardela;
        SDL_Surface* Surf_marida;
        SDL_Surface* Surf_mudi;
        SDL_Surface* Surf_Futoplankton;
        SDL_Surface* Surf_Zwoplankton;

       /* int some1;
        int some2;
        char mouse[8];
        SDL_Surface* Font_Motion;*/
};

PlayState PlayState::m_PlayState;

void PlayState::Init()
{
    setPause(true);

    //Font_Motion = NULL;

	playSprite = NULL;
    Surf_karxarias = NULL;
    Surf_delfini = NULL;
    Surf_kefalos = NULL;
    Surf_tsipoura = NULL;
    Surf_xtapodi = NULL;
    Surf_sardela = NULL;
    Surf_marida = NULL;
    Surf_mudi = NULL;
    Surf_Futoplankton = NULL;
    Surf_Zwoplankton = NULL;

	playSprite = Sprite::Load("img/background.bmp");
    Surf_karxarias = Sprite::Load("fish/shark.png");
    Surf_delfini = Sprite::Load("fish/dolphin.png");
    Surf_kefalos = Sprite::Load("fish/mullet.png");
    Surf_tsipoura = Sprite::Load("fish/bream.png");
    Surf_xtapodi = Sprite::Load("fish/octopus.png");
    Surf_sardela = Sprite::Load("fish/sardine.png");
    Surf_marida = Sprite::Load("fish/fry.png");
    Surf_mudi = Sprite::Load("fish/mussel.png");
    Surf_Futoplankton = Sprite::Load("img/fytoplankton.png");
    Surf_Zwoplankton = Sprite::Load("img/zooplankton1.png");

	printf("PlayState Init Successful\n");
}

void PlayState::Clean()
{
    SDL_FreeSurface(playSprite);
    SDL_FreeSurface(Surf_karxarias);
    SDL_FreeSurface(Surf_delfini);
    SDL_FreeSurface(Surf_kefalos);
    SDL_FreeSurface(Surf_tsipoura);
    SDL_FreeSurface(Surf_xtapodi);
    SDL_FreeSurface(Surf_sardela);
    SDL_FreeSurface(Surf_marida);
    SDL_FreeSurface(Surf_mudi);
    SDL_FreeSurface(Surf_Futoplankton);
    SDL_FreeSurface(Surf_Zwoplankton);

    //SDL_FreeSurface(Font_Motion);
}

void PlayState::Pause()
{
	printf("PlayState Paused\n");
}

void PlayState::Resume()
{
	printf("PlayState Resumed\n");
}

// in handle events
void PlayState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				    // gia ola ta events ginontai aparaithtoi elegxoi kai arxikopoihseis
				    case SDLK_ESCAPE:
                        game->Quit();
                        break;

                    case SDLK_SPACE:
                        game->setPause( !game->getPause());
                        break;

                    case SDLK_n:
                        netsFlag=1;
                        game->PushState(AddNetsState::Instance(), game);
                        break;

                    case SDLK_p:
                        str = ""; // gia to input
                        var11 = 1;
                        polutionFlag1 = 0;
                        polutionFlag = 1;
                        game->PushState(AddPolutionState::Instance(), game);
                        break;

                    case SDLK_g:
                        // arxikopoihseis pinakwn
                        for (int i=0; i<11; i++)
                        {
                            counterAge[i] = 0;
                            counterDeath[i] = 0;
                            counterMegethos[i] = 0;
                        }
                        for (int i=0; i<10; i++) counterAlive[i]=0;
                        for (int i=0; i<8; i++)
                        {
                            FoodPerWeek[i] = 0;
                            avgFoodPerWeek[i] = 0;
                        }
                        flag1=true;
                        game->PushState(GeneralInfoState::Instance(), game);
                        break;

                    case SDLK_h:
                        game->PushState(HelpState::Instance(), game);
                        break;

                    case SDLK_r:
                        restart();
                        break;

                    case SDLK_UP:
                        speed = speed - 0.25;
                        break;

                    case SDLK_DOWN:
                        speed = speed + 0.25;
                        break;
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        xClicked = event.button.x / 32;
                        yClicked = event.button.y / 32;

                        if (world[ xClicked ][ yClicked ] == NULL ) // if null ->> add new organism
                        {
                            flag3 = true;
                            str = ""; // mhdenismos tou string pou krataei ta stoixeia eisagwghs tou xrhsth
                            game->PushState(AddState::Instance(), game);
                        }
                        else
                            game->PushState(PrintInfoState::Instance(), game); //an den einai NULL - vlepw ta statistika tou
                        break;
                }
            break;
/*
            case SDL_MOUSEMOTION:
                some1 = event.motion.x / 32;
                some2 = event.motion.y / 32;


                    itoa( some1, temp, 10 );
                    strcpy( mouse, temp );
                    strcat( mouse, " , ");
                    itoa( some2, temp, 10 );
                    strcat( mouse, temp );
                    Font_Motion = TTF_RenderText_Solid( font, mouse, textColor );

            break;*/
        }
    }
}

void PlayState::Update(Game* game)
{
}

void PlayState::Draw(Game* game, int worldGraph[map_size][map_size])
{
	Sprite::Draw(game->GetScreen(), playSprite, 0, 0);

    for( int x = 0; x < map_size; x++)
    {
        for( int y = 0; y < map_size; y++ )
        {
            if( worldGraph[x][y] == 0 ) Sprite::Draw( game->GetScreen(), Surf_karxarias, x*32, y*32 );
            else if( worldGraph[x][y] == 1 ) Sprite::Draw( game->GetScreen(), Surf_delfini, x*32, y*32 );
            else if( worldGraph[x][y] == 2 ) Sprite::Draw( game->GetScreen(), Surf_kefalos, x*32, y*32 );
            else if( worldGraph[x][y] == 3 ) Sprite::Draw( game->GetScreen(), Surf_tsipoura, x*32, y*32 );
            else if( worldGraph[x][y] == 4 ) Sprite::Draw( game->GetScreen(), Surf_xtapodi, x*32, y*32 );
            else if( worldGraph[x][y] == 5 ) Sprite::Draw( game->GetScreen(), Surf_sardela, x*32, y*32 );
            else if( worldGraph[x][y] == 6 ) Sprite::Draw( game->GetScreen(), Surf_marida, x*32, y*32 );
            else if( worldGraph[x][y] == 7 ) Sprite::Draw( game->GetScreen(), Surf_mudi, x*32, y*32 );
            else if( worldGraph[x][y] == 8 ) Sprite::Draw( game->GetScreen(), Surf_Futoplankton, x*32, y*32 );
            else if( worldGraph[x][y] == 9 ) Sprite::Draw( game->GetScreen(), Surf_Zwoplankton, x*32, y*32 );
        }
    }
    /*if(  game->getPause() )
    {
        Sprite::Draw( game->GetScreen(), Font_Motion, some1*32, some2*32 );
    }*/
    SDL_Flip(game->GetScreen());
}
//****************************************************************************************



//************************* MENU STATE ***************************************************
class MenuState : public GameState
{
	public:
		void Init();
		void Clean();

		void Pause();
		void Resume();

		void HandleEvents(Game* game, organism *world[map_size][map_size]);
		void Update(Game* game);
		void Draw(Game* game, int worldGraph[map_size][map_size]);

		// Implement Singleton Pattern
		static MenuState* Instance()
		{
			return &m_MenuState;
		}

	protected:
		MenuState() {}

	private:
		static MenuState m_MenuState;

        int moveFishX, moveFishY, moveFishX1, moveFishY1, moveFish2Y;
		SDL_Surface* menuSprite;
        SDL_Surface* message;
        SDL_Surface* movedFish;
        SDL_Surface* movedFish1;
        SDL_Surface* movedFish2;
        SDL_Surface* menuSpriteFix;
        bool flagFish, flagFish1, flagDraw;
};

MenuState MenuState::m_MenuState;

void MenuState::Init()
{
    srand(time(NULL));
    flagDraw = true;


    flagFish = false;
    moveFishX =  1; // X kinoumenou = 10 pixels
    moveFishY = rand()%(48); // random 0-48
    moveFishY =  moveFishY * 10 + 310; // ton random ton kanoume se pixels *10 + 310 xondrika gia na mhn pesoume sta grammata

    flagFish1 = false;
    moveFishX1 = 750;
    moveFishY1 = rand()%(48); // random 0-48
    moveFishY1 =  moveFishY1 * 10 + 310; // ton random ton kanoume se pixels *10 + 310 xondrika gia na mhn pesoume sta grammata
    //moveFish2Y = 10;

	message = NULL;
    movedFish = NULL;
    movedFish = Sprite::Load("img/Goldfish.png");
    movedFish1 = NULL;
    movedFish1 = Sprite::Load("img/Goldfish1.png");
    menuSpriteFix = NULL;
    menuSpriteFix = Sprite::Load("img/seaFix.png");
    menuSprite = NULL;
    menuSprite = Sprite::Load("img/sea.jpg");

    TTF_Init();
    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

	printf("MenuState Init Successful\n");
}

void MenuState::Clean()
{
    SDL_FreeSurface( message );
    SDL_FreeSurface( menuSprite );
    SDL_FreeSurface( movedFish );
    SDL_FreeSurface( movedFish1 );
    SDL_FreeSurface( menuSpriteFix );

    TTF_CloseFont( font );

    printf("MenuState Clean Successful\n");
}

void MenuState::Pause()
{
	printf("MenuState Paused\n");
}

void MenuState::Resume()
{
	printf("MenuState Resumed\n");
}

void MenuState::HandleEvents(Game* game, organism *world[map_size][map_size])
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				    case SDLK_ESCAPE:
                        game->Quit();
                        break;

                    case SDLK_SPACE:
                        game->PushState(PlayState::Instance(), game);
                        break;
                }
                break;
		}
	}
}

void MenuState::Update(Game* game)
{
}

void MenuState::Draw(Game* game, int worldGraph[map_size][map_size])
{

    //to font olo na mpei sto background edited
    if(flagDraw)
    {
        Sprite::Draw(game->GetScreen(), menuSprite, 0, 0);
        message = TTF_RenderText_Solid( font, "Press Space to Start, Pause and Resume." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 10);
        message = TTF_RenderText_Solid( font, "Press R to Restart simulation." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 35);
        message = TTF_RenderText_Solid( font, "Press G to get General Information about the organisms." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 60);
        message = TTF_RenderText_Solid( font, "By clicking on a fish, you see its statistics." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 85);
        message = TTF_RenderText_Solid( font, "By clicking in the sea, you can add a new fish." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 110);
        message = TTF_RenderText_Solid( font, "Press P to add Polution." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 135);
        message = TTF_RenderText_Solid( font, "Press N to add Nets." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 160);
        message = TTF_RenderText_Solid( font, "Press H to see additional help about the simulation." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 185);
        message = TTF_RenderText_Solid( font, "You can change the speed of the simulation by pressing up to increase or" , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 210);
        message = TTF_RenderText_Solid( font, " down to decrease it. Every change is 0.25 sec. Default time is 1 day per " , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 235);
        message = TTF_RenderText_Solid( font, " 0.75 sec (750 msec)." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 260);
        message = TTF_RenderText_Solid( font, "Press Esc or (X) to exit / finish simulation." , textColor );
        Sprite::Draw( game->GetScreen(), message, 10, 285);
        SDL_Flip(game->GetScreen());
    }
    flagDraw = false;

    Sprite::Draw(game->GetScreen(), menuSpriteFix, 0, 0);
    Sprite::Draw( game->GetScreen(), movedFish, moveFishX, moveFishY);
    Sprite::Draw( game->GetScreen(), movedFish1, moveFishX1, moveFishY1);
    //Sprite::Draw( game->GetScreen(), movedFish2, moveFish2X, moveFish2Y);

    //ftia3imo constructor gia to goldfish???

    SDL_Delay(25);
    if (!flagFish) moveFishX += 2;
    if (flagFish) moveFishX -= 2;
    if ((moveFishX == 740) || (moveFishX == 741))
    {
        flagFish = true;
        movedFish = Sprite::Load("img/Goldfish1.png");
    }
    if ((moveFishX == 1) || (moveFishX == 2))
    {
        flagFish = false;
        movedFish = Sprite::Load("img/Goldfish.png");
    }
    if (flagFish1) moveFishX1 += 3;
    if (!flagFish1) moveFishX1 -= 3;
    if ((moveFishX1 == 740) || (moveFishX1 == 741) || (moveFishX1 == 742) )
    {
        flagFish1 = false;
        movedFish1 = Sprite::Load("img/Goldfish1.png");
    }
    if ((moveFishX1 == 1) || (moveFishX1 == 2) || (moveFishX1 == 3))
    {
        flagFish1 = true;
        movedFish1 = Sprite::Load("img/Goldfish.png");
    }

    SDL_Flip(game->GetScreen());
}


#endif

