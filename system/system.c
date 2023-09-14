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

void system_visible_update(BeComponent *comp)
{
    BeComponentVisibility *cv = (BeComponentVisibility *)comp;
    cv->visible = !cv->visible;
}