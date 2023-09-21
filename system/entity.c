#include <system/entity.h>

#include <stdlib.h>

#include <utilities/checker.h>

BeEntity *be_entity_new()
{
    BeEntity *entt = (BeEntity *)malloc(sizeof(BeEntity));
    entt->id = 0;
    u32 i = 0;
    for (i = 0; i < NUMB_COMPONENT; i++)
    {
        entt->component_id[i] = 0;
        entt->has_component[i] = false;
    }

    return entt;
}

void be_entity_destroy(BeEntity *entt)
{
    if (NULL == entt)
    {
        return;
    }
    DESTROYER(entt);
}