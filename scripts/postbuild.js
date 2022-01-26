#!/usr/bin/env npx zx

import 'zx/globals';

import { buildType } from './common.js';
import debug from 'debug';

const log = debug('node-ndi:scripts');

switch (process.platform) {
    case 'linux':
        await $`patchelf --add-needed libndi.so build/${buildType}/ndi.node`;
        break;
    case 'darwin':
        log(`It's macOS. Hence, nothing else is needed.`);
        $`file -p build/${buildType}/ndi.node`
        break;
}
