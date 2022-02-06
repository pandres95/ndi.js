export interface VideoFrame {
  height: number;
  width: number;

  colourSpace: VideoColourSpace;
  framerate: VideoFramerate;

  data: Buffer | Uint8Array;
}

export enum VideoColourSpace {
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
  RGBX = 11,
}

export enum VideoFramerate {
  F24 = 1,
  F2498 = 2,
  F25 = 3,
  F2997 = 4,
  F30 = 5,
  F50 = 6,
  F5994 = 7,
  F60 = 8,
}
