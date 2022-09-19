#include <find/find_sources.h>
#include <find/source_instance.h>
#include <iostream>

Napi::Value FindSources(const Napi::CallbackInfo &info) {
  NDIlib_find_create_t NDI_find_create_desc;
  NDIlib_find_instance_t pNDI_find =
      NDIlib_find_create_v2(&NDI_find_create_desc);

  uint32_t timeout_in_ms = 5000;
  if (info.Length() == 1) {
    timeout_in_ms = info[0].As<Napi::Number>();
  }

  if (!NDIlib_find_wait_for_sources(pNDI_find, timeout_in_ms)) {
    return Napi::Array::New(info.Env());
  } else {
    // Get the updated list of sources
    uint32_t no_sources = 0;
    const NDIlib_source_t *p_sources =
        NDIlib_find_get_current_sources(pNDI_find, &no_sources);

    // Display all the sources.
    Napi::Array sourcesList = Napi::Array::New(info.Env(), (size_t)no_sources);

    for (uint32_t i = 0; i < no_sources; i++) {
      NDIlib_source_t p_source = NDIlib_source_t(p_sources[i]);

      Napi::Object sourceInstance = SourceInstance::New(info.Env(), &p_source);
      sourcesList[i] = sourceInstance;
    }

    NDIlib_find_destroy(pNDI_find);

    return sourcesList;
  }
}
