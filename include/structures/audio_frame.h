#include <vector>
#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_STRUCTURES_AUDIO_FRAME_H_
#define _SRC_STRUCTURES_AUDIO_FRAME_H_

class AudioFrame {
public:
  AudioFrame(const Napi::Object &);

  int sampleRate;
  Napi::Array channels;

  operator NDIlib_audio_frame_v3_t() const;
};

#endif
