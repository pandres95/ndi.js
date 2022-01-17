#include <ndi.h>

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    if (!NDIlib_initialize())
    {
        Napi::Error::New(env, "The NDI library could not be initialized")
            .ThrowAsJavaScriptException();
    }

    SendInstance::Init(env, Napi::Value(env, exports).As<Napi::Object>());

    napi_status status = napi_add_env_cleanup_hook(env, onDestroyEnvironment, exports);
    assert(status == napi_ok);

    return exports;
}

void SendInstance::Init(Napi::Env env, Napi::Object exports)
{
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SendInstance", {
        InstanceMethod<&SendInstance::Initialize>("initialize"),
        InstanceMethod<&SendInstance::Send>("send"),
    });

    exports.Set("SendInstance", func);
}

static void onDestroyEnvironment(void *arg)
{
    NDIlib_destroy();
}

NODE_API_MODULE(ndi, Init)
