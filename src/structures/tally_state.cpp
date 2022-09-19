#include <structures/tally_state.h>

TallyState::TallyState(const Napi::Object &object)
    : onProgram(object.Get("onProgram").ToBoolean()),
      onPreview(object.Get("onPreview").ToBoolean()) {}

TallyState::operator NDIlib_tally_t() const {
  NDIlib_tally_t out;

  out.on_preview = this->onPreview;
  out.on_program = this->onProgram;

  return out;
}
