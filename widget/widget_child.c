#include <widget/widget_child.h>

#include <stdlib.h>
#include <string.h>

#include <utilities/checker.h>
#include <system/component.h>
#include <widget/widget_parent.h>

BeWidgetChild *be_widget_child_new()
{
	BeWidgetChild *wdg = (BeWidgetChild *)malloc(sizeof(BeWidgetChild));
	wdg->numb_child = 0;
	wdg->cap_child = DEFAULT_CHILD_CAPACITY;
	wdg->childs = NULL;

	return wdg;
}

void be_widget_child_destroy(BeWidgetChild *widget)
{
	if (NULL == widget)
	{
		return;
	}

	// delete all children

	if (widget->childs)
	{
		DESTROYER(widget->childs);
	}

	DESTROYER(widget);
}

void be_widget_add_child(BeScene *scene, BeWidget *widget, BeWidget *child)
{
	NULL_CHECKER(widget);
	NULL_CHECKER(child);

	RETURN_IF_NOT_WIDGET(widget);
	RETURN_IF_NOT_WIDGET(child);

	if (child->has_component[BE_WIDGET_TYPE_PARENT])
	{
		LOGE("Child already added to another parent");
		return;
	}

	BeWidgetType *w_widget_type = be_widget_get_component(scene, widget, (BeComponentType)BE_WIDGET_TYPE)->component;
	BeWidgetType *c_widget_type = be_widget_get_component(scene, child, (BeComponentType)BE_WIDGET_TYPE)->component;

	RETURN_IF_NOT_SAME(scene, w_widget_type->scene);
	RETURN_IF_NOT_SAME(scene, c_widget_type->scene);
	RETURN_IF_NOT_SAME(w_widget_type->scene, c_widget_type->scene);

	RETURN_IF_NOT_HAS_COMPONENT(widget, (BeComponentType)BE_WIDGET_TYPE_CHILD, BeWidgetChild);

	// Get widget child component here
	BeWidgetChild *comp = be_widget_get_component(scene, widget, (BeComponentType)BE_WIDGET_TYPE_CHILD)->component;

	if (NULL == comp->childs)
	{
		comp->childs = (BeWidget **)malloc(sizeof(BeWidget *) * comp->cap_child);
	}

	if (comp->numb_child >= comp->cap_child)
	{
		comp->cap_child *= 2;
		comp->childs = (BeWidget **)realloc(comp->childs, sizeof(BeWidget *) * comp->cap_child);
	}

	// add widget
	comp->childs[comp->numb_child] = child;

	// add parent widget component to child
	BeWidgetParent *p = be_widget_parent_new(comp->numb_child, widget);
	BeComponent *cp = be_component_new((BeComponentType)BE_WIDGET_TYPE_PARENT, p);

	be_entity_add_component(scene, child, cp);
	comp->numb_child++;
}

void be_widget_remove_child(BeScene *scene, BeWidget *widget, BeWidget *child_widget)
{
	NULL_CHECKER(scene);
	NULL_CHECKER(widget);
	NULL_CHECKER(child_widget);

	BeWidgetType *w_widget_comp = be_widget_get_component(scene, widget, (BeComponentType)BE_WIDGET_TYPE)->component;
	BeWidgetType *c_widget_comp = be_widget_get_component(scene, child_widget, (BeComponentType)BE_WIDGET_TYPE)->component;

	RETURN_IF_NOT_SAME(scene, w_widget_comp->scene);
	RETURN_IF_NOT_SAME(scene, c_widget_comp->scene);
	RETURN_IF_NOT_SAME(w_widget_comp->scene, w_widget_comp->scene);

	RETURN_IF_NOT_HAS_COMPONENT(child_widget, BE_WIDGET_TYPE_PARENT, BeWidgetParent);
	RETURN_IF_NOT_HAS_COMPONENT(widget, BE_WIDGET_TYPE_CHILD, BeWidgetChild);

	// get component widget parent
	BeWidgetParent *child_comp = be_widget_get_component(scene, child_widget, (BeComponentType)BE_WIDGET_TYPE_PARENT)->component;

	BeWidgetChild *parent_comp = be_widget_get_component(scene, widget, (BeComponentType)BE_WIDGET_TYPE_CHILD)->component;

	u32 offset = child_comp->index_in_parent + 1;
	if (offset == parent_comp->numb_child)
	{
		be_widget_destroy(scene, parent_comp->childs[offset]);
		parent_comp->numb_child--;
		return;
	}

	BeWidget **tmp = (BeWidget **)malloc(sizeof(BeWidget *) * (parent_comp->numb_child - offset));
	memcpy(tmp, &(parent_comp->childs[offset]), parent_comp->numb_child - offset);

	if (parent_comp->numb_child < parent_comp->cap_child)
	{
		parent_comp->cap_child *= 2;
		parent_comp->childs = realloc(parent_comp->childs, sizeof(BeWidget *) * (parent_comp->numb_child - 1));
	}

	memcpy(&(parent_comp->childs[child_comp->index_in_parent]), tmp, sizeof(BeWidget *) * (parent_comp->numb_child - offset));
	parent_comp->numb_child--;

	free(tmp);
	tmp = NULL;

	be_widget_destroy(scene, child_widget);
}

void be_widget_clear_child(BeScene *scene, BeWidget *widget)
{
	NULL_CHECKER(scene);
	NULL_CHECKER(widget);

	RETURN_IF_NOT_WIDGET(widget);

	BeWidgetType *widget_type_comp = be_widget_get_component(scene, widget, (BeComponentType)BE_WIDGET_TYPE)->component;

	RETURN_IF_NOT_SAME(scene, widget_type_comp->scene);

	RETURN_IF_NOT_HAS_COMPONENT(widget, BE_WIDGET_TYPE_CHILD, BeWidgetChild);

	BeWidgetChild *parent_comp = be_widget_get_component(scene, widget, (BeComponentType)BE_WIDGET_TYPE_CHILD)->component;
	u32 i = 0;
	// delete all child widget
	for (i = 0; i < parent_comp->numb_child; i++)
	{
		be_widget_destroy(scene, parent_comp->childs[i]);
	}

	free(parent_comp->childs);
	parent_comp->childs = NULL;
	parent_comp->childs = (BeWidget **)malloc(sizeof(BeWidget *) * DEFAULT_CHILD_CAPACITY);
	parent_comp->numb_child = 0;
	parent_comp->cap_child = DEFAULT_CHILD_CAPACITY;
}