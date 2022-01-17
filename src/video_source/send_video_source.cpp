#include <iostream>

#include <video_source/send_video_source.h>
#include <video_source/incoming_video.h>

using namespace std;

void SendVideoSource::Send(const Napi::CallbackInfo &info)
{
    Napi::Object incomingVideoParameters = info[0].As<Napi::Object>();
    NDIlib_video_frame_v2_t NDI_video_frame = IncomingVideo(incomingVideoParameters);

    Napi::Array frames = incomingVideoParameters.Get("frames").As<Napi::Array>();

    for (uint32_t idx = 0; idx < frames.Length(); idx++)
    {
        Napi::Buffer<uint8_t> buffer = frames.Get(idx).As<Napi::Buffer<uint8_t> >();
        uint8_t *buffer_data = buffer.Data();

        NDI_video_frame.p_data = buffer_data;
        NDIlib_send_send_video_async_v2(this->sendInstance, &NDI_video_frame);
    }
}
