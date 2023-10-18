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

#ifndef GIHEX_ENTITY_H
#define GIHEX_ENTITY_H

#include <stdbool.h>

#include <utilities/mangle.h>
#include <system/component.h>

#define DEFAULT_COMPONENT_CAPACITY 4

#ifdef __cplusplus
extern C
{
#endif

    typedef struct _be_entity BeEntity;

    struct _be_entity
    {
        u32 id;
        u32 component_id[NUMB_TYPE_COMPONENT];
        bool has_component[NUMB_TYPE_COMPONENT];
    };

    BeEntity *be_entity_new();
    void be_entity_destroy(BeEntity * entt);

#ifdef __cplusplus
}
#endif

#endif/* GIHEX_ENTITY_H */
