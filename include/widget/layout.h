ifndef GIHEX_LAYOUT_H
#define GIHEX_WIDGET_HGIHEX_LAYOUT_H

#include <system/entity>
#include <utilities/mangle.h>

ifdef __cplusplus
extern C
{
#endif

typedef enum _be_linear_orientation BeLinearOrientation;

enum _be_linear_orientation{
    BE_LINEAR_ORIENTATION_HORIZONTAL,
    BE_LINEAR_ORIENTATION_VERTICAL
}

typedef _be_linear_layout BeLinearLayout;

struct _be_linear_layout{
    BeLinearOrientation orientation;
}

BeLinearLayout* be_linear_layout_new(BeLinearOrientation*orientation);

typedef _be_layout_padding BeLayoutPadding;

struct _be_layout_padding{
    u32 padding_top;
    u32 padding_bottom;
    u32 padding_left;
    u32 padding_right;
}



ifdef __cplusplus
}
#endif

#endif /*GIHEX_LAYOUT_H*/