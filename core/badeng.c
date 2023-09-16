#include <badeng.h>

#include <stdlib.h>

#include <utilities/log.h>

static BeEngine *be_engine = NULL;

static BeEngine *create_engine()
{
    BeEngine *eng = (BeEngine *)malloc(sizeof(BeEngine));
    eng->numb_entity = 0;
    eng->numb_component = 0;
    eng->cap_component = DEFAULT_COMPONENT_CAPACITY;
    eng->components = NULL;
    eng->system = be_system_new();
    return eng;
}

BeEngine *be_engine_new()
{
    LOGI("Create new engine");
    return be_engine = NULL != be_engine ? be_engine : create_engine();
}

void be_engine_run(BeEngine *engine)
{
    LOGI("start run engine");
}

void be_engine_destroy(BeEngine *engine)
{
    LOGI("Destroy engine");
    if (engine == NULL)
    {
        return;
    }
    if (NULL != engine->components)
    {
        for (u32 i = 0; i < NUMB_COMPONENT; i++)
        {
            free(engine->system.id_slice_component[i]);
        }
    }

    free(engine);
    engine = NULL;
}

void be_engine_add_entity(BeEngine *eng, BeEntity *entity)
{
    LOGI("Create new entity");
    if (NULL == eng)
    {
        LOGE("Failed create Entity because engine is NULL");
        return;
        // add abort here
    }

    if (NULL == entity)
    {
        LOGE("Cannot add component because Entity is NULL");
        return;
    }

    entity->id = eng->numb_entity;

    eng->numb_entity++;
}

void be_engine_add_component(BeEngine *eng, BeEntity *entity, BeComponent *component)
{
    if (NULL == eng)
    {
        LOGE("Cannot add component because Engine is NULL");
        return;
    }

    if (NULL == entity)
    {
        // abort
        LOGE("Cannot add component because Entity is NULL");
        return;
    }

    if (NULL == component)
    {
        // abort;
        LOGE("Cannot add component because component is NULL");
        return;
    }

    // add component id to entity
    if (NULL == entity->component_id)
    {
        entity->component_id = malloc(sizeof(u32) * entity->capacity_component);
    }

    if (entity->numb_component >= entity->capacity_component / 2)
    {
        entity->capacity_component *= 2;
        entity->component_id = realloc(entity->component_id, sizeof(u32) * entity->capacity_component);
        // TODO!! check if need copy to new pointer
    }

    entity->component_id[entity->numb_component] = eng->numb_component;
    entity->numb_component++;

    // add to engine->system
    if (NULL == eng->system.id_slice_component[component->type])
    {
        eng->system.id_slice_component[component->type] = (u32 *)malloc(sizeof(u32) * eng->system.cap_slice_component[component->type]);
    }

    if (eng->system.numb_slice_component[component->type] >= eng->system.cap_slice_component[component->type])
    {
        eng->system.cap_slice_component[component->type] *= 2;
        eng->system.id_slice_component[component->type] = realloc(eng->system.id_slice_component[component->type], sizeof(u32) * eng->system.cap_slice_component[component->type]);
    }

    eng->system.id_slice_component[component->type][eng->system.numb_slice_component[component->type]] = eng->numb_component;
    eng->system.numb_slice_component[component->type]++;

    // add to engine;
    if (be_engine->components == NULL)
    {
        be_engine->components = malloc(sizeof(BeComponent) * eng->cap_component);
    }

    if (eng->numb_component >= eng->cap_component / 2)
    {
        eng->cap_component *= 2;
        be_engine->components = realloc(be_engine->components, sizeof(BeComponent) * eng->cap_component);
        // TODO!! check if need copy to new pointer
    }

    // if handler component is null, then use default
    if (NULL == component->system_handler)
    {
        component->system_handler = default_handler[component->type];
    }

    be_engine->components[eng->numb_component] = component;
    eng->numb_component++;
}

void be_engine_system_update(BeEngine *eng, BeComponentType type)
{
    u32 i = 0;
    for (i = 0; i < eng->system.numb_slice_component[type]; i++)
    {
        //    system->id_slice_component[type][i];
        u32 component_id = eng->system.id_slice_component[type][i];
        switch (type)
        {
        case VISIBILITY:
            eng->components[component_id]->system_handler(eng->components[component_id]);
            // system_visible_update(eng->components[component_id]);
            break;

        default:
            break;
        }
    }
}
