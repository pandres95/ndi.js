#include <napi.h>

#ifndef _SRC_FIND_FIND_SOURCES_H_
#define _SRC_FIND_FIND_SOURCES_H_

/**
 * Calls `NDIlib_find_get_current_sources` and retrieves the list of
 * the available sources to be retrieved.
 *
 * If no sources are available, or the `NDIlib_find_wait_for_sources`
 * call fails, retrieves an empty list.
 */
Napi::Value FindSources(const Napi::CallbackInfo&);

#endif
