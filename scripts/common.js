/**
 * Build type. Either 'debug' or 'release', depending on the environment.
 */
export const buildType =
  process.env.BUILDTYPE?.toLowerCase() ??
  (process.env.NODE_ENV === "production" ? "release" : "debug");

export const toCapitalCase = (/** @type {string} */str) =>
  `${str[0].toUpperCase()}${str.slice(1).toLowerCase()}`
