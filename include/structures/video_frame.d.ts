/**
 * This structure holds the metadata and binary
 * representation of a single frame of video, that can
 * be sent into an encoder or decoder
 */
export interface VideoFrame {
  /** The height of the video frame */
  height: number;
  /** The width of the video frame */
  width: number;

  /**
   * The coulourspace format of the frame. This helps encoders/decoders
   * figure out how to read the video buffer
   */
  colourSpace: VideoColourSpace;
  /**
   * This metadata is used for the video source to understand the
   * frame is part of a video stream of a certain framerate.
   */
  framerate: VideoFramerate;
  /** A buffer-like binary representation of the video frame */
  data: Buffer | Uint8Array;
}

/**
 * The possible values for the colourspace
 * for which a certain frame is encoded
 */
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

/**
 * The possible values for the framerate at
 * which a video stream is being encoded
 */
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
