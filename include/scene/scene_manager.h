#ifndef GIHEX_SCENE_MANAGER_H
#define GIHEX_SCENE_MANAGER_H

#include <stdbool.h>

#include <scene/scene.h>
#include <utilities/mangle.h>

#ifdef __cplusplus
extern C
{
#endif /* GIHEX_SCENE_MANAGER_H */

    typedef struct _be_scene_manager BeSceneManager;

    struct _be_scene_manager
    {
        BeScene *current_scene;
    };

    BeSceneManager *be_scene_manager_new();

    void be_scene_manager_destroy(BeSceneManager * manager);

    void be_scene_manager_start_scene(BeSceneManager * manager, BeScene * scene, bool destroy_current_scene, BeSceneChoice choice);

    BeScene *be_scene_manager_get_current_scene(BeSceneManager * manager);

    void be_scene_manager_update(BeSceneManager * manager, BeComponentType type);

    void be_scene_manager_draw(BeSceneManager * manager);

#ifdef __cplusplus
}
#endif /* GIHEX_SCENE_MANAGER_H */

#endif /* GIHEX_SCENE_MANAGER_H */
