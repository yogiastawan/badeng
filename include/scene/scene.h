#ifndef GIHEX_SCENE_H
#define GIHEX_SCENE_H

#include <utilities/mangle.h>
#include <system/component.h>
#include <system/system.h>
#include <system/entity.h>

#include <scene/renderer_batch.h>

#ifdef __cplusplus
extern C
{
#endif

    typedef enum _be_scene_choice BeSceneChoice;

    enum _be_scene_choice
    {
        BE_SCENE_CHOICE_DEFAULT = 0,
        BE_SCENE_CHOICE_COMPONENT = 1,
        BE_SCENE_CHOICE_ENTITY = 2,

    };

    typedef struct _be_scene BeScene;

    /**
     * @brief BeScene structure
     */
    struct _be_scene
    {

        i32 width;                     /**< Width of screen*/
        i32 height;                    /**< Height of screen*/
        u32 numb_entity;               /**< Numb of entities*/
        u32 cap_entity;                /**< Capacity of entities*/
        BeEntity **entites;            /**< List of `BeEntity` pointers*/
        u32 cap_component;             /**< Capacity of components*/
        u32 numb_component;            /**< Numb of `BeComponent` */
        BeComponent **components;      /**< List of `BeComponents` pointers */
        BeSystem *system;              /**< System*/
        BeRendererBatch *vertex_batch; /**< Contain of combination vertex of `BeComponent` that has type `BE_COMPONENT_TYPE_SPRITE`*/
    };

    /**
     * @brief Create new scene
     *
     * @param width Integer value of screen width
     * @param height Integer vcalue of screen height
     * @return Pointer to `BeScene` object
     */
    BeScene *be_scene_new(i32 width, i32 height);

    /**
     * @brief Destroy `BeScene`
     *
     * @param scene Pointer to `BeScene` that will be deleted
     * @param choice `BeSceneChoice` value. -`BE_SCENE_CHOICE_DEFAULT` will do not do anything to `BeComponent` and `BeEntity` that assoiated with scene. -`BE_SCENE_CHOICE_COMPONENT` will delete all `BeComponent` that asoisated with \a scene.
     *  -`BE_SCENE_CHOICE_ENTITY` will delete all `BeEntity` that assoiated with \a scene. Multiple choice is approved.
     */
    void be_scene_destroy(BeScene * scene, BeSceneChoice choice);

    void be_scene_add_entity(BeScene * scene, BeEntity * entity);

    /**
     * @brief Remove `BeEntity` from `BeScene`
     *
     * @note When this function called, `entity` will be removed from assoiated `scene` and delete it from memory. All `BeComponent` that asoiated with `entity`
     * will be deleted from memory.
     *
     * @param scene Pointer to `BeScene` that assoiated with \a entity.
     * @param entity Pointer to `BeEntity` that will be remove.
     */
    void be_scene_remove_entity(BeScene * scene, BeEntity * entity);

    void be_entity_add_component(BeScene * scene, BeEntity * entity, BeComponent * component);

    /**
     * @brief Remove `BeComponent` from `BeEntity`
     *
     * @note When this function called, `comp` will be removed from assoiated entity, but `comp` not destroyed.
     * Use `be_component_destroyer(BeComponent *comp)` to delete Component from memory.
     *
     * @param scene Pointer to `BeScene` that assoiated with pointer \a entity.
     * @param comp Pointer to `BeComponent` that will be remove.
     */
    void be_entity_remove_component(BeScene * scene, BeComponent * comp);

    void be_scene_system_update(BeScene * scene, BeComponentType type);

    void be_scene_draw(BeScene * scene);

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_SCENE_H */
