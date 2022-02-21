import { AudioFrame } from '../structures/audio_frame';
import { VideoFrame } from '../structures/video_frame';
import { SendCreate } from './send_create';

export class SendInstance {
  initialize(initParameters: SendCreate): void;
  send(frames: {
    video?: VideoFrame,
    audio?: AudioFrame
  }[]): void;
}
