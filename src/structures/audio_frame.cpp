#include <structures/audio_frame.h>

AudioFrame::AudioFrame(const Napi::Object &object)
    : sampleRate(object.Get("sampleRate").ToNumber()),
      channels(object.Get("channels").As<Napi::Array>()) {}

AudioFrame::operator NDIlib_audio_frame_v3_t() const {
  NDIlib_audio_frame_v3_t out;

  out.no_channels = this->channels.Length();
  out.sample_rate = this->sampleRate;

  Napi::Float32Array firstChannel =
      this->channels[(uint32_t)0].As<Napi::Float32Array>();
  int samples_in_frame = firstChannel.ElementLength();

  out.no_samples = samples_in_frame;
  out.channel_stride_in_bytes = sizeof(float) * samples_in_frame;

  out.p_data = (uint8_t *)malloc(out.no_channels * out.channel_stride_in_bytes);

  for (int ch = 0; ch < out.no_channels; ch++) {
    Napi::Float32Array channelData =
        this->channels.Get(ch).As<Napi::Float32Array>();

    float *buffer = channelData.Data();

    // Get the pointer to the start of this ch
    float *p_ch =
        (float *)((uint8_t *)out.p_data + (ch * out.channel_stride_in_bytes));

    // Fill it with the audio source
    for (int sample_no = 0; sample_no < out.no_samples; sample_no++)
      p_ch[sample_no] = buffer[sample_no];
  }

  return out;
}
