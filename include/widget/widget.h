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

typedef struct _be_widget BeWidget;

struct _be_widget{
    BeScene *scene;
    u32 *entity_id;
}

BeWidget *be_widget_new(BeScene*scene);

void be_widget_destroy(BeWidget*widget);


#ifdef __cplusplus
}
#endif

#endif /*GIHEX_WIDGET_H*/