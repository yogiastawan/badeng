#include <widget/widget.h>

#include <stdlib.h>
#include <utilities/checker.h>
#include <utilities/log.h>


BeWidget *be_widget_new(BeScene*scene){
    LOGI("Create new widget");
    BeWidget *widget=(BeWidget*)malloc(sizeof(BeWidget));
    widget->scene=scene;
    BeEntity *entity=be_entity_new();
    be_scene_add_entity(widget->scene,entity);
    widget->entity_id=entity->id;
    return widget;
}

void be_widget_destroy(BeWidget*widget){
    LOGI("Destroy widget");
    if(NULL==widget){
        return;
    }
    
    be_scene_remove_entity(widget->scene,widget->scene->entities[widget->entity_id]);
    
    DESTROYER(widget);
}