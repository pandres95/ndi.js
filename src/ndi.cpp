#include <cassert>
#include <ndi.h>

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  if (!NDIlib_initialize()) {
    Napi::Error::New(env, "The NDI library could not be initialized")
        .ThrowAsJavaScriptException();
  }

  SendInstance::Init(env, Napi::Value(env, exports).As<Napi::Object>());
  SourceInstance::Init(env, Napi::Value(env, exports).As<Napi::Object>());

  exports.Set("findSources", Napi::Function::New(env, FindSources));

  napi_status status =
      napi_add_env_cleanup_hook(env, onDestroyEnvironment, exports);
  assert(status == napi_ok);

  return exports;
}

void SendInstance::Init(Napi::Env env, Napi::Object exports) {
  // This method is used to hook the accessor and method callbacks
  Napi::Function func =
      DefineClass(env, "SendInstance",
                  {
                      InstanceMethod<&SendInstance::Initialize>("initialize"),
                      InstanceMethod<&SendInstance::Send>("send"),
                  });

  exports.Set("SendInstance", func);
}

Napi::FunctionReference SourceInstance::constructor;
void SourceInstance::Init(Napi::Env env, Napi::Object exports) {
  // This method is used to hook the accessor and method callbacks
  Napi::Function func =
      DefineClass(env, "SourceInstance",
                  {
                      InstanceMethod<&SourceInstance::SetTally>("setTally"),
                      InstanceAccessor<&SourceInstance::GetIpAddress>("ipAddress"),
                      InstanceAccessor<&SourceInstance::GetName>("name"),
                      InstanceAccessor<&SourceInstance::GetUrlAddress>("urlAddress"),
                  });

  SourceInstance::constructor = Napi::Persistent(func);
  SourceInstance::constructor.SuppressDestruct();

  exports.Set("SourceInstance", func);
}

static void onDestroyEnvironment(void *arg) { NDIlib_destroy(); }

NODE_API_MODULE(ndi, Init)
