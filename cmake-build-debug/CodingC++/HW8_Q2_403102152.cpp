#include <SDL2/SDL.h>
#include <iostream>
#include <valarray>
#include <vector>

enum DrawMode {
    FREE,
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
    POLYGON
};

struct Shape {
    DrawMode mode;
    SDL_Rect rect;
    SDL_Color color;
};

SDL_Color currentColor = {0, 0, 0, 255};
DrawMode currentMode = LINE;
std::vector<Shape> shapes;
bool drawing = false, poly = false;
SDL_Point startPoint;

void circle(SDL_Renderer* renderer, int x, int y, int radius) {
    int offsetX, offsetY, d;
    offsetX = 0;
    offsetY = radius;
    d = radius - 1;
    while (offsetY >= offsetX) {
        SDL_RenderDrawPoint(renderer, x + offsetX, y + offsetY);
        SDL_RenderDrawPoint(renderer, x + offsetY, y + offsetX);
        SDL_RenderDrawPoint(renderer, x - offsetX, y + offsetY);
        SDL_RenderDrawPoint(renderer, x - offsetY, y + offsetX);
        SDL_RenderDrawPoint(renderer, x + offsetX, y - offsetY);
        SDL_RenderDrawPoint(renderer, x + offsetY, y - offsetX);
        SDL_RenderDrawPoint(renderer, x - offsetX, y - offsetY);
        SDL_RenderDrawPoint(renderer, x - offsetY, y - offsetX);

        if (d >= 2 * offsetX) {
            d -= 2 * offsetX + 1;
            offsetX++;
        } else if (d < 2 * (radius - offsetY)) {
            d += 2 * offsetY - 1;
            offsetY--;
        } else {
            d += 2 * (offsetY - offsetX - 1);
            offsetY--;
            offsetX++;
        }
    }
}

void triangle(SDL_Renderer* renderer, int cx, int cy, int x1, int y1) {
    int x2, x3, y2, y3;
    if (x1 < cx) {
        x2 = x1 + 2*abs(cx-x1);
        x3 = x1 + abs(cx - x1);
    }
    else {
        x2 = x1 - 2*abs(cx-x1);
        x3 = x1 - abs(cx - x1);
    }
    if (y1 < cy) {
        y3 = cy + 2*abs(cy - y1);
    }
    else {
        y3 = cy - 2*abs(cy - y1);
    }
    y2 = y1;
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
}

void mouseSE(SDL_Renderer *renderer, SDL_Event &event) {
    for (const auto &shape : shapes) {
        if (shape.mode == POLYGON) {
            poly = true;
        }
        else {
            poly = false;
        }
    }
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (!poly) {
                if (drawing) {
                    drawing = false;
                    shapes.push_back({currentMode, {startPoint.x, startPoint.y, event.button.x - startPoint.x, event.button.y - startPoint.y}, currentColor});
                }
                else {
                    drawing = true;
                    startPoint = {event.button.x, event.button.y};
                }
            }
            else {
                if (drawing) {
                    shapes.push_back({currentMode, {startPoint.x, startPoint.y, event.button.x - startPoint.x, event.button.y - startPoint.y}, currentColor});
                }
                drawing = true;
                startPoint = {event.button.x, event.button.y};
            }
            break;
    }
}

void modes(SDL_Renderer *renderer) {
    for (const auto &shape : shapes) {
        SDL_SetRenderDrawColor(renderer, shape.color.r, shape.color.g, shape.color.b, shape.color.a);
        if (shape.mode == LINE) {
            SDL_RenderDrawLine(renderer, shape.rect.x, shape.rect.y, shape.rect.x + shape.rect.w, shape.rect.y + shape.rect.h);
        }
        else if (shape.mode == RECTANGLE) {
            SDL_RenderDrawRect(renderer, &shape.rect);
        }
        else if (shape.mode == CIRCLE) {
            circle(renderer, shape.rect.x, shape.rect.y, abs(shape.rect.w));
        }
        else if (shape.mode == TRIANGLE) {
            triangle(renderer, shape.rect.x, shape.rect.y, shape.rect.x + shape.rect.w, shape.rect.y + shape.rect.h);
        }
        else if (shape.mode == POLYGON) {
            SDL_RenderDrawLine(renderer, shape.rect.x, shape.rect.y, shape.rect.x + shape.rect.w, shape.rect.y + shape.rect.h);
        }
        else {
            SDL_RenderDrawPoint(renderer, shape.rect.x, shape.rect.y);
        }
    }
}

void keys(SDL_Renderer *renderer, SDL_Event &event) {
    switch (event.key.keysym.sym) {
        case SDLK_0:
            shapes = {};
            break;
        case SDLK_1:
            currentMode = FREE;
            break;
        case SDLK_2:
            currentMode = LINE;
            break;
        case SDLK_3:
            currentMode = RECTANGLE;
            break;
        case SDLK_4:
            currentMode = CIRCLE;
            break;
        case SDLK_5:
            currentMode = TRIANGLE;
            break;
        case SDLK_6:
            currentMode = POLYGON;
            break;
        case SDLK_r:
            currentColor = {255, 0, 0, 255};
            break;
        case SDLK_g:
            currentColor = {0, 255, 0, 255};
            break;
        case SDLK_b:
            currentColor = {0, 0, 255, 255};
            break;
        case SDLK_y:
            currentColor = {200, 200, 0, 255};
            break;
        case SDLK_p:
            currentColor = {200, 0, 200, 255};
            break;
        case SDLK_m:
            currentColor = {0, 0, 0, 255};
            break;
        case SDLK_e:
            currentColor = {255, 255, 255, 255};
            break;
    }
}

int main(int argc, char *argv[]) {
    std::cout<<"RESET = 0"<<std::endl;
    std::cout<<"Eraser = e"<<std::endl;
    std::cout<<"Thickness: increase = + / decrease = -"<<std::endl;
    std::cout<<"COLORS:"<<std::endl;
    std::cout<<"Red = r"<<std::endl;
    std::cout<<"Green = g"<<std::endl;
    std::cout<<"Blue = b"<<std::endl;
    std::cout<<"Yellow = y"<<std::endl;
    std::cout<<"Purple = p"<<std::endl;
    std::cout<<"Black = m"<<std::endl;
    std::cout<<"DRAW MODES:"<<std::endl;
    std::cout<<"FREE = 1"<<std::endl;
    std::cout<<"LINE = 2"<<std::endl;
    std::cout<<"RECTANGLE = 3"<<std::endl;
    std::cout<<"CIRCLE = 4"<<std::endl;
    std::cout<<"TRIANGLE = 5"<<std::endl;
    std::cout<<"POLYGON = 6"<<std::endl;

    SDL_Window *window = SDL_CreateWindow("Paint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    bool quit = false, clicked = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (currentMode == FREE) {
                        clicked = true;
                    }
                    else {
                        mouseSE(renderer, e);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    clicked = false;
                    break;
                case SDL_MOUSEMOTION:
                    if (clicked) {
                        shapes.push_back({currentMode, {e.button.x, e.button.y, 0, 0}, currentColor});
                    }
                    break;
                case SDL_KEYDOWN:
                    keys(renderer, e);
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        modes(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
