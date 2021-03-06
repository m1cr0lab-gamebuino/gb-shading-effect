#ifndef SHADING_EFFECT_RENDERABLE
#define SHADING_EFFECT_RENDERABLE

#include <Gamebuino-Meta.h>

class Renderable
{
    public:

        // pure virtual desctructor
        // it will have to be extended in derived classes
        virtual ~Renderable() = 0;

        // pure virtual method
        virtual void draw(uint8_t sliceY, uint8_t sliceHeight, uint16_t* buffer) = 0;
};

#endif