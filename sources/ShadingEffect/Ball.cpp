#include <Gamebuino-Meta.h>
#include "Ball.h"
#include "constants.h"

// we copy the descriptive parameters of our sprite
const uint8_t Ball::FRAME_WIDTH = 16;
const uint8_t Ball::FRAME_HEIGHT = 16;
const uint16_t Ball::TRANSPARENT_COLOR = 0xffff;
// the ball is positioned in the center of the screen...
// note that these coordinates correspond to the corner
// at the top left of our sprite
const uint8_t Ball::X_POS = (SCREEN_WIDTH - FRAME_WIDTH) / 2;
const uint8_t Ball::Y_POS = (SCREEN_HEIGHT - FRAME_HEIGHT) / 2;

// we copy the value of the variable `spritedata`
// that the transcoding tool provided us with
const uint16_t Ball::BITMAP[] = {
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0x0ef8, 0x5cfe, 0x5cfe, 0x5cfe, 0x5cfe, 0x5cfe, 0x0ef8, 0x0ef8, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0x0ef8, 0x5cfe, 0x5cfe, 0x5cfe, 0x5cfe, 0x5cfe, 0x5cfe, 0x5cfe, 0x0ef8, 0x0ef8, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0x0ef8, 0x5cfe, 0x5cfe, 0x5cfe, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x5cfe, 0x0ef8, 0x0780, 0xffff, 0xffff,
    0xffff, 0xffff, 0x0ef8, 0x5cfe, 0x5cfe, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0450, 0x0000, 0xffff,
    0xffff, 0xffff, 0x0ef8, 0x5cfe, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0780, 0x0450, 0x0000, 0xffff,
    0xffff, 0xffff, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0780, 0x0450, 0x0000, 0xffff,
    0xffff, 0xffff, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0780, 0x0780, 0x0450, 0x0000, 0xffff,
    0xffff, 0xffff, 0x0780, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0780, 0x0450, 0x0450, 0x0000, 0xffff,
    0xffff, 0xffff, 0xffff, 0x0780, 0x0780, 0x0ef8, 0x0ef8, 0x0ef8, 0x0ef8, 0x0780, 0x0780, 0x0450, 0x0450, 0x0000, 0x0000, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0x0450, 0x0780, 0x0780, 0x0780, 0x0780, 0x0780, 0x0450, 0x0450, 0x0000, 0x0000, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0450, 0x0450, 0x0450, 0x0450, 0x0450, 0x0450, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};

// and we define the method of calculating the rendering of the ball
void Ball::draw(uint8_t sliceY, uint8_t sliceHeight, uint16_t* buffer) {
    // the portion of the sprite which is located within
    // the current slice is determined along the Y axis
    int8_t startIndex = Y_POS <= sliceY ? 0 : Y_POS - sliceY;
    int8_t endIndex = Y_POS + FRAME_HEIGHT >= sliceY + sliceHeight ? sliceHeight - 1 : Y_POS + FRAME_HEIGHT - sliceY - 1;
    // we prepare a variable that will receive in turn the color codes
    // of each of the pixels that make up the sprite (in the current slice)
    uint16_t value;
    // coordinates of the processed pixel
    uint8_t x,y;
    // now we go through the portion of the sprite that is in the slice
    // along the Y axis...
    for (y = startIndex; y <= endIndex; y++) {
        // and the X axis
        for (x = X_POS; x < X_POS + FRAME_WIDTH; x++) {
            // we will pick the color of the corresponding pixel
            value = BITMAP[x - X_POS + (y + sliceY - Y_POS) * FRAME_WIDTH];
            // and if it is not the transparent color
            if (value != TRANSPARENT_COLOR) {
                // we copy it into the buffer
                buffer[x + y * SCREEN_WIDTH] = value;
            }
        }
    }
}