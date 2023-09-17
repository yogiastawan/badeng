#ifndef GIHEX_RENDERER_BATCH_H
#define GIHEX_RENDERER_BATCH_H

#include <utilities/mangle.h>
#include <system/component.h>

#ifdef __cplusplus
extern C
{
#endif

    typedef struct _be_renderer_batch BeRendererBatch;

    struct _be_renderer_batch
    {
        f32 *vertexs;
        u64 numb_vertex;
    };

    BeRendererBatch *be_renderer_batch_new();

    void be_renderer_batch_destroy(BeRendererBatch * renderer);

    void be_renderer_batch_add_vertexs(BeRendererBatch * renderer, BeComponent * comp);

    void be_renderer_batch_update(BeRendererBatch * renderer, BeComponent * comp);

    void be_renderer_batch_remove(BeRendererBatch * renderer, BeComponent * comp);

    void be_renderer_batch_render(BeRendererBatch * renderer);

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_RENDERER_BATCH_H */
