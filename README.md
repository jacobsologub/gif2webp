gif2webp
========

A GIF to [WebP](https://developers.google.com/speed/webp/?csw=1) converter for NodeJS using [Google's gif2webp example](https://chromium.googlesource.com/webm/libwebp/+/0.4.0/examples/gif2webp.c).

Usage
-------
    var gif2webp = require ("gif2webp");
    var fs = require ("fs");
    
    var buffer = fs.readFileSync ("some.gif");
    var options = {
	    source: buffer,
	    lossy: true
    };
    
    gif2webp.convert (options, function (error, buffer) {
      // do something with the WebP buffer.
    };
    

### convert (options, callback)

The first argument is an `options` object. The only required option is `source`, this should be a `Buffer` containing the gif data; all others are optional.

* `source` - The gif `Buffer`.
* `lossy` - Encode image using lossy compression `Boolean`.
* `mixed` - For each frame in the image, pick lossy or lossless compression heuristically `Boolean`.
* `quality` - Quality factor (0:small..100:big).
* `method` - Compression method Quality (0=fast, 6=slowest).
* `kmin` - Min distance between key frames.
* `kmax` - Max distance between key frames.
* `filter` - Filter strength (0=off..100).
* `metadata` - Comma separated list of metadata to copy from the input to the output if present. Valid values: all, none, icc, xmp (default) `String`.
* `mt` - Use multi-threading if available `Boolean`.
* `verbose` - Verbose output `Boolean`.

For more info on the options listed above please vist the [gif2webp](https://developers.google.com/speed/webp/docs/gif2webp#options) page.

The callback argument gets 2 arguments:

1. An `error` when applicable.
2. An [`Buffer`](http://nodejs.org/api/buffer.html) object containing the WebP data.

Installation
-------

First downlaod and install [GIFLIB 4.2.x](http://sourceforge.net/projects/giflib/files/giflib-4.x/). Then downlaod and install [WebP](https://developers.google.com/speed/webp/download). If you are installing [WebP](https://developers.google.com/speed/webp/download) form source then take a look [here](https://developers.google.com/speed/webp/docs/compiling) and don't forget to use <code>--enable-libwebpmux</code> during the <code>configure</code> process, this is needed for gif conversion.

    $ npm install gif2webp
    
[License](https://github.com/jacobsologub/gif2webp/edit/master/LICENSE)
-------
The MIT License (MIT)

Copyright (c) 2014 [Jacob Sologub](https://github.com/jacobsologub)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

WebP Source License
-------

The WebP source is governed by a BSD-style license that can be found in the [COPYING](https://code.google.com/p/webm/source/browse/COPYING?repo=libwebp) file in the root of the source tree. An additional intellectual property rights grant can be found in the file [PATENTS](https://code.google.com/p/webm/source/browse/PATENTS?repo=libwebp). All contributing project authors may be found in the [AUTHORS](https://code.google.com/p/webm/source/browse/AUTHORS?repo=libwebp) file in the root of the source tree.
