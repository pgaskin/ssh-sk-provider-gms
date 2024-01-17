#include <android/log.h>
#include <stdint.h>
#include "sk-api.h"

#define ANDROID_LOG_TAG "SkGmsNative"
#define ANDROID_LOG(level, fmt, ...) __android_log_print(ANDROID_LOG_##level, ANDROID_LOG_TAG, fmt, ##__VA_ARGS__)

__attribute__((constructor))
static void sk_init_dvm() {
    ANDROID_LOG(VERBOSE, "initializing dalvik vm");
    // TODO: load libdvm and use it like dalvikvm
}

__attribute__((destructor))
static void sk_destroy_dvm() {
    ANDROID_LOG(VERBOSE, "destroying dalvik vm");
}

uint32_t sk_api_version(void) {
    return SSH_SK_VERSION_MAJOR;
}

int sk_enroll(uint32_t alg, const uint8_t *challenge, size_t challenge_len,
    const char *application, uint8_t flags, const char *pin,
    struct sk_option **options, struct sk_enroll_response **enroll_response) {
    return SSH_SK_ERR_UNSUPPORTED;
}

int sk_sign(uint32_t alg, const uint8_t *data, size_t data_len,
    const char *application, const uint8_t *key_handle, size_t key_handle_len,
    uint8_t flags, const char *pin, struct sk_option **options,
    struct sk_sign_response **sign_response) {
    return SSH_SK_ERR_UNSUPPORTED;
}

int sk_load_resident_keys(const char *pin, struct sk_option **options,
    struct sk_resident_key ***rks, size_t *nrks) {
    return SSH_SK_ERR_UNSUPPORTED;
}
