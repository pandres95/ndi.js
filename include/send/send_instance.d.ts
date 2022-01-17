import { IncomingVideo } from "./incoming_video";
import { SendInstanceInitParameters } from './send_instance_init_params';

export class SendInstance {
  initialize(initParameters: SendInstanceInitParameters): void;
  send(incomingVideo: IncomingVideo): void;
}
