#include <scene/scene.h>

#include <utilities/checker.h>

static void be_scene_remove_component(BeScene *scene, BeComponent *comp);

static void be_scene_remove_component(BeScene *scene, BeComponent *comp)
{
    NULL_CHECKER(scene);
    NULL_CHECKER(comp);
    // update scene
    u32 offset = comp->id + 1;
    if (offset == scene->numb_component)
    {
        scene->numb_component--;
        scene->components[comp->id] = NULL;
        return;
    }

    u32 size_pack = scene->numb_component - offset;
    BeComponent *temp = (BeComponent *)malloc(sizeof(BeComponent) * size_pack);
    // copy from scene to temp
    memcpy(temp, &(scene->components[offset]), sizeof(BeComponent) * size_pack);
    // realloc
    scene->numb_component--;
    if (scene->numb_component < scene->cap_component / 2)
    {
        scene->cap_component = scene->cap_component / 2;
        scene->components = realloc(scene->components, sizeof(BeComponent) * scene->cap_component);
    }

    // copy back to scene
    memcpy(&(scene->components[comp->id]), temp, sizeof(BeComponent) * (size_pack));
    DESTROYER(temp);
}

BeScene *be_scene_new(i32 width, i32 height)
{
    BeScene *sc = (BeScene *)malloc(sizeof(BeScene));
    sc->numb_entity = 0;
    sc->cap_entity = DEFAULT_COMPONENT_CAPACITY;
    sc->entities = NULL;
    sc->numb_component = 0;
    sc->cap_component = DEFAULT_COMPONENT_CAPACITY;
    sc->components = NULL;
    sc->system = be_system_new();
    sc->vertex_batch = be_renderer_batch_new();
    sc->width = width;
    sc->height = height;
    return sc;
}

void be_scene_destroy(BeScene *scene, BeSceneChoice choice)
{
    if (NULL == scene)
    {
        return;
    }

    be_system_destroy(scene->system);
    be_renderer_batch_destroy(scene->vertex_batch);
    if (BE_SCENE_CHOICE_COMPONENT && choice)
    {
        u32 i = 0;
        for (i = 0; i < scene->numb_component; i++)
        {
            be_component_destroy(scene->components[i]);
        }
    }

    if (BE_SCENE_CHOICE_ENTITY && choice)
    {
        u32 i = 0;
        for (i = 0; i < scene->numb_entity; i++)
        {
            be_entity_destroy(scene->entities[i]);
        }
    }

    DESTROYER(scene->components);
    DESTROYER(scene->entities);
    DESTROYER(scene);
}

void be_scene_add_entity(BeScene *scene, BeEntity *entity)
{
    LOGI("Create new scene");
    NULL_CHECKER(scene);
    NULL_CHECKER(entity);

    if (NULL == scene->entities)
    {
        scene->entities = malloc(sizeof(BeEntity *) * scene->cap_entity);
    }

    if (scene->numb_entity >= scene->cap_entity)
    {
        scene->cap_entity *= 2;
        scene->entities = realloc(scene->entities, sizeof(BeScene *) * scene->cap_entity);
    }

    entity->id = scene->numb_entity;
    scene->entities[scene->numb_entity] = entity;
    scene->numb_entity++;
}

void be_scene_remove_entity(BeScene *scene, BeEntity *entity)
{
    NULL_CHECKER(scene);
    NULL_CHECKER(entity);
    if (entity->id >= scene->numb_entity)
    {
        ASSOIATED_FAILED(entity, scene);
    }

    u32 i = 0;
    for (i = 0; i < NUMB_TYPE_COMPONENT; i++)
    {
        if (!entity->has_component[i])
        {
            continue;
        }

        u32 c_id = entity->component_id[i];
        BeComponent *comp = scene->components[c_id];
        // update system
        be_system_remove_component(scene->system, comp);
        // update renderer
        switch (comp->type)
        {
        case BE_COMPONENT_TYPE_SPRITE:
            be_renderer_batch_remove(scene->vertex_batch, comp);
            break;

        default:
            break;
        }
        // update scene
        be_scene_remove_component(scene, comp);
        be_component_destroy(comp);
    }
    be_entity_destroy(entity);
}

void be_entity_add_component(BeScene *scene, BeEntity *entity, BeComponent *component)
{
    NULL_CHECKER(scene);
    NULL_CHECKER(entity);
    NULL_CHECKER(component);

    // Add to entity
    component->entity_id = entity->id;
    entity->component_id[component->type] = scene->numb_component;
    entity->has_component[component->type] = true;

    // Add to scene->system
    if (NULL == scene->system->id_slice_component[component->type])
    {
        scene->system->id_slice_component[component->type] = (u32 *)malloc(sizeof(u32) * scene->system->cap_slice_component[component->type]);
    }

    if (scene->system->numb_slice_component[component->type] >= scene->system->cap_slice_component[component->type])
    {
        scene->system->cap_slice_component[component->type] *= 2;
        scene->system->id_slice_component[component->type] = realloc(scene->system->id_slice_component[component->type], sizeof(u32) * scene->system->cap_slice_component[component->type]);
    }

    scene->system->id_slice_component[component->type][scene->system->numb_slice_component[component->type]] = scene->numb_component;
    component->index_in_system = scene->system->numb_slice_component[component->type];
    scene->system->numb_slice_component[component->type]++;

    // Add to scene
    if (NULL == scene->components)
    {
        scene->components = malloc(sizeof(BeComponent *) * scene->cap_component);
    }

    if (scene->numb_component >= scene->cap_component / 2)
    {
        scene->cap_component *= 2;
        scene->components = realloc(scene->components, sizeof(BeComponent *) * scene->cap_component);
    }

    // if handler component is null, then use default
    if (NULL == component->system_handler)
    {
        component->system_handler = be_system_get_default_handler(component->type);
    }

    scene->components[scene->numb_component] = component;
    component->id = scene->numb_component;
    scene->numb_component++;
}

void be_entity_remove_component(BeScene *scene, BeComponent *comp)
{
    NULL_CHECKER(scene);
    NULL_CHECKER(scene->components);
    NULL_CHECKER(comp);

    if (comp->id >= scene->numb_component)
    {
        ASSOIATED_FAILED(comp, scene);
    }

    if (comp->entity_id >= scene->numb_entity)
    {
        ASSOIATED_FAILED(scene->entities[comp->entity_id], scene);
    }

    // update entity
    BeEntity *entity = scene->entities[comp->entity_id];
    entity->component_id[comp->type] = 0;
    entity->has_component[comp->type] = false;

    // update system
    be_system_remove_component(scene->system, comp);

    // update renderer
    switch (comp->type)
    {
    case BE_COMPONENT_TYPE_SPRITE:
        be_renderer_batch_remove(scene->vertex_batch, comp);
        break;

    default:
        break;
    }

    // update scene
    be_scene_remove_component(scene, comp);

    comp->id = 0;
    comp->index_in_system = 0;
}

void be_scene_system_update(BeScene *scene, BeComponentType type)
{
    NULL_CHECKER(scene);
    u32 i = 0;
    for (i = 0; i < scene->system->numb_slice_component[type]; i++)
    {
        u32 c_id = scene->system->id_slice_component[type][i];

        scene->components[c_id]->system_handler(scene->components[c_id]);

        // switch (type)
        // {
        // case BE_COMPONENT_TYPE_VISIBILITY:
        //     /* code */
        //     break;

        // default:
        //     break;
        // }
    }
}

void be_scene_draw(BeScene *scene)
{
    NULL_CHECKER(scene);
}