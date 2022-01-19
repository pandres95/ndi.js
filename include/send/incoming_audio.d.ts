export interface IncomingAudioParameters {
    /**
     * This is the current audio sample rate. For instance, this might be 44100, 48000 or 96000.
     * It can, however, be any value.
     */
    sampleRate: Number;

    /**
     * This is the number of discrete audio channels. 1 represents MONO audio, 2 represents STEREO,
     * and so on. There is no reasonable limit on the number of allowed audio channels.
     */
    channelsNumber: Number;

    /**
     * This is the floating-point audio data in planar format, with each frame being split,
     * each frame being comprised by the channels, with the samples chunk for each channel being a Buffer.
     *
     * ```js
     * [
     *      [ Buffer([ ... ]), Buffer([ ... ]), ... ],
     *      ...
     * ]
     * ```
     */
    frames: Float32Array[][]
}
