#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 1200
#define HEIGHT 700
#define COLOUR_WHITE 0xffffffff
#define COLOUR_BLACK 0x00000000
#define COLOUR_GRAY 0xefefefef
#define COLOUR_RAY 0xf0ab2b
#define RAYS_NUMBER 500

struct Circle{
    double x; // x coordinate of circle
    double y; // y coordinate of circle
    double r; // radius of circle
};

struct Ray{
    double x_start, y_start;
    double angle;
};

/*
*   in fillCircle(*args),
*   Each individual pixel that lies inside the given radius, is filled with
*   colour: Uint32
*   SDL2 does not have an implementation of a circle and it is implemented
*   explicitly by the user inform of filling each individual pixel
*/
void fillCircle(SDL_Surface *surface, struct Circle source, Uint32 colour){
    double radius_squared = pow(source.r, 2);
    for(double x = source.x - source.r; x <= source.x + source.r; x++){
        for(double y = source.y - source.r; y <= source.y + source.r; y++){
            
            // Checks if the point is inside the source
            double distance_squared = pow(x - source.x, 2) + pow(y - source.y, 2);
            if (distance_squared < radius_squared){
                SDL_Rect pixel = {x, y, 1, 1};
                SDL_FillRect(surface, &pixel, colour);
            }
        }
    }
}

void generate_rays(struct Circle circle, struct Ray rays[RAYS_NUMBER]){
    for(int i = 0; i < RAYS_NUMBER; i++){
        // Generates rays based on the position of struct Circle circle
        double angle = ((double) i / RAYS_NUMBER) * 2 * M_PI;
        struct Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
    }
}

void fillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], Uint32 colour, struct Circle object){
    
    double object_radius_square = pow(object.r, 2);
    for (int i = 0; i < RAYS_NUMBER; i++){
        // Manipulates the current ray object
        struct Ray ray = rays[i];

        // boolean to decide if the ray is inside the screen
        int end_of_screen = 0;
        int object_hit = 0;

        // starting point of the ray
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;

        // the loop draws (fills) each individual ray inside the screen
        while(!end_of_screen && !object_hit){
            // the x_component of the ray is generated
            x_draw += cos(ray.angle);
            // the y_component of the ray is generated
            y_draw += sin(ray.angle);

            // Fill in the ray pixel by pixel
            SDL_Rect pixel = {x_draw, y_draw, 1, 1};
            SDL_FillRect(surface, &pixel, colour);

            // check the bounds
            if(x_draw < 0 || x_draw > WIDTH) end_of_screen = 1;
            if(y_draw < 0 || y_draw > HEIGHT) end_of_screen = 1;
        
            // check for collision
            double distance_squared = pow(x_draw - object.x, 2) + pow(y_draw - object.y, 2);
            if (distance_squared < object_radius_square){
                break;
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
    // SDL_Rect rect = {
        // 200, // x coordinate 
        // 200, // y coordinate
        // 200, // width
        // 200  // height
    // };
    // Fill the rectangle with white colour 
    // SDL_FillRect(surface, &rect, COLOR_WHITE);
    
    // Initialize the light source
    struct Circle source = {200, 200, 80};
    struct Circle object = {600, 300, 120};
    
    // Spans across the entire window, it makes sure that the circle does not leave behind a trail of colour
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};
    
    // Initializes an array of rays around the light source
    struct Ray rays[RAYS_NUMBER];
    generate_rays(source, rays);
    // boolean to check the exit condition
    int simulation_running = 1;
    // Event captures external interactions to the window and surface
    SDL_Event event;
    while(simulation_running){
        while(SDL_PollEvent(&event)){
            //  SDL_QUIT -> clicking the 'x' button to close the window
            if(event.type == SDL_QUIT){
                simulation_running = 0;
            }
            if(event.type == SDL_MOUSEMOTION && event.motion.state != 0){
                // Draw Circle on moving the mouse pointer
                source.x = event.motion.x;
                source.y = event.motion.y;

                // Generate the rays based on the position of the light source
                generate_rays(source, rays);
            }
        }
        
        // This makes sure that the circle does not leave a trail of white colour on moving it
        SDL_FillRect(surface, &erase_rect, COLOUR_BLACK);
        
        // Fill the circle with white colour
        fillCircle(surface, source, COLOUR_WHITE);
        fillCircle(surface, object, COLOUR_WHITE);

        // Fill the generated rays
        fillRays(surface, rays, COLOUR_RAY, object);
        // Update the surface
        SDL_UpdateWindowSurface(window);
        
        // Corresponds to 100 FPS
        SDL_Delay(10);
    }
    
    return 0;
}