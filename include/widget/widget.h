#ifndef GIHEX_WIDGET_H
#define GIHEX_WIDGET_H

#include <stdbool.h>

#include <utilities/mangle.h>
#include <utilities/checker.h>
#include <system/entity.h>
#include <system/component.h>
#include <scene/scene.h>

#define RETURN_IF_NOT_HAS_COMPONENT(E, T, C)                   \
	if (!E->has_component[T])                                  \
                                                               \
	{                                                          \
		LOGE("\"%s\" does not has component: \"%s\"", #E, #C); \
		return;                                                \
	}

#define RETURN_VAL_IF_NOT_HAS_COMPONENT(E, T, C, VAL)          \
	if (!E->has_component[T])                                  \
                                                               \
	{                                                          \
		LOGE("\"%s\" does not has component: \"%s\"", #E, #C); \
		return VAL;                                            \
	}

#define RETURN_IF_NOT_WIDGET(W) RETURN_IF_NOT_HAS_COMPONENT(W, (BeComponentType)BE_WIDGET_TYPE, BeWidgetType);

#define RETURN_IF_NOT_SAME(X, Y) \
	if (X != Y)                  \
	{                            \
		ASSOIATED_FAILED(X, Y);  \
	}

#define RETURN_VAL_IF_NOT_SAME(X, Y, VAL)                    \
	if (X != Y)                                              \
	{                                                        \
		LOGE("\"%s\" is not assoiated with \"%s\"", #X, #Y); \
		return VAL;                                          \
	}

#define DEFAULT_CHILD_CAPACITY 4

#ifdef __cplusplus
extern C
{
#endif

	typedef BeEntity BeWidget;

	BeWidget *be_widget_new(BeScene * scene);
	void be_widget_destroy(BeScene * scene, BeWidget * widget);

	BeComponent *be_widget_get_component(BeScene * scene, const BeWidget *widget, BeComponentType type);

	typedef struct _be_widget_type BeWidgetType;
	struct _be_widget_type
	{
		BeScene *scene;
	};

	BeWidgetType *be_widget_type_new(BeScene * scene);

	void be_widget_type_destroy(BeWidgetType * widget);

#ifdef __cplusplus
}
#endif

#endif /*GIHEX_WIDGET_H*/