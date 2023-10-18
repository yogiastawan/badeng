#include <widget/layout.h>

#include <stdlib.h>

BeLinearLayoutOrientation *be_linear_orientation_new(BeLinearOrientation orientation)
{
    BeLinearLayoutOrientation *layout = (BeLinearLayoutOrientation *)malloc(sizeof(BeLinearLayoutOrientation));

    layout->orientation = orientation;

    return layout;
}

BeLayoutPadding *be_layout_padding_new(u32 top, u32 bottom, u32 left, u32 right)
{
    BeLayoutPadding *padding = (BeLayoutPadding *)malloc(sizeof(BeLayoutPadding));
    padding->top = top;
    padding->bottom = bottom;
    padding->left = left;
    padding->right = right;

    return padding;
}

BeLayoutMargin *be_layout_margin_new(u32 top, u32 bottom, u32 left, u32 right)
{
    BeLayoutMargin *m = (BeLayoutMargin *)malloc(sizeof(BeLayoutMargin));
    m->top = top;
    m->bottom = bottom;
    m->left = left;
    m->right = right;

    return m;
}