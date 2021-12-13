import { SendVideoSource } from '../src';

const sleep = millis => new Promise((resolve) => setTimeout(resolve, millis));

async function main () {
    console.log('Library successfully initialized');

    console.log('Initializing instance...');
    const sendVideoSource = new SendVideoSource();
    sendVideoSource.initialize({
        name: 'my dummy video source name',
    });
    console.log('Instance successfully initialized');

    await sleep(500);

    sendVideoSource.destroy();
}

main();
