#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1280

typedef struct {
    double x;
    double y;
} Vec2;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        return 1;
    }

    if (Mix_Init(MIX_INIT_OGG) == 0) {
        fprintf(stderr, "Mix_Init failed: %s\n", Mix_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(
        "Moving Cube Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);

    Mix_Chunk* moveSound = Mix_LoadWAV("./assets/sounds/helicopter.wav");
    if (!moveSound) {
        fprintf(stderr, "Mix_LoadWAV failed: %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music* backgroudMusic = Mix_LoadMUS("./assets/sounds/music.wav");
    if (!backgroudMusic) {
        fprintf(stderr, "Mix_LoadMUS failed: %s\n", Mix_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("./assets/fonts/arial.ttf", 18);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont failed: %s\n", TTF_GetError());
        return 1;
    }

    Vec2 p = { 10.0, 20.0 };
    Vec2 p1 = { 100.0, 20.0 };

    SDL_Event event;

    int quit = 0;
    long double dt;
    long double millisecsPreviousFrame = 0.0;

    int frames = 0;
    int fps = 0;

    Mix_PlayMusic(backgroudMusic, -1);
    Mix_VolumeMusic(5);
    Mix_Volume(-1, 5);
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    Uint32 prevTicks = SDL_GetTicks64();
    while (!quit) {
        // Calculate FPS
        Uint32 currentTicks = SDL_GetTicks64();
        Uint32 frameTime = currentTicks - prevTicks;
        if (frameTime >= 1000) {
            fps = frames;
            frames = 0;
            prevTicks = currentTicks;
        }
        frames++;

        dt = currentTicks - millisecsPreviousFrame;
        millisecsPreviousFrame = currentTicks;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }

        if (keyboardState[SDL_SCANCODE_W]) {
            p1.y -= dt / 3;
            Mix_PlayChannel(-1, moveSound, 0);
        }
        if (keyboardState[SDL_SCANCODE_S]) {
            p1.y += dt / 3;
            Mix_PlayChannel(-1, moveSound, 0);
        }
        if (keyboardState[SDL_SCANCODE_A]) {
            p1.x -= dt / 3;
            Mix_PlayChannel(-1, moveSound, 0);
        }
        if (keyboardState[SDL_SCANCODE_D]) {
            p1.x += dt / 3;
            Mix_PlayChannel(-1, moveSound, 0);
        }

        SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
        SDL_RenderClear(renderer);

        // Draw FPS text
        SDL_Color textColor = { 0, 255, 0, 255 };
        char fpsText[20];
        snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, fpsText, textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = { 10, 10, textSurface->w, textSurface->h };

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);

        // Draw a PNG texture
        SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface);

        p.x += dt / 3;
        p.y += dt / 3;

        if (p.x > SCREEN_WIDTH) {
            p.x = 0;
        }
        if (p.y > SCREEN_HEIGHT) {
            p.y = 0;
        }
        if (p1.x > SCREEN_WIDTH) {
            p1.x = 0;
        }
        if (p1.x < 0) {
            p1.x = SCREEN_WIDTH;
        }
        if (p1.y > SCREEN_HEIGHT) {
            p1.y = 0;
        }
        if (p1.y < 0) {
            p1.y = SCREEN_HEIGHT;
        }

        SDL_Rect dstRect = {
            (int)p.x,
            (int)p.y,
            32, 32
        };

        SDL_Rect dstRect1 = {
            (int)p1.x,
            (int)p1.y,
            32, 32
        };

        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_RenderCopy(renderer, texture, NULL, &dstRect1);
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(texture1);
        SDL_FreeSurface(surface);

        SDL_RenderPresent(renderer);
    }

    Mix_FreeChunk(moveSound);
    Mix_FreeMusic(backgroudMusic);
    Mix_CloseAudio();
    Mix_Quit();

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
