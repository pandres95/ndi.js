#include <napi.h>
#include <Processing.NDI.Advanced.h>

#include <video_source.h>

static Napi::Object Init(Napi::Env env, Napi::Object exports);
static void onDestroyEnvironment(void *arg);
