#include <find/source_instance.h>
#include <iostream>
#include <structures/tally_state.h>

using namespace std;

Napi::Object SourceInstance::New(Napi::Env env,
                                 NDIlib_source_t *ndiSourceInstance) {
  return SourceInstance::constructor.Value().New({
      Napi::External<NDIlib_source_t>::New(env, ndiSourceInstance),
  });
}

SourceInstance::SourceInstance(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<SourceInstance>(info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1 || (info[0].Type() != napi_external)) {
    throw Napi::Error::New(
        env, "SourceInstances can only be constructed by native code");
  }

  NDIlib_source_t ndiSourceInstance =
      *(info[0].As<Napi::External<NDIlib_source_t> >().Data());

  string str_ndi_name = ndiSourceInstance.p_ndi_name;
  char *cstr_ndi_name = new char[str_ndi_name.length()];
  strcpy(cstr_ndi_name, str_ndi_name.c_str());

  string str_url_address = ndiSourceInstance.p_url_address;
  char *cstr_url_address = new char[str_url_address.length()];
  strcpy(cstr_url_address, str_url_address.c_str());

  this->ndiSourceInstance = NDIlib_source_t(cstr_ndi_name, cstr_url_address);

  this->Initialize(info);
}

void SourceInstance::Initialize(const Napi::CallbackInfo &info) {
  NDIlib_recv_create_v3_t NDI_recv_create_desc(this->ndiSourceInstance);

  try {
    this->ndiRecvInstance = NDIlib_recv_create_v3(&NDI_recv_create_desc);

    if (!this->ndiRecvInstance) {
      throw Napi::Error::New(info.Env(),
                             "Could not initialize source receiver");
    }
  } catch (const Napi::Error &error) {
    error.ThrowAsJavaScriptException();
  }
}

void SourceInstance::SetTally(const Napi::CallbackInfo &info) {
  if (!info[0].IsObject()) {
    Napi::TypeError::New(info.Env(),
                         "The tallyState argument is expected to be an object")
        .ThrowAsJavaScriptException();
    return;
  }

  NDIlib_tally_t tally_state = (TallyState)info[0].ToObject();
  NDIlib_recv_set_tally(this->ndiRecvInstance, &tally_state);
}

Napi::Value SourceInstance::GetIpAddress(const Napi::CallbackInfo &info) {
  return Napi::String::New(info.Env(), this->ndiSourceInstance.p_ip_address);
}

Napi::Value SourceInstance::GetName(const Napi::CallbackInfo &info) {
  return Napi::String::New(info.Env(), this->ndiSourceInstance.p_ndi_name);
}

Napi::Value SourceInstance::GetUrlAddress(const Napi::CallbackInfo &info) {
  return Napi::String::New(info.Env(), this->ndiSourceInstance.p_url_address);
}

SourceInstance::~SourceInstance() {
  if (!this->ndiRecvInstance) {
    return;
  }

  NDIlib_recv_destroy(this->ndiRecvInstance);
}
