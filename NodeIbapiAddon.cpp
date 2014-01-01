#include <node.h>
#include "NodeIbapi.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    NodeIbapi::Init(exports);
}

NODE_MODULE(NodeIbapiAddon, InitAll)