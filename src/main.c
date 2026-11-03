
//#standard library installed on the machine + raylib
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

// written modules
#include "assets.h" // to write on the display
#include "giffer.h" // to play the gif
#include"socket_wrapper.h" // to communicate with the socket

static bool ring_trigger = false;

const Vector2 ORIGIN = { 0, 0 };

int main(void) {

    // initialization of the window, set fps target and generate a random seed
    int width = 1280, height = 1024;
    InitWindow(width, height, "asdSaver");
    if (!IsWindowReady()) {
        fprintf(stderr, "Failed to create a window...");
        return 1;
    }
    SetTargetFPS(60);
    srand((unsigned)GetTime());

    Image icon = LoadImage("images/icon.png");
    Image bg = LoadImage("images/background.png");
    SetWindowIcon(icon);
    Texture2D background = LoadTextureFromImage(bg);
    UnloadImage(bg);

    // initialization of all the fonts and of the initial gif
    FontSet fontSet = LoadFontSet();
    GifPlayer *reeeng = GifPlayerLoad("images/gifs/ne-scendere-ne-salire.gif");
    if(reeeng) {
        GifPlayerSetFrameTime(reeeng, 0.10f);
        GifPlayerSetDuration(reeeng, 5.0);
    }

    sio_client_handle *sock = sio_client_create("");
    sio_client_on_event(sock, "weeetofono", &ring_trigger);

    // initialization of buffer for words and counter, time of the last drawn word and the counter origin point
    static Word history[MAX_HISTORY];
    int   historyCount = 0;

    double lastDraw  = GetTime();
    double nextInterval = ((double)(rand()%29) + 1.0)/10;

    bool test = 1;
    HideCursor();

    // loop, it closes the windows if `Esc` or the close button is pressed
    while (!WindowShouldClose()) {

        double now = GetTime();

        // if there is still space in the buffer it creates a new word using random values
        // muduled on the max value of each field
        if (now - lastDraw >= nextInterval && historyCount < MAX_HISTORY) {
            lastDraw = now;
            Word asd;
            asd = generateWord(&fontSet);
            history[historyCount++] = asd;
            nextInterval = ((double) (rand() % 29) + 1.0) / 10;
        }

        if (/*__atomic_exchange_n(&ring_trigger, false, __ATOMIC_SEQ_CST)*/ test) {
            GifPlayerTriggerAt(reeeng, 38);
            test = 0;
        }

        GifPlayerUpdate(reeeng, GetFrameTime());
        // start to draw on a black screen the word with all the defined parameters
        BeginDrawing();
            ClearBackground(BLACK);

            Rectangle src = {0, 0, (float)background.width, (float)background.height};
            Rectangle dst = {0, 0, (float)width, (float)height};
            DrawTexturePro(background, src, dst, ORIGIN,0.0f, WHITE);

            for (int i = 0; i < historyCount; i++) {
                Word *asd = &history[i];
                DrawTextPro(asd->font, asd->msg, asd->pos, ORIGIN, asd->angle, asd->size, asd->spacing, asd->col);
            }

            DrawClockOverlay(fontSet.font[6]);

            GifPlayerDraw(reeeng, (Rectangle){0, 0, (float) width, (float) height});
        EndDrawing();

        // in case we have filled the buffer, we set back the counter at 0 to restart and clean the screen
        if (historyCount == MAX_HISTORY) {
            historyCount = 0;
        }
    }

    sio_client_destroy(sock);

    UnloadFontSet(&fontSet);
    UnloadImage(icon);
    //UnloadImage(bg);
    UnloadTexture(background);
    GifPlayerUnload(reeeng);
    CloseWindow();
    return 0;
}
