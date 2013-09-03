#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "NodeIbapi.h"

using namespace v8;

NodeIbapi::NodeIbapi() {};
NodeIbapi::~NodeIbapi() {};

void NodeIbapi::Init(Handle<Object> exports) {
	// Prep constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("NodeIbapi"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// prototype

	/// connect
	tpl->PrototypeTemplate()->Set(String::NewSymbol("connect"),
		FunctionTemplate::New(Connect)->GetFunction());
	/// disconnect
	tpl->PrototypeTemplate()->Set(String::NewSymbol("disconnect"),
		FunctionTemplate::New(Disconnect)->GetFunction());
	/// isConnected
	tpl->PrototypeTemplate()->Set(String::NewSymbol("isConnected"),
		FunctionTemplate::New(IsConnected)->GetFunction());

	//
	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("NodeIbapi"), constructor);
}

Handle<Value> NodeIbapi::New(const Arguments& args) {
	HandleScope scope;
	NodeIbapi* obj = new NodeIbapi();
	obj->Wrap(args.This());

	return args.This();
}

Handle<Value> NodeIbapi::Connect(const Arguments& args) {
	HandleScope scope;
	NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

	if (args.Length() < 3) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}
	if (!args[1]->IsNumber() || !args[2]->IsNumber()) {
		ThrowException(Exception::TypeError(String::New("Wrong input for arguments")));
		return scope.Close(Undefined());
	}

	char * host = getChar(args[0],""); 

	return scope.Close(
		Boolean::New(obj->m_client.connect(host, args[1]->Uint32Value(), (int)args[2]->IntegerValue()))
		);
}

// TODO disconnect method should return something
Handle<Value> NodeIbapi::Disconnect(const Arguments& args) {
	HandleScope scope;
	NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
	obj->m_client.disconnect();
	return scope.Close(Integer::New(1));
}

Handle<Value> NodeIbapi::IsConnected(const Arguments& args) {
	HandleScope scope;
	NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
	return scope.Close(Boolean::New(obj->m_client.isConnected()));
}

// see http://stackoverflow.com/questions/10507323/shortest-way-one-liner-to-get-a-default-argument-out-of-a-v8-function
char *NodeIbapi::getChar(v8::Local<v8::Value> value, const char *fallback) {
	if (value->IsString()) {
		v8::String::AsciiValue string(value);
		char *str  = (char *) malloc(string.length() + 1);
		strcpy(str, *string);
		return str;
	}
	char *str = (char *) malloc(strlen(fallback) + 1);
	strcpy(str, fallback);
	return str;
}