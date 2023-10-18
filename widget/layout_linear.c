#include <widget/layout_linear.h>

#include <widget/widget_child.h>
#include <system/component.h>
#include <utilities/checker.h>

BeLayoutLinear *be_layout_linear_new(BeScene *scene, BeLinearOrientation orientation)
{
    NULL_CHECKER_VAL(scene, NULL);

    BeLayoutLinear *la = be_widget_new(scene);

    // WIDGET CHILD
    BeWidgetChild *ch = be_widget_child_new();
    BeComponent *child_comp = be_component_new((BeComponentType)BE_WIDGET_TYPE_CHILD, ch);
    be_entity_add_component(scene, la, child_comp);

    // orientation
    BeLinearLayoutOrientation * or = be_linear_orientation_new(orientation);
    BeComponent *or_comp = be_component_new((BeComponentType)BE_WIDGET_TYPE_ORIENTATION, or);
    be_entity_add_component(scene, la, or_comp);

    // padding
    // do not add padding, add padding component when user need only

    // margin
    // do not add margin, add margin component when user need only

    return la;
}

void be_linear_layout_destroy(BeScene *scene, BeLayoutLinear *layout)
{
    if (NULL == layout)
    {
        LOGI("layout is null");
        return;
    }

    // TODO delete all child's entity in scene
    be_widget_clear_child(scene, layout);

    be_widget_destroy(scene, layout);

    // user must delete childs widget manualy
}

void be_layout_linear_set_orientation(BeScene *scene, BeLayoutLinear *layout, BeLinearOrientation orientation)
{
    NULL_CHECKER(layout);
    RETURN_IF_NOT_HAS_COMPONENT(layout, BE_WIDGET_TYPE_ORIENTATION, BeLinearOrientation);
    BeLinearLayoutOrientation *or_comp = (BeLinearLayoutOrientation *)be_widget_get_component(scene, layout, (BeComponentType)BE_WIDGET_TYPE_ORIENTATION)->component;

    or_comp->orientation = orientation;
}

void be_layout_linear_add_children(BeScene *scene, BeLayoutLinear *layout, BeWidget *child)
{
    be_widget_add_child(scene, layout, child);
}

void be_layout_linear_remove_children(BeScene *scene, BeLayoutLinear *layout, BeWidget *child)
{
    be_widget_remove_child(scene, layout, child);
}

void be_layout_linear_set_margin(BeScene *scene, BeLayoutLinear *layout, u32 top, u32 bottom, u32 left, u32 right)
{
    NULL_CHECKER(scene);
    NULL_CHECKER(layout);

    RETURN_IF_NOT_WIDGET(layout);

    BeWidgetType *w_t = be_widget_get_component(scene, layout, (BeComponentType)BE_WIDGET_TYPE)->component;
    RETURN_IF_NOT_SAME(scene, w_t->scene);

    BeComponent *comp;
    if (layout->has_component[BE_WIDGET_TYPE_LAYOUT_MARGIN])
    {
        comp = be_widget_get_component(scene, layout, (BeComponentType)BE_WIDGET_TYPE_LAYOUT_MARGIN);
        BeLayoutMargin *margin = comp->component;
        margin->top = top;
        margin->bottom = bottom;
        margin->left = left;
        margin->right = left;
        return;
    }
    BeLayoutMargin *margin = be_layout_margin_new(top, bottom, left, right);
    comp = be_component_new((BeComponentType)BE_WIDGET_TYPE_LAYOUT_MARGIN, margin);

    be_entity_add_component(scene, layout, comp);
}

void be_layout_linear_set_padding(BeScene *scene, BeLayoutLinear *layout, u32 top, u32 bottom, u32 left, u32 right)
{
    NULL_CHECKER(scene);
    NULL_CHECKER(layout);

    RETURN_IF_NOT_WIDGET(layout);

    BeWidgetType *w_t = be_widget_get_component(scene, layout, (BeComponentType)BE_WIDGET_TYPE)->component;
    RETURN_IF_NOT_SAME(scene, w_t->scene);

    BeComponent *comp;
    if (layout->has_component[BE_WIDGET_TYPE_LAYOUT_PADDING])
    {
        comp = be_widget_get_component(scene, layout, (BeComponentType)BE_WIDGET_TYPE_LAYOUT_PADDING);
        BeLayoutPadding *padding = comp->component;
        padding->top = top;
        padding->bottom = bottom;
        padding->left = left;
        padding->right = left;
        return;
    }
    BeLayoutMargin *margin = be_layout_margin_new(top, bottom, left, right);
    comp = be_component_new((BeComponentType)BE_WIDGET_TYPE_LAYOUT_PADDING, margin);

    be_entity_add_component(scene, layout, comp);
}
