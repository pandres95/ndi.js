#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_STRUCTURES_SOURCE_INSTANCE_H_
#define _SRC_STRUCTURES_SOURCE_INSTANCE_H_

class SourceInstance : public Napi::ObjectWrap<SourceInstance> {
public:
  static void Init(Napi::Env env, Napi::Object exports);
  static Napi::Object New(Napi::Env env, NDIlib_source_t *ndiSourceInstance);
  static Napi::FunctionReference constructor;

  SourceInstance(const Napi::CallbackInfo &info);
  ~SourceInstance();

  void SetTally(const Napi::CallbackInfo &info);

  Napi::Value GetIpAddress(const Napi::CallbackInfo &info);
  Napi::Value GetName(const Napi::CallbackInfo &info);
  Napi::Value GetUrlAddress(const Napi::CallbackInfo &info);


private:
  void Initialize(const Napi::CallbackInfo &info);

  NDIlib_source_t ndiSourceInstance;
  NDIlib_recv_instance_t ndiRecvInstance;
};

#endif
