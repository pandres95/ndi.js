#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_SEND_SEND_CREATE_H_
#define _SRC_SEND_SEND_CREATE_H_

class SendCreate : Napi::Object {
public:
  SendCreate(const Napi::Object &object);
  operator NDIlib_send_create_t() const;
};

#endif
