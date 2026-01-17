#include "character.h"

void draw_character(character_t c) {
    float frame_size = c.texture.width / 2;

    DrawTextureRec(
        c.texture,
        (Rectangle) {frame_size * c.hovered, 0, frame_size * (c.hovered + 1), c.texture.height},
        c.position,
        WHITE
    );
}

void check_hovered(character_t *c) {
    bool collided = CheckCollisionPointRec(
        GetMousePosition(),
        c -> collision
    );

    c -> hovered = collided;

    if (collided) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            c -> animation_timer = 0;
        }
    }
} 

Rectangle calculate_collision(
    character_t c,
    float clip_l, float clip_r, float clip_t, float clip_b
) {
    return (Rectangle) {
        c.position.x + clip_l,
        c.position.y + clip_t,
        c.texture.width / 2 - clip_r,
        c.texture.height - clip_b
    };
}

void update_yippee(character_t *c, float height) {
    c -> position.y = c -> origin.y - fmax(0, (-0.03) * pow(c -> animation_timer - (c -> animation_length / 2), 2) + height);
    c -> animation_timer > c -> animation_length ?
        c -> animation_timer : c -> animation_timer++;
}

