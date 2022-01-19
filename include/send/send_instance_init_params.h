#include <napi.h>
#include <Processing.NDI.Lib.h>

class SendInstanceInitParameters : Napi::Object {
public:
  SendInstanceInitParameters(const Napi::Object &object);
  operator NDIlib_send_create_t() const;
};
