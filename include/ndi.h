#include <napi.h>
#include <Processing.NDI.Lib.h>

#include <send/send_instance.h>

static Napi::Object Init(Napi::Env env, Napi::Object exports);
static void onDestroyEnvironment(void *arg);
