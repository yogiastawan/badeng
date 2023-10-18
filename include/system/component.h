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

#ifndef GIHEX_COMPONENT_H
#define GIHEX_COMPONENT_H

#include <stdbool.h>

#include <utilities/mangle.h>
#include <system/component_type.h>

#ifdef __cplusplus
extern C
{
#endif

    typedef struct _be_component BeComponent;
    typedef void (*BeComponentHandler)(BeComponent *component);

    struct _be_component
    {
        u32 id;
        BeComponentType type;
        void *component;
        BeComponentHandler system_handler;
        u32 index_in_system;
        u32 entity_id;
    };

    BeComponent *be_component_new(BeComponentType type, void *component);
    void be_component_destroy(BeComponent * component);

    void be_component_set_system_handler(BeComponent * component, BeComponentHandler handler);

    typedef struct _be_component_visibility BeComponentVisibility;
    struct _be_component_visibility
    {
        bool visible;
    };

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_COMPONENT_H */
