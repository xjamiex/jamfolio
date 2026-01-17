#include "chat.h"

void draw_chat(chat_t chat, const char *dialogue[], Font font, float x, float y, int size, int spacing) {
    DrawTexture(chat.character.portrait, 0, 0, WHITE);
    DrawTexture(chat.tex, 0, 0, WHITE); 
    DrawTextEx(
        font, dialogue[chat.sen_index],
        (Vector2) {
            x, y 
        }, size, spacing, WHITE 
    );
}
