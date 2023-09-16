#include <badeng.h>

int main(int argc, char const *argv[])
{
    BeEngine *eng = be_engine_new();
    be_engine_run(eng, BE_ENGINE_TYPE_VULKAN);
    be_engine_destroy(eng);
    return 0;
}
