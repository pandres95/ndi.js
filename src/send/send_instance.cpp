#include <iostream>

#include <send/send_instance.h>
#include <send/send_instance_init_params.h>
#include <send/incoming_audio.h>
#include <send/incoming_video.h>

using namespace std;

SendInstance::SendInstance(const Napi::CallbackInfo &info) : Napi::ObjectWrap<SendInstance>(info) {}

void SendInstance::Initialize(const Napi::CallbackInfo &info)
{
    // Validate the initParameters argument
    if (info.Length() == 0)
    {
        Napi::TypeError::New(info.Env(), "The initParameters argument is expected")
            .ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsObject())
    {
        Napi::TypeError::New(info.Env(), "The initParameters argument is expected to be an object")
            .ThrowAsJavaScriptException();
        return;
    }

    // Initialize sendCreate parameters using the initParameters argument
    try {
        NDIlib_send_create_t sendCreateParams = (SendInstanceInitParameters) info[0].ToObject();

        this->ndiSendInstance = NDIlib_send_create(&sendCreateParams);

        if (!this->ndiSendInstance)
        {
            throw Napi::Error::New(info.Env(), "Could not initialize the instance");
        }
    } catch (Napi::Error error) {
        error.ThrowAsJavaScriptException();
    }
}

void SendInstance::Send(const Napi::CallbackInfo &info)
{
    IncomingVideoParameters incomingVideoParameters = info[0].As<Napi::Object>();
    IncomingAudioParameters* incomingAudioParameters = NULL;

    if (info.Length() == 2) {
        IncomingAudioParameters params = info[1].As<Napi::Object>();
        incomingAudioParameters = &params;
    }

    NDIlib_video_frame_v2_t videoFrame = incomingVideoParameters;
    NDIlib_audio_frame_v2_t audioFrame = NULL;

    if (incomingAudioParameters != NULL) {
        incomingAudioParameters->framerate_N = videoFrame.frame_rate_N;
        incomingAudioParameters->framerate_D = videoFrame.frame_rate_D;

        audioFrame = *incomingAudioParameters;
    }

    for (uint32_t idx = 0; idx < incomingVideoParameters.frames.Length(); idx++)
    {
        cout << incomingAudioParameters->frames.Length() << " audio frames" << endl; // TODO: Delete this log

        if (incomingAudioParameters != NULL) {
            audioFrame.p_data = (float*) malloc(audioFrame.no_channels * audioFrame.channel_stride_in_bytes);
            Napi::Array frame = incomingAudioParameters->frames.Get(idx).As<Napi::Array>();

            cout << frame.Length() << " channels on frame" << idx << endl; // TODO: Delete this log

            for (int channel = 0; channel < incomingAudioParameters->channelsNumber; channel++) {
                Napi::Float32Array channelData = frame.Get(channel).As<Napi::Float32Array>();

                cout << audioFrame.no_samples << " audio samples on channel" << channel + 1 << endl; // TODO: Delete this log

                float* buffer = channelData.Data();

                cout << "Buffer example: "; // TODO: Delete this log
                for (int i = 0; i < 20; i++) { cout << buffer[i] << " "; } // TODO: Delete this log
                cout << endl << endl; // TODO: Delete this log

                // Get the pointer to the start of this channel
                float* p_ch = (float*)((uint8_t*)audioFrame.p_data + (channel * audioFrame.channel_stride_in_bytes));

                // Fill it with silence
                for (int sample_no = 0; sample_no < audioFrame.no_samples; sample_no++)
                    p_ch[sample_no] = buffer[sample_no];
            }

            NDIlib_send_send_audio_v2(this->ndiSendInstance, &audioFrame);
            free(audioFrame.p_data);
        }

        Napi::Buffer<uint8_t> buffer = incomingVideoParameters.frames
            .Get(idx).As<Napi::Buffer<uint8_t> >();
        uint8_t *buffer_data = buffer.Data();

        videoFrame.p_data = buffer_data;
        NDIlib_send_send_video_async_v2(this->ndiSendInstance, &videoFrame);
    }
}

SendInstance::~SendInstance()
{
    NDIlib_send_destroy(this->ndiSendInstance);
}
