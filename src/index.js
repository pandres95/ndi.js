import bindings from 'bindings';
const addon = bindings('ndi');

/**
 * @type {import('./index').SendInstance}
 */
const SendInstance = addon.SendInstance;

/**
 * @type {import('./index').findSources}
 */
const findSources = addon.findSources;

export { SendInstance, findSources };
export * from './structures/video_frame.js';
