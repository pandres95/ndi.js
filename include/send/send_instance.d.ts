import { IncomingAudioParameters } from "./incoming_audio";
import { IncomingVideoParameters } from "./incoming_video";
import { SendInstanceInitParameters } from './send_instance_init_params';

export class SendInstance {
  initialize(initParameters: SendInstanceInitParameters): void;
  send(incomingVideo: IncomingVideoParameters, incomingAudio?: IncomingAudioParameters): void;
}
