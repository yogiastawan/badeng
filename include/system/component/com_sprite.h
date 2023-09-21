#ifndef GIHEX_COM_SPRITE_H
#define GIHEX_COM_SPRITE_H

#include <utilities/mangle.h>

#ifdef __cplusplus
extern C
{
#endif

    typedef enum _be_sprite_type BeSpriteType;

    enum _be_sprite_type
    {
        BE_SPRITE_2D,
        BE_SPRITE_3D
    };

    typedef struct _be_sprite BeSprite;

    struct _be_sprite
    {
        BeSpriteType type;
        u32 numb_vertexs;
        f32 *vertexs;
        u32 offset;
    };

    BeSprite *be_sprite_new(BeSpriteType type, u32 numb, f32 * vertexs);
    void be_sprite_destroy(BeSprite *comp);

#ifdef __cplusplus
}
#endif

#endif/* GIHEX_COM_SPRITE_H */
