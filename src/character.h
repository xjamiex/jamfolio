#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include <math.h>
#include <stdio.h>

typedef struct {
    char *name;
    Vector2 position;
    Texture texture;
    Texture portrait;

    float animation_length;

    int dialogue_length;

    Rectangle collision;
    int hovered;
    
    float animation_timer;
    Vector2 origin;
    
} character_t;

void draw_character(character_t c);
void check_hovered(character_t *c);
void update_yippee(character_t *c, float height);

Rectangle calculate_collision(character_t c, float clip_l, float clip_r, float clip_t, float clip_b);

#endif // CHARACTER_H

