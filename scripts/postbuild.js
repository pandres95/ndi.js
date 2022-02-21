#!/usr/bin/env node

import { buildType, toCapitalCase } from './common.js';

import { $ } from 'zx';
import debug from 'debug';

const log = debug('node-ndi:scripts');

switch (process.platform) {
    case 'linux':
        await $`patchelf --add-needed libndi.so build/${toCapitalCase(buildType)}/ndi.node`;
        break;
    case 'darwin':
        log(`It's macOS. Hence, nothing else is needed.`);
        $`file -p build/${toCapitalCase(buildType)}/ndi.node`
        break;
}
