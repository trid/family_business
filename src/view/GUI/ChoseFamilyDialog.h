//
// Created by TriD on 01.06.2015.
//

#ifndef FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H
#define FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H

#include "Dialog.h"


class ChoseFamilyDialog: public Dialog {

public:
    ChoseFamilyDialog(int x, int y, int w, int h) : Dialog(x, y, w, h) { }

    virtual void draw(SDL_Renderer *renderer, const Point &offset);
};


#endif //FAMILY_BUSINESS_CHOSEFAMILYDIALOG_H
