#include <system/entity.h>
#include <stdlib.h>

BeEntity be_entity_new()
{
    BeEntity entt = {0, 0, DEFAULT_COMPONENT_CAPACITY, NULL};
    return entt;
}