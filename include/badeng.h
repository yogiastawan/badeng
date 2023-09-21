/**
 * Copyright 2023 I Gede Yogi Astawan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GIHEX_BADENG_H
#define GIHEX_BADENG_H

#include <utilities/mangle.h>
#include <system/entity.h>
#include <system/component.h>
#include <system/system.h>
#include <scene/scene_manager.h>

#include <SDL.h>

#ifdef __cplusplus
extern C
{
#endif

    typedef enum _be_engine_type BeEngineType;

    enum _be_engine_type
    {
        BE_ENGINE_TYPE_OPENGL,
        BE_ENGINE_TYPE_VULKAN,
        BE_ENGINE_TYPE_METAL,
    };

    typedef struct _be_engine BeEngine;

    /**
     * @brief BeEngine data structure
     */
    struct _be_engine
    {

        i32 width;          /**< Width of screen*/
        i32 height;         /**< Height of screen*/
        SDL_Window *window; /**< Window context*/
        BeSceneManager *scene_manager;
        BeScene *startup_scene;
        u32 startup_time_millis;
        BeScene *main_scene;
    };

    /**
     * @brief Create new `BeEngine`
     *
     * @return Pointer of `BeEngine`
     */
    BeEngine *be_engine_new();

    bool be_engine_init(BeEngine * engine, BeEngineType type);

    void be_engine_run(BeEngine * engine);

    void be_engine_destroy(BeEngine * engine);

    void be_engine_set_startup_scene(BeEngine * engine, BeScene * scene);

    /**
     * @brief Set `BeEngine` length time in milliseconds
     *
     * @param engine Pointer to BeEngine that will be set
     * @param u32   Time length in milliseconds
     */
    void be_engine_set_startup_length(BeEngine * engine, u32 time_millis);

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_BADENG_H */
