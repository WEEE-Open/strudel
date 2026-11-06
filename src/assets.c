#include "assets.h"
#include "raymedia.h"
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// it takes the module of a random number and return a string
// based on the value obtained, it uses a if-else construct
// to decide the word
static const char *generateMessage(void);

// It will unload all the fonts inside the `FontSet` passed by using the
// `UnloadFont` only on the valid fonts, it will ignore the ones that failed to
// load previously it resets the count of the set at 0 after having freed all of
// the fonts
static void UnloadFontSet(FontSet *fontSet);

const Color COLOURS[MAX_COLOURS] = {
    MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME, GOLD,
    RED,    GREEN,  BLUE,      PURPLE,   YELLOW,     PINK
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
    "resources/MartianMono_Condensed-ExtraBold.ttf",
};

int Initialize() {
    int width = 1280,
        height = 1024;
    InitWindow(width, height, "asdSaver");
    if (!IsWindowReady()) {
        fprintf(stderr, "Failed to create a window...");
        return 1;
    }
    SetTargetFPS(60);
    srand(rand() * rand());
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        fprintf(stderr, "Failed to initialize audio...\n only video will play");
        return 2;
    }
    return 0;
}

FontSet LoadFontSet() {
  FontSet fontSet = {0};
  for (int i = 0; i < MAX_FONTS; i++) {
    if (IsFileExtension(FONT_PATHS[i], ".png")) {fontSet.font[i] = LoadFont(FONT_PATHS[i]);}
    else {fontSet.font[i] = LoadFontEx(FONT_PATHS[i], 256, NULL, 0);}

    if (!IsFontValid(fontSet.font[i])) {TraceLog(LOG_WARNING, "error: FAILED to load font n.%d: %s", i,FONT_PATHS[i]);}
  }
  return fontSet;
}

MediaStream LoadMediaAndCheck(char *videoPath) {
    MediaStream reeeng = LoadMedia(videoPath);
    if(!IsMediaValid(reeeng)) {
        fprintf(stderr, "failed to load the  reeeng video...");
        return (MediaStream) {0};
    }
    SetMediaLooping(reeeng, false);
    return reeeng;
}

void DrawClockOverlay(Font font) {
  char timeBuf[6],
       dateBuf[10];
  time_t seconds_time = time(NULL);
  struct tm *time = localtime(&seconds_time);
  strftime(timeBuf, sizeof(timeBuf), "%H:%M", time);
  strftime(dateBuf, sizeof(dateBuf), "%A", time);

  const int fontSizeInternal = 110, fontSizeExternal = 150;
  int tw = MeasureTextEx(font, timeBuf, fontSizeExternal, 7).x,
      dw = MeasureTextEx(font, dateBuf, fontSizeExternal, 7).x,
      x = GetScreenWidth() / 2 - tw / 2,
      x2 = GetScreenWidth() / 2 - dw / 2,
      y = GetScreenHeight() / 3 * 2;
  Vector2 posExt = {x, y}, origin = {0, 0},
          posInt = {x + 10, y + 22},
          pos2Ext = {x2, y + 120},
          pos2Int = {x2 + 10, y + 145};
  Color colourExternal = GREEN,
        colourInternal = WHITE;

  SetTextLineSpacing(20);
  DrawTextPro(font, timeBuf, posExt,  origin, 0.0, fontSizeExternal, 7, colourExternal);
  DrawTextPro(font, dateBuf, pos2Ext, origin, 0.0, fontSizeExternal, 7, colourExternal);
  SetTextLineSpacing(35);
  DrawTextPro(font, timeBuf, posInt,  origin, 0.0, fontSizeInternal, 27, colourInternal);
  DrawTextPro(font, dateBuf, pos2Int, origin, 0.0, fontSizeInternal, 27, colourInternal);
}

Word generateWord(FontSet *fontSet) {
  Word asd;
  asd.font = fontSet->font[rand() % MAX_FONTS];
  asd.msg = generateMessage();
  asd.pos.x = (float)(rand() % (GetRenderWidth()));
  asd.pos.y = (float)(rand() % (GetRenderHeight()));
  asd.angle = (float)(rand() % 90) - 45.0f;
  asd.size = (float)((rand() % 400) + 20) / 10.0f;
  asd.spacing = (float)(rand() % 7 + 1);
  asd.col = COLOURS[rand() % MAX_COLOURS];
  return asd;
}

static const char *generateMessage(void) {
  char *asd;

  int val = rand() % 100;
  if (val == 4)                         {asd = "4";}
  else if (val < 10)                    {asd = "WEEE Open";}
  else if (val == 11)                   {asd = "LoL";}
  else if (val == 12)                   {asd = "FULL BRIDGE RECTIFIER";}
  else if (val < 30 && (val % 3) == 0)  {asd = "Debian";}
  else if (val < 30 && (val % 3) == 1)  {asd = "Arch BTW";}
  else if (val < 30 && (val % 3) == 2)  {asd = "WEEEbian";}
  else if (val < 35)                    {asd = "MicroSlop";}
  else {asd = "asd";}

  return asd;
}

void UnloadFontSet(FontSet *fontSet) {
  for (int i = 0; i < MAX_FONTS; i++) {
    if (IsFontValid(fontSet->font[i])) {UnloadFont(fontSet->font[i]);}
  }
}

void DeinitializeAll(FontSet *fontSet, Image icon, Texture2D background, MediaStream mp4) {
    CloseAudioDevice();
    UnloadFontSet(fontSet);
    UnloadImage(icon);
    UnloadMedia(&mp4);
    UnloadTexture(background);
    CloseWindow();
}
