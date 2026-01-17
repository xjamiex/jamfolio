#include "raylib.h"
#include "character.h"
#include "chat.h"
#include <math.h>
#include <emscripten/emscripten.h>

const int screen_width = 480;
const int screen_height = 360;

Texture bg_tex;
Texture cursor_tex;
Texture chat_tex;

character_t jane;
character_t fae;

chat_t chat;

Font bbt_font;

void draw_frame(void);
void update_frame(void);
void load(void);

const char *jane_dialogue[] = {
    "Oh, sup.",
    "I'm Jane, I guess...",
    "At least that's what they call me.",
    "The wounds? well...",
    "Long story really.",
    "Same with my face.",
    "Oh don't worry im not in pain.",
    "That over there is my wife.",
    "Go ask her I guess..."
};

int main(void) {
    InitWindow(screen_width, screen_height, "jamfolio");

    //init textures
    load();
    emscripten_set_main_loop(update_frame, 0, 1);
   
    //Unload stuff
    UnloadTexture(bg_tex);
    UnloadTexture(cursor_tex);
    UnloadTexture(chat_tex);
    UnloadFont(bbt_font);
    UnloadTexture(jane.texture);
    UnloadTexture(jane.portrait);
    UnloadTexture(fae.texture);
    CloseWindow();
    return 0;
}

void load(void){
    bg_tex = LoadTexture("resources/bg.png");
    cursor_tex = LoadTexture("resources/cursor.png");

    bbt_font = LoadFont("resources/fonts/bigblue_terminal.TTF");

    jane = (character_t) {
        "jane",
        (Vector2) {145, 67},
        LoadTexture("resources/jane.png"),
        LoadTexture("resources/jane_portrait.png"),
        50, 9 
    };

    //debug
    fae = (character_t) {
        "fae",
        (Vector2) {285, 134},
        LoadTexture("resources/fae.png"),
        LoadTexture("resources/fae.png"),
        50, 1 
    };

    chat = (chat_t) {
        LoadTexture("resources/chat_ui.png"), jane, false, 0
    };

    jane.origin = jane.position;
    fae.origin = fae.position;

    //load char collision boxes
    jane.collision = calculate_collision(jane, 10, 40, 10, 10);
    fae.collision = calculate_collision(fae, 80, 122, 20, 30);
}

void update_frame(void) {
    check_hovered(&jane);
    check_hovered(&fae);

    if (jane.hovered) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            chat.character = jane;
            chat.open = true;
        }
    }

    if (fae.hovered) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            chat.character = fae;
            chat.open = true;
        }
    }
    
    if (chat.open) {
        if (IsKeyPressed(KEY_ENTER)) {
            chat.sen_index++;
            if (chat.sen_index >= chat.character.dialogue_length) {
                chat.open = false;
                chat.sen_index = 0;
            }
        }
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        chat.open = false;
    }

    //update position of characters in case of jumping  
    update_yippee(&jane, 30); 
    update_yippee(&fae, 30);

    HideCursor();
    draw_frame();
}

void draw_frame(void) {
    BeginDrawing();
    ClearBackground(BLACK);
   
    DrawTexture(bg_tex, 0, 0, WHITE);
    
    //DrawRectangleRec(jane_collision, RED);
    draw_character(jane);
    draw_character(fae);
    
    if (chat.open) {
        draw_chat(chat, jane_dialogue, bbt_font, 5, screen_height - 90, 12, 1);
    }

    //draw cursor
    DrawTexture(cursor_tex, GetMousePosition().x, GetMousePosition().y, WHITE);

    EndDrawing();
}
