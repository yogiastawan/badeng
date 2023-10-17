#include<widget/widget_child.h>

#include<string.h>

#include<system/component.h>
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
    // delete all childs
    u32 i=0;
    for(i=0;i<widget->numb_child;i++){
    	be_widget_destroy(widget->childs[i]);
    }
    
    if(widget->childs){
        DESTROYER(widget->childs);
    }
    
    DESTROYER(widget);
}

void be_widget_add_child(BeScene *scene,BeWidget *widget, BeWidget *child){
    NULL_CHECKER(widget);
    NULL_CHECKER(child);
    
    RETURN_IF_NOT_WIDGET_COMPONENT(widget,BE_WIDGET_TYPE,BeWidgetType);
    RETURN_IF_NOT_WIDGET_COMPONENT(child,BE_WIDGET_TYPE,BeWidgetType);
    //=======
    //BeEntity *child_entity=child->scene->entities[child->entity_id];
    //BeEntity *widget_child=widget->scene->entites[widget->entity_id];
    
    if(child_entity->has_component[BE_WIDGET_TYPE_WIDGET_PARENT]){
    	LOGE("Child already added to another parent");
    	return;
    }
    
    u32 id_widg_p=widget->component_id[BE_WIDGET_TYPE];
    u32 id_widg_c=child->component_id[BE_WIDGET_TYPE];
    
    if(id_widg_p>s=cene->NUMB_COMPONENT){
    	ASSOIATED_FAILED(widget,scene);
    }
    
    if(id_widg_c>=scene->numb_component){
    	ASSOIATED_FAILED(child,scene);
    }
    
    BeComponent *comp_wdgt_p=scene->components[id_widg_p];
    BeWidgetType *comp_p=(BeWidgetType*)comp_wdgt_p->component;
    BeComponent *comp_wdgt_c=scene->components[id_widg_c];
    BeWidgetType *comp_c=(BeWidgetType*)comp_wdgt_p->component;
       
    if(comp_p->scene!=comp_c->scene){
        ASSOIATED_FAILED(widget,child);
    }
    
    RETURN_IF_NOT_WIDGET_COMPONENT(widget,BE_WIDGET_TYPE_WIDGET_CHILD,BeWidgetChild);
    
    u32 widget_child_id=widget->component_id[BE_WIDGET_TYPE_WIDGET_CHILD];
    // Get widget child component here
    BeComponent *c=comp_p->scene->components[widget_child_id];//=
    BeWidgetChild *comp=c->component;
    
    if(NULL==comp->childs){
        comp->childs=(BeWidget**)malloc(sizeof(BeWidget*)*comp->cap_child);
    }
    
    if(comp->numb_child>=comp->cap_child){
        comp->cap_child*=2;
        comp->childs=(BeWidget**)realloc(comp->childs,sizeof(BeWidget*)*comp->cap_child);
    }
    
    // add widget
    comp->childs[comp->numb_child]=child;
    
    //add parent widget component to child
    BeWidgetParent *p=be_widget_parent_new(widget);
    
    be_entity_add_component(comp_c->scene,child_entity,p);
    comp->numb_child++;
}

void be_widget_remove_child(BeWidget*widget, BeWidget*child_widget){
	NULL_CHECKER(widget);
	NULL_CHECKER(child_widget);
	
	BeEntity*widget_entity=widget->scene->entities[widget->entity_id];
	BeEntity *child_widget_entity=child_widget->scene->entites[child_widget->entity_id];
	
	if(widget->scene!=child_widget->scene){
		LOGE("Widget and child are not in same scene");
		return;
	}
	
	RETURN_IF_NOT_WIDGET_COMPONENT(child_widget_entity,BE_WIDGET_TYPE_WIDGET_PARENT,BeWidgetParent);

	RETURN_IF_NOT_WIDGET_COMPONENT(widget_entity,BE_WIDGET_TYPE_WIDGET_CHILD,BeWidgetChild);
	
	// get component widget child
	u32 id_comp=child_widget_entity->component_id[BE_WIDGET_TYPE_WIDGET_PARENT];
	BeComponent*c_comp=child_widget->scene->components[id_comp];
	BeWidgetParent*child_comp=c_comp->component;
	
	u32 id_parent=widget_entity->component_id[BE_WIDGET_TYPE_WIDGET_CHILD];
	BeComponent*p_comp=widget->scene->components[id_parent];
	BeWidgetChild*parent_comp=p->component;
	
	u32 offset=child_comp->index_in_parent+1;
	if(offset==parent_comp->numb_child){
		be_widget_destroy(parent_comp->childs[offset]);
		parent_comp->numb_child--;
		return;
	}
	
	BeWidget**tmp=(BeWidget**)malloc(sizeof(BeWidget*)*(parent_comp->numb_child-offset));
	memcpy(tmp,&(parent_comp->childs[offset]),parent_comp->numb_child-offset);
	
	if(parent_comp->numb_child<parent_comp->cap_child){
		parent_comp->cap_child*=2;
		parent_comp->childs=realloc(parent_comp->childs,sizeof(BeWidget*)*(parent_comp->numb_child-1);
	}
	
	memcpy(&(parent_comp->childs[child_comp->index_entity_in_parent]),tmp,sizeof(BeWidget*)*(parent_comp->numb_child-offset));
	parent_comp->numb_child--;
	
	free(tmp);
	tmp=NULL;
	
	be_widget_destroy(child_widget);
}

void be_widget_clear_child(BeScene*scene,BeWidget*widget){
	NULL_CHECKER(widget);
	NULL_CHECKER(scene);
	
	//BeEntity*widget_entity=widget->scene->entities[widget->entity_id];
	
	RETURN_IF_NOT_WIDGET_COMPONENT(widget,BE_WIDGET_TYPE,BeWidgetType);
	
	RETURN_IF_NOT_WIDGET_COMPONENT(widget,BE_WIDGET_TYPE_WIDGET_CHILD,BeWidgetChild);
	
	u32 id_widget=widget->component_id[BE_WIDGET_TYPE];
	
	if(id_widget>=scene->numb_component){
		ASSOIATED_FAILED(widget,scene);
	}
	
	BeComponent*w_comp=scene->components[id_widget];
	BeWidgetType comp_w=(BeWidgetType*)w_comp->component;
	
	if(comp_w->scene!=scene){
		ASSOIATED_FAILED(widget,scene);
	}
	
	u32 id_parent=widget->component_id[BE_WIDGET_TYPE_WIDGET_CHILD];
	BeComponent*p_comp=comp_w->scene->components[id_parent];
	BeWidgetChild*parent_comp=(BeWidgetChild*)p->component;
	u32 i=0;
	// delete all child widget
	for(i=0;i<parent_comp->numb_child;i++){
		be_scene_remove_entity(compw->scene,parent_comp->childs[i]);
	}
	
	DESTROYER(parent_comp->childs);
	parent_comp->childs=(BeWidget**)malloc(sizeof(BeWidget*)*DEFAULT_CHILD_CAPACITY);
	parent_comp->numb_child=0;
	parent_comp->cap_child=DEFAULT_CHILD_CAPACITY;
}