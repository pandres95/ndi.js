#include <napi.h>
#include <Processing.NDI.Lib.h>

#include <video_source/send_video_source.h>

static Napi::Object Init(Napi::Env env, Napi::Object exports);
static void onDestroyEnvironment(void *arg);
