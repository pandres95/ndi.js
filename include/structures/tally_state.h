#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_STRUCTURES_TALLY_STATE_H_
#define _SRC_STRUCTURES_TALLY_STATE_H_

class TallyState {
public:
  TallyState(const Napi::Object &);

  bool onProgram;
  bool onPreview;

  operator NDIlib_tally_t() const;
};

#endif
