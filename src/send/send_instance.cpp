#include <iostream>

#include <send/send_create.h>
#include <send/send_instance.h>
#include <structures/audio_frame.h>
#include <structures/video_frame.h>

using namespace std;

SendInstance::SendInstance(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<SendInstance>(info) {}

void SendInstance::Initialize(const Napi::CallbackInfo &info) {
  // Validate the initParameters argument
  if (info.Length() == 0) {
    Napi::TypeError::New(info.Env(), "The initParameters argument is expected")
        .ThrowAsJavaScriptException();
    return;
  }

  if (!info[0].IsObject()) {
    Napi::TypeError::New(
        info.Env(), "The initParameters argument is expected to be an object")
        .ThrowAsJavaScriptException();
    return;
  }

  // Initialize sendCreate parameters using the initParameters argument
  try {
    NDIlib_send_create_t sendCreateParams =
        (SendCreate)info[0].ToObject();

    this->ndiSendInstance = NDIlib_send_create(&sendCreateParams);

    if (!this->ndiSendInstance) {
      throw Napi::Error::New(info.Env(), "Could not initialize the instance");
    }
  } catch (const Napi::Error &error) {
    error.ThrowAsJavaScriptException();
  }
}

void SendInstance::Send(const Napi::CallbackInfo &info) {
  if (info.Length() == 0 || info[0].IsUndefined() || info[0].IsNull() || !info[0].IsArray()) {
    Napi::TypeError::New(
      info.Env(), "The frames argument is expected to be an Array"
    ).ThrowAsJavaScriptException();
    return;
  }

  const Napi::Array frames = info[0].As<Napi::Array>();

  for (uint32_t idx = 0; idx < frames.Length(); idx++) {
    const Napi::Object frame = frames.Get(idx).As<Napi::Object>();

    if (frame.Has("audio") && !frame.Get("audio").IsUndefined() && !frame.Get("audio").IsNull()) {
      const NDIlib_audio_frame_v3_t audioFrame = (AudioFrame) frame.Get("audio").As<Napi::Object>();
      NDIlib_send_send_audio_v3(this->ndiSendInstance, &audioFrame);
      free(audioFrame.p_data);
    }

    if (frame.Has("video") && !frame.Get("video").IsUndefined() && !frame.Get("video").IsNull()) {
      const NDIlib_video_frame_v2_t ndiVideoFrame = (VideoFrame) frame.Get("video").As<Napi::Object>();
      NDIlib_send_send_video_async_v2(this->ndiSendInstance, &ndiVideoFrame);
    }
  }
}

SendInstance::~SendInstance() { NDIlib_send_destroy(this->ndiSendInstance); }
