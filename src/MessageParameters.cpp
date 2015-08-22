//
// Created by TriD on 26.07.2015.
//

#include "MessageParameters.h"

void MessageParameters::save(std::ofstream &out) {
    int count = parameters.size();
    out.write((char*)&count, sizeof(count));

    for (auto item: parameters) {
        int len = item.first.size();
        out.write((char*)&len, sizeof(len));
        out.write(item.first.c_str(), len);
        //TODO: rewrite to Variant::save later. Do not forget, you need to differ if you save strings as variant
        out.write((char*)&item.second, sizeof(item.second));
    }
}
