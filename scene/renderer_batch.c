#include <scene/renderer_batch.h>

#include <stdlib.h>
#include <string.h>

#include <utilities/log.h>
#include <utilities/checker.h>
#include <system/component/com_sprite.h>
// #include <system/system.h>

BeRendererBatch *be_renderer_batch_new()
{
    BeRendererBatch *rnd = (BeRendererBatch *)malloc(sizeof(BeRendererBatch));
    rnd->numb_vertex = 0;
    rnd->vertexs = NULL;
    return rnd;
}
void be_renderer_batch_destroy(BeRendererBatch *renderer)
{
    if (renderer->vertexs)
    {
        free(renderer->vertexs);
        renderer->vertexs = NULL;
    }
    free(renderer);
    renderer = NULL;
}
void be_renderer_batch_add_vertexs(BeRendererBatch *renderer, BeComponent *comp)
{
    NULL_CHECKER(renderer);

    NULL_CHECKER(comp);

    if (BE_COMPONENT_TYPE_SPRITE != comp->type)
    {
        LOGI("Component is not contains vertex");
        return;
    }

    BeSprite *sprite = (BeSprite *)comp->component;

    if (NULL == renderer->vertexs)
    {
        renderer->vertexs = (f32 *)malloc(sizeof(f32) * sprite->numb_vertexs);
    }
    else
    {
        renderer->vertexs = realloc(renderer->vertexs, sizeof(f32) * (renderer->numb_vertex + sprite->numb_vertexs));
    }

    memcpy(&(renderer->vertexs[renderer->numb_vertex]), sprite->vertexs, sizeof(f32) * sprite->numb_vertexs);
    sprite->offset = renderer->numb_vertex;
    renderer->numb_vertex += sprite->numb_vertexs;
}

void be_renderer_batch_update(BeRendererBatch *renderer, BeComponent *comp)
{
    NULL_CHECKER(renderer);
    NULL_CHECKER(comp);

    BeSprite *spr = (BeSprite *)comp->component;

    memcpy(&(renderer->vertexs[spr->offset]), spr->vertexs, sizeof(f32) * spr->numb_vertexs);
}

void be_renderer_batch_remove(BeRendererBatch *renderer, BeComponent *comp)
{
    NULL_CHECKER(renderer);
    NULL_CHECKER(comp);

    BeSprite *spr = (BeSprite *)comp->component;

    NULL_CHECKER(spr->vertexs);

    // temp vertexs;
    u32 offset = spr->offset + spr->numb_vertexs;
    f32 *tmp = (f32 *)malloc(sizeof(f32) * (renderer->numb_vertex - offset));

    // copy to temp
    memcpy(tmp, &(renderer->vertexs[offset]), sizeof(f32) * (renderer->numb_vertex - offset));

    // realloc
    renderer->vertexs = realloc(renderer->vertexs, sizeof(f32) * (renderer->numb_vertex - spr->numb_vertexs));

    // copy back to vertexs
    memcpy(&(renderer->vertexs[spr->offset]), tmp, sizeof(f32) * (renderer->numb_vertex - offset));

    // free temp;
    free(tmp);
    tmp = NULL;
}