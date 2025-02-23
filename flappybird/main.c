#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PIPE_WIDTH 50
#define PIPE_GAP 150
#define PIPE_SPEED 2
#define JUMP_SPEED 12
#define GRAVITY 1

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
SDL_Texture* gScoreTexture = NULL;

typedef struct {
    SDL_Rect rect;
    int yVelocity;
} Player;

typedef struct {
    SDL_Rect rect;
    bool scored;
} Pipe;

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    return !(a.y + a.h <= b.y || a.y >= b.y + b.h || a.x + a.w <= b.x || a.x >= b.x + b.w);
}

Player createPlayer() {
    Player player = {{SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 50, 50}, 0};
    return player;
}

void createPipe(Pipe* topPipe, Pipe* bottomPipe, int x, int gapY) {
    topPipe->rect = (SDL_Rect){x, 0, PIPE_WIDTH, gapY};
    topPipe->scored = false;
    bottomPipe->rect = (SDL_Rect){x, gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - (gapY + PIPE_GAP)};
    bottomPipe->scored = false;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    gWindow = SDL_CreateWindow("Flappy Bird Clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) return false;
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) return false;
    if (TTF_Init() == -1) return false;
    gFont = TTF_OpenFont("arial.ttf", 28);
    return gFont != NULL;
}

void closeGame() {
    SDL_DestroyTexture(gScoreTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_Quit();
    SDL_Quit();
}

void renderScore(int score) {
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, scoreText, textColor);
    if (!textSurface) return;
    gScoreTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    SDL_FreeSurface(textSurface);
}

void renderTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect renderRect = {x, y, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &renderRect.w, &renderRect.h);
    SDL_RenderCopy(gRenderer, texture, NULL, &renderRect);
}

int main() {
    srand(time(NULL));
    if (!init()) return 1;

    bool quit = false;
    while (!quit) {
        Player player = createPlayer();
        Pipe pipe1, pipe2;
        createPipe(&pipe1, &pipe2, SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - PIPE_GAP));
        int score = 0;
        bool gameOver = false;

        while (!quit && !gameOver) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) quit = true;
                else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_SPACE) player.yVelocity = -JUMP_SPEED;
                    if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;
                }
            }

            player.rect.y += player.yVelocity;
            player.yVelocity += GRAVITY;
            pipe1.rect.x -= PIPE_SPEED;
            pipe2.rect.x -= PIPE_SPEED;

            if (checkCollision(player.rect, pipe1.rect) || checkCollision(player.rect, pipe2.rect) || player.rect.y + player.rect.h > SCREEN_HEIGHT) {
                printf("Game over! Score: %d\n", score);
                gameOver = true;
            }

            if (!pipe1.scored && pipe1.rect.x + pipe1.rect.w < player.rect.x) {
                pipe1.scored = true;
                score++;
                renderScore(score);
            }
            if (!pipe2.scored && pipe2.rect.x + pipe2.rect.w < player.rect.x) {
                pipe2.scored = true;
                score++;
                renderScore(score);
            }

            if (pipe1.rect.x + pipe1.rect.w < 0) createPipe(&pipe1, &pipe2, SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - PIPE_GAP));

            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            SDL_RenderFillRect(gRenderer, &player.rect);
            SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
            SDL_RenderFillRect(gRenderer, &pipe1.rect);
            SDL_RenderFillRect(gRenderer, &pipe2.rect);
            renderTexture(gScoreTexture, SCREEN_WIDTH / 2 - 50, 10);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(16);
        }
    }

    closeGame();
    return 0;
}

