#ifndef GIHEX_CHECKER_H
#define GIHEX_CHECKER_H

#include <utilities/log.h>

#ifdef __cplusplus
extern C
{
#endif

#ifdef GX_DEBUG
#define VAR_NAME(X) #X
#define NULL_CHECKER(X)                      \
    if (NULL == X)                           \
    {                                        \
        LOGE("\"%s\" is NULL", VAR_NAME(X)); \
        return;                              \
    }
#define NULL_CHECKER_VAL(X, V)               \
    if (NULL == X)                           \
    {                                        \
        LOGE("\"%s\" is NULL", VAR_NAME(X)); \
        return V;                            \
    }
#else
#define VAR_NAME(X)
#define NULL_CHECKER(X)
#define NULL_CHECKER_VAL(X, V)
#endif

#define DESTROYER(X)                 \
    LOGI(":>Destroying \"%s\"", #X); \
    free(X);                         \
    X = NULL

#define NULLER(X)                 \
    LOGI(":>Nulling \"%s\"", #X); \
    X = NULL

#define ASSOIATED_FAILED(X, Y)                   \
    LOGE("\"%s\" is not assoiated with \"%s\"", #X, #Y); \
    return

#ifdef __cplusplus
}
#endif

#endif /* GIHEX_CHECKER_H */
