#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_STRUCTURES_SOURCE_INSTANCE_H_
#define _SRC_STRUCTURES_SOURCE_INSTANCE_H_

/**
 * An instance of an NDI (send/recv) source
 */
class SourceInstance : public Napi::ObjectWrap<SourceInstance> {
public:
  static void Init(Napi::Env env, Napi::Object exports);
  static Napi::Object New(Napi::Env env, NDIlib_source_t *ndiSourceInstance);
  static Napi::FunctionReference constructor;

  /** Initializes an instance of a sender/receiver source */
  SourceInstance(const Napi::CallbackInfo &info);
  ~SourceInstance();

  /** Sets the tally state of the source instance */
  void SetTally(const Napi::CallbackInfo &info);

  /** Retrieves the IP Address of the instance */
  Napi::Value GetIpAddress(const Napi::CallbackInfo &info);
  /** Retrieves the name of the instance */
  Napi::Value GetName(const Napi::CallbackInfo &info);
  /** Retrieves the URL Address of the instance */
  Napi::Value GetUrlAddress(const Napi::CallbackInfo &info);


private:
  void Initialize(const Napi::CallbackInfo &info);

  NDIlib_source_t ndiSourceInstance;
  NDIlib_recv_instance_t ndiRecvInstance;
};

#endif
