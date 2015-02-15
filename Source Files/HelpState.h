#ifndef  _HELPSTATE_H
#define _HELPSTATE_H

#include "GameGamestate.h"
#include "Ssprite.h"

class HelpState : public GameState
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
		static HelpState* Instance()
		{
			return &m_HelpState;
		}

	protected:
		HelpState() {}

	private:
		static HelpState m_HelpState;

		SDL_Surface* helpSprite;
        SDL_Surface* message;
        TTF_Font *font;
        bool flag2;
        SDL_Color textColor;
};

HelpState HelpState::m_HelpState;

void HelpState::Init()
{
	helpSprite = NULL;
	helpSprite = Sprite::Load("img/GeneralInfoState.png");
	message = NULL;

    textColor = { 255, 255, 255 };
    flag2 = true;
	TTF_Init();
    font = TTF_OpenFont( "ttf/comic.ttf", 22 );

	printf("HelpState Init Successful\n");
}

void HelpState::Clean()
{
    SDL_FreeSurface( message );
    SDL_FreeSurface( helpSprite );
    TTF_CloseFont( font );

    printf("HelpState Clean Successful\n");
}

void HelpState::Pause()
{
	printf("HelpState Paused\n");
}

void HelpState::Resume()
{
	printf("HelpState Resumed\n");
}

void HelpState::HandleEvents(Game* game, organism *world[map_size][map_size])
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

void HelpState::Update(Game* game)
{
}

void HelpState::Draw(Game* game, int worldGraph[map_size][map_size])
{
    Sprite::Draw(game->GetScreen(), helpSprite, 0, 0);
    message = TTF_RenderText_Solid( font, "If you press Space, you Start, Pause and Resume the simulation." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 10);
    message = TTF_RenderText_Solid( font, "If you press R you Restart it." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 32);
    message = TTF_RenderText_Solid( font, "If you press G you get General Information about it." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 54);
    message = TTF_RenderText_Solid( font, "By clicking on a fish, you see its statistics (age, size, growth rate..." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 76);
    message = TTF_RenderText_Solid( font, "By clicking in the sea, you can add a new fish and you give the age," , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 98);
    message = TTF_RenderText_Solid( font, " size and growth rate you want." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 120);
    message = TTF_RenderText_Solid( font, "If you press P you can add Polution to the sea." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 142);
    message = TTF_RenderText_Solid( font, "If you press N you can add Nets to the sea." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 164);
    message = TTF_RenderText_Solid( font, "You can change the speed of the simulation. If you press up you increase it" , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 186);
    message = TTF_RenderText_Solid( font, " by 0.2 sec. If you press down you decrease it by 0.2 sec.  " , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 208);
    message = TTF_RenderText_Solid( font, "Wherever you see 'week' means 7 days. It depends the time you have " , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 230);
    message = TTF_RenderText_Solid( font, " chosen for the simulation. The default time for it is 1 day per 0.8 sec." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 252);
    message = TTF_RenderText_Solid( font, "If you press Esc or (X) you can exit / finish the simulation." , textColor );
    Sprite::Draw( game->GetScreen(), message, 5, 274);

    SDL_Flip(game->GetScreen());

    game->setRender( false ); //ola na ginoun mia fora

}

#endif

