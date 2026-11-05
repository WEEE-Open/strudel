#ifndef ASSETS_H
#define ASSETS_H

    #include "raylib.h"
    #include <time.h>

    // constants used to define the number of fonts, colours, messages displayed and max number of elements on the screen
    #define MAX_FONTS    13
    #define MAX_COLOURS  14
    #define MAX_MESSAGES 13
    #define MAX_HISTORY  3000


    extern const Color COLOURS[MAX_COLOURS];

    typedef struct {
        Font         font; // chosen font
        const char * msg; // chosen message
        Vector2      pos; // position
        float        angle; // angle
        float        size; // size of the font
        float        spacing; // spacing of the font
        Color        col; // colour of the font
    } Word;

    typedef struct {
        Font font[MAX_FONTS];
        int count;
    }FontSet;

    // loading and defining functions
    FontSet LoadFontSet();

    // drawing and operational functions
    void DrawClockOverlay(Font font);

    // generate a Word
    Word generateWord(FontSet *fontSet);

    void UnloadFontSet(FontSet *fontSet);


#endif
