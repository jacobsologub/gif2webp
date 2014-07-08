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
                            "/usr/local/include",
                            "src/webp",
                            
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
                            "/usr/local/include",
                            "/app/build/include",
                            "src/webp",
                            
                        ],

                        "conditions": [
                            [
                                'HEROKU=="true"', 
                                {
                                    "include_dirs": [
                                        "/app/build/include",
                                        "src/webp",
                                    ]
                                }
                            ]
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