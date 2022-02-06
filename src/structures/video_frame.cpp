#include <cassert>
#include <iostream>
#include <structures/video_frame.h>

using namespace std;

VideoFrame::VideoFrame(const Napi::Object &object)
    : width(object.Get("width").ToNumber()),
      height(object.Get("height").ToNumber()),
      colourSpace(object.Get("colourSpace").ToNumber()),
      framerate(object.Get("framerate").ToNumber()), data(object.Get("data")) {}

VideoFrame::operator NDIlib_video_frame_v2_t() const {
  NDIlib_video_frame_v2_t out;

  out.xres = this->width;
  out.yres = this->height;

  out.picture_aspect_ratio = float(this->width) / float(this->height);

  switch (this->framerate) {
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

  float rstride_in_bytes = 0;

  switch (this->colourSpace) {
  case UYVY:
    // 4:2:2 = 16 bit (2 bytes)
    rstride_in_bytes = 2;
    out.FourCC = NDIlib_FourCC_video_type_UYVY;
    break;
  case UYVA:
    // 4:2:2:4 = 24 bit (3 bytes)
    rstride_in_bytes = 3;
    out.FourCC = NDIlib_FourCC_video_type_UYVA;
    break;
  case P216:
    // 4:2:2 = 16 bit (2 bytes)
    rstride_in_bytes = 2;
    out.FourCC = NDIlib_FourCC_video_type_P216;
    break;
  case PA16:
    // 4:2:2:4 = 24 bit (3 bytes)
    rstride_in_bytes = 3;
    out.FourCC = NDIlib_FourCC_video_type_PA16;
    break;
  case YV12:
    // 4:2:0 = 12 bit (1.5 bytes)
    rstride_in_bytes = 1.5;
    out.FourCC = NDIlib_FourCC_video_type_YV12;
    break;
  case I420:
    // 4:2:0 = 12 bit (1.5 bytes)
    rstride_in_bytes = 1.5;
    out.FourCC = NDIlib_FourCC_video_type_I420;
    break;
  case NV12:
    // 4:2:0 = 12 bit (1.5 bytes)
    rstride_in_bytes = 1.5;
    out.FourCC = NDIlib_FourCC_video_type_NV12;
    break;
  case BGRA:
    // 4:4:4:4 = 32 bit (4 bytes)
    rstride_in_bytes = 4;
    out.FourCC = NDIlib_FourCC_video_type_BGRA;
    break;
  case BGRX:
    // 4:4:4:x = 32 bit (4 bytes)
    rstride_in_bytes = 4;
    out.FourCC = NDIlib_FourCC_video_type_BGRX;
    break;
  case RGBA:
    // 4:4:4:4 = 32 bit (4 bytes)
    rstride_in_bytes = 4;
    out.FourCC = NDIlib_FourCC_video_type_RGBA;
    break;
  case RGBX:
    // 4:4:4:x = 32 bit (4 bytes)
    rstride_in_bytes = 4;
    out.FourCC = NDIlib_FourCC_video_type_RGBX;
    break;
  }

  out.line_stride_in_bytes = this->width * rstride_in_bytes;

  if (!this->data.IsTypedArray() || !this->data.IsBuffer()) {
    throw Napi::TypeError::New(
        this->data.Env(), "`data` should be either a Buffer or a Uint8Array");
    return NULL;
  }

  float frameStride = 0;
  uint8_t *buffer_data;

  if (this->data.IsTypedArray()) {
    Napi::Uint8Array dataFrame = this->data.As<Napi::Uint8Array>();

    frameStride = (dataFrame.ElementLength() / (this->width * this->height));
    buffer_data = dataFrame.Data();
  } else {
    Napi::Buffer<uint8_t> dataFrame = this->data.As<Napi::Buffer<uint8_t> >();

    frameStride = (dataFrame.ElementLength() / (this->width * this->height));
    buffer_data = dataFrame.Data();
  }

  if (frameStride != rstride_in_bytes) {
    string errorMessage = "stream `rstride_in_bytes` is " +
                          to_string(frameStride) + ", it should be " +
                          to_string(rstride_in_bytes);
    throw Napi::Error::New(this->data.Env(), errorMessage);
    return NULL;
  }

  out.p_data = buffer_data;

  return out;
}
