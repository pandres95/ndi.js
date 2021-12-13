#include <_module_.h>

void SendVideoSource::Init(Napi::Env env, Napi::Object exports)
{
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "SendVideoSource", {
        InstanceMethod<&SendVideoSource::Initialize>("initialize"),
        InstanceMethod<&SendVideoSource::Send>("send"),
    });

    // Napi::FunctionReference* constructor = new Napi::FunctionReference();

    // Create a persistent reference to the class constructor. This will allow
    // a function called on a class prototype and a function
    // called on instance of a class to be distinguished from each other.
    // *constructor = Napi::Persistent(func);
    exports.Set("SendVideoSource", func);

    // Store the constructor as the add-on instance data. This will allow this
    // add-on to support multiple instances of itself running on multiple worker
    // threads, as well as multiple instances of itself running in different
    // contexts on the same thread.
    //
    // By default, the value set on the environment here will be destroyed when
    // the add-on is unloaded using the `delete` operator, but it is also
    // possible to supply a custom deleter.
    // env.SetInstanceData<Napi::FunctionReference>(constructor);
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    if (!NDIlib_initialize())
    {
        Napi::Error::New(env, "The NDI library could not be initialized")
            .ThrowAsJavaScriptException();
    }

    SendVideoSource::Init(env, Napi::Value(env, exports).As<Napi::Object>());

    napi_status status = napi_add_env_cleanup_hook(env, onDestroyEnvironment, exports);
    assert(status == napi_ok);

    return exports;
}

static void onDestroyEnvironment(void *arg)
{
    NDIlib_destroy();
}

NODE_API_MODULE(ndi, Init)
