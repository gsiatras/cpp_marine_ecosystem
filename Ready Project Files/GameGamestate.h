#ifndef  _GAMEGAMESTATE_H
#define _GAMEGAMESTATE_H
#include <vector>

#include "organism.h"
#include "plangkton.h"
#include "nonplanktonic.h"

class GameState;

class Game
{
	public:
        SDL_Surface* GetScreen() {return m_pScreen;}

		Game();

		void Init(const char* title, int width, int height, int bpp, bool fullscreen);

		void ChangeState(GameState* state);
		void PushState(GameState* state, Game* game);
		void PopState(Game* game);

		void HandleEvents(organism *world[map_size][map_size]);

		void Update();
		void generalinfoGraph(Game* game);

		void Draw( int worldGraph[map_size][map_size] );

		void Clean();

        bool getPause() { return m_pause; }
        void setPause( bool m_pause ) { this->m_pause = m_pause; }
        bool getRender() { return m_therender; }
        void setRender(bool m_therender) { this-> m_therender = m_therender;}

		bool Running() { return m_bRunning; }
		void Quit() { m_bRunning = false; }

	private:
		// the stack of states
		std::vector<GameState*> states;

		SDL_Surface* m_pScreen;

        bool pause;
        bool m_pause;
        bool m_therender;
		bool m_bFullscreen;
		bool m_bRunning;
};

void printInfoGraph(int xClicked, int yClicked, organism* world[map_size][map_size], Game* game, SDL_Surface* message0) //check gia ta floats
{

}

//****************************************************************************************
//********************************* GAME STATE *******************************************
class GameState
{
    public:
		virtual void Init() = 0;
		virtual void Clean() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(Game* game, organism *world[map_size][map_size]) = 0;
		virtual void Update(Game* game) = 0;
		virtual void Draw(Game* game, int worldGraph[map_size][map_size]) = 0;

		void ChangeState(Game* game, GameState* state)
		{
		    game->ChangeState(state);
		}

	protected:
		GameState() {}
};

Game::Game()
{
    setPause(true);
    setRender(true);
}

void Game::Init(const char* title, int width, int height, int bpp, bool fullscreen)
{
	int flags = 0;




	SDL_Init(SDL_INIT_EVERYTHING);
    SDL_EnableUNICODE( SDL_ENABLE );
    TTF_Init();

	SDL_WM_SetCaption(title, title);

	if ( fullscreen ) {	flags = SDL_FULLSCREEN; }

	m_pScreen = SDL_SetVideoMode(width, height, bpp, flags);
	m_bFullscreen = fullscreen;
	m_bRunning = true;

	printf("Game Initialised Succesfully\n");
}

void Game::ChangeState(GameState* state)
{
	// cleanup the current state
	if ( !states.empty() )
	{
		states.back()->Clean();
		states.pop_back();
	}
    setRender(true);
	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void Game::PushState(GameState* state, Game* game)
{
	// pause current state
	if ( !states.empty() ) states.back()->Pause();
    setRender(true);
	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void Game::PopState(Game* game)
{
	// cleanup the current state
	if ( !states.empty() )
	{
		states.back()->Clean();
		states.pop_back();
	}
	setRender(true);
    //game->setRender(true);
	// resume previous state
	if ( !states.empty() ) states.back()->Resume();
}

void Game::HandleEvents(organism *world[map_size][map_size])
{
	// let the state handle events
	states.back()->HandleEvents(this, world);
}

void Game::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void Game::Draw( int worldGraph[map_size][map_size] )
{
	// let the state draw the screen
	states.back()->Draw(this, worldGraph );
	//SDL_Flip(m_pScreen);
}

void Game::Clean()
{
	while ( !states.empty() )
	{
		states.back()->Clean();
		states.pop_back();
	}
}

#endif
