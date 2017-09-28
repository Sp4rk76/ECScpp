//
// Created by Sp4rk on 10-08-17.
//

#ifndef CES_SHAPEBUILDER_H
#define CES_SHAPEBUILDER_H

#include <SDL_rect.h>
#include <SDL_render.h>
#include <iostream>
#include "ShapeType.h"

class ShapeBuilder {
public:
    SDL_Rect createShape(int x, int y, int w, int h);

    SDL_Rect loadShape(ShapeType shapeType);

    void setShape(ShapeType shapeType, int x = 0, int y = 0, int w = 0, int h = 0);

    void drawBox(SDL_Renderer *renderer, const SDL_Rect *shape, Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00,
                 Uint8 = 0xFF);

    void init();

private:
    SDL_Rect shapes_[ShapeType::TOTAL];
};

SDL_Rect ShapeBuilder::createShape(int x, int y, int w, int h) {
    return {x, y, w, h};
}

void ShapeBuilder::init() {
    shapes_[BOX] = createShape(32, 32, 64, 128);
}

SDL_Rect ShapeBuilder::loadShape(ShapeType shapeType) {
    return shapes_[BOX];
}

void ShapeBuilder::setShape(ShapeType shapeType, int x, int y, int w, int h) {
    shapes_[shapeType] = createShape(x, y, w, h);
}

void ShapeBuilder::drawBox(SDL_Renderer *renderer, const SDL_Rect *shape, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, shape);
}


#endif //CES_SHAPEBUILDER_H
