#ifndef GIHEX_WIDGET_H
#define GIHEX_WIDGET_H

#include <stdbool.h>

#include <utilities/mangle.h>
#include <system/entity.h>

#define DEFAULT_CHILD_CAPACITY 4

#ifdef __cplusplus
extern C
{
#endif

typedef struct _be_widget_child BeWidgetChild;

struct _be_widget_child{
    u32 numb_child;
    u32 cap_child;
    u32 *childs;
    BeEntity *temp_child_entities;
};

BeWidgetChild* be_widget_child_new();
void be_widget_child_destroy(BeWidgetChild* widget);

typedef struct _be_widget_parent BeWidgetParent;

struct _be_widget_parent{
    u32 parent;
}

BeWidgetParent* be_widget_parent_new();

void be_widget_parent_destroy(BeWidgetParent* widgdet);



#ifdef __cplusplus
}
#endif


#endif