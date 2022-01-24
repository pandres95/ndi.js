{
    "targets": [
        {
            "target_name": "<(module_name)",
            "cflags!": ["-fno-exceptions"],
            "cflags+": ["-fexceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "cflags_cc+": ["-fexceptions"],
            "sources": [
                "src/ndi.cpp",
                "src/send/operator_incoming_audio.cpp",
                "src/send/operator_incoming_video.cpp",
                "src/send/operator_send_instance_init_params.cpp",
                "src/send/send_instance.cpp",
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
                             "-lndi"
                         ],
                     },
                     "copies": [
                         {
                             "destination": "$(BUILDTYPE)/",
                             "files": [
                                 "<!@(node -p \"require('./utils/paths').ndi_sdk.lib_dir\")/libndi.dylib",
                                 "<!@(node -p \"require('./utils/paths').ndi_sdk.lib_dir\")/libndi_licenses.txt",
                             ]
                         }
                     ],
                     'xcode_settings': {
                         'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                     }
                 }
                 ],
                ["OS==\"linux\"",
                 {
                     "link_settings": {
                         "libraries": [
                             "-Wl,-rpath='$$ORIGIN'",
                             "-Wl,-rpath='$$ORIGIN'/..",
                             #  "-l:libndi.so.5.0.10" # TODO: Find a way to appropriately bind the library without needing to use `patchelf --add-needed libndi.so.5.0.10` build/${BUILDTYPE}/ndi.node
                         ],
                     },
                     "copies": [
                         {
                             "destination": "$(BUILDTYPE)",
                             "files": [
                                 "<!@(node -p \"require('./utils/paths').ndi_sdk.lib_dir\")/libndi.so.5.0.10",
                             ]
                         }
                     ]
                 }
                 ]
            ],
            "defines": ['NAPI_CPP_EXCEPTIONS']
        }
    ]
}
