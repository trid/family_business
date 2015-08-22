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
