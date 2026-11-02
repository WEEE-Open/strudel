#include "assets.h"
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

static char *generateMessage();


const Color COLOURS[MAX_COLOURS] = {
        MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME,
        GOLD, RED, GREEN, BLUE, PURPLE, YELLOW, PINK // , WHITE
    };

// Here are hardcoded all the path for the fonts, this way they are defined
// all in the same place so it's easier to update them for any reason
static const char *FONT_PATHS[MAX_FONTS] = {
    "resources/sprite_fonts/alagard.png",
    "resources/sprite_fonts/pixelplay.png",
    "resources/sprite_fonts/mecha.png",
    "resources/sprite_fonts/setback.png",
    "resources/sprite_fonts/romulus.png",
    "resources/sprite_fonts/pixantiqua.png",
    "resources/sprite_fonts/alpha_beta.png",
    "resources/sprite_fonts/jupiter_crash.png",
    "resources/MapleMono.ttf",
    "resources/DotGothic16-Regular.ttf",
    "resources/KAISG.ttf",
    "resources/Papyrus.ttf",
};

// Function to load all the above specified fonts, it will load all of them in a `FontSet` structure
// before returning it in case the path of a font is broken or missing for any reason, it will give
// an error on the LOG_WARNING, since it will be replaced by a default font, there is no need to
// exit the program and we can continue with the execution of the program
FontSet LoadFontSet() {
    FontSet fontSet = {0};
    fontSet.count = MAX_FONTS;

    for (int i = 0; i<MAX_FONTS; i++) {
        fontSet.font[i] = LoadFont(FONT_PATHS[i]);
        if (!IsFontValid(fontSet.font[i])) {
            TraceLog(LOG_WARNING, "error: FAILED to load font n.%d: %s", &i, FONT_PATHS[i]);
        }
    }
    return fontSet;
}


// function to draw the time, it makes 2 strings and takes a font as parameter,
// the strings are "aligned" on the center of the 1/3 lower part of the screen,
// with a green, non aligned border and a white text
void DrawClockOverlay(Font font) {
    char timeBuf[16];
    char dateBuf[32];
    time_t seconds_time = time(NULL);
    struct tm *time = localtime(&seconds_time);
    strftime(timeBuf, sizeof(timeBuf), "%H:%M", time);
    strftime(dateBuf, sizeof(dateBuf), "%A", time);

    const int fontSizeInternal = 110, fontSizeExternal = 145;
    int tw = MeasureText(timeBuf, fontSizeExternal);
    int dw = MeasureText(dateBuf, fontSizeExternal);
    int x = GetScreenWidth() / 2 - tw/2;
    int x2 = GetScreenWidth() / 2 - dw/2;
    int y = GetScreenHeight() / 3 * 2;
    Vector2 posExt = {x, y}, origin = {0, 0}, posInt = {x+3, y + 17},
        pos2Ext = {x2, y + 120}, pos2Int = {x2+ 15, y + 145};
    Color colourExternal = GREEN, colourInternal = WHITE;

    SetTextLineSpacing(20);
    DrawTextPro(font, timeBuf, posExt, origin, 0.0, fontSizeExternal, 7, colourExternal);
    DrawTextPro(font, dateBuf, pos2Ext, origin, 0.0, fontSizeExternal, 7, colourExternal);
    SetTextLineSpacing(35);
    DrawTextPro(font, timeBuf, posInt, origin, 0.0, fontSizeInternal, 20, colourInternal);
    DrawTextPro(font, dateBuf, pos2Int, origin, 0.0, fontSizeInternal, 25, colourInternal);
}

// generate a word from the messages and the passed font list, it gives a
// random clour, size and spacing it uses the internal function to decide the word to print
Word generateWord(FontSet *fontSet) {
    Word asd;

    asd.font    = fontSet->font[rand() % MAX_FONTS];
    asd.msg     = generateMessage();
    asd.pos.x   = (float)(rand() % (GetRenderWidth()));
    asd.pos.y   = (float)(rand() % (GetRenderHeight()));
    asd.angle   = (float)(rand() % 90) - 45.0f;
    asd.size    = (float)((rand() % 400) + 20) / 10.0f;
    asd.spacing = (float)(rand() % 7 + 1);
    asd.col     = COLOURS[rand() % MAX_COLOURS];



    return asd;
}

char *generateMessage() {
    char *asd;

    int val = rand() % 100;
    if (val < 10) {
        asd = "WEEE Open";
    } else if (val == 11) {
        asd = "LoL";
    } else if (val == 12) {
        asd = "FULL BRIDGE RECTIFIER";
    } else if (val < 30 && (val % 3) == 0) {
        asd = "Debian";
    } else if (val < 30 && (val % 3) == 1) {
        asd = "Arch BTW";
    } else if (val < 30 && (val % 3) == 2) {
        asd = "WEEEbian";
    } else if (val < 35) {
        asd = "MicroSlop";
    } else {
        asd = "asd";
    }

    return asd;
}

// It will unload all the fonts inside the `FontSet` passed by using the `UnloadFont`
// only on the valid fonts, it will ignore the ones that failed to load previously
// it resets the count of the set at 0 after having freed all of the fonts
void UnloadFontSet(FontSet *fontSet) {
    for (int i = 0; i < fontSet->count; i++) {
        if (IsFontValid(fontSet->font[i])) {
            UnloadFont(fontSet->font[i]);
        }
    }
    fontSet->count = 0;
}
