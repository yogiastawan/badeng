#ifndef GIHEX_LINEAR_LAYOUT_H
#define GIHEX_LINEAR_LAYOUT_H

#include <widget/widget.h>
#include <scene/scene.h>
#include <widget/layout.h>

#ifdef _cplusplus
extern C
{
#endif

typedef BeWidget BeLayoutLinear;

BeLayoutLinear* be_layout_linear_new(BeScene *scene, BeLinearOrientation orientation);

void be_layout_linear_set_orientation(BeLayoutLinear *layout, BeLinearOrientation orientation);

void be_layout_linear_add_children(BeLayoutLinear *layout, BeWidget *child);

void be_layout_linear_remove_children(BeLayoutLinear *layout, BeWidget *child);


#ifdef _cplusplus
}
#endif

#endif /*GIHEX_LINEAR_LAYOUT_H*/