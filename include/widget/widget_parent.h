#ifndef GIHEX_WIDGET_PARENT_H
#define GIHEX_WIDGET_PARENT_H

#include<widget/widget.h>
#include<utilities/mangle.h>

#ifdef __cplusplus
extern C
{
#endif

typedef struct _be_widget_parent BeWidgetParent;

struct _be_widget_parent{
    u32 parent_id;
    u32 inxex_entity_in_parent;
}

BeWidgetParent* be_widget_parent_new(u32 entity_id);

void be_widget_parent_destroy(BeWidgetParent* widget);

#ifdef __cplusplus
}
#endif