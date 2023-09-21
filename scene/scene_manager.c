#include <scene/scene_manager.h>

#include <stdlib.h>

#include <utilities/checker.h>
#include <utilities/log.h>

#include <SDL.h>

BeSceneManager *be_scene_manager_new()
{
    LOGI("Create new Scene Manager");
    BeSceneManager *mgr = (BeSceneManager *)malloc(sizeof(BeSceneManager));

    mgr->current_scene = NULL;
    return mgr;
}

void be_scene_manager_destroy(BeSceneManager *manager)
{
    LOGI("Destroy Scene Manager");
    if (NULL == manager)
    {
        return;
    }

    DESTROYER(manager);
}

void be_scene_manager_start_scene(BeSceneManager *manager, BeScene *scene, bool destroy_current_scene)
{
    NULL_CHECKER(manager);
    NULL_CHECKER(scene);
    if (destroy_current_scene && manager->current_scene)
    {
        be_scene_destroy(manager->current_scene, true);
    }

    manager->current_scene = scene;
}

BeScene *be_scene_manager_get_current_scene(BeSceneManager *manager)
{
    return manager->current_scene;
}

void be_scene_manager_update(BeSceneManager *manager, BeComponentType type)
{
    NULL_CHECKER(manager);
    be_scene_system_update(manager->current_scene, type);
}

void be_scene_manager_draw(BeSceneManager *manager)
{
    NULL_CHECKER(manager);
    be_scene_draw(manager->current_scene);
}
