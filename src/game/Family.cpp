//
// Created by TriD on 24.05.2015.
//

#include "Family.h"

void Family::save(std::ofstream &out) {
    out.write((char*)&id, sizeof(id));
    out.write((char*)&father, sizeof(father));
    out.write((char*)&mother, sizeof(mother));
    int childrenCount = children.size();
    out.write((char*)&childrenCount, sizeof(childrenCount));

    for (int child: children) {
        out.write((char*)&child, sizeof(child));
    }

    out.write((char*)&home, sizeof(home));

    int lastNameSize = lastName.size();
    out.write((char*)&lastNameSize, sizeof(lastNameSize));
    out.write(lastName.c_str(), lastNameSize);
}

void Family::load(std::ifstream &in) {
    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&father), sizeof(father));
    in.read(reinterpret_cast<char*>(&mother), sizeof(mother));
    int childrenCount{0};
    in.read(reinterpret_cast<char*>(&childrenCount), sizeof(childrenCount));

    for (int i = 0; i < childrenCount; i++) {
        int childId{0};
        in.read(reinterpret_cast<char*>(&childId), sizeof(childId));
        children.push_back(childId);
    }
    in.read(reinterpret_cast<char*>(&home), sizeof(home));
    int lastNameSize{0};
    in.read(reinterpret_cast<char*>(&lastNameSize), sizeof(lastNameSize));
    char* buff = new char[lastNameSize + 1];
    buff[lastNameSize] = '\0';
    in.read(buff, lastNameSize);
    lastName = buff;
    delete[] buff;
}
