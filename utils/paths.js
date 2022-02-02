require("dotenv/config");

const { join } = require("path");
const { ensureSymlinkSync } = require("fs-extra");

const VENDOR_DIR_NAME = ".vendor";

function exportNDIPaths() {
  const DIR_NAME = join(VENDOR_DIR_NAME, "ndi");

  return {
    dir: DIR_NAME,
    lib_dir: join(DIR_NAME, "lib", process.platform, process.platform !== 'darwin' ? `${process.arch}${process.env.raspberry_version ? `-${process.env.raspberry_version}` : ''}` : '.'),
    include_dir: join(DIR_NAME, "include"),
  };
}

function exportNodeGypPaths() {
  const DIR_NAME = join(VENDOR_DIR_NAME, "node-gyp");

  const { NODE_GYP_DIR } = process.env;

  if (NODE_GYP_DIR === undefined) {
    return {};
  }

  ensureSymlinkSync(NODE_GYP_DIR, DIR_NAME);

  return {
    dir: DIR_NAME,
    include_dir: join(DIR_NAME, "include", "node"),
  };
}

const ndiSdk = exportNDIPaths();
const nodeGyp = exportNodeGypPaths();

module.exports = {
  ndi_sdk: ndiSdk,
  node_gyp: nodeGyp,
};
