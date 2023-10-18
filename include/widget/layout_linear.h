#ifndef GIHEX_LAYOUT_LINEAR_H
#define GIHEX_LAYOUT_LINEAR_H

#include <widget/widget.h>
#include <scene/scene.h>
#include <widget/layout.h>

#ifdef _cplusplus
extern C
{
#endif

    typedef BeWidget BeLayoutLinear;

    BeLayoutLinear *be_layout_linear_new(BeScene * scene, BeLinearOrientation orientation);

    void be_linear_layout_destroy(BeScene * scene, BeLayoutLinear * layout);

    void be_layout_linear_set_orientation(BeScene * scene, BeLayoutLinear * layout, BeLinearOrientation orientation);

    void be_layout_linear_add_children(BeScene * scene, BeLayoutLinear * layout, BeWidget * child);

    void be_layout_linear_remove_children(BeScene * scene, BeLayoutLinear * layout, BeWidget * child);

    void be_layout_linear_set_margin(BeScene * scene, BeLayoutLinear * layout, u32 top, u32 bottom, u32 left, u32 right);

    void be_layout_linear_set_padding(BeScene * scene, BeLayoutLinear * layout, u32 top, u32 bottom, u32 left, u32 right);

#ifdef _cplusplus
}
#endif

#endif /*GIHEX_LINEAR_LAYOUT_H*/