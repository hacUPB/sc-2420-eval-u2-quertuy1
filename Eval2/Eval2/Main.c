#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define BALL_SIZE 20
#define BALL_SPEED 5

#define PLATFORM_WIDTH 100
#define PLATFORM_HEIGHT 20
#define PLATFORM_SPEED 2 // Velocidad a la que suben las plataformas

#define GRAVITY 0.1f
#define MAX_FALL_SPEED 5.0f

#define PLATFORM_GENERATION_INTERVAL 1000 // Intervalo de generación de plataformas en milisegundos

typedef struct Platform {
    SDL_Rect rect;
    bool active;
} Platform;

// Función para inicializar SDL
bool init(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("No se pudo inicializar SDL. Error: %s", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Rapid Roll",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (*window == NULL) {
        SDL_Log("No se pudo crear la ventana. Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        SDL_Log("No se pudo crear el renderer. Error: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}

// Función para crear una nueva plataforma
void createPlatform(Platform* platform) {
    platform->rect.w = PLATFORM_WIDTH;
    platform->rect.h = PLATFORM_HEIGHT;
    platform->rect.x = rand() % (WINDOW_WIDTH - PLATFORM_WIDTH);
    platform->rect.y = WINDOW_HEIGHT; // Aparecerá en la parte inferior de la pantalla
    platform->active = true;
}

// Función para dibujar plataformas
void drawPlatforms(SDL_Renderer* renderer, Platform platforms[], int numPlatforms) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
    for (int i = 0; i < numPlatforms; ++i) {
        if (platforms[i].active) {
            SDL_RenderFillRect(renderer, &platforms[i].rect);
        }
    }
}

// Función para actualizar las plataformas
void updatePlatforms(Platform platforms[], int numPlatforms) {
    // Mover las plataformas hacia arriba
    for (int i = 0; i < numPlatforms; ++i) {
        if (platforms[i].active) {
            platforms[i].rect.y -= PLATFORM_SPEED; // Mover hacia arriba

            // Si la plataforma ha pasado el borde superior, desactivarla
            if (platforms[i].rect.y + PLATFORM_HEIGHT < 0) {
                platforms[i].active = false;
            }
        }
    }
}

// Función principal del juego
int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    Platform platforms[100]; // Número inicial de plataformas, puede ser cualquier valor
    int ballX = WINDOW_WIDTH / 2;
    int ballY = WINDOW_HEIGHT / 2;
    float ballVelX = BALL_SPEED;
    float ballVelY = 0;
    float ballDirX = 0;
    bool running = true;
    bool onPlatform = false;
    int score = 0;
    int numPlatforms = 0;

    // Temporizador para la generación de plataformas
    Uint32 lastPlatformGenerationTime = 0;
    Uint32 currentTime = 0;

    if (!init(&window, &renderer)) {
        return -1;
    }

    // Inicializar las plataformas
    for (int i = 0; i < 100; ++i) { // Asegúrate de que la cantidad inicial sea suficiente
        platforms[i].active = false;
    }

    // Generar las plataformas iniciales
    for (int i = 0; i < 2; ++i) {
        createPlatform(&platforms[numPlatforms++]);
    }

    while (running) {
        currentTime = SDL_GetTicks(); // Obtener el tiempo actual

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    ballDirX = -1;
                    break;
                case SDLK_RIGHT:
                    ballDirX = 1;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                    ballDirX = 0;
                }
            }
        }

        // Mover la bola horizontalmente
        ballX += ballDirX * BALL_SPEED;

        // Verificar colisiones con los bordes de la ventana
        if (ballX < 0) ballX = 0;
        if (ballX > WINDOW_WIDTH - BALL_SIZE) ballX = WINDOW_WIDTH - BALL_SIZE;

        // Movimiento vertical
        ballVelY += GRAVITY;
        if (ballVelY > MAX_FALL_SPEED) {
            ballVelY = MAX_FALL_SPEED;
        }
        ballY += (int)ballVelY;

        // Actualizar plataformas
        updatePlatforms(platforms, numPlatforms);

        // Generar nuevas plataformas basadas en el tiempo
        if (currentTime - lastPlatformGenerationTime >= PLATFORM_GENERATION_INTERVAL) {
            // Crear una nueva plataforma y agregarla al arreglo
            createPlatform(&platforms[numPlatforms]);
            numPlatforms++; // Incrementar el número de plataformas
            lastPlatformGenerationTime = currentTime; // Actualizar el tiempo de generación
        }

        // Colisiones con las plataformas
        onPlatform = false;
        for (int i = 0; i < numPlatforms; ++i) {
            if (platforms[i].active) {
                if (ballX + BALL_SIZE > platforms[i].rect.x &&
                    ballX < platforms[i].rect.x + PLATFORM_WIDTH &&
                    ballY + BALL_SIZE > platforms[i].rect.y &&
                    ballY + BALL_SIZE < platforms[i].rect.y + PLATFORM_HEIGHT) {
                    ballY = platforms[i].rect.y - BALL_SIZE;
                    ballVelY = 0;
                    onPlatform = true;
                    score++;
                }
            }
        }

        if (!onPlatform && ballY > WINDOW_HEIGHT) {
            // La bola cayó al vacío
            running = false;
        }

        // Limpiar pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
        SDL_RenderClear(renderer);

        // Dibujar la bola
        SDL_Rect ballRect = { ballX, ballY, BALL_SIZE, BALL_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
        SDL_RenderFillRect(renderer, &ballRect);

        // Dibujar las plataformas
        drawPlatforms(renderer, platforms, numPlatforms);

        // Mostrar el renderer
        SDL_RenderPresent(renderer);

        // Controlar la velocidad del juego
        SDL_Delay(16); // Aproximadamente 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Juego terminado. Puntaje final: %d\n", score);

    return 0;
}
