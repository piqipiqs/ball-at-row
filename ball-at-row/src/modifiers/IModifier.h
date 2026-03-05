#ifndef IMODIFIER_H
#define IMODIFIER_H

#include <string>

class IModifier {
public:
    virtual ~IModifier() {}

    // tampilkan nama modifier di shop/daftar
    virtual std::string getName() const = 0;

    // ubah score
    virtual int apply(int baseScore) = 0;
};

#endif