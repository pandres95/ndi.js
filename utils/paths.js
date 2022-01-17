require('dotenv/config');

const { join, dirname, basename } = require('path');
const { ensureSymlinkSync } = require('fs-extra');

const { VENDOR_DIR_NAME = '.vendor' } = process.env;

function exportNDIPaths() {
    const DIR_NAME = join(VENDOR_DIR_NAME, 'ndi');

    const {
        NDI_SDK_DIR,
        NDI_SDK_LIB,
    } = process.env;

    ensureSymlinkSync(join(NDI_SDK_DIR, 'include'), join(DIR_NAME, 'include'));
    ensureSymlinkSync(join(NDI_SDK_DIR, NDI_SDK_LIB), join(DIR_NAME, 'lib'));

    return {
        dir: DIR_NAME,
        lib_dir: join(DIR_NAME, 'lib'),
        include_dir: join(DIR_NAME, 'include')
    };
}

function exportNodeGypPaths() {
    const DIR_NAME = join(VENDOR_DIR_NAME, 'node-gyp');

    const { NODE_GYP_DIR } = process.env;

    ensureSymlinkSync(NODE_GYP_DIR, DIR_NAME);

    return {
        dir: DIR_NAME,
        include_dir: join(DIR_NAME, 'include', 'node')
    };
}


module.exports = {
    ndi_sdk: exportNDIPaths(),
    node_gyp: exportNodeGypPaths()
};
