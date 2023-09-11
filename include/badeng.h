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

#ifdef __cplusplus
extern C
{
#endif

    typedef struct _be_engine BeEngine;

    struct _be_engine
    {
        /* data */
        u32 numb_entity;
        u32 cap_component;
        u32 numb_component;
        BeComponent **components;
    };

    BeEngine *be_engine_new();

    void be_engine_run(BeEngine * engine);

    void be_engine_destroy(BeEngine * engine);

    void bd_engine_add_entity(BeEngine * eng, BeEntity * entity);

    void be_engine_add_component(BeEngine * eng, BeEntity * entity, BeComponent *component);

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_BADENG_H */
