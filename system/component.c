#include <system/component.h>

#include <stdlib.h>

#include <utilities/checker.h>

BeComponent *be_component_new(BeComponentType type, void *component)
{
    BeComponent *comp = malloc(sizeof(BeComponent));
    comp->id = 0;
    comp->type = type;
    comp->component = component;
    comp->system_handler = NULL;
    comp->index_in_system = 0;
    return comp;
}
void be_component_destroy(BeComponent *component)
{
    if (NULL == component)
    {
        LOGI("Component is NULL");
        return;
    }

    DESTROYER(component);
}
void be_component_set_system_handler(BeComponent *component, BeComponentHandler handler)
{
    component->system_handler = handler;
}