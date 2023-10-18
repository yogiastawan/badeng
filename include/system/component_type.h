#ifndef GIHEX_COMPONENT_TYPE_H
#define GIHEX_COMPONENT_TYPE_H

#ifdef __cplusplus
extern C
{
#endif

    typedef enum _be_component_type BeComponentType;
    enum _be_component_type
    {
        BE_COMPONENT_TYPE_VISIBILITY = 0,
        BE_COMPONENT_TYPE_POSITION,
        BE_COMPONENT_TYPE_SPRITE,
        NUMB_TYPE
    };

    typedef enum _be_widget_component_type BeWidgetComponentType;

    enum _be_widget_component_type
    {
        BE_WIDGET_TYPE = NUMB_TYPE,
        BE_WIDGET_TYPE_CHILD,
        BE_WIDGET_TYPE_PARENT,
        BE_WIDGET_TYPE_ORIENTATION,
        BE_WIDGET_TYPE_LAYOUT_PADDING,
        BE_WIDGET_TYPE_LAYOUT_MARGIN,
        NUMB_TYPE_COMPONENT
    };

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_COMPONENT_TYPE_H */
