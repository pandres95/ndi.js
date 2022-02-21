#!/usr/bin/env node

import { arch, buildType } from './common.js';

import { $ } from 'zx';
import debug from 'debug';

const log = debug('node-ndi:scripts');

log(`Build:
cwd: ${process.cwd()}
platform: ${process.platform}
arch: ${arch}
type: ${buildType}
`);

log(await (await (import('../utils/paths.js'))).default);

await $`node-pre-gyp build --${buildType} --arch=${arch}`;
