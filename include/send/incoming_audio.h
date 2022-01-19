#include <vector>
#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_INCOMING_AUDIO_H_
#define _SRC_INCOMING_AUDIO_H_

class IncomingAudioParameters {
public:
  IncomingAudioParameters(const Napi::Object &);

  int sampleRate;
  int framerate_N;
  int framerate_D;
  int channelsNumber;

  Napi::Array frames;

  operator NDIlib_audio_frame_v2_t() const;
};

#endif
