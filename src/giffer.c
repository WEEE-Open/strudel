#include "giffer.h"
#include <stdlib.h>

// custom type to simplify the gif playing procedure
// it contains all the values needed to raylib to play a gif
struct GifPlayer {
    Image     image;
    Texture2D texture;
    int       frameCount;
    int       currentFrame;
    float     frameTime;
    float     accumulator;
    double    startTime;
    double    duration;
    bool      playing;
};

// function to load the used gif in memory, it gives it a framerate and all the values needed
GifPlayer *GifPlayerLoad(const char *path) {
    int frames = 0;
    Image img = LoadImageAnim(path, &frames);
    if (img.data == NULL || frames <= 0) {
        TraceLog(LOG_WARNING, "GIF: failed to load %s", path);
        return NULL;
    }

    GifPlayer *p = calloc(1, sizeof(*p));
    if (!p) { UnloadImage(img); return NULL; }

    p->image      = img;
    p->frameCount = frames;
    p->texture    = LoadTextureFromImage(img);
    p->frameTime  = 0.10f;
    p->duration   = 0.0;
    return p;
}

// function to say to the caller that the gif is starting to play at a custom starting point
void GifPlayerTriggerAt(GifPlayer *p, int startFrame) {
    if (!p || p->frameCount <= 0) return;

    p->playing      = true;
    // modulo handles startFrame >= frameCount and negatives cleanly
    p->currentFrame = ((startFrame % p->frameCount) + p->frameCount) % p->frameCount;
    p->accumulator  = 0.0f;
    p->startTime    = GetTime();

    // upload the chosen frame immediately so frame 0 isn't shown for one tick
    unsigned int offset = (unsigned int)p->image.width
                        * p->image.height * 4 * p->currentFrame;
    UpdateTexture(p->texture, ((unsigned char *)p->image.data) + offset);
}

// function to say to the caller that the gif is starting to play
void GifPlayerTrigger(GifPlayer *p) {
    GifPlayerTriggerAt(p, 0);
}

// update the gif, going to the next frame
void GifPlayerUpdate(GifPlayer *p, float dt) {
    if (!p || !p->playing) return;

    p->accumulator += dt;
    while (p->accumulator >= p->frameTime) {
        p->accumulator -= p->frameTime;
        p->currentFrame = (p->currentFrame + 1) % p->frameCount;

        unsigned int offset = (unsigned int)p->image.width
                            * p->image.height * 4 * p->currentFrame;
        UpdateTexture(p->texture, ((unsigned char *)p->image.data) + offset);
    }

    if (p->duration > 0.0 && (GetTime() - p->startTime) >= p->duration) {
        p->playing = false;
    }
}

// draw the current gif frame
void GifPlayerDraw(GifPlayer *p, Rectangle dst) {
    if (!p || !p->playing) return;
    Rectangle src = { 0, 0, (float)p->texture.width, (float)p->texture.height };
    DrawTexturePro(p->texture, src, dst, (Vector2){ 0, 0 }, 0.0f, WHITE);
}

// return simply if the gif is playing or not
bool GifPlayerIsPlaying(const GifPlayer *p) { return p && p->playing; }

// function to set framerate, unless the display will ever be changed, just set it to 60fps
void GifPlayerSetFrameTime(GifPlayer *p, float seconds) {
    if (p && seconds > 0.0f) p->frameTime = seconds;
}

// sets the duration of the gif, to use only once if there is 1 gif, to re-use
// multiple times in case the grillo will ever support multiple rings
void GifPlayerSetDuration(GifPlayer *p, double seconds) {
    if (p) p->duration = seconds;
}

// function to unload the gif
void GifPlayerUnload(GifPlayer *p) {
    if (!p) return;
    UnloadTexture(p->texture);
    UnloadImage(p->image);
    free(p);
}
