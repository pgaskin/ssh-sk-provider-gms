#include <alloca.h>
#include <android/log.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "sk-api.h"

#define ANDROID_LOG_TAG "SkGmsNative"
#define ANDROID_LOG(level, fmt, ...) __android_log_print(ANDROID_LOG_##level, ANDROID_LOG_TAG, fmt, ##__VA_ARGS__)

#define ERROR_LOG(fmt, ...) do { \
    ANDROID_LOG(ERROR, "(%s:%d) " fmt, __func__, __LINE__, ##__VA_ARGS__); \
    fprintf("ssh-sk-provider-gms: error: (%s:%d) " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
} while (0)

static char sk_init_err[4096];

#define SK_INIT_ERR(fmt, ...) do { \
    if (snprintf(sk_init_err, sizeof(sk_init_err), "(%s:%d) " fmt, __func__, __LINE__, ##__VA_ARGS__) < 0) { \
        if (snprintf(sk_init_err, sizeof(sk_init_err), "(%s:%d) unknown error", __func__, __LINE__) < 0) { \
            strncpy(sk_init_err, "unknown error", sizeof(sk_init_err)); \
        } \
    } \
    ANDROID_LOG(FATAL, "init failed: %s", sk_init_err); \
} while (0)

#define SK_INIT_ERR_CHK() (*sk_init_err ? fprintf(stderr, "ssh-sk-provider-gms: init failed: %s\n", sk_init_err), true : false)

__attribute__((constructor))
static void sk_init_dvm() {
    Dl_info dli;
    if (!dladdr(sk_api_version, &dli)) {
        SK_INIT_ERR("cannot locate own lib");
        return;
    }
    ANDROID_LOG(VERBOSE, "own lib '%s'", dli.dli_fname);

    size_t dli_fname_n = strlen(dli.dli_fname);
    if (dli_fname_n > 3 && dli.dli_fname[dli_fname_n-3] == '.' && dli.dli_fname[dli_fname_n-2] == 's' && dli.dli_fname[dli_fname_n-1] == 'o') {
        dli_fname_n -= 3;
    }
    char *dex_path = alloca(strlen(dli.dli_fname) + 5);
    memcpy(dex_path, dli.dli_fname, dli_fname_n);
    memcpy(&dex_path[dli_fname_n], ".dex\0", 5);
    if (access(dex_path, R_OK) == -1) {
        SK_INIT_ERR("cannot read dex '%s': %s", dex_path, strerror(errno));
        return;
    }
    ANDROID_LOG(VERBOSE, "use dex '%s'", dex_path);

    ANDROID_LOG(VERBOSE, "initializing dalvik vm");
    // TODO: load libdvm and use it like dalvikvm
    SK_INIT_ERR("not implemented");
}

__attribute__((destructor))
static void sk_destroy_dvm() {
    ANDROID_LOG(VERBOSE, "destroying dalvik vm");
}

uint32_t sk_api_version(void) {
    if (*sk_init_err) return SSH_SK_VERSION_MAJOR;
    // TODO: ensure dex sk version equals SSH_SK_VERSION_MAJOR
    return SSH_SK_VERSION_MAJOR;
}

int sk_enroll(uint32_t alg, const uint8_t *challenge, size_t challenge_len,
    const char *application, uint8_t flags, const char *pin,
    struct sk_option **options, struct sk_enroll_response **enroll_response) {
    if (SK_INIT_ERR_CHK()) return SSH_SK_ERR_GENERAL;
    return SSH_SK_ERR_UNSUPPORTED;
}

int sk_sign(uint32_t alg, const uint8_t *data, size_t data_len,
    const char *application, const uint8_t *key_handle, size_t key_handle_len,
    uint8_t flags, const char *pin, struct sk_option **options,
    struct sk_sign_response **sign_response) {
    if (SK_INIT_ERR_CHK()) return SSH_SK_ERR_GENERAL;
    return SSH_SK_ERR_UNSUPPORTED;
}

int sk_load_resident_keys(const char *pin, struct sk_option **options,
    struct sk_resident_key ***rks, size_t *nrks) {
    if (SK_INIT_ERR_CHK()) return SSH_SK_ERR_GENERAL;
    return SSH_SK_ERR_UNSUPPORTED;
}
