#include <system/system.h>
#include <stdlib.h>

BeSystem be_system_new()
{
    BeSystem b;
    u32 i;
    for (i = 0; i < NUMB_COMPONENT; i++)
    {
        b.cap_slice_component[i] = DEFAULT_COMPONENT_CAPACITY;
        b.numb_slice_component[i] = 0;
        b.id_slice_component[i] = NULL;
    }
    return b;
}

BeComponentHandler be_system_get_default_handler(BeComponentType type)
{
    static BeComponentHandler default_handler[NUMB_COMPONENT] = {system_visible_update, 0};
    return default_handler[type];
}

void system_visible_update(BeComponent *comp)
{
    BeComponentVisibility *cv = (BeComponentVisibility *)comp->component;
    cv->visible = !cv->visible;
}