#ifndef NODEIBAPI_H
#define NODEIBAPI_H

#define IB_USE_STD_STRING

#include <node.h>
#include "IbPosixClient.h"

class NodeIbapi : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> exports);

private:
	NodeIbapi();
	~NodeIbapi();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Connect(const v8::Arguments& args);
	static v8::Handle<v8::Value> Disconnect(const v8::Arguments& args);
	static v8::Handle<v8::Value> IsConnected(const v8::Arguments& args);

private:
	static char *getChar(v8::Local<v8::Value> value, const char *fallback = "");

	IbPosixClient m_client;

};

#endif