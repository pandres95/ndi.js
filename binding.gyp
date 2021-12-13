{
    "targets": [
        {
            "target_name": "ndi",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": [
                "src/_module_.cpp",
                "src/video_source/handlers.cpp",
                "src/video_source/send.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include_dir\")",
                "<!@(node -p \"require('./tools/ndi').ndi_sdk.include_dir\")",
                "include"
            ],
            "link_settings": {
                "libraries": [
                    "-lndi",
                    "-lndi_advanced"
                ],
                "library_dirs": [
                    "/usr/local/lib"
                ],
            },
            "defines": ['NAPI_DISABLE_CPP_EXCEPTIONS'],
            # "copies": [
            #     {
            #         "destination": "$(BUILDTYPE)",
            #         "files": [
            #             "<!@(node -p \"require('./tools/ndi').ndi_sdk.lib_dir\")/<!@(node -p \"require('./tools/ndi').ndi_sdk.lib\")"
            #         ]
            #     }
            # ]
        }
    ]
}
