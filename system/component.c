#include <system/component.h>
#include <stdlib.h>

BeComponent *be_component_new(BeComponentType type, void *component)
{
    BeComponent *comp = malloc(sizeof(BeComponent));
    comp->type = type;
    comp->component = component;
    return comp;
}
void be_component_destroy(BeComponent *component)
{
    free(component->component);
    free(component);
    component = NULL;
}