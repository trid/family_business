//
// Created by TriD on 26.07.2015.
//

#include "MessageParameters.h"

using namespace MEng;

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

void MessageParameters::load(std::ifstream &in) {
    int count{0};
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        int len{};
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        char* buff = new char[len + 1];
        buff[len] = '\0';
        in.read(buff, len);
        std::string name{buff};
        delete[] buff;

        Variant variant;
        in.read(reinterpret_cast<char*>(&variant), sizeof(variant));

        setParameter(name, variant);
    }
}
