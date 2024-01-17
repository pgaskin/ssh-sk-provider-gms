<h1 align="center">ssh-sk-provider-gms</h1>

<a href="https://github.com/pgaskin/ssh-sk-provider-gms/actions/workflows/ci.yml"><img align="right" src="https://github.com/pgaskin/ssh-sk-provider-gms/actions/workflows/ci.yml/badge.svg" alt="ci"></a>

**OpenSSH security key provider for Play Services on Android.**

> [!IMPORTANT]
> This is still a work-in-progress, and is not functional yet.

> [!NOTE]
> Setting a custom relying party (i.e., application ID) and enumerating keys requires access to the [`Fido2PrivilegedApiClient`](https://developers.google.com/android/reference/com/google/android/gms/fido/fido2/Fido2PrivilegedApiClient), which uses a whitelist of app certificates. Without this, resident keys cannot be enumerated (i.e., `ssh-add -K`), and the application ID for all keys is chosen by GMS based on the app certificate (meaning you must generate new keys for each app).

#### Usage

1. Ensure `libssh-sk-provider-gms.so` and `libssh-sk-provider-dms.dex` are in the same directory.
2. For `ssh-keygen` and `ssh-add`, set the `SSH_SK_PROVIDER` env var to the path of `libssh-sk-provider-gms.so`.
3. For `ssh`, set the `SecurityKeyProvider` ssh option to the path of `libssh-sk-provider-gms.so`.
4. To generate a new key, TODO.

#### Build

Ensure `ANDROID_HOME` is set to the path of the sdk installation (including build tools 33 and the NDK) and a Java 17+ installation is in your `PATH`.

```bash
# build
$ ./gradlew app:assembleDebugProvider

# extract (e.g., in Termux)
$ tar xf /path/to/app/build/outputs/provider/debug/provider-debug.tar --transform 's#^.+/##x' libssh-sk-provider-gms.dex lib/$(getprop ro.product.cpu.api)/libssh-sk-provider-gms.so
```

You can [download](https://nightly.link/pgaskin/ssh-sk-provider-gms/workflows/ci/master/provider-debug) CI artifacts from GitHub Actions.
