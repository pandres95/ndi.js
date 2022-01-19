#include <cmath>
#include <send/incoming_audio.h>

IncomingAudioParameters::IncomingAudioParameters(const Napi::Object &object)
    : sampleRate(object.Get("sampleRate").ToNumber()),
      channelsNumber(object.Get("channels").ToNumber()),
      frames(object.Get("frames").As<Napi::Array>()) {}

IncomingAudioParameters::operator NDIlib_audio_frame_v2_t() const {
  NDIlib_audio_frame_v2_t out;

  out.no_channels = this->channelsNumber;
  out.sample_rate = this->sampleRate;

  float framerate = (float)this->framerate_N / (float)this->framerate_D;
  int samples_in_frame = (int)ceil((float)out.sample_rate / framerate);

  out.no_samples = samples_in_frame;
  out.channel_stride_in_bytes = sizeof(float) * samples_in_frame;

  return out;
}
