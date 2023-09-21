#include <system/component/com_sprite.h>
#include <stdlib.h>
#include <string.h>

#include <utilities/checker.h>

BeSprite *be_sprite_new(BeSpriteType type, u32 numb, f32 *vertexs)
{
    BeSprite *spr = (BeSprite *)malloc(sizeof(BeSprite));
    spr->type = type;
    spr->numb_vertexs = numb;
    spr->offset = 0;
    spr->vertexs = (f32 *)malloc(sizeof(f32) * numb);
    // copy vertex to structure
    memcpy(spr->vertexs, vertexs, sizeof(f32) * numb);

    return spr;
}

void be_sprite_destroy(BeSprite *comp)
{
    NULL_CHECKER(comp);

    NULL_CHECKER(comp->vertexs);

    DESTROYER(comp->vertexs);
    DESTROYER(comp);
}
