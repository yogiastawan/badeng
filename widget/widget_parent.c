#include <widget/widget_parent.h>

#include <stdlib.h>

#include <utilities/checker.h>
#include <utilities/log.h>

BeWidgetParent *be_widget_parent_new(u32 index_in_parent, BeWidget *widget_parent)
{
	NULL_CHECKER_VAL(widget_parent, NULL);

	RETURN_VAL_IF_NOT_HAS_COMPONENT(widget_parent, BE_WIDGET_TYPE_CHILD, BeWidgetChild, NULL);

	BeWidgetParent *prn = (BeWidgetParent *)malloc(sizeof(BeWidgetParent));
	prn->parent_id = widget_parent->id;

	// get index of widget child component
	u32 id_comp = widget_parent->component_id[BE_WIDGET_TYPE_CHILD];

	prn->index_in_parent = index_in_parent;

	return prn;
}

void be_widget_parent_destroy(BeWidgetParent *widget)
{
	if (NULL == widget)
	{
		LOGE("Component widget parent is NULL");
		return;
	}
	free(widget);
	widget = NULL;
}