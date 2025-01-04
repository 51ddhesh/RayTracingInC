#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff

struct Circle{
    double x; // x coordinate of circle
    double y; // y coordinate of circle
    double r; // radius of circle
};

/*
*   in fillCircle(*args),
*   Each individual pixel that lies inside the given radius, is filled with
*   colour: Uint32
*   SDL2 does not have an implementation of a circle and it is implemented
*   explicitly by the user inform of filling each individual pixel
*/
void fillCircle(SDL_Surface *surface, struct Circle circle, Uint32 colour){
    double radius_squared = pow(circle.r, 2);
    for(double x = circle.x - circle.r; x <= circle.x + circle.r; x++){
        for(double y = circle.y - circle.r; y <= circle.y + circle.r; y++){
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distance_squared < radius_squared){
                SDL_Rect pixel = (SDL_Rect) {x, y, 1, 1};
                SDL_FillRect(surface, &pixel, colour);
            }
        }
    }
}

int main(int argc, char** argv){
    // Initializes the SDL library
    SDL_Init(SDL_INIT_VIDEO);
    // Creates a window, as in a pop up GUI
    SDL_Window *window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    
    // Create a surface to interact with the window
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    // Create a rectangle
    // SDL_Rect rect = (SDL_Rect) {
        // 200, // x coordinate 
        // 200, // y coordinate
        // 200, // width
        // 200  // height
    // };
    // Fill the rectangle with white colour 
    // SDL_FillRect(surface, &rect, COLOR_WHITE);
    
    struct Circle circle = {200, 200, 80};
    fillCircle(surface, circle, COLOR_WHITE);
    // Update the surface
    SDL_UpdateWindowSurface(window);


    // Pauses the program for 5000ms, often used to control frame rates
    // ./main exits after 5000 ms
    SDL_Delay(5000);

    return 0;
}