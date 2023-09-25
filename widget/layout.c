#include<widget/layout.h>

#include<stdlib.h>

BeLinearLayout* be_linear_layout_new(BeLinearOrientation*orientation){
    BeLinearLayout *layout=(BeLinearLayout*)malloc(sizeof(BeLinearLayout));
    
    layout->orientation=orientation;
    
    return layout;
}

BeLayoutPadding *be_layout_padding_new(u32 top,u32 bottom,u32 left,u32 right){
    BeLayoutPadding*padding=(BeLayoutPadding*)malloc(sizeof(BeLayoutPadding));
    padding->padding_top=top;
    padding->padding_bottom=bottom;
    padding->padding_left=left;
    padding->padding_right=right;
    
    return padding;
}
