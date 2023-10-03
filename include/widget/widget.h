#ifndef GIHEX_WIDGET_H
#define GIHEX_WIDGET_H

#include <stdbool.h>

#include <utilities/mangle.h>
#include <system/entity.h>
#include <system/component.h>
#include <scene/scene.h>

#define DEFAULT_CHILD_CAPACITY 4

#ifdef __cplusplus
extern C
{
#endif

typedef struct _be_widget BeWidget;

struct _be_widget{
    BeScene *scene;
    BeEntity *entity;
}

BeWidget *be_widget_new(BeScene*scene);

void be_widget_destroy(BeWidget*widget);


#ifdef __cplusplus
}
#endif

#endif /*GIHEX_WIDGET_H*/