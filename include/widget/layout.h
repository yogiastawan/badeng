ifndef GIHEX_LAYOUT_H
#define GIHEX_WIDGET_HGIHEX_LAYOUT_H

#include <system/entity>
#include <utilities/mangle.h>

ifdef __cplusplus
extern C
{
#endif

typedef enum _be_orientation BeOrientation;

enum _be_linear_orientation{
    BE_LINEAR_ORIENTATION_HORIZONTAL,
    BE_LINEAR_ORIENTATION_VERTICAL
};

typedef _be_linear_orientation BeLinearOrientation;

struct _be_linear_orientation{
    BeOrientation orientation;
};

BeLinearOrientation* be_linear_orientation_new(BeOrientation*orientation);

typedef _be_layout_padding BeLayoutPadding;

struct _be_layout_padding{
    u32 padding_top;
    u32 padding_bottom;
    u32 padding_left;
    u32 padding_right;
};

BeLayoutPadding *be_layout_padding_new(u32 top,u32 bottom, u32 left, u32 right);

typedef _be_layout_margin BeLayoutMargin;

struct _be_layout_margin{
	u32 top,
	u32 bottom,
	u32 left,
	u32 right
};

BeLayoutMargin *be_layout_margin_new(u32 top,u32 bottom,u32 left,u32 right);

ifdef __cplusplus
}
#endif

#endif /*GIHEX_LAYOUT_H*/