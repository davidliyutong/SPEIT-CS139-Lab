#include "debug.h"

int main() {
    LOGI("Hello, %s world!", "this");
    LOGE("GoodBye");
    void* ptr = NULL;
    CHECK(ptr, "Pointer is NULL");
    return 0;
error:
    return ENOMEM;
}