#include <stdlib.h>

#include <utilities/checker.h>
#include<utilities/log.h>


BeWidgetParent* be_widget_parent_new(BeWidget *widget){
	NULL_CHECKER(widget);
	
	RETURN_IF_NOT_WIDGET_COMPONENT(widget->entity,BE_WIDGET_TYPE_WIDGET_CHILD,BeWidgetChild);
	
	BeWidgetParent* prn=(BeWidgetParent*)malloc(sizeof(BeWidgetParent);
	prn->parent_id=widget->entity->id;
	
	// get index of widget child component
	u32 id_comp=widget->entity->component_id[BE_WIDGET_TYPE_WIDGET_CHILD];
	prn->index_in_parent=widget->scene->components[id_comp]->numb_child;
	
	return prn;
}

void be_widget_parent_destroy(BeWidgetParent* widget){
	if(NULL==widget){
		LOGE("Component widget parent is NULL");
		return;
	}
	free(widget);
	widget=NULL;
}