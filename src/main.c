#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"

// video library for raylib
#include "raymedia.h"

// written modules
#include "assets.h" // to write on the display
#include"socket_wrapper.h" // to communicate with the socket (c++)

static bool ring_trigger = false;

const Vector2 ORIGIN = { 0, 0 };

int main(void) {
    // initialization of the window and audio,
    // set fps target, generate a random seed
    int isInitialized = Initialize();
    if (isInitialized == 1) {return 1;}

    // load icon image
    Image icon = LoadImage("images/icon.png");
    SetWindowIcon(icon);

    // load of background image, it can be unloaded
    // immediately after loadin the texture
    Image bg = LoadImage("images/background.png");
    Texture2D background = LoadTextureFromImage(bg);
    UnloadImage(bg);

    // initialization of all the fonts and ring
    FontSet fontSet = LoadFontSet();
    MediaStream reeeng = LoadMediaAndCheck("video/slap.webm");
    if (!IsMediaValid(reeeng)) {return 1;}

    // creation of socket to listen the weeetofono
    sio_client_handle *sock = sio_client_create("");
    sio_client_on_event(sock, "weeetofono", &ring_trigger);

    // initialization of buffer for words and counter,
    // time of the last drawn word and the counter origin point
    static Word history[MAX_HISTORY];
    int historyCount = 0;

    double lastDraw  = GetTime(),
    nextInterval = ((double)(rand()%29) + 1.0)/10;

    bool test = 0;

    HideCursor();

    // initialize the background dimensions
    Rectangle src = {0, 0, (float)background.width, (float)background.height};
    Rectangle dst = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

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

        if (/*__atomic_exchange_n(&ring_trigger, false, __ATOMIC_SEQ_CST)*/ test) {UpdateMedia(&reeeng);}

        // start to draw on a black screen the word with all the defined parameters
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(background, src, dst, ORIGIN,0.0f, WHITE);

            for (int i = 0; i < historyCount; i++) {
                Word *asd = &history[i];
                DrawTextPro(asd->font, asd->msg, asd->pos, ORIGIN, asd->angle, asd->size, asd->spacing, asd->col);
            }

            DrawClockOverlay(fontSet.font[12]);

            if (GetMediaState(reeeng) == MEDIA_STATE_STOPPED) {test = 0;}
            else if (test == 1) {
                Rectangle vidSrc = {0, 0, (float) reeeng.videoTexture.width, (float) reeeng.videoTexture.height};
                DrawTexturePro(reeeng.videoTexture, vidSrc, dst, ORIGIN, 0, WHITE);
            }
        EndDrawing();

        // in case we have filled the buffer, we set back the counter at 0 to restart and clean the screen
        if (historyCount == MAX_HISTORY) {historyCount = 0;}
    }

    sio_client_destroy(sock);
    DeinitializeAll(&fontSet, icon, background, reeeng);
    return 0;
}
