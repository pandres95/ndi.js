#include <napi.h>
#include <Processing.NDI.Advanced.h>

#ifndef _VIDEO_SOURCE_H_
#define _VIDEO_SOURCE_H_

class SendVideoSource : public Napi::ObjectWrap<SendVideoSource>
{
public:
    static void Init(Napi::Env env, Napi::Object exports);

    SendVideoSource(const Napi::CallbackInfo& info);
    ~SendVideoSource();

    void Initialize(const Napi::CallbackInfo& info);
    void Send(const Napi::CallbackInfo& info);
private:
    NDIlib_send_instance_t sendInstance;
};

#endif
