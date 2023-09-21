#include <badeng.h>

#include <stdlib.h>

#include <utilities/log.h>

#include <utilities/checker.h>

static BeEngine *create_engine()
{
    BeEngine *eng = (BeEngine *)malloc(sizeof(BeEngine));
    eng->width = 0;
    eng->height = 0;
    eng->window = NULL;
    eng->scene_manager = be_scene_manager_new();
    eng->startup_scene = NULL;
    eng->startup_time_millis = 3000;
    eng->main_scene = NULL;
    return eng;
}

BeEngine *be_engine_new()
{
    LOGI("Create new engine");
    return create_engine();
}

bool be_engine_init(BeEngine *engine, BeEngineType type)
{
    LOGI("Init engine");
    // init SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOGE("Cannot init SDL2. Error: %s", SDL_GetError());
        return false;
    }

    // create window
    u32 backend_type;
    switch (type)
    {
    case BE_ENGINE_TYPE_OPENGL:
        backend_type = SDL_WINDOW_OPENGL;
        break;
    case BE_ENGINE_TYPE_VULKAN:
        backend_type = SDL_WINDOW_VULKAN;
        break;
    case BE_ENGINE_TYPE_METAL:
        backend_type = SDL_WINDOW_METAL;
        break;

    default:
        LOGW("Invalid engine type. Trying to use default OPENGL");
        backend_type = SDL_WINDOW_OPENGL;
        break;
    }

    engine->window = SDL_CreateWindow("Badeng ",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      0, 0,
                                      SDL_WINDOW_FULLSCREEN | backend_type);

    if (NULL == engine->window)
    {
        LOGE("Cannot create window. Error: %s", SDL_GetError());
        return false;
    }

    SDL_GetWindowSizeInPixels(engine->window, &(engine->width), &(engine->height));
    return true;
}

void be_engine_set_startup_long(BeEngine *engine, u32 time_millis)
{
    engine->startup_time_millis = time_millis;
}

void be_engine_set_startup_scene(BeEngine *engine, BeScene *scene)
{
    engine->startup_scene = scene;
}

void be_engine_run(BeEngine *engine)
{
    LOGI("Start run engine");
    static bool engine_already_run = false;

    if (engine_already_run)
    {
        LOGI("Engine already run");
        return;
    }
    engine_already_run = true;

    be_scene_manager_start_scene(engine->scene_manager, engine->startup_scene, false);

    bool quite = false;
    u32 time_start = SDL_GetTicks();
    bool on_startup = true;
    SDL_Event e;
    // loop
    while (!quite)
    {
        // event capture
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quite = true;
            }
        }
        // update
        be_scene_manager_update(engine->scene_manager, BE_COMPONENT_TYPE_VISIBILITY);

        // render
        be_scene_manager_draw(engine->scene_manager);
        if (!on_startup)
        {
            continue;
        }

        if (SDL_GetTicks() - time_start >= engine->startup_time_millis)
        {
            LOGI("Start main scene");
            be_scene_manager_start_scene(engine->scene_manager, engine->main_scene, true);
            on_startup = false;
        }
    }

    engine_already_run = false;
}

void be_engine_destroy(BeEngine *engine)
{
    LOGI("Destroy engine");
    if (NULL == engine)
    {
        return;
    }
    if (engine->window)
    {
        SDL_DestroyWindow(engine->window);
        NULLER(engine->window);
    }

    if (engine->scene_manager)
    {
        be_scene_manager_destroy(engine->scene_manager);
    }

    SDL_Quit();
    DESTROYER(engine);
}