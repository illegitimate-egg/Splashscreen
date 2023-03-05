#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

const int SCREEN_WIDTH = 412;
const int SCREEN_HEIGHT = 468;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[\x1B[31mSDL ERROR\x1B[0m] | SDL couldn't initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        printf("[\x1B[36mINFO\x1B[0m]      | SDL Initialized\n");
        image = SDL_LoadBMP("Frame 1.bmp");

        SDL_Rect display_bounds;
        if(SDL_GetDisplayUsableBounds(0, &display_bounds) < 0) {
           printf("[\x1B[31mSDL ERROR\x1B[0m] | Failed to get display bounds! SDL Error: %s\n", SDL_GetError());
        }

        int center_x = display_bounds.x + display_bounds.w / 2;
        int center_y = display_bounds.y + display_bounds.h / 2;

        window = SDL_CreateWindow("Splashscreen", center_x - (SCREEN_WIDTH / 2), center_y - (SCREEN_HEIGHT / 2), SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_SKIP_TASKBAR);
        if(window == NULL) {
            printf("[\x1B[31mSDL ERROR\x1B[0m] | Window could not be created! SDL Error: %s\n", SDL_GetError());
        } else {
            printf("[\x1B[36mINFO\x1B[0m]      | Window Created\n");
            renderer = SDL_CreateRenderer(window, -1, 0);
            texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_UpdateWindowSurface(window);

            int target = (int)time(NULL) + 5;

            SDL_Event e;
            bool quit = false;
            while(quit == false) {
                while(SDL_PollEvent(&e)) {
                    if(e.type == SDL_QUIT) {
                        printf("[\x1B[36mINFO\x1B[0m]      | External Interrupt Recieved\n");
                        quit = true;
                    }
                }
                if((int)time(NULL) >= target) {
                    quit = true;
                }
            }

            SDL_DestroyTexture(texture);
            SDL_FreeSurface(image);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }
}