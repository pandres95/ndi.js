export interface AudioFrame {
  /**
   * This is the current audio sample rate. For instance, this might be 44100, 48000 or 96000.
   * It can, however, be any value.
   */
  sampleRate: Number;

  /**
   * This is the floating-point audio data in planar format, split in channels,
   * with each channel being a Float32Array.
   *
   * ```js
   * [
   *    Float32Array([ ... ]), // Left channel
   *    Float32Array([ ... ]), // Right channel
   *    ...
   * ]
   * ```
   *
   * The lenght of this array is the discrete number of audio channels. 1 represents MONO audio, 2 represents STEREO,
   * and so on. There is no reasonable limit on the number of allowed audio channels.
   */
  channels: Float32Array[];
}
