#include<widget/layout.h>

#include<stdlib.h>

BeLinearLayout* be_linear_orientation_new(BeOrientation*orientation){
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

BeLayoutPadding *be_layout_padding_new(u32 top,u32 bottom, u32 left, u32 right){
	BeLayoutMargin*m=(BeLayoutMargin*)malloc(sizeof(BeLayoutMargin));
	m->top=top;
	m->bottom=bottom;
	m->left=left;
	m->right=right;
	
	return m;
}