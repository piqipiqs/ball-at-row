#ifndef IMODIFIER_H
#define IMODIFIER_H

class IModifier {
public:
    virtual ~IModifier() {}
    virtual int apply(int baseScore) = 0;
};

#endif