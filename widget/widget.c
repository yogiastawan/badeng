#include <widget/widget.h>

#include <stdlib.h>
#include <utilities/checker.h>

BeWidgetChild* be_widget_child_new(){
    BeWidgetChild* wdg=(BeWidgetChild*)malloc(sizeof(BeWidgetChild));
    wdg->numb_child=0;
    wdg->cap_child=DEFAULT_CHILD_CAPACITY;
    wdg->childs=NULL;
    wdg->temp_child_entities=NULL;
    
    return wdg;
}

void be_widget_child_destroy(BeWidgetChild* widget){
    if(NULL==widget){
        return;
    }
    
    if(widget->childs){
        DESTROYER(widget->childs);
    }
    
    if(widget->temp_child_entities){
        DESTROYER(widget->temp_child_entities)
    }
    
    DESTROYER(widget);
}
