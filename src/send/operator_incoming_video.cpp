#include <send/incoming_video.h>

IncomingVideo::IncomingVideo(Napi::Object object) : width(object.Get("width").ToNumber()),
                                                                height(object.Get("height").ToNumber()),
                                                                colourSpace(object.Get("colourSpace").ToNumber()),
                                                                framerate(object.Get("framerate").ToNumber()) {}

IncomingVideo::operator NDIlib_video_frame_v2_t() const
{
    NDIlib_video_frame_v2_t out;

    out.xres = this->width;
    out.yres = this->height;

    out.picture_aspect_ratio = float(this->width) / float(this->height);

    switch (this->framerate)
    {
    case F24:
        out.frame_rate_N = 24000;
        out.frame_rate_D = 1000;
        break;
    case F2498:
        out.frame_rate_N = 25000;
        out.frame_rate_D = 1001;
        break;
    case F25:
        out.frame_rate_N = 25000;
        out.frame_rate_D = 1000;
        break;
    case F2997:
        out.frame_rate_N = 30000;
        out.frame_rate_D = 1001;
        break;
    case F30:
        out.frame_rate_N = 30000;
        out.frame_rate_D = 1000;
        break;
    case F50:
        out.frame_rate_N = 50000;
        out.frame_rate_D = 1000;
        break;
    case F5994:
        out.frame_rate_N = 60000;
        out.frame_rate_D = 1001;
        break;
    case F60:
        out.frame_rate_N = 60000;
        out.frame_rate_D = 1000;
        break;
    }

    switch (this->colourSpace)
    {
    case UYVY:
        out.FourCC = NDIlib_FourCC_type_UYVY;
        break;

    case UYVA:
        out.FourCC = NDIlib_FourCC_type_UYVA;
        break;

    case P216:
        out.FourCC = NDIlib_FourCC_type_P216;
        break;

    case PA16:
        out.FourCC = NDIlib_FourCC_type_PA16;
        break;

    case YV12:
        out.FourCC = NDIlib_FourCC_type_YV12;
        break;

    case I420:
        out.FourCC = NDIlib_FourCC_type_I420;
        break;

    case NV12:
        out.FourCC = NDIlib_FourCC_type_NV12;
        break;

    case BGRA:
        out.FourCC = NDIlib_FourCC_type_BGRA;
        break;

    case BGRX:
        out.FourCC = NDIlib_FourCC_type_BGRX;
        break;

    case RGBA:
        out.FourCC = NDIlib_FourCC_type_RGBA;
        break;

    case RGBX:
        out.FourCC = NDIlib_FourCC_type_RGBX;
        break;
    }

    out.line_stride_in_bytes = this->width * 4;

    return out;
}
