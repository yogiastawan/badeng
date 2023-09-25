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

BeWidgetParent* be_widget_parent_new(u32 parent_id){
    BeWidgetParent* prn=(BeWidgetParent*)malloc(sizeof(BeWidgetParent));
    
    prn->parent_id=parent_id;
    
    return prn;
}izeof(u32)*wdgt->cap_child);
        wdgt->temp_child_entities=(BeEntity*)malloc(sizeof(BeEntity*)*wdgt->cap_child);
    }
    
    if(wdgt->numb_child>=wdgt->cap_child){
        wdgt->cap_child*=2;
        wdgt->childs=realloc(wdgt->childs, sizeof(u32)*wdgt->cap_child);
        wdgt->temp_child_entities=realloc(wdgt->temp_child_entities,sizeof(BeEntity*)*wdgt->childs);
    }
    
    entity->id=wdgt->numb_child;
    
    wdgt->childs[wdgt->numb_child]=entity->id;
    wdgt->temp_child_entities[wdgt->numb_child]=entity;
    
    wdgt->numb_child++;
}

