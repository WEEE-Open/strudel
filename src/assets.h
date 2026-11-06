#ifndef ASSETS_H
#define ASSETS_H

    #include "giffer.h"
    #include "raylib.h"
    #include "raymedia.h"
    #include <time.h>

    // constants used to define the number of fonts, colours, messages displayed and max number of elements on the screen
    #define MAX_FONTS    13
    #define MAX_COLOURS  14
    #define MAX_MESSAGES 13
    #define MAX_HISTORY  3000

    // array of all the used colours, this way it's easier to add or remove colours
    extern const Color COLOURS[MAX_COLOURS];

    // struct to define all the parameters of a word, it conains
    // font, printed message, position, angle, font size, spacing and colour
    typedef struct {
        Font         font; // chosen font
        const char * msg; // chosen message
        Vector2      pos; // position
        float        angle; // angle
        float        size; // size of the font
        float        spacing; // spacing of the font
        Color        col; // colour of the font
    } Word;

    // struct to contain all the defined fonts, this way it's possible
    // to add all the fonts that one want without changing the code
    typedef struct {
        Font font[MAX_FONTS];
    }FontSet;

    // function to initialize the window and it's fps lock, seed and audio.
    // it returns
    // - 1 if there is a problem in the window initialization,
    // - 2 if there is a problem with the audio initialization,
    //      it can be ignored as a warning
    int Initialize();

    // Function to load all the above specified fonts, it will load all of them in a
    // `FontSet` structure before returning it in case the path of a font is broken
    // or missing for any reason, it will give an error on the LOG_WARNING, since it
    // will be replaced by a default font, there is no need to exit the program and
    // we can continue with the execution of the program
    FontSet LoadFontSet();

    // function to draw the time, it makes 2 strings and takes a font as parameter,
    // the strings are "aligned" on the center of the 1/3 lower part of the screen,
    // with a green, non aligned border and a white text
    void DrawClockOverlay(Font font);

    // generate a word from the messages and the passed font list, it gives a
    // random clour, size and spacing it uses the internal function to decide the
    // word to print
    Word generateWord(FontSet *fontSet);

    // function to deinitialize everything,other than the passed arguments
    // it also deinitialize audio and the window
    void DeinitializeAll(FontSet *fontSet, Image icon, Texture2D background, MediaStream mp4);

    // function to load a video and check if it's working or not,
    // also disable the loop (just in case)
    MediaStream LoadMediaAndCheck(char *videoPath);
#endif
