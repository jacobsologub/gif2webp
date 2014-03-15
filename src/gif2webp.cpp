/*
  ==============================================================================
   
   Copyright (c) 2014 Jacob Sologub
   
   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the "Software"), to deal 
   in the Software without restriction, including without limitation the rights 
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
   copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in 
   all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
   SOFTWARE.

  ==============================================================================
*/

#include "gif2webpMain.h"
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <string.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace v8;
using namespace node;

// {
//     source      required. <Buffer>  Buffer with binary image data.
//     lossy:      optional. <Boolean> Encode image using lossy compression
//     mixed:      optional. <Boolean> For each frame in the image, pick lossy or lossless compression heuristically.
//     quality:    optional. <Number>  Quality factor (0:small..100:big)
//     method:     optional. <Number>  Compression method Quality (0=fast, 6=slowest)
//     kmin:       optional. <Number>  Min distance between key frames
//     kmax:       optional. <Number>  Max distance between key frames
//     filter:     optional. <Number>  Filter strength (0=off..100)
//     metadata:   optional. <String>  comma separated list of metadata to copy from the input to the output if present. Valid values: all, none, icc, xmp (default)
//     mt:         optional. <Boolean> Use multi-threading if available
//     verbose:    optional. <Boolean> Verbose output from gif2webp
// }

Handle<Value> convert (const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2) {
        return ThrowException (Exception::TypeError (String::New ("Wrong number of arguments.")));
    }

    if (!args [0]->IsObject()) {
        return ThrowException (Exception::TypeError (String::New ("First argument must be be an object.")));
    }

    if (!args [1]->IsFunction()) {
        return ThrowException (Exception::TypeError (String::New ("Second argument must be a callback function.")));
    }

    Local<Object> options = args [0]->ToObject();

    Local<Object> buffer = Local<Object>::Cast (options->Get (String::NewSymbol ("source")));
    if (buffer->IsUndefined() || !Buffer::HasInstance (buffer)) {
        return ThrowException (Exception::TypeError (String::New ("First argument should have \"source\" key with a Buffer instance")));
    }

    std::vector <std::string> optionArgs;

    if (!options->Get (String::NewSymbol ("lossy"))->IsUndefined()) {
        Local<Boolean> value = options->Get (String::NewSymbol ("lossy"))->ToBoolean();

        if (value->Value()) {
            optionArgs.push_back ("-lossy");
        }
    }

    if (!options->Get (String::NewSymbol ("mixed"))->IsUndefined()) {
        Local<Boolean> value = options->Get (String::NewSymbol ("mixed"))->ToBoolean();
        if (value->Value()) {
            optionArgs.push_back ("-mixed");
        }
    }

    if (!options->Get (String::NewSymbol ("quality"))->IsUndefined()) {
        Local<Number> value = options->Get (String::NewSymbol ("quality"))->ToNumber();
        optionArgs.push_back ("-q");
        std::ostringstream s;
        s << (double) value->Value();
        optionArgs.push_back (s.str());
    }

    if (!options->Get (String::NewSymbol ("method"))->IsUndefined()) {
        Local<Number> value = options->Get (String::NewSymbol ("method"))->ToNumber();
        optionArgs.push_back ("-m");
        std::ostringstream s;
        s << (double) value->Value();
        optionArgs.push_back (s.str());
    }

    if (!options->Get (String::NewSymbol ("kmin"))->IsUndefined()) {
        Local<Number> value = options->Get (String::NewSymbol ("kmin"))->ToNumber();
        optionArgs.push_back ("-kmin");
        std::ostringstream s;
        s << (double) value->Value();
        optionArgs.push_back (s.str());
    }

    if (!options->Get (String::NewSymbol ("kmax"))->IsUndefined()) {
        Local<Number> value = options->Get (String::NewSymbol ("kmax"))->ToNumber();
        optionArgs.push_back ("-kmax");
        std::ostringstream s;
        s << (double) value->Value();
        optionArgs.push_back (s.str());
    }

    if (!options->Get (String::NewSymbol ("filter"))->IsUndefined()) {
        Local<Number> value = options->Get (String::NewSymbol ("filter"))->ToNumber();
        optionArgs.push_back ("-f");
        std::ostringstream s;
        s << (double) value->Value();
        optionArgs.push_back (s.str());
    }

    if (!options->Get (String::NewSymbol ("metadata"))->IsUndefined()) {
        Local<String> value = options->Get (String::NewSymbol ("metadata"))->ToString();
        String::Utf8Value utf8Value (value);
        optionArgs.push_back ("-metadata");
        optionArgs.push_back (std::string (*utf8Value));
    }

    if (!options->Get (String::NewSymbol ("mt"))->IsUndefined()) {
        Local<Boolean> value = options->Get (String::NewSymbol ("mt"))->ToBoolean();
        if (value->Value()) {
            optionArgs.push_back ("-mt");
        }
    }

    if (!options->Get (String::NewSymbol ("verbose"))->IsUndefined()) {
        Local<Boolean> value = options->Get (String::NewSymbol ("verbose"))->ToBoolean();
        if (value->Value()) {
            optionArgs.push_back ("-v");
        }
    }

    const char* convert_argv [optionArgs.size()];
    int convert_argc = optionArgs.size();
    for (int i = 0; i < (int) optionArgs.size(); ++i) {
        convert_argv [i] = optionArgs [i].c_str();
    }

    const size_t inDataSize = Buffer::Length (buffer);
    const char* inData = Buffer::Data (buffer);

    WebPData outData;
    convert (convert_argc, convert_argv, (char*) inData, inDataSize, &outData);

    Local<Object> globalObj = v8::Context::GetCurrent()->Global();

    Buffer* slowBuffer = node::Buffer::New (outData.size);
    memcpy (node::Buffer::Data (slowBuffer), outData.bytes, outData.size);
    Local<Function> bufferConstructor = Local<Function>::Cast (globalObj->Get (String::New ("Buffer")));

    Handle<Value> constructorArgs [3] = { 
      slowBuffer->handle_, 
      Integer::New (outData.size),
      Integer::New (0) 
    };

    Local<Object> actualBuffer = bufferConstructor->NewInstance (3, constructorArgs);
    WebPDataClear (&outData);

    const unsigned argc = 2;
    Local<Value> argv [argc] = {
        Local<Value>::New (Null()),
        Local<Value>::New (actualBuffer)
    };

    Local<Function> callback = Local<Function>::Cast (args [1]);
    callback->Call (Context::GetCurrent()->Global(), argc, argv);

    return Undefined();
}

void RegisterModule (v8::Handle<v8::Object> target) {
     target->Set (String::NewSymbol ("convert"), FunctionTemplate::New (convert)->GetFunction());
}

NODE_MODULE (gif2webp, RegisterModule);
