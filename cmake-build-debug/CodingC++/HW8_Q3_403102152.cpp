#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
int color = 0,nf;

void tree(SDL_Renderer* renderer,int x1,int y1,double angle,int n) {
    if(n == 0) return;

    int l = n*5;
    int x2 = x1+l*cos(angle);
    int y2 = y1-l*sin(angle);

    SDL_SetRenderDrawColor(renderer,color,0,color,255);
    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);

    color += (255/nf);
    tree(renderer,x2,y2,angle-M_PI/6,n-1);
    tree(renderer,x2,y2,angle+M_PI/6,n-1);
    color -= (255/nf);
}

int main(int argc, char* argv[]) {
    int n;
    std::cin>>n;
    nf = n+1;

    SDL_Window* window = SDL_CreateWindow("Fractal Tree",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event e;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);

        color = 0;
        tree(renderer,WIDTH/2,HEIGHT,M_PI/2,n+1);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
