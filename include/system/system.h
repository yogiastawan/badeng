#ifndef GIHEX_SYSTEM_H
#define GIHEX_SYSTEM_H

#include <system/component.h>

#ifdef __cplusplus
extern C
{
#endif
    typedef struct _be_system BeSystem;
    struct _be_system
    {
        u32 numb_slice_component[NUMB_COMPONENT];
        u32 cap_slice_component[NUMB_COMPONENT];
        u32 *id_slice_component[NUMB_COMPONENT];
    };

    BeSystem be_system_new();
    void system_visible_update(BeComponent * comp);
    
#ifdef __cplusplus
}
#endif

#endif /* GIHEX_SYSTEM_H */
