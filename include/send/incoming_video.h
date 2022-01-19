#include <napi.h>
#include <Processing.NDI.Lib.h>

#ifndef _SRC_INCOMING_BUFFERS_H_
#define _SRC_INCOMING_BUFFERS_H_

class IncomingVideoParameters
{
public:
    IncomingVideoParameters(const Napi::Object&);

    int width;
    int height;

    int colourSpace;
    int framerate;

    Napi::Array frames;

    operator NDIlib_video_frame_v2_t() const;
};

typedef enum video_colour_space_type
{
    UYVY = 1,
    UYVA = 2,
    P216 = 3,
    PA16 = 4,
    YV12 = 5,
    I420 = 6,
    NV12 = 7,
    BGRA = 8,
    BGRX = 9,
    RGBA = 10,
    RGBX = 11
} video_colour_space_type;

typedef enum video_framerate
{
    F24 = 1,
    F2498 = 2,
    F25 = 3,
    F2997 = 4,
    F30 = 5,
    F50 = 6,
    F5994 = 7,
    F60 = 8
} video_framerate;

#endif
