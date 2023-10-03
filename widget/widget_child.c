#include<widget/widget_child.h>

#include<string.h>

#include<widget/widget_parent.h>

BeWidgetChild* be_widget_child_new(){
    BeWidgetChild* wdg=(BeWidgetChild*)malloc(sizeof(BeWidgetChild));
    wdg->numb_child=0;
    wdg->cap_child=DEFAULT_CHILD_CAPACITY;
    wdg->childs=NULL;
    
    return wdg;
}

void be_widget_child_destroy(BeWidgetChild* widget){
    if(NULL==widget){
        return;
    }
    
    if(widget->childs){
        DESTROYER(widget->childs);
    }
    
    DESTROYER(widget);
}

void be_widget_add_child(BeWidget *widget, BeWidget *child){
    NULL_CHECKER(widget);
    NULL_CHECKER(child);
    
    if(child->entity->has_component[BE_WIDGET_TYPE_WIDGET_PARENT]){
    	LOGE("Child already added to another parent");
    	return;
    }
    
    if(child->scene!=widget->scene){
        LOGE("Child already bind to another widget or scene");
        return;
    }
    
    RETURN_IF_NOT_WIDGET_COMPONENT(widget->entity,BE_WIDGET_TYPE_WIDGET_CHILD,BeWidgetChild);
    
    u32 widget_child_id=widget->entity->component_id[BE_WIDGET_TYPE_WIDGET_CHILD];
    // Get widget child component here
    BeWidgetChild *comp=widget->scene->components[widget_child_id];//=
    
    if(NULL==comp->childs){
        comp->childs=(u32*)malloc(sizeof(u32)*wdgt->cap_child);
    }
    
    if(comp->numb_child>=wdgt->cap_child){
        comp->cap_child*=2;
        comp->childs=(u32*)realloc(wdgt->childs,sizeof(u32)*wdgt->cap_child);
    }
    
    // add entity id
    comp->childs[comp->numb_child]=child->entity->id;
    
    //add parent widget component to child
    BeWidgetParent *p=be_widget_parent_new(widget);
    
    be_entity_add_component(child->scene,child->entity,p);
    comp->numb_child++;
}

void be_widget_remove_child(BeWidget*widget, BeWidget*child_widget){
	NULL_CHECKER(widget);
	NULL_CHECKER(child_widget);
	
	if(widget->scene!=child_widget->scene){
		LOGE("Widget and child are not in same scene");
		return;
	}
	
	RETURN_IF_NOT_WIDGET_COMPONENT(child_widget->entity,BE_WIDGET_TYPE_WIDGET_PARENT,BeWidgetParent);

	RETURN_IF_NOT_WIDGET_COMPONENT(widget->entity,BE_WIDGET_TYPE_WIDGET_CHILD,BeWidgetChild);
	
	// get component widget child
	u32 id_comp=child_widget->entity->component_id[BE_WIDGET_TYPE_WIDGET_PARENT];
	BeWidgetParent*child_comp=child_widget->scene->components[id_comp];
	
	u32 id_parent=widget->entity->component_id[BE_WIDGET_TYPE_WIDGET_CHILD];
	BeWidgetChild*parent_comp=widget->scene->components[id_parent];
	
	
	
	u32 offset=child_comp->index_entity_in_parent+1;
	if(offset==parent_comp->numb_child){
		parent_comp->childs[offset]=-1;
		parent_comp->numb_child--;
		return;
	}
	
	u32*tmp=(u32*)malloc(sizeof(u32)*(parent_comp->numb_child-offset));
	memcpy(tmp,&(parent_comp->childs[offset]),parent_comp->numb_child-offset);
	
	if(parent_comp->numb_child<parent_comp->cap_child){
		parent_comp->cap_child*=2;
		parent_comp->childs=realloc(parent_comp->childs,sizeof(u32)*(parent_comp->numb_child-1);
	}
	
	memcpy(&(parent_comp->childs[child_comp->index_entity_in_parent]),tmp,sizeof(u32)*(parent_comp->numb_child-offset));
	parent_comp->numb_child--;
	
	free(tmp);
	tmp=NULL;
}