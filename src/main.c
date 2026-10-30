
#include <stdlib.h>
#include "raylib.h"
#include "assets.h"

int main(void) {

    // initialization of the window,
    // afterwards we set an fps target and generate a random seed
    int width = 1280, height = 1024;
    InitWindow(width, height, "asdSaver");
    SetTargetFPS(60);
    srand((unsigned)GetTime());

    Image icon = LoadImage("images/icon.png");
    Image bg = LoadImage("images/background.png");
    SetWindowIcon(icon);
    Texture2D background = LoadTextureFromImage(bg);

    FontSet fontSet = LoadFontSet();

    // loaded messages, the repetition of 'asd' is to make sure that it has a higher chance to appear
    const char *messages[MAX_MESSAGES] = {
        "ASD", "asd", "WEEEopen",
        "lol", "Debian", "Arch",
        "MaNgIaRo", "ASD", "asd",
        "FULL BRIDGE RECTIFIER",
        "MicroSLOP", "ASD", "asd"
    };

    // loaded colours used, all aleady defined by raylib
    Color colours[MAX_COLOURS] = {
        MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME,
        GOLD, RED, GREEN, BLUE, PURPLE, YELLOW, PINK // , WHITE
    };

    // initialization of buffer for words and counter, time of the last drawn word and the counter origin point
    static Word history[MAX_HISTORY];
    int   historyCount = 0;

    double lastDraw  = GetTime();
    Vector2 origin = { 0, 0 };

    HideCursor();
    int xTimeInc = 0, yTimeInc = 0;

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
            Rectangle dst = {0, 0, (float)width, (float)height};
            DrawTexturePro(background, src, dst, origin,0.0f, WHITE);

            for (int i = 0; i < historyCount; i++) {
                Word *asd = &history[i];
                DrawTextPro(fontSet.font[asd->fontIdx], messages[asd->msgIdx],
                            asd->pos, origin, asd->angle, asd->size, asd->spacing, asd->col);

                DrawClockOverlay(fontSet.font[6]);
            }
        EndDrawing();

        // in case we have filled the buffer, we set back the counter at 0 to restart and clean the screen
        if (historyCount == MAX_HISTORY) {
            historyCount = 0;
        }
    }

    UnloadFontSet(&fontSet);

    UnloadImage(icon);
    UnloadImage(bg);
    CloseWindow();
    return 0;
}
