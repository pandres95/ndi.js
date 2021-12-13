import { SendVideoSource } from '../src';

const sleep = millis => new Promise((resolve) => setTimeout(resolve, millis));

async function main () {
    let sendVideoSource = new SendVideoSource();
    sendVideoSource.initialize({
        name: 'my dummy video source name',
    });

    await sleep(process.argv[2] ? Number(process.argv[2]) : 1_000);
}

main();
