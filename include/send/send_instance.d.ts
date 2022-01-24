import { AudioFrame } from './audio_frame';
import { VideoFrame } from './video_frame';
import { SendCreate } from './send_create';

export class SendInstance {
  initialize(initParameters: SendCreate): void;
  send(frames: {
    video: VideoFrame,
    audio: AudioFrame
  }[]): void;
}
