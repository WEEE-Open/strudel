#ifndef GIFFER_H
#define GIFFER_H

#include "raylib.h"

typedef struct GifPlayer GifPlayer;   // opaque

GifPlayer *GifPlayerLoad(const char *path);
void       GifPlayerTrigger(GifPlayer *p);                      // start from frame 0
void       GifPlayerTriggerAt(GifPlayer *p, int startFrame);    // start from a custom frame
void       GifPlayerUpdate(GifPlayer *p, float dt);             // call every frame
void       GifPlayerDraw(GifPlayer *p, Rectangle dst);          // call inside BeginDrawing
bool       GifPlayerIsPlaying(const GifPlayer *p);
void       GifPlayerUnload(GifPlayer *p);

// Optional tunables
void       GifPlayerSetFrameTime(GifPlayer *p, float seconds);  // default 0.10 s
void       GifPlayerSetDuration(GifPlayer *p, double seconds);  // 0.0 = loop forever

#endif
