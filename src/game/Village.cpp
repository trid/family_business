//
// Created by TriD on 24.05.2015.
//

#include "Village.h"

void Village::save(std::ofstream &out) {
    out.write((char*)&center, sizeof(Point));
}

void Village::load(std::ifstream &in) {
    in.read((char*)&center, sizeof(Point));
}
