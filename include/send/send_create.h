#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_SEND_SEND_CREATE_H_
#define _SRC_SEND_SEND_CREATE_H_

/**
 * This structure holds the options used for creating a send (output) video
 * source
 */
class SendCreateOptions : Napi::Object {
public:
  /**
   * Constructs an instance of SendCreateOptions, which holds the
   * options for creating a `SendInstance`
   */
  SendCreateOptions(const Napi::Object &object);
  /**
   * A cast operator between this object and the `NDIlib_send_create_t` struct
   */
  operator NDIlib_send_create_t() const;
};

#endif
