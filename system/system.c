#include <system/system.h>

#include <stdlib.h>
#include <string.h>

#include <system/entity.h>
#include <utilities/checker.h>

BeSystem *be_system_new()
{
    BeSystem *b = (BeSystem *)malloc(sizeof(BeSystem));
    u32 i;
    for (i = 0; i < NUMB_COMPONENT; i++)
    {
        b->cap_slice_component[i] = DEFAULT_COMPONENT_CAPACITY;
        b->numb_slice_component[i] = 0;
        b->id_slice_component[i] = NULL;
    }
    return b;
}

void be_system_destroy(BeSystem *system)
{
    u32 i = 0;
    for (i = 0; i < NUMB_COMPONENT; i++)
    {
        free(system->id_slice_component[i]);
        system->id_slice_component[i] = NULL;
    }
    DESTROYER(system);
}

void be_system_remove_component(BeSystem *system, BeComponent *comp)
{
    if (comp->index_in_system >= system->numb_slice_component[comp->type])
    {
        ASSOIATED_FAILED(comp, system);
    }

    // update system
    u32 offset = comp->index_in_system + 1; // 1 is range
    if (offset == system->numb_slice_component[comp->type])
    {
        system->numb_slice_component[comp->type]--;
        system->id_slice_component[comp->type][comp->index_in_system] = 0;
        return;
    }

    u32 size_pack = system->numb_slice_component[comp->type] - offset;
    u32 *tmp = (u32 *)malloc(sizeof(u32) * size_pack);
    // copy from system to tmp;
    memcpy(tmp, &(system->id_slice_component[comp->type][offset]), sizeof(u32) * size_pack);
    // realloc
    system->numb_slice_component[comp->type]--;
    if (system->numb_slice_component[comp->type] < system->cap_slice_component[comp->type] / 2)
    {
        system->cap_slice_component[comp->type] = system->cap_slice_component[comp->type] / 2;
        system->id_slice_component[comp->type] = realloc(system->id_slice_component[comp->type], sizeof(u32) * system->cap_slice_component[comp->type]);
    }

    // copy back to system
    memcpy(&(system->id_slice_component[comp->type][comp->index_in_system]), tmp, sizeof(u32) * (size_pack + 1));
    DESTROYER(tmp);
}

BeComponentHandler be_system_get_default_handler(BeComponentType type)
{
    static BeComponentHandler default_handler[NUMB_COMPONENT] = {
        system_visible_update,
        0};
    return default_handler[type];
}

void system_visible_update(BeComponent *comp)
{
    BeComponentVisibility *cv = (BeComponentVisibility *)comp->component;
    cv->visible = !cv->visible;
}