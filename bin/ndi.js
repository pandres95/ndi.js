#! /usr/bin/env node --experimental-specifier-resolution=node

import { isAbsolute, resolve } from "path";

import ProgressBar from "progress";
import { SendInstance } from "../src";
import UVC from "uvc";
import { VideoCapture } from "camera-capture";
import callback from "callback-stream";
import commander from "commander";
import { cwd } from "process";
import prompts from "prompts";
import sharp from "sharp";

const { createCommand, program } = commander;
const { Context, Controls, FrameStreamer, LibUvc } = UVC;

async function main() {
  const processAction =
    (action) =>
    (args, options, /** @type {import('commander').Command} */ command) => {
      let sendInstance = new SendInstance();
      sendInstance.initialize({
        name: options.sourceName ?? `ndi.js ${command.name()}`,
      });

      action(sendInstance, args, options, command);
    };

  await program
    .version("0.0.1")
    .option("-s, --source-name", "video source name")
    .addCommand(
      createCommand("random")
        .description("Sends a random video signal")
        .argument(
          "[seconds]",
          "The number of seconds to send out the signal",
          "5"
        )
        .option("-f, --frames <frames>", "Number of frames per second", "60")
        .option("-A, --no-audio", "Should it include audio?")
        .option("-c, --channels <channels>", "Number of channels", "2")
        .option("-r, --sample-rate <sampleRate>", "Number of channels", "48000")
        .action(processAction(randomSignalTest))
    )
    .addCommand(createCommand("webcam").action(processAction(webcamSignalTest)))
    .addCommand(
      createCommand("webcam-uvc").action(processAction(webcamUVCSignalTest))
    )
    .addCommand(
      createCommand("ogv")
        .description("Sends a signal based on an OGV packed video")
        .argument("<path>", "The path to the file")
        .action(processAction(ogvSignalTest))
    )
    .parseAsync();
}

/**
 *
 * @param {import('../src').SendInstance} sendInstance
 * @param {number} timeout
 */
async function randomSignalTest(sendInstance, timeout = 5, options) {
  const sineWaveFLTAudioFrame = (frequency = 440, sampleRate = 48000) =>
    Float32Array.from(Array(sampleRate), (_, i) =>
      Math.sin((Math.PI * i) / frequency)
    );
  const randomRGBAVideoFrame = (width, height) =>
    Array.from(Array(height * width * 4), (_, k) =>
      k % 4 === 3 ? 255 : Math.round(255 * Math.random())
    );
  const framerateTable = {
    24: 1 /* VideoFramerate.F24 */,
    24.98: 2 /* VideoFramerate.F2498 */,
    25: 3 /* VideoFramerate.F25 */,
    29.97: 4 /* VideoFramerate.F2997 */,
    30: 5 /* VideoFramerate.F30 */,
    50: 6 /* VideoFramerate.F50 */,
    59.94: 7 /* VideoFramerate.F5994 */,
    60: 8 /* VideoFramerate.F60 */,
  };

  // Setup random video data
  const width = 1920;
  const height = 1080;

  const fps = Number(options?.frames ?? 60);

  console.log("Creating video frames");
  const videoProgressBar = new ProgressBar(":bar :current/:total", {
    total: fps,
  });
  videoProgressBar.render();

  const videoFrames = Array.from(Array(fps), () => {
    videoProgressBar.tick(1);
    return Buffer.from(randomRGBAVideoFrame(height, width));
  });

  videoProgressBar.terminate();

  // Setup random audio data
  const channels = Number(options?.channels ?? 2);
  const sampleRate = Number(options?.sampleRate ?? 48_000);

  let audioFrames = [];
  if (options.audio) {
    console.log("Creating audio frames");
    /**
     * 523.25Hz (C5) tuned sine wave
     */
    const s440Frame = sineWaveFLTAudioFrame(130.81, sampleRate);
    const samplesInFrame = Math.ceil(sampleRate / fps);

    const audioProgressBar = new ProgressBar(":bar :current/:total", {
      total: fps,
    });
    audioProgressBar.render();

    audioFrames = Array.from(Array(fps), (_, frame) => {
      audioProgressBar.tick(1);

      return Array.from(Array(channels), (_, ch) =>
        s440Frame
          .slice(frame * samplesInFrame, (frame + 1) * samplesInFrame - 1)
          .map((k) => k * (-1) ** ch)
      );
    });

    audioProgressBar.terminate();
  }

  // Start broadcasting
  const start = Date.now();

  let count = 0;
  while (count < timeout) {
    const start = Date.now();
    sendInstance.send(
      {
        width,
        height,
        colourSpace: 10 /* VideoColourSpace.RGBA */,
        framerate: framerateTable[fps],
        frames: videoFrames,
      },
      options.audio
        ? {
            channels,
            sampleRate,
            frames: audioFrames,
          }
        : undefined
    );
    console.log(`Sent ${fps} frames of video in ${Date.now() - start}ms`);

    count++;
  }

  console.log(`\nSent ${timeout} seconds of signal in ${Date.now() - start}ms`);
}

/**
 *
 * @param {import('../src').SendInstance} sendInstance
 */
async function webcamSignalTest(sendInstance) {
  /** @type {import('camera-capture').CaptureOptions} */
  const captureOptions = {
    width: 1280,
    height: 720,
    fps: 30,
    mime: "image/jpeg",
    puppeteerOptions: {
      args: ["--disable-dev-shm-usage"],
    },
  };

  const capture = new VideoCapture(captureOptions);

  await capture.initialize();

  let start = Date.now();
  capture.addFrameListener(async ({ width, height, data }) => {
    const frame = await sharp(data).raw().toBuffer();

    // sendInstance.send({
    //     width,
    //     height,
    //     colourSpace: 10 /* VideoColourSpace.RGBA */,
    //     framerate: 5 /* VideoFramerate.F30 */,
    //     frames: [frame]
    // });

    console.log(`Sent 1 frame in ${Date.now() - start}ms`);
    start = Date.now();
  });

  await capture.start();
}

/**
 *
 * @param {import('../src').SendInstance} sendInstance
 */
async function webcamUVCSignalTest(sendInstance) {
  const libuvc = new LibUvc();
  await libuvc.initialize();

  const context = new Context(libuvc);
  await context.initialize();

  const devices = await context.getDeviceList();

  if (!devices.length) {
    return;
  }

  const { device } = await prompts({
    type: "select",
    name: "device",
    choices: await Promise.all(
      devices.map(async (device) => ({
        title: await device.getDescriptor().then(async (d) => {
          await d.initialize();
          return d.productName;
        }),
        value: device,
      }))
    ),
    message: "Select the device:",
  });

  await device.initialize();

  const deviceHandle = await device.open();
  await deviceHandle.initialize();

  const controls = new Controls(libuvc, deviceHandle);
  await controls.initialize();

  const UVC_AUTO_EXPOSURE_MODE_AUTO = 2;
  const UVC_AUTO_EXPOSURE_MODE_APERTURE_PRIORITY = 8;

  try {
    await controls.ae_mode.set(UVC_AUTO_EXPOSURE_MODE_AUTO);
  } catch (error) {
    if (error.code === "UVC_ERROR_PIPE") {
      await controls.ae_mode.set(UVC_AUTO_EXPOSURE_MODE_APERTURE_PRIORITY);
    } else {
      throw error;
    }
  }

  const frameStreamer = new FrameStreamer(
    libuvc,
    deviceHandle,
    libuvc.constants.uvc_frame_format.UVC_FRAME_FORMAT_MJPEG,
    1280,
    720,
    30
  );
  const frameStream = await frameStreamer.initialize();

  frameStream.pipe(
    callback((error, data) => {
      if (error) {
        return;
      }

      debugger;
    })
  );
}

/**
 * Sends a video signal over
 * @param {import('../src').SendInstance} sendInstance
 * @param {string} inputPath
 */
async function ogvSignalTest(sendInstance, inputPath) {
  const path = isAbsolute(inputPath) ? inputPath : resolve(cwd(), inputPath);
}

main();
