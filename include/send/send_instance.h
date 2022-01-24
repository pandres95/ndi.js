#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_SEND_SEND_INSTANCE_H_
#define _SRC_SEND_SEND_INSTANCE_H_

class SendInstance : public Napi::ObjectWrap<SendInstance> {
public:
  static void Init(Napi::Env env, Napi::Object exports);

  SendInstance(const Napi::CallbackInfo &info);
  ~SendInstance();

  void Initialize(const Napi::CallbackInfo &info);
  void Send(const Napi::CallbackInfo &info);

private:
  NDIlib_send_instance_t ndiSendInstance;
};

#endif
