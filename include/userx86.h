#ifndef USERX86_H_
#define USERX86_H_

#ifdef __cplusplus
extern "C" {
#endif

// 把串
static inline void
stosb(void *addr, int data, int cnt) {
    asm volatile(
        "cld; rep stosb":
        "=D"(addr), "=c"(cnt):
        "0"(addr), "1"(cnt), "a"(data):
        "memory", "cc"
    );
}

static inline void
stosl(void *addr, int data, int cnt) {
    asm volatile(
        "cld; rep stosl":
        "=D"(addr), "=c"(cnt):
        "0"(addr), "1"(cnt), "a"(data):
        "memory", "cc"
    );
}


#ifdef __cplusplus
}
#endif

#endif
