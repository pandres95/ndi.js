import bindings from 'bindings';
const addon = bindings('ndi');

/**
 * @type {import('./index').SendVideoSource}
 */
const SendVideoSource = addon.SendVideoSource;

export { SendVideoSource };
