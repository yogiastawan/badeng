#include <widget/widget.h>

#include <stdlib.h>
#include <utilities/checker.h>
#include <utilities/log.h>


BeWidget *be_widget_new(BeScene*scene){
    LOGI("Create new widget");
    BeWidget *widget=(BeWidget*)malloc(sizeof(BeWidget));
    widget->scene=scene;
    widget->entity=be_entity_new();
    be_scene_add_entity(widget->scene,widget->entity);
    return widget;
}

void be_widget_destroy(BeWidget*widget){
    LOGI("Destroy widget");
    if(NULL==widget){
        return;
    }
    
    be_scene_remove_entity(widget->scene,widget->entity);
    
    if(widget->entity){
        DESTROYER(widget->entity);
    }
    
    DESTROYER(widget);
}