
#include <stdlib.h>
#include "raylib.h"

// constants used to define the number of fonts, colours, messages displayed and max number of elements on the screen
#define MAX_FONTS    8
#define MAX_COLOURS  14
#define MAX_MESSAGES 13
#define MAX_HISTORY  3000

typedef struct {
    int     fontIdx; // chosen font
    int     msgIdx; // chosen message
    Vector2 pos; // position
    float   angle; // angle
    float   size; // size of the font
    float   spacing; // spacing of the font
    Color   col; // colour of the font
} Word;

int main(void) {

    // initialization of the window, the `0, 0` implies to be in full-screen, afterwards we set an fps target and
    // generate a random seed
    InitWindow(0, 0, "asdSaver");
    SetTargetFPS(60);
    srand((unsigned)GetTime());

    Image icon = LoadImage("images/icon.png");
    Image bg = LoadImage("images/background.png");
    SetWindowIcon(icon);
    Texture2D background = LoadTextureFromImage(bg);

    // loaded fonts, all are preinstalled with raylib
    Font fonts[MAX_FONTS] = { 0 };
        fonts[0] = LoadFont("resources/sprite_fonts/alagard.png");
        fonts[1] = LoadFont("resources/sprite_fonts/pixelplay.png");
        fonts[2] = LoadFont("resources/sprite_fonts/mecha.png");
        fonts[3] = LoadFont("resources/sprite_fonts/setback.png");
        fonts[4] = LoadFont("resources/sprite_fonts/romulus.png");
        fonts[5] = LoadFont("resources/sprite_fonts/pixantiqua.png");
        fonts[6] = LoadFont("resources/sprite_fonts/alpha_beta.png");
        fonts[7] = LoadFont("resources/sprite_fonts/jupiter_crash.png");

    // loaded messages, the repetition of 'asd' is to make sure that it has a higher chance to appear
    const char *messages[MAX_MESSAGES] = {
                                            "ASD", "asd", "WEEEopen",
                                            "lol", "Debian", "Arch",
                                            "MaNgIaRo", "ASD", "asd",
                                            "FULL BRIDGE RECTIFIER",
                                            "MicroSLOP", "ASD", "asd"};

    // loaded colours used, all aleady defined by raylib
    Color colours[MAX_COLOURS] = {
        MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME,
        GOLD, RED, GREEN, BLUE, PURPLE, YELLOW, WHITE,  PINK
    };

    // initialization of buffer for words and counter, time of the last drawn word and the counter origin point
    static Word history[MAX_HISTORY];
    int   historyCount = 0;

    double lastDraw  = GetTime();
    Vector2 origin = { 0, 0 };

    HideCursor();

    // loop, it closes the windows if `Esc` or the close button is pressed
    while (!WindowShouldClose()) {

        // it generates a random time to wait before printing a new word, it goes from 0 to 2 sec
        // and then takes the new time time
        const double interval = ((double)(rand()%29) + 1.0)/10;
        double now = GetTime();

        // if there is still space in the buffer it creates a new word using random values
        // muduled on the max value of each field
        if (now - lastDraw >= interval && historyCount < MAX_HISTORY) {
            lastDraw = now;
            Word asd;
            asd.fontIdx = rand() % MAX_FONTS;
            asd.msgIdx  = rand() % MAX_MESSAGES;
            asd.pos.x   = (float)(rand() % (GetRenderWidth()));
            asd.pos.y   = (float)(rand() % (GetRenderHeight()));
            asd.angle   = (float)(rand() % 90) - 45.0f;
            asd.size    = (float)((rand() % 400) + 20) / 10.0f;
            asd.spacing = (float)(rand() % 7 + 1);
            asd.col     = colours[rand() % MAX_COLOURS];
            history[historyCount++] = asd;
        }

        // start to draw on a black screen the word with all the defined parameters
        BeginDrawing();
            ClearBackground(BLACK);

            Rectangle src = {0, 0, (float)background.width, (float)background.height};
            Rectangle dst = {0, 0, (float)GetScreenWidth(), (float)GetRenderHeight()};
            DrawTexturePro(background, src, dst, origin,0.0f, WHITE);

            for (int i = 0; i < historyCount; i++) {
                Word *asd = &history[i];
                DrawTextPro(fonts[asd->fontIdx], messages[asd->msgIdx],
                            asd->pos, origin, asd->angle, asd->size, asd->spacing, asd->col);
            }
        EndDrawing();

        // in case we have filled the buffer, we set back the counter at 0 to restart and clean the screen
        if (historyCount == MAX_HISTORY) {
            historyCount = 0;
            // ClearBackground(BLACK);
        }
    }

    // unloading the used fonts to prevent memory leaks when the program terminates
    for (int i = 0; i < MAX_FONTS; i++) UnloadFont(fonts[i]);
    UnloadImage(icon);
    UnloadImage(bg);
    CloseWindow();
    return 0;
}
