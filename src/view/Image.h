//
// Created by TriD on 04.08.2015.
//

#ifndef FAMILY_BUSINESS_IMAGE_H
#define FAMILY_BUSINESS_IMAGE_H

#include <memory>

#include "Drawable.h"
#include "../Point.h"

class Image: public Drawable {
private:
    SDL_Texture* texture;
    Point position;
public:
    Image(SDL_Texture* texture, Point position = {0, 0}): texture(texture), position(position) { }
    void draw(SDL_Renderer *renderer) override;

    Point getPosition() { return position; }
    void setPosition(Point point) { this->position = point; }
};

using ImagePtr = std::shared_ptr<Image>;

#endif //FAMILY_BUSINESS_IMAGE_H
