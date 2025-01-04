#include <stdio.h>
#include <SDL2/SDL.h>
#define WIDTH 900
#define HEIGHT 600

int main(int argc, char** argv){
    // Initializes the SDL library
    SDL_Init(SDL_INIT_VIDEO);
    // Creates a window, as in a pop up GUI
    SDL_Window *window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    // Pauses the program for 5000ms, often used to control frame rates
    SDL_Delay(5000);

    return 0;
}