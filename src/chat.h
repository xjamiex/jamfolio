#ifndef CHAT_H
#define CHAT_H

#define MAX_LINE_COUNT 10

#include "raylib.h"
#include "character.h"

typedef struct {
    Texture tex;
    character_t character;

    bool open;
    int sen_index;
} chat_t;

typedef struct {
    const char **text;
    int length;
} dialogue_t;

void draw_chat(chat_t chat, const char *dialogue[], Font font, float x, float y, int size, int spacing);
void open_chat(chat_t chat, character_t character);

#endif // !CHAT_H
