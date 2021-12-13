export interface SendVideoInitParameters {
  /**
   * The name of the send video source.
   */
  name: string;

  /**
   * A list of tags.
   *
   * These will be used for a NDI client to group video sources
   * into groups labelled as such.
   */
  groups?: string[];

  /**
   * Whether the video of this source should be "clocked".
   *
   * When it is, video frames added will be rate-limited to match the current framerate they
   * are submitted at.
   *
   * In general, if you are submitting video and audio off a single thread you should only clock
   * one of them (video is probably the better choice to clock off). If you are submitting audio
   * and video of separate threads then having both clocked can be useful.
   *
   * A simplified view of the how works is that, when you submit a frame, it will keep track of the
   * time the next frame would be required at. If you submit a frame before this time, the call
   * will wait until that time. This ensures that, if you sit in a tight loop and render frames as
   * fast as you can go, they will be clocked at the framerate that you desire.
   *
   * Default value is true.
   */
  clockVideo?: boolean;

  /**
   * Whether the audio part of this source should be "clocked".
   *
   * When it is, video frames added will be rate-limited to match the current framerate they
   * are submitted at.
   *
   * In general, if you are submitting video and audio off a single thread you should only clock
   * one of them (video is probably the better choice to clock off). If you are submitting audio
   * and video of separate threads then having both clocked can be useful.
   *
   * A simplified view of the how works is that, when you submit a frame, it will keep track of the
   * time the next frame would be required at. If you submit a frame before this time, the call
   * will wait until that time. This ensures that, if you sit in a tight loop and render frames as
   * fast as you can go, they will be clocked at the framerate that you desire.
   *
   * Default value is false.
   */
  clockAudio?: boolean;
}

export class SendVideoSource {
  initialize(initParameters: SendVideoInitParameters): void;
  send(sourceBuffer: Buffer): void;
  destroy(): void;
}
