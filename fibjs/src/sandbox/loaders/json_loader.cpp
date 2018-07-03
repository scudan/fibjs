/*
 * json_loader.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: lion
 */

#include "object.h"
#include "SandBox.h"
#include "ifs/encoding.h"
#include "loaders.h"

namespace fibjs {
result_t JsonLoader::run(SandBox::Context* ctx, Buffer_base* src, exlib::string name,
    exlib::string arg_names, v8::Local<v8::Value>* args, int32_t args_count)
{
    exlib::string strScript;
    v8::Local<v8::Value> v;

    src->toString(strScript);
    result_t hr = json_base::decode(strScript, v);
    if (hr < 0)
        return hr;

    Isolate* isolate = ctx->m_sb->holder();
    v8::Local<v8::Object> module = v8::Local<v8::Object>::Cast(args[5]);
    module->Set(isolate->NewString("exports"), v);

    return 0;
}
}