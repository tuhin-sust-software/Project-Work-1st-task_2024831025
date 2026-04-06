#include <SDL3/SDL.h>
#include <stdbool.h>

void DrawCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius * 2);

    while (x >= y) {
        SDL_RenderPoint(renderer, cx + x, cy + y);
        SDL_RenderPoint(renderer, cx + y, cy + x);
        SDL_RenderPoint(renderer, cx - y, cy + x);
        SDL_RenderPoint(renderer, cx - x, cy + y);
        SDL_RenderPoint(renderer, cx - x, cy - y);
        SDL_RenderPoint(renderer, cx - y, cy - x);
        SDL_RenderPoint(renderer, cx + y, cy - x);
        SDL_RenderPoint(renderer, cx + x, cy - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius * 2);
        }
    }
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return 1;
    }

    int windowWidth = 800;
    int windowHeight = 600;
    SDL_Window *window = SDL_CreateWindow("Task 102 - Expanding Circle", windowWidth, windowHeight, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    bool running = true;
    SDL_Event event;

    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;
    
    // Initial Radius সেট 
    int initialRadius = 20;
    int currentRadius = initialRadius;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // সময়ের সাথে সাথে radius বৃদ্ধি করা
        currentRadius += 2; 

        // Boundary Collision Check: বৃত্ত উইন্ডোর বর্ডারে পৌঁছালে reset হবে
        if ((centerX - currentRadius <= 0) || (centerX + currentRadius >= windowWidth) ||
            (centerY - currentRadius <= 0) || (centerY + currentRadius >= windowHeight)) {
            currentRadius = initialRadius; 
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); 
        DrawCircle(renderer, centerX, centerY, currentRadius);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
