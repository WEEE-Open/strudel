
#include <stdlib.h>
#include "raylib.h"

#define MAX_FONTS    8
#define MAX_COLOURS  14
#define MAX_MESSAGES 13
#define MAX_HISTORY  3000

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
        GOLD, RED, GREEN, BLUE, PURPLE, YELLOW, WHITE,  PINK
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
            Word asd;
            asd.fontIdx = rand() % MAX_FONTS;
            asd.msgIdx  = rand() % MAX_MESSAGES;
            asd.pos.x   = (float)(rand() % (GetRenderWidth()));
            asd.pos.y   = (float)(rand() % (GetRenderHeight()));
            asd.angle   = (float)(rand() % 90) - 45.0f;
            asd.size    = (float)((rand() % 400) + 20) / 10.0f;
            asd.spacing = (float)(rand() % 7 + 1);
            asd.col     = colors[rand() % MAX_COLOURS];
            history[historyCount++] = asd;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < historyCount; i++) {
                Word *asd = &history[i];
                DrawTextPro(fonts[asd->fontIdx], messages[asd->msgIdx],
                            asd->pos, origin, asd->angle, asd->size, asd->spacing, asd->col);
            }
        EndDrawing();

        if (historyCount == MAX_HISTORY) {
            historyCount = 0;
            ClearBackground(BLACK);
        }
    }

    for (int i = 0; i < MAX_FONTS; i++) UnloadFont(fonts[i]);
    CloseWindow();
    return 0;
}
