#include<widget/widget_child.h>

#include<system/component.h>

BeLayoutLinear* be_layout_linear_new(BeScene *scene, BeOrientation orientation){
    BeLayoutLinear *la=be_widget_new(scene);

    //WIDGET CHILD
    BeWidgetChild *ch=be_widget_child_new();
    BeComponent* child_comp=be_component_new(BE_WIDGET_TYPE_CHILD,ch);
    be_entity_add_component(la->scene,la->entity,child_comp);

    //orientation
    BeLinearOrientation *or=be_linear_orientation_new(orientation);
    BeComponent *or_comp=be_component_new(BE_WIDGET_TYPE_ORIENTATION,or);
    be_entity_add_component(la->scene,la->entity,or_comp);

    // padding
    // do not add padding, add padding component when user need only

    // margin
    // do not add margin, add margin component when user need only

    return la;
}

void be_layout_linear_set_orientation(BeLayoutLinear *layout, BeOrientation orientation){
    // get index orientation component
    RETURN_IF_NOT_WIDGET_COMPONENT(layout->entity,BE_WIDGET_TYPE_ORIENTATION,BeLinearOrientation);
    u32 id=layout->entity->component_id[BE_WIDGET_TYPE_ORIENTATION];

    BeComponent *comp=layout->scene->components[id];
    BeLinearOrientation *or_comp=comp->component;

    or_comp->orientation=orientation;
}

void be_layout_linear_add_children(BeLayoutLinear *layout, BeWidget *child){
    be_widget_add_child(layout, child);
}

void be_layout_linear_remove_children(BeLayoutLinear *layout, BeWidget *child){
    be_widget_remove_child(layout,child);
}

void be_layout_linear_set_margin(BeLayoutLinear *layout,u32 top,u32 bottom,,u22 left, u32 right){
	BeLayoutMargin *margin=be_layout_margin_new(top,bottom,left,right);
	BeComponent *comp=be_component_new(BE_WIDGET_TYPE_LAYOUT_MARGIN, margin);
	be_entity_add_component(layou->scene,layout->entity,comp);
}

void be_layout_linear_set_padding(BeLayoutLinear *layou*, u32 top,u32 bottom, u32 left,u32 right){
	BeLayoutPadding *padding=be_layout_padding_new(top,bottom,left,right);
	BeComponent *comp=be_component_new(BE_WIDGET_TYPE_LAYOUT_PADDING,padding);
	be_entity_add_component(layout->scene,layout->entity,comp);
}
