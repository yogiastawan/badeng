#ifndef GIHEX_WIDGET_H
#define GIHEX_WIDGET_H

#include <stdbool.h>

#include <utilities/mangle.h>
#include <system/entity.h>
#include <system/component.h>
#include <scene/scene.h>

#define RETURN_IF_NOT_WIDGET_COMPONENT(E,T,C) if(!E->has_components[T]){{\
											LOGE("\"%s\" does not has component: \"%s\"",#E,#C);\
											return; 	\
										}

#define DEFAULT_CHILD_CAPACITY 4

#ifdef __cplusplus
extern C
{
#endif

//TODO: change be widget to component that hold BeSene pointer only
typedef BeEntity BeWidget;

typedef struct _be_widget_t BeWidgetType;

struct _be_widget_t{
    BeScene *scene;
}

BeWidgetType *be_widget_type_new(BeScene*scene);

void be_widget_type_destroy(BeWidgetType*widget);


#ifdef __cplusplus
}
#endif

#endif /*GIHEX_WIDGET_H*/