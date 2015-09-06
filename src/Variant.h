//
// Created by TriD on 26.07.2015.
//

#ifndef FAMILY_BUSINESS_VARIANT_H
#define FAMILY_BUSINESS_VARIANT_H

#include <cassert>
#include <string>

namespace MEng {

    class Variant {
    private:
        enum class Type {
            Integer,
            Float,
            Bool,
            Pointer,
            None
        };

        Type type;

        union {
            int intData;
            float floatData;
            bool boolData;
            void *pointerData; // If you have to use it, may be something is wrong
        } data;
    public:
        Variant(int i) { setData(i); }

        Variant(float f) { setData(f); }

        Variant(bool b) { setData(b); }

        Variant(void *p) { setData(p); }

        Variant() { type = Type::None; }

        void setData(int data) {
            this->data.intData = data;
            type = Type::Integer;
        }

        void setData(float data) {
            this->data.floatData = data;
            type = Type::Float;
        }

        void setData(bool data) {
            this->data.boolData = data;
            type = Type::Bool;
        }

        // Be especially careful with this one
        void setData(void *data) {
            this->data.pointerData = data;
            type = Type::Pointer;
        }

        int getInt() {
            assert(type == Type::Integer);
            return data.intData;
        }

        float getFloat() {
            assert(type == Type::Float);
            return data.floatData;
        }

        bool getBool() {
            assert(type == Type::Bool);
            return data.boolData;
        }

        // Again, be careful.
        void *getPointer() {
            assert(type == Type::Pointer);
            return data.pointerData;
        }
    };

}

#endif //FAMILY_BUSINESS_VARIANT_H
