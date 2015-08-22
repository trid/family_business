//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_MESSAGEPARAMETERS_H
#define FAMILY_BUSINESS_MESSAGEPARAMETERS_H

#include <fstream>
#include <initializer_list>
#include <string>
#include <unordered_map>

#include "Variant.h"

using Parameters = std::unordered_map<std::string, Variant>;

class MessageParameters {
private:
    Parameters parameters;
public:
    MessageParameters() = default;
    MessageParameters(const std::initializer_list<std::pair<std::string, Variant>> parameters) {
        for (auto item: parameters){
            this->parameters[item.first] = item.second;
        }
    }

    Variant getParameter(const std::string &name) const { return parameters.at(name); }
    void setParameter(const std::string& name, Variant param) { parameters[name] = param; }

    void save(std::ofstream& out);
};


#endif //FAMILY_BUSINESS_MESSAGEPARAMETERS_H
