//
// Created by TriD on 08.06.2015.
//

#include "FamilyButton.h"

#include "../../Family.h"
#include "../../../view/Screen.h"
#include "../../../view/GUI/FontsCache.h"
#include "../../FamilyManager.h"

using namespace MEng::View::GUI;
using namespace Main;

FamilyButton::FamilyButton(int x, int y, int w, int h, int familyId, Callback callback) : Widget(x, y, w, h),
                                                                                                     familyId(familyId),
                                                                                                     callback(
                                                                                                             callback) {
    font = FontsCache::getInstance().getFont("res/fonts/FreeMono.ttf", 16);
    SDL_Surface *surface = TTF_RenderText_Solid(font, getFamilyById(familyId).getLastName().c_str(), SDL_Color{0, 0, 0, 255});
    label = SDL_CreateTextureFromSurface(MEng::View::Screen::getInstance().getRenderer(), surface);
    SDL_FreeSurface(surface);
}

FamilyButton::~FamilyButton() {
    SDL_DestroyTexture(label);
}

bool FamilyButton::onClick(Point point, int button) {
    if (Widget::onClick(point, button)) {
        callback(familyId);
        return true;
    }
    return false;
}

void FamilyButton::onRedraw(SDL_Renderer *renderer) {
    SDL_Rect rect = SDL_Rect{0, 0, getWidth(), getHeight()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderCopy(renderer, label, nullptr, &rect);
}
