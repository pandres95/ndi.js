import bindings from 'bindings';
const addon = bindings('ndi');

/**
 * @type {import('./index').SendInstance}
 */
const SendInstance = addon.SendInstance;

export { SendInstance };
export * from './structures/video_frame.js';
