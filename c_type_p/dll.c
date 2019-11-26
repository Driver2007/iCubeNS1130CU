#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)
#  define DLL_EXPORT __declspec(dllexport)
#else
#  define DLL_EXPORT
#endif

#define PRINT_MSG_2SX(ARG0, ARG1) printf("From C - [%s] (%d) - [%s]:  ARG0: [%s], ARG1: 0x%016llX\n", __FILE__, __LINE__, __FUNCTION__, ARG0, (unsigned long long)ARG1)


static float f = 1.618033;

typedef struct Effect {
    void *ptr;
} 
Effect;


DLL_EXPORT void test(Effect *pEffect, int null) {
    PRINT_MSG_2SX("pEffect", pEffect);
    PRINT_MSG_2SX("pEffect->ptr", pEffect->ptr);
    PRINT_MSG_2SX("&pEffect->ptr", &pEffect->ptr);
    pEffect->ptr = !null ? NULL : &f;
    PRINT_MSG_2SX("new pEffect->ptr", pEffect->ptr);
}
