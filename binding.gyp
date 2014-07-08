{
    "variables": {
        "HEROKU%": '<!(echo $HEROKU)'
    },

    "targets": [
        {
            "target_name": "gif2webp",
            "defines": [
                
            ],
            "sources": [
                "src/gif2webp.cpp",
                "src/webp/example_util.cpp",
                "src/webp/gif2webp_util.cpp",
                "src/webp/gif2webpMain.cpp"
            ],
            "conditions": [
                [
                    'OS=="mac"',
                    {
                        "include_dirs": [
                            "vendor/webp/include",
                            "src/webp"
                        ],

                        "libraries": [
                            "-lwebp",
                            "-lwebpmux",
                            "-lgif"
                        ]
                    }
                ],
                [
                    'OS=="linux"',
                    {
                        "include_dirs": [
                            "vendor/webp/include",
                            "src/webp"
                        ],

                        "libraries": [
                            "-lwebp",
                            "-lwebpmux",
                            "-lgif"
                        ]
                    }
                ]
            ]
        }
    ]
}