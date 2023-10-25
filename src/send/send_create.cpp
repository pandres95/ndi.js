#include <send/send_create.h>
#include <string>

using namespace std;

/**
 * Constructs an instance of SendCreateOptions, which holds the
 * options for creating a `SendInstance`
 */
SendCreateOptions::SendCreateOptions(
    const Napi::Object &object)
    : Napi::Object(object) {}


SendCreateOptions::operator NDIlib_send_create_t() const {
  NDIlib_send_create_t sendCreateParams;

  if (!this->Has("name") || this->Get("name").IsUndefined()) {
    throw Napi::TypeError::New(
        this->Env(), "sendInstanceInitParameters.name value is expected");
  } else if (!this->Get("name").IsString()) {
    throw Napi::TypeError::New(this->Env(),
                               "sendInstanceInitParameters.name expected to be "
                               "a value of String type");
  } else {
    string ndiName = this->Get("name").ToString();
    char *p_ndi_name = new char[ndiName.length()];
    strcpy(p_ndi_name, ndiName.c_str());

    sendCreateParams.p_ndi_name = p_ndi_name;
  }

  sendCreateParams.clock_video =
      (this->Has("clockVideo") && this->Get("clockVideo").IsBoolean())
          ? this->Get("clockVideo").As<Napi::Boolean>().Value()
          : true;

  sendCreateParams.clock_audio =
      (this->Has("clockAudio") && this->Get("clockAudio").IsBoolean())
          ? this->Get("clockAudio").As<Napi::Boolean>().Value()
          : false;

  return sendCreateParams;
}
