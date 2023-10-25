import { AudioFrame } from '../structures/audio_frame';
import { VideoFrame } from '../structures/video_frame';
import { SendCreateOptions } from './send_create';

/**
 * A send (output) NDI instance
 */
export class SendInstance {
  /**
   * Initializes an instance for sending video
   * @param initParameters The options to initialize the instance
   */
  initialize(initParameters: SendCreateOptions): void;
  /**
   * Sends a raw representation of frames (each one containing
   * a {@link VideoFrame} and {@link AudioFrame}) into the NDI protocol.
   * @param frames The video/audio frames to be sent into the network
   */
  send(frames: {
    video?: VideoFrame,
    audio?: AudioFrame
  }[]): void;
}
