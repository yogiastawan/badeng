#ifndef GIHEX_WIDGET_CHILD_H
#define GIHEX_WIDGET_CHILD_H

#include<widget/widget.h>

#ifdef __cplusplus
extern C
{
#endif

typedef struct _be_widget_child BeWidgetChild;

struct _be_widget_child{
    u32 numb_child;
    u32 cap_child;
    BeWidget **childs;
};

BeWidgetChild* be_widget_child_new();
void be_widget_child_destroy(BeWidgetChild* widget);

void be_widget_add_child(BeWidget *widget, BeWidget *child);

void be_widget_remove_child(BeWidget*widget, BeWidget*child);

void be_widget_clear_child(BeWidget*widget);

ifdef __cplusplus
}
#endif

#endif /*GIHEX_WIDGET_CHILD_H*/