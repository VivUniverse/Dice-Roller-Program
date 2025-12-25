#include <iostream>
#include <random>
#include <chrono>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <string>
#include <SDL3_image/SDL_image.h>
#include <algorithm>


std::vector<SDL_Texture*> diceTexture;
int total = 0;
int enemyTotal = 0;

class ScoreGraphics {
private:
	SDL_Texture* scoreBoredTexture;
	SDL_FRect rect;
public:

	// Methods
	void displayScoreBoard(SDL_Renderer* renderer, float scale) {
		scoreBoredTexture = IMG_LoadTexture(
			renderer, "ScoreBoard/ScoreBoard4.png"
		);

		float tw, th;
		SDL_GetTextureSize(scoreBoredTexture, &tw, &th);

		rect.x = -80;
		rect.y = 100;
		rect.w = tw * scale;
		rect.h = th * scale;

		SDL_RenderTexture(renderer, scoreBoredTexture,
			nullptr, &rect);

		SDL_DestroyTexture(scoreBoredTexture);
	}
};

class Random {
protected:
	int rolling = 0;
	int enemyRolling = 0;
	SDL_FRect playerScoreRect;
	SDL_FRect enemyScoreRect;
public:

	// Methods
	void roll(const SDL_Event& event, SDL_Renderer* renderer,
		float scale, TTF_Font* font) {
		unsigned playerSeed = std::chrono::steady_clock::now()
			.time_since_epoch().count();
		unsigned enemySeed = std::chrono::steady_clock::now()
			.time_since_epoch().count();

		SDL_Keycode key = event.key.key;
		if (event.type == SDL_EVENT_KEY_DOWN) {
			switch (key) {
			case SDLK_RETURN:
				std::mt19937 playerEngine(playerSeed);
				std::uniform_int_distribution<> playerDist(1, 6);
				rolling = playerDist(playerEngine);

				std::cout << "--------------------\n";
				std::cout << "--- Rolls ---\n\n";

				std::cout << "You rolled: "
					<< rolling << "\n\n";

				std::mt19937 enemyEngine(enemySeed);
				std::uniform_int_distribution<> enemyDist(1, 6);
				enemyRolling = enemyDist(enemyEngine);


				std::cout << "Enemy rolled: "
					<< enemyRolling << "\n\n";

				std::cout << "--------------------\n\n";

				std::cout << "--------------------\n";
				std::cout << "--- Total ---\n\n";

				total += rolling;
				enemyTotal += enemyRolling;

				std::cout << "Player Total: "
					<< total << "\n\n";

				std::cout << "Enemy Total: "
					<< enemyTotal << "\n\n";
				std::cout << "--------------------\n";
				break;
			}
		}
	}

	void displayPlayerToalOnWindow(SDL_Renderer* renderer, TTF_Font* font,
		float scale) {

		std::string playerTextTotal = std::to_string(total);

		SDL_Color color = { 0,0,0,255 };
		SDL_Surface* playerScoreTextSurface = TTF_RenderText_Blended(
			font, playerTextTotal.c_str(), 0, color
		);

		if (playerScoreTextSurface) {
			SDL_Texture* playerScoreTextTexture =
				SDL_CreateTextureFromSurface(
					renderer, playerScoreTextSurface
				);

			float tw, th;
			SDL_GetTextureSize(
				playerScoreTextTexture, &tw, &th
			);

			playerScoreRect.x = 350;
			playerScoreRect.y = 550;
			playerScoreRect.w = tw * scale;
			playerScoreRect.h = th * scale;

			SDL_RenderTexture(renderer, playerScoreTextTexture,
				nullptr, &playerScoreRect);

			SDL_DestroyTexture(playerScoreTextTexture);
		}
		SDL_DestroySurface(playerScoreTextSurface);
	}

	void displayEnemyToalOnWindow(SDL_Renderer* renderer, TTF_Font* font,
		float scale) {

		std::string enemyTextTotal = std::to_string(enemyTotal);

		SDL_Color color = { 0,0,0,255 };
		SDL_Surface* enemyScoreTextSurface = TTF_RenderText_Blended(
			font, enemyTextTotal.c_str(), 0, color
		);

		if (enemyScoreTextSurface) {
			SDL_Texture* enemyScoreTextTexture =
				SDL_CreateTextureFromSurface(
					renderer, enemyScoreTextSurface
				);

			float tw, th;
			SDL_GetTextureSize(
				enemyScoreTextTexture, &tw, &th
			);

			enemyScoreRect.x = 550;
			enemyScoreRect.y = 550;
			enemyScoreRect.w = tw * scale;
			enemyScoreRect.h = th * scale;

			SDL_RenderTexture(renderer, enemyScoreTextTexture,
				nullptr, &enemyScoreRect);

			SDL_DestroyTexture(enemyScoreTextTexture);
		}
		SDL_DestroySurface(enemyScoreTextSurface);
	}
};

class Dice : public Random {
private:
	SDL_FRect rect;
public:

	// Constructor
	Dice(SDL_Renderer* renderer) {
		for (int i = 0; i <= 6; i++) {

			std::string path = "Dice/Dice" + std::to_string(i) + ".png";
			std::cout << "File path: " << path << std::endl;

			SDL_Texture* texture = IMG_LoadTexture(
				renderer, path.c_str()
			);
			diceTexture.push_back(texture);
		}
	}

	// Destructor
	~Dice() {
		std::cout << "Destructor Activated\n";

		for (int i = 0; i < diceTexture.size(); i++) {
			SDL_DestroyTexture(diceTexture[i]);
		}
	}

	// Methods
	void displayPlayerDice(SDL_Renderer* renderer, float scale) {

		for (int i = 0; i < diceTexture.size(); i++) {
			float tw, th;
			SDL_GetTextureSize(diceTexture[i], &tw, &th);

			rect.x = 80;
			rect.y = 400;
			rect.w = tw * scale;
			rect.h = th * scale;

			if (rolling == 1) {
				SDL_RenderTexture(renderer, diceTexture[1],
					nullptr, &rect);
			}
			else if (rolling == 2) {
				SDL_RenderTexture(renderer, diceTexture[2],
					nullptr, &rect);
			}
			else if (rolling == 3) {
				SDL_RenderTexture(renderer, diceTexture[3],
					nullptr, &rect);
			}
			else if (rolling == 4) {
				SDL_RenderTexture(renderer, diceTexture[4],
					nullptr, &rect);
			}
			else if (rolling == 5) {
				SDL_RenderTexture(renderer, diceTexture[5],
					nullptr, &rect);
			}
			else if (rolling == 6) {
				SDL_RenderTexture(renderer, diceTexture[6],
					nullptr, &rect);
			}
		}
	}

	void displayEnemyDice(SDL_Renderer* renderer, float scale) {

		for (int i = 0; i < diceTexture.size(); i++) {
			float tw, th;
			SDL_GetTextureSize(diceTexture[i], &tw, &th);

			rect.x = 700;
			rect.y = 400;
			rect.w = tw * scale;
			rect.h = th * scale;

			if (enemyRolling == 1) {
				SDL_RenderTexture(renderer, diceTexture[1],
					nullptr, &rect);
			}
			else if (enemyRolling == 2) {
				SDL_RenderTexture(renderer, diceTexture[2],
					nullptr, &rect);
			}
			else if (enemyRolling == 3) {
				SDL_RenderTexture(renderer, diceTexture[3],
					nullptr, &rect);
			}
			else if (enemyRolling == 4) {
				SDL_RenderTexture(renderer, diceTexture[4],
					nullptr, &rect);
			}
			else if (enemyRolling == 5) {
				SDL_RenderTexture(renderer, diceTexture[5],
					nullptr, &rect);
			}
			else if (enemyRolling == 6) {
				SDL_RenderTexture(renderer, diceTexture[6],
					nullptr, &rect);
			}
		}
	}
};


int main(int argc, char* argv[]) {
	// Initilize
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init Error: "
			<< SDL_GetError() << std::endl;
		return 1;
	}

	if (!TTF_Init()) {
		std::cerr << "TTF_Init Error: "
			<< SDL_GetError() << std::endl;
		return 1;
	}

	// Game Varibles
	int WIDTH = 1000;
	int HEIGHT = 800;

	// Load Fonts
	TTF_Font* font = TTF_OpenFont(
		"Fonts/OpenSans-Italic.ttf", 24
	);

	if (!font) {
		std::cerr << "Loading Font Error: "
			<< SDL_GetError() << std::endl;
		return 1;
	}

	// Create Window And Renderer
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_CreateWindowAndRenderer(
		"Dice Roller Program",
		WIDTH, HEIGHT,
		SDL_WINDOW_RESIZABLE,
		&window, &renderer
	);

	if (!window || !renderer) {
		std::cerr
			<< "SDL_CreateWindowAndRenderer Error: "
			<< SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create Objects
	Dice dice(renderer);
	ScoreGraphics sg;
	Random random;

	// Main Loop
	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		// Event Loop
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				isRunning = false;
			}

			dice.roll(event, renderer, 0.8, font);
		}
		// Fill Screen
		SDL_SetRenderDrawColor(
			renderer, 246, 206, 252, 255
		);
		SDL_RenderClear(renderer);

		// Graphics
		sg.displayScoreBoard(renderer, 0.6);
		dice.displayPlayerDice(renderer, 0.1);
		dice.displayEnemyDice(renderer, 0.1);
		random.displayPlayerToalOnWindow(renderer, font, 2);
		random.displayEnemyToalOnWindow(renderer, font, 2);

		// Present Renderer
		SDL_RenderPresent(renderer);

		// FPS
		SDL_Delay(16);
	}
	// Clean Up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}