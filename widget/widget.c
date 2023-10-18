#include <widget/widget.h>

#include <stdlib.h>
#include <utilities/checker.h>
#include <utilities/log.h>

BeWidget *be_widget_new(BeScene *scene)
{
    BeWidget *widget = be_entity_new();
    BeWidgetType *widget_type = be_widget_type_new(scene);
    BeComponent *widget_component = be_component_new((BeComponentType)BE_WIDGET_TYPE, (void *)widget_type);

    // Add entity to scene
    be_scene_add_entity(scene, widget);

    // Add widget type to entity
    be_entity_add_component(scene, widget, widget_component);

    return widget;
}

void be_widget_destroy(BeScene *scene, BeWidget *widget)
{
    if (NULL == scene)
    {
        LOGE("scene is NULL");
        return;
    }
    if (NULL == widget)
    {
        LOGE("widget is NULL");
        return;
    }
    RETURN_IF_NOT_WIDGET(widget);

    // remove all components of entity and entity from scene
    be_scene_remove_entity(scene, widget);
}

BeComponent *be_widget_get_component(BeScene *scene, const BeWidget *widget, BeComponentType type)
{
    NULL_CHECKER_VAL(scene, NULL);
    NULL_CHECKER_VAL(widget, NULL);

    if (!widget->has_component[type])
    {
        LOGE("\"widget\" does not has component: \"type\"");
        return NULL;
    }

    u32 com_id = widget->component_id[type];
    if (com_id >= scene->numb_component)
    {
        LOGE("\"widget\" is out of length: \"scene->num_component\"");
        return NULL;
    }

    BeComponent *comp = scene->components[com_id];
    return comp;
}

BeWidgetType *be_widget_type_new(BeScene *scene)
{
    LOGI("Create new widget");
    BeWidgetType *widget = (BeWidgetType *)malloc(sizeof(BeWidgetType));
    widget->scene = scene;
    return widget;
}

void be_widget_type_destroy(BeWidgetType *widget)
{
    LOGI("Destroy widget");
    if (NULL == widget)
    {
        return;
    }

    DESTROYER(widget);
}