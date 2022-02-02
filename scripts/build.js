#!/usr/bin/env node

import { $ } from 'zx';
import { buildType } from './common.js';
import debug from 'debug';

const log = debug('node-ndi:scripts');

log(`Build:
cwd: ${process.cwd()}
platform: ${process.platform}
arch: ${process.arch}
type: ${buildType}
`);

await $`node-pre-gyp build --${buildType}`;
