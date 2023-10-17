#include <widget/widget.h>

#include <stdlib.h>
#include <utilities/checker.h>
#include <utilities/log.h>


BeWidgetType *be_widget_type_new(BeScene*scene){
    LOGI("Create new widget");
    BeWidgetType *widget=(BeWidgetType*)malloc(sizeof(BeWidgetType));
    widget->scene=scene;
    return widget;
}

void be_widget_type_destroy(BeWidgetType*widget){
    LOGI("Destroy widget");
    if(NULL==widget){
        return;
    }
    
    DESTROYER(widget);
}