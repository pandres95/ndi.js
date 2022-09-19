export interface TallyState {
  /**
   * Whether a source should be marked as "onProgram", which can be understood as "LIVE", "Recording", etc.
   */
  onProgram: boolean;

  /**
   * Whether a source should be marked as "onPreview", which indicates that e.g the source is being previewed by a monitor.
   */
  onPreview: boolean;
}
