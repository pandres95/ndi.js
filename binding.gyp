{
    "targets": [
        {
            "target_name": "<(module_name)",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": [
                "src/ndi.cpp",
                "src/video_source/handlers.cpp",
                "src/video_source/incoming_video.cpp",
                "src/video_source/send_video_source.cpp"
            ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include_dir\")",
                "<!@(node -p \"require('./utils/paths').ndi_sdk.include_dir\")",
                "include"
            ],
            "conditions": [
                ["OS==\"mac\"",
                 {
                     "link_settings": {
                         "libraries": [
                             "-Wl,-rpath,@loader_path",
                             "-Wl,-rpath,@loader_path/..",
                         ],
                     },
                     "copies": [
                         {
                             "destination": "$(BUILDTYPE)/",
                             "files": [
                                 "<!@(node -p \"require('./utils/paths').ndi_sdk.lib_dir\")/libndi.dylib",
                             ]
                         }
                     ]
                 }
                 ],
                ["OS==\"linux\"",
                 {
                     "link_settings": {
                         "libraries": [
                             "-Wl,-rpath,'$$ORIGIN'",
                             "-Wl,-rpath,'$$ORIGIN'/.."
                         ],
                     },
                     "copies": [
                         {
                             "destination": "$(BUILDTYPE)",
                             "files": [
                                 "<!@(node -p \"require('./utils/paths').ndi_sdk.lib_dir\")/libndi.so.5",
                             ]
                         }
                     ]
                 }
                 ]
            ],
            "copies": [
                {
                    "destination": "$(BUILDTYPE)",
                    "files": [
                        "<!@(node -p \"require('./utils/paths').ndi_sdk.lib_dir\")/libndi_licenses.txt",
                    ]
                }
            ],
            "link_settings": {
                "libraries": [
                    "-lndi"
                ],
            },
            "defines": ['NAPI_DISABLE_CPP_EXCEPTIONS']
        }
    ]
}
