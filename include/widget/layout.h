#ifndef GIHEX_LAYOUT_H
#define GIHEX_LAYOUT_H

#include <system/entity.h>
#include <utilities/mangle.h>

#ifdef __cplusplus
extern C
{
#endif

    typedef enum _be_linear_orientation BeLinearOrientation;

    enum _be_linear_orientation
    {
        BE_LINEAR_ORIENTATION_HORIZONTAL,
        BE_LINEAR_ORIENTATION_VERTICAL
    };

    typedef struct _be_linear_layout_orientation BeLinearLayoutOrientation;

    struct _be_linear_layout_orientation
    {
        BeLinearOrientation orientation;
    };

    BeLinearLayoutOrientation *be_linear_orientation_new(BeLinearOrientation orientation);

    typedef struct _be_layout_padding BeLayoutPadding;

    struct _be_layout_padding
    {
        u32 top;
        u32 bottom;
        u32 left;
        u32 right;
    };

    BeLayoutPadding *be_layout_padding_new(u32 top, u32 bottom, u32 left, u32 right);

    typedef struct _be_layout_margin BeLayoutMargin;

    struct _be_layout_margin
    {
        u32 top;
        u32 bottom;
        u32 left;
        u32 right;
    };

    BeLayoutMargin *be_layout_margin_new(u32 top, u32 bottom, u32 left, u32 right);

#ifdef __cplusplus
}
#endif

#endif /*GIHEX_LAYOUT_H*/