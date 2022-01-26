/**
 * Build type. Either 'debug' or 'release', depending on the environment.
 */
export const buildType =
  process.env.BUILDTYPE?.toLowerCase() ??
  (process.env.NODE_ENV === "production" ? "release" : "debug");
