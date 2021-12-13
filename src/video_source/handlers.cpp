#include <string>
#include <video_source.h>
#include <iostream>

using namespace std;

SendVideoSource::SendVideoSource(const Napi::CallbackInfo &info) : Napi::ObjectWrap<SendVideoSource>(info) {}

void SendVideoSource::Initialize(const Napi::CallbackInfo &info)
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

    Napi::Object initParameters = info[0].ToObject();

    // Initialize sendCreate parameters using the initParameters argument
    NDIlib_send_create_t sendCreateParams;

    if (!initParameters.Has("name") || initParameters.Get("name").IsUndefined())
    {
        Napi::TypeError::New(info.Env(), "initParameters.name value is expected")
            .ThrowAsJavaScriptException();
        return;
    }
    else if (!initParameters.Get("name").IsString())
    {
        Napi::TypeError::New(info.Env(), "initParameters.name expected to be a value of String type")
            .ThrowAsJavaScriptException();
        return;
    }
    else
    {
        string ndiName = initParameters.Get("name").ToString().Utf8Value();
        char* p_ndi_name = new char[ndiName.length() + 1];
        strcpy(p_ndi_name, ndiName.c_str());

        sendCreateParams.p_ndi_name = p_ndi_name;
    }

    if (initParameters.Has("groups") && initParameters.Get("groups").IsArray())
    {
        string groupsStr;
        Napi::Array groups = initParameters.Get("groups").As<Napi::Array>();

        for (uint32_t i = 0; i < groups.Length(); i++)
        {
            Napi::String group = groups.Get(i).ToString();
            groupsStr += string(group) + (i < groups.Length() - 1 ? "," : "");
        }

        sendCreateParams.p_groups = groupsStr.c_str();
    }
    else
    {
        sendCreateParams.p_groups = NULL;
    }

    sendCreateParams.clock_video = (initParameters.Has("clockVideo") && initParameters.Get("clockVideo").IsBoolean())
                                       ? initParameters.Get("clockVideo").As<Napi::Boolean>().Value()
                                       : true;

    sendCreateParams.clock_audio = (initParameters.Has("clockAudio") && initParameters.Get("clockAudio").IsBoolean())
                                       ? initParameters.Get("clockAudio").As<Napi::Boolean>().Value()
                                       : false;

    this->sendInstance = NDIlib_send_create(&sendCreateParams);

    if (!this->sendInstance)
    {
        Napi::Error::New(info.Env(), "Could not initialize the source")
            .ThrowAsJavaScriptException();
    }
}

void SendVideoSource::DoDestroy()
{
    if (this->sendInstance != NULL)
        NDIlib_send_destroy(this->sendInstance);
}

void SendVideoSource::Destroy(const Napi::CallbackInfo &info)
{
    this->DoDestroy();
}

SendVideoSource::~SendVideoSource()
{
    this->DoDestroy();
}
