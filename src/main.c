
#include <stdlib.h>
#include "raylib.h"

#define MAX_FONTS    8
#define MAX_COLOURS  12
#define MAX_MESSAGES 13
#define MAX_HISTORY  5000

typedef struct {
    int     fontIdx;
    int     msgIdx;
    Vector2 pos;
    float   angle;
    float   size;
    float   spacing;
    Color   col;
} Word;

int main(void) {
    InitWindow(0, 0, "asdSaver");
    SetTargetFPS(60);
    srand((unsigned)GetTime());

    Font fonts[MAX_FONTS] = { 0 };
    fonts[0] = LoadFont("resources/sprite_fonts/alagard.png");
    fonts[1] = LoadFont("resources/sprite_fonts/pixelplay.png");
    fonts[2] = LoadFont("resources/sprite_fonts/mecha.png");
    fonts[3] = LoadFont("resources/sprite_fonts/setback.png");
    fonts[4] = LoadFont("resources/sprite_fonts/romulus.png");
    fonts[5] = LoadFont("resources/sprite_fonts/pixantiqua.png");
    fonts[6] = LoadFont("resources/sprite_fonts/alpha_beta.png");
    fonts[7] = LoadFont("resources/sprite_fonts/jupiter_crash.png");

    const char *messages[MAX_MESSAGES] = {
                                            "ASD",
                                            "asd",
                                            "WEEEopen",
                                            "lol",
                                            "Debian",
                                            "Arch",
                                            "MaNgIaRo",
                                            "ASD",
                                            "asd",
                                            "FULL BRIDGE RECTIFIER",
                                            "MicroSLOP",
                                            "ASD",
                                            "asd"};
    Color colors[MAX_COLOURS] = {
        MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME,
        GOLD, RED, GREEN, BLUE, PURPLE, YELLOW
    };

    static Word history[MAX_HISTORY];
    int   historyCount = 0;

    double lastDraw  = GetTime();
    Vector2 origin = { 0, 0 };

    while (!WindowShouldClose()) {
        const double interval = ((double)(rand()%30))/10;
        double now = GetTime();
        if (now - lastDraw >= interval && historyCount < MAX_HISTORY) {
            lastDraw = now;
            Word w;
            w.fontIdx = rand() % MAX_FONTS;
            w.msgIdx  = rand() % MAX_MESSAGES;
            w.pos.x   = (float)(rand() % (GetRenderWidth()));
            w.pos.y   = (float)(rand() % (GetRenderHeight()));
            w.angle   = (float)(rand() % 90) - 45.0f;
            w.size    = (float)((rand() % 400) + 20) / 10.0f;
            w.spacing = (float)(rand() % 7 + 1);
            w.col     = colors[rand() % MAX_COLOURS];
            history[historyCount++] = w;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < historyCount; i++) {
                Word *w = &history[i];
                DrawTextPro(fonts[w->fontIdx], messages[w->msgIdx],
                            w->pos, origin, w->angle, w->size, w->spacing, w->col);
            }
        EndDrawing();
    }

    for (int i = 0; i < MAX_FONTS; i++) UnloadFont(fonts[i]);
    CloseWindow();
    return 0;
}
