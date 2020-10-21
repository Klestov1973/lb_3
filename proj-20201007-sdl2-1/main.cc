/*
 * main.cc
 *
 *  Created on: 7 окт. 2020 г.
 *      Author: unyuu
 */


#include <iostream>
#include <memory>
#include <cmath>


#include <SDL2/SDL.h>

constexpr double Pi = acos(-1.);

#ifdef _WIN32
# include <SDL2/SDL_main.h>
#endif

constexpr int WIDTH = 800, HEIGHT = 600;

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Cicle",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "При создании окна произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;

	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(ren.get(), 0, 48, 64, 255);
		SDL_RenderClear(ren.get());


		SDL_SetRenderDrawColor(ren.get(), 255, 255, 255, 255);

		int centreX=300;
		int centreY=400;
		int radius = 100;
		const int diameter = (radius * 2);

		int x = (radius - 1);
		int y = 0;
		int tx = 1;
		int ty = 1;
		int error = (tx - diameter);

		while (x >= y)
		{
		SDL_RenderDrawPoint(ren.get(), centreX + x, centreY - y);
		SDL_RenderDrawPoint(ren.get(), centreX + x, centreY + y);
		SDL_RenderDrawPoint(ren.get(), centreX - x, centreY - y);
		SDL_RenderDrawPoint(ren.get(), centreX - x, centreY + y);
		SDL_RenderDrawPoint(ren.get(), centreX + y, centreY - x);
		SDL_RenderDrawPoint(ren.get(), centreX + y, centreY + x);
		SDL_RenderDrawPoint(ren.get(), centreX - y, centreY - x);
		SDL_RenderDrawPoint(ren.get(), centreX - y, centreY + x);

		if (error <= 0)
		{
		++y;
		error += ty;
		ty += 2;
		}

		if (error > 0)
		{
		--x;
		tx += 2;
		error += (tx - diameter);
		}
		}



			}
		SDL_RenderPresent(ren.get());



	return 0;
	}

