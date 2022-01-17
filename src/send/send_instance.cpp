#include <send/send_instance.h>

#include <send/incoming_video.h>
#include <send/send_instance_init_params.h>

SendInstance::SendInstance(const Napi::CallbackInfo &info) : Napi::ObjectWrap<SendInstance>(info) {}

void SendInstance::Initialize(const Napi::CallbackInfo &info)
{
    // Validate the initParameters argument
    if (info.Length() == 0)
    {
        Napi::TypeError::New(info.Env(), "The initParameters argument is expected")
            .ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsObject())
    {
        Napi::TypeError::New(info.Env(), "The initParameters argument is expected to be an object")
            .ThrowAsJavaScriptException();
        return;
    }

    // Initialize sendCreate parameters using the initParameters argument
    try {
        NDIlib_send_create_t sendCreateParams = (SendInstanceInitParameters) info[0].ToObject();

        this->ndiSendInstance = NDIlib_send_create(&sendCreateParams);

        if (!this->ndiSendInstance)
        {
            Napi::Error::New(info.Env(), "Could not initialize the instance")
                .ThrowAsJavaScriptException();
        }
    } catch (const char* error) {
        Napi::TypeError::New(info.Env(), error)
            .ThrowAsJavaScriptException();
    }
}

void SendInstance::Send(const Napi::CallbackInfo &info)
{
    Napi::Object incomingVideoParameters = info[0].As<Napi::Object>();
    NDIlib_video_frame_v2_t NDI_video_frame = IncomingVideo(incomingVideoParameters);

    Napi::Array frames = incomingVideoParameters.Get("frames").As<Napi::Array>();

    for (uint32_t idx = 0; idx < frames.Length(); idx++)
    {
        Napi::Buffer<uint8_t> buffer = frames.Get(idx).As<Napi::Buffer<uint8_t> >();
        uint8_t *buffer_data = buffer.Data();

        NDI_video_frame.p_data = buffer_data;
        NDIlib_send_send_video_async_v2(this->ndiSendInstance, &NDI_video_frame);
    }
}

SendInstance::~SendInstance()
{
    NDIlib_send_destroy(this->ndiSendInstance);
}
