package net.pgaskin.ssh.sk.provider.gms;

import android.app.Application;
import com.google.android.gms.fido.Fido;
import com.google.android.gms.fido.fido2.Fido2ApiClient;

// see sk-api.h
public final class SkApi {
    private final String TAG = "SkGms";

    // flags
    public static final int SSH_SK_USER_PRESENCE_REQD = 0x01;
    public static final int SSH_SK_USER_VERIFICATION_REQD = 0x04;
    public static final int SSH_SK_FORCE_OPERATION = 0x10;
    public static final int SSH_SK_RESIDENT_KEY = 0x20;

    // algs
    public static final int SSH_SK_ECDSA = 0x00;
    public static final int SSH_SK_ED25519 = 0x01;

    // error codes
    public static final int SSH_SK_ERR_GENERAL = -1;
    public static final int SSH_SK_ERR_UNSUPPORTED = -2;
    public static final int SSH_SK_ERR_PIN_REQUIRED = -3;
    public static final int SSH_SK_ERR_DEVICE_NOT_FOUND = -4;
    public static final int SSH_SK_ERR_CREDENTIAL_EXISTS = -5;

    public static final class sk_enroll_response {
        public byte flags;
        public byte[] public_key;
        public byte[] key_handle;
        public byte[] signature;
        public byte[] attestation_cert;
        public byte[] authdata;
    }

    public static final class sk_sign_response {
        public byte flags;
        public int counter; // uint32
        public byte[] sig_r;
        public byte[] sig_s;
    }

    public static final class sk_resident_key {
        public int alg; // uint32
        public long slot; // size_t
        public String application; // char*
        public sk_enroll_response key;
        public byte flags;
        public byte[] user_id;
    }

    public static final class sk_option {
        public String name; // char*
        public String value; // char*
        public boolean required; // uint8
    }

    public static int SSH_SK_VERSION_MAJOR = 0x000a0000;
    public static int SSH_SK_VERSION_MAJOR_MASK = 0xffff0000;

    public int sk_api_version() {
        return SSH_SK_VERSION_MAJOR;
    }

    public static sk_enroll_response sk_enroll(int /* uint32 */ alg, byte[] challenge, String /* char* */ application, byte flags, String /* char* */ pin, sk_option[] options) {
        final Fido2ApiClient fido2 = Fido.getFido2ApiClient(getApplicationContext());
        throw new RuntimeException("not implemented");
    }

    public static sk_sign_response sk_sign(int /* uint32 */ alg, byte[] data, String /* char* */ application, byte[] key_handle, byte flags, String /* char* */ pin, sk_option[] options) {
        final Fido2ApiClient fido2 = Fido.getFido2ApiClient(getApplicationContext());
        throw new RuntimeException("not implemented");
    }

    public static sk_resident_key[] sk_load_resident_keys(String /* char* */ pin, sk_option[] options) {
        throw new RuntimeException("not implemented");
    }

    private static Application getApplicationContext() {
        try {
            try {
                Application c = (Application) Class.forName("android.app.ActivityThread").getMethod("currentApplication").invoke(null, (Object[]) null);
                if (c == null)
                    throw new NullPointerException("android.app.ActivityThread.currentApplication() == null");
                return c;
            } catch (Exception e) {
                Application c = (Application) Class.forName("android.app.AppGlobals").getMethod("getInitialApplication").invoke(null, (Object[]) null);
                if (c == null)
                    throw new NullPointerException("android.app.AppGlobals.getInitialApplication() == null");
                return c;
            }
        } catch (Exception e) {
            throw new RuntimeException("Failed to get application context using reflection: " + e, e);
        }
    }
}
