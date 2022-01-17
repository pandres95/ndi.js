#include <string>
#include <send/send_instance_init_params.h>

using namespace std;

SendInstanceInitParameters::SendInstanceInitParameters(const Napi::Object &object) : Napi::Object(object) {}

SendInstanceInitParameters::operator NDIlib_send_create_t() const
{
    NDIlib_send_create_t sendCreateParams;

    if (!this->Has("name") || this->Get("name").IsUndefined())
    {
        throw "sendInstanceInitParameters.name value is expected";
    }
    else if (!this->Get("name").IsString())
    {
        throw "sendInstanceInitParameters.name expected to be a value of String type";
    }
    else
    {
        string ndiName = this->Get("name").ToString().Utf8Value();
        char* p_ndi_name = new char[ndiName.length() + 1];
        strcpy(p_ndi_name, ndiName.c_str());

        sendCreateParams.p_ndi_name = p_ndi_name;
    }

    if (this->Has("groups") && this->Get("groups").IsArray())
    {
        string groupsStr;
        Napi::Array groups = this->Get("groups").As<Napi::Array>();

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

    sendCreateParams.clock_video = (this->Has("clockVideo") && this->Get("clockVideo").IsBoolean())
                                       ? this->Get("clockVideo").As<Napi::Boolean>().Value()
                                       : true;

    sendCreateParams.clock_audio = (this->Has("clockAudio") && this->Get("clockAudio").IsBoolean())
                                       ? this->Get("clockAudio").As<Napi::Boolean>().Value()
                                       : false;

    return sendCreateParams;
}
