#include <cstring>
#include <sstream>
#include <node.h>
#include "NodeIbapi.h"
#include "import/Contract.h"
#include "import/Order.h"
#include "import/Execution.h"

using namespace v8;

NodeIbapi::NodeIbapi() {};
NodeIbapi::~NodeIbapi() {};

void NodeIbapi::Init(Handle<Object> exports) {
    // Prep constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("NodeIbapi"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // prototype
    // TODO need to write test, not sure what would be a good one..
    tpl->PrototypeTemplate()->Set(String::NewSymbol("processMsg"),
        FunctionTemplate::New(ProcessMsg)->GetFunction());
    /// getters
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getNextValidId"),
        FunctionTemplate::New(NextValidId)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getCurrentTime"),
        FunctionTemplate::New(CurrentTime)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickPrice"),
        FunctionTemplate::New(TickPrice)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickSize"),
        FunctionTemplate::New(TickSize)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickOptionComputation"),
        FunctionTemplate::New(TickOptionComputation)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickGeneric"),
        FunctionTemplate::New(TickGeneric)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickString"),
        FunctionTemplate::New(TickString)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickEFP"),
        FunctionTemplate::New(TickEFP)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getTickSnapshotEnd"),
        FunctionTemplate::New(TickSnapshotEnd)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getMarketDataType"),
        FunctionTemplate::New(MarketDataType)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("getOrderStatus"),
        FunctionTemplate::New(OrderStatus)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getOpenOrder"),
        FunctionTemplate::New(OpenOrder)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getRealtimeBar"),
        FunctionTemplate::New(RealtimeBar)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getWinError"),
        FunctionTemplate::New(WinError)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getError"),
        FunctionTemplate::New(Error)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getUpdateAccountValue"),
        FunctionTemplate::New(UpdateAccountValue)->GetFunction());

    /// EClientSocket
    tpl->PrototypeTemplate()->Set(String::NewSymbol("connect"),
        FunctionTemplate::New(Connect)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("disconnect"),
        FunctionTemplate::New(Disconnect)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("isConnected"),
        FunctionTemplate::New(IsConnected)->GetFunction());

    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqMktData"),
        FunctionTemplate::New(ReqMktData)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelMktData"),
        FunctionTemplate::New(CancelMktData)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("placeSimpleOrder"),
        FunctionTemplate::New(PlaceSimpleOrder)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("placeOrder"),
        FunctionTemplate::New(PlaceOrder)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelOrder"),
        FunctionTemplate::New(CancelOrder)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqOpenOrders"),
        FunctionTemplate::New(ReqOpenOrders)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqAccountUpdates"),
        FunctionTemplate::New(ReqAccountUpdates)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqExecutions"),
        FunctionTemplate::New(ReqExecutions)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqIds"),
        FunctionTemplate::New(ReqIds)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("checkMessages"),
        FunctionTemplate::New(CheckMessages)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqContractDetails"),
        FunctionTemplate::New(ReqContractDetails)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqMktDepth"),
        FunctionTemplate::New(ReqMktDepth)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelMktDepth"),
        FunctionTemplate::New(CancelMktDepth)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqNewsBulletins"),
        FunctionTemplate::New(ReqNewsBulletins)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelNewsBulletins"),
        FunctionTemplate::New(CancelNewsBulletins)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setServerLogLevel"),
        FunctionTemplate::New(SetServerLogLevel)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqAutoOpenOrders"),
        FunctionTemplate::New(ReqAutoOpenOrders)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqAllOpenOrders"),
        FunctionTemplate::New(ReqAllOpenOrders)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqManagedAccts"),
        FunctionTemplate::New(ReqManagedAccts)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("requestFA"),
        FunctionTemplate::New(RequestFA)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("replaceFA"),
        FunctionTemplate::New(ReplaceFA)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqHistoricalData"),
        FunctionTemplate::New(ReqHistoricalData)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("exerciseOptions"),
        FunctionTemplate::New(ExerciseOptions)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelHistoricalData"),
        FunctionTemplate::New(CancelHistoricalData)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqRealtimeBars"),
        FunctionTemplate::New(ReqRealTimeBars)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelRealTimeBars"),
        FunctionTemplate::New(CancelRealTimeBars)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelScannerSubscription"),
        FunctionTemplate::New(CancelScannerSubscription)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqScannerParameters"),
        FunctionTemplate::New(ReqScannerParameters)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqScannerSubscription"),
        FunctionTemplate::New(ReqScannerSubscription)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqCurrentTime"),
        FunctionTemplate::New(ReqCurrentTime)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqFundamentalData"),
        FunctionTemplate::New(ReqFundamentalData)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelFundamentalData"),
        FunctionTemplate::New(CancelFundamentalData)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("calculateImpliedVolatility"),
        FunctionTemplate::New(CalculateImpliedVolatility)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("calculateOptionPrice"),
        FunctionTemplate::New(CalculateOptionPrice)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelCalculateImpliedVolatility"),
        FunctionTemplate::New(CancelCalculateImpliedVolatility)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelCalculateOptionPrice"),
        FunctionTemplate::New(CancelCalculateOptionPrice)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqGlobalCancel"),
        FunctionTemplate::New(ReqGlobalCancel)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqMarketDataType"),
        FunctionTemplate::New(ReqMarketDataType)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqPositions"),
        FunctionTemplate::New(ReqPositions)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelPositions"),
        FunctionTemplate::New(CancelPositions)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqAccountSummary"),
        FunctionTemplate::New(ReqAccountSummary)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("cancelAccountSummary"),
        FunctionTemplate::New(CancelAccountSummary)->GetFunction());

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

    if ( isWrongArgNumber(args,3) || isWrongType(!args[0]->IsString(), 0) ||
        isWrongType(!args[1]->IsUint32(), 1) || isWrongType(!args[2]->IsInt32(), 2)) {
        return scope.Close(Undefined());
    }

    char * host = getChar(args[0],""); 

    return scope.Close(
            Boolean::New(obj->m_client.connect(host, 
                    args[1]->Uint32Value(), args[2]->Int32Value()))
            );
}

// TODO disconnect method should return something
Handle<Value> NodeIbapi::Disconnect(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    obj->m_client.disconnect();
    return scope.Close(Undefined());
}

Handle<Value> NodeIbapi::IsConnected(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    return scope.Close(Boolean::New(obj->m_client.isConnected()));
}

Handle<Value> NodeIbapi::ProcessMsg(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    obj->m_client.processMessages();
    return scope.Close(Undefined());
}


///////////////////////////////////////////////////////////////////////////////
// node implementation for EClientSocket methods
///////////////////////////////////////////////////////////////////////////////

Handle<Value> NodeIbapi::ReqMktData(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    if ( isWrongArgNumber(args,4) ) {
        return scope.Close(Undefined());
    }

    TickerId tickerId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast(args[1]);
    // checks if order is being submitted through Conract ID from 
    //  contract specification
    contract.conId = ibContract->Get(String::New("conId"))->Int32Value();
    contract.exchange = getChar(ibContract->Get(String::New("exchange")));
    if (contract.conId == 0) {
        contract.symbol = getChar(ibContract->Get(String::New("symbol")));
        contract.secType = getChar(ibContract->Get(String::New("secType")));
        
        contract.primaryExchange = getChar(ibContract->Get(String::New("primaryExchange")));
        contract.currency = getChar(ibContract->Get(String::New("currency")));
    }

    IBString genericTick = getChar(args[2]);

    bool snapShot = args[3]->BooleanValue();

    obj->m_client.reqMktData(tickerId, contract, genericTick, snapShot);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelMktData(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    if ( isWrongArgNumber(args, 1) || isWrongType(!args[0]->IsUint32(),0)) {
        return scope.Close(Undefined());
    }

    TickerId tickerId = args[0]->Int32Value();

    obj->m_client.cancelMktData(tickerId);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::PlaceSimpleOrder(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    if ( isWrongArgNumber(args, 10) || isWrongType(!args[0]->IsUint32(),0) ||
        isWrongType(!args[1]->IsString(),1) || isWrongType(!args[2]->IsString(),2) ||
        isWrongType(!args[3]->IsString(),3) || isWrongType(!args[4]->IsString(),4) ||
        isWrongType(!args[5]->IsString(),5) || isWrongType(!args[6]->IsString(),6) || 
        isWrongType(!args[7]->IsInt32(),7) ||
        isWrongType(!args[8]->IsString(),8) || isWrongType(!args[9]->IsNumber(),9) ) {
        return scope.Close(Undefined());
    }
    
    OrderId orderId;
    Contract contract;
    Order order;

    orderId = args[0]->Int32Value();
    contract.symbol = getChar(args[1]);
    contract.secType = getChar(args[2]);
    contract.exchange = getChar(args[3]);
    contract.primaryExchange = getChar(args[4]);
    contract.currency = getChar(args[5]);

    order.action = getChar(args[6]);
    order.totalQuantity = args[7]->Int32Value();
    order.orderType = getChar(args[8]);
    order.lmtPrice = args[9]->NumberValue();

    obj->m_client.placeOrder(orderId, contract, order);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::PlaceOrder(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    if ( isWrongArgNumber(args,6) ) {
        return scope.Close(Undefined());
    }

    OrderId orderId;
    Contract contract;
    Order order;

    orderId = args[0]->Int32Value();
    Handle<Object> ibContract = Handle<Object>::Cast(args[1]);

    // checks if order is being submitted through Conract ID from 
    //  contract specification
    contract.conId = ibContract->Get(String::New("conId"))->Int32Value();
    contract.exchange = getChar(ibContract->Get(String::New("exchange")));
    if (contract.conId == 0) {
        contract.symbol = getChar(ibContract->Get(String::New("symbol")));
        contract.secType = getChar(ibContract->Get(String::New("secType")));
        
        contract.primaryExchange = getChar(ibContract->Get(String::New("primaryExchange")));
        contract.currency = getChar(ibContract->Get(String::New("currency")));
    }

    order.action = getChar(args[2]);
    order.totalQuantity = args[3]->Int32Value();
    order.orderType = getChar(args[4]);
    order.lmtPrice = args[5]->NumberValue();

    obj->m_client.placeOrder(orderId, contract, order);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelOrder(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    if (isWrongArgNumber(args, 1) || isWrongType(!args[0]->IsUint32(),0)) {
        return scope.Close(Undefined());
    }
    obj->m_client.cancelOrder(args[0]->Int32Value());
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqOpenOrders(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    obj->m_client.reqOpenOrders();
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqAccountUpdates(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    if (isWrongArgNumber(args, 2) || isWrongType(!args[0]->IsBoolean(),0)
        || isWrongType(!args[1]->IsString(),1)) {
        return scope.Close(Undefined());
    }
    bool subscribe = args[0]->BooleanValue();;
    IBString acctCode = getChar(args[1]);

    obj->m_client.reqAccountUpdates(subscribe,acctCode);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqExecutions(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    if (isWrongArgNumber(args,8)) {
        return scope.Close(Undefined());
    }
    int reqId = args[0]->Int32Value();
    ExecutionFilter filter;
    filter.m_clientId = args[1]->Int32Value();
    filter.m_acctCode = getChar(args[2]);
    filter.m_time = getChar(args[3]);
    filter.m_symbol = getChar(args[4]);
    filter.m_secType = getChar(args[5]);
    filter.m_exchange = getChar(args[6]);
    filter.m_side = getChar(args[7]);

    obj->m_client.reqExecutions(reqId,filter);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqIds(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    if (isWrongArgNumber(args,1)) {
        return scope.Close(Undefined());
    }
    int numIds = args[0]->Int32Value();
    obj->m_client.reqIds(numIds);
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CheckMessages(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    obj->m_client.checkMessages();
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqContractDetails(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqMktDepth(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelMktDepth(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqNewsBulletins(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelNewsBulletins(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::SetServerLogLevel(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqAutoOpenOrders(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqAllOpenOrders(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqManagedAccts(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::RequestFA(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReplaceFA(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqHistoricalData(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ExerciseOptions(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelHistoricalData(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqRealTimeBars(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    if ( isWrongArgNumber(args,5) ) {
        return scope.Close(Undefined());
    }

    TickerId tickerId = args[0]->Int32Value();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast(args[1]);
    // checks if order is being submitted through Conract ID from 
    //  contract specification
    contract.conId = ibContract->Get(String::New("conId"))->Int32Value();
    contract.exchange = getChar(ibContract->Get(String::New("exchange")));
    if (contract.conId == 0) {
        contract.symbol = getChar(ibContract->Get(String::New("symbol")));
        contract.secType = getChar(ibContract->Get(String::New("secType")));
        
        contract.primaryExchange = getChar(ibContract->Get(String::New("primaryExchange")));
        contract.currency = getChar(ibContract->Get(String::New("currency")));
    }

    int barSize = args[2]->Int32Value();
    IBString whatToShow = getChar(args[3]);
    bool useRTH = args[4]->BooleanValue();
    obj->m_client.reqRealTimeBars(tickerId, contract, barSize, whatToShow, useRTH);

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelRealTimeBars(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    if ( isWrongArgNumber(args,1) ) {
        return scope.Close(Undefined());
    }

    TickerId tickerId = args[0]->Int32Value();
    obj->m_client.cancelRealTimeBars(tickerId);

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelScannerSubscription(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqScannerParameters(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqScannerSubscription(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqCurrentTime(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    obj->m_client.reqCurrentTime();
    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqFundamentalData(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelFundamentalData(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CalculateImpliedVolatility(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CalculateOptionPrice(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelCalculateImpliedVolatility(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelCalculateOptionPrice(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqGlobalCancel(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqMarketDataType(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqPositions(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelPositions(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::ReqAccountSummary(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelAccountSummary(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

    return scope.Close(Undefined());
}




Handle<Value> NodeIbapi::NextValidId(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    return scope.Close(Integer::New(obj->m_client.getNextValidId()));
}

Handle<Value> NodeIbapi::CurrentTime(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    return scope.Close(String::New(obj->m_client.getCurrentTime().c_str()));
}

Handle<Value> NodeIbapi::TickPrice(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickPriceData newTickPrice;
    newTickPrice = obj->m_client.getTickPrice();

    Handle<Object> retTickPrice = Object::New();
    retTickPrice->Set(String::NewSymbol("tickerId"), 
        Integer::New(newTickPrice.tickerId));
    retTickPrice->Set(String::NewSymbol("field"), 
        Integer::New(newTickPrice.field));
    retTickPrice->Set(String::NewSymbol("price"), 
        Number::New(newTickPrice.price));
    retTickPrice->Set(String::NewSymbol("canAutoExecute"), 
        Integer::New(newTickPrice.canAutoExecute));
 
    return scope.Close(retTickPrice);
}
Handle<Value> NodeIbapi::TickSize(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickSizeData newTickSize;
    newTickSize = obj->m_client.getTickSize();

    Handle<Object> retTickSize = Object::New();
    retTickSize->Set(String::NewSymbol("tickerId"), Integer::New(newTickSize.tickerId));
    retTickSize->Set(String::NewSymbol("field"), Integer::New(newTickSize.field));
    retTickSize->Set(String::NewSymbol("size"), Integer::New(newTickSize.size));

    return scope.Close(retTickSize);
}
Handle<Value> NodeIbapi::TickOptionComputation(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickOptionComputationData newTickOpt;
    newTickOpt = obj->m_client.getTickOptionComputation();

    Handle<Object> retTickOpt = Object::New();
    retTickOpt->Set(String::NewSymbol("tickerId"), Integer::New(newTickOpt.tickerId));
    retTickOpt->Set(String::NewSymbol("tickType"), Integer::New(newTickOpt.tickType));
    retTickOpt->Set(String::NewSymbol("impliedVol"), Number::New(newTickOpt.impliedVol));
    retTickOpt->Set(String::NewSymbol("delta"), Number::New(newTickOpt.delta));
    retTickOpt->Set(String::NewSymbol("optPrice"), Number::New(newTickOpt.optPrice));
    retTickOpt->Set(String::NewSymbol("pvDividend"), Number::New(newTickOpt.pvDividend));
    retTickOpt->Set(String::NewSymbol("gamma"), Number::New(newTickOpt.gamma));
    retTickOpt->Set(String::NewSymbol("vega"), Number::New(newTickOpt.vega));
    retTickOpt->Set(String::NewSymbol("theta"), Number::New(newTickOpt.theta));
    retTickOpt->Set(String::NewSymbol("undPrice"), Number::New(newTickOpt.undPrice));
    return scope.Close(retTickOpt);
}
Handle<Value> NodeIbapi::TickGeneric(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickGenericData newTickGen;
    newTickGen = obj->m_client.getTickGeneric();

    Handle<Object> retTickGen = Object::New();
    retTickGen->Set(String::NewSymbol("tickerId"), Integer::New(newTickGen.tickerId));
    retTickGen->Set(String::NewSymbol("tickType"), Integer::New(newTickGen.tickType));
    retTickGen->Set(String::NewSymbol("value"), Number::New(newTickGen.value));
    return scope.Close(retTickGen);
}
Handle<Value> NodeIbapi::TickString(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickStringData newTickStr;
    newTickStr = obj->m_client.getTickString();

    Handle<Object> retTickStr = Object::New();
    retTickStr->Set(String::NewSymbol("tickerId"), Integer::New(newTickStr.tickerId));
    retTickStr->Set(String::NewSymbol("tickType"), Integer::New(newTickStr.tickType));
    retTickStr->Set(String::NewSymbol("value"), String::New(newTickStr.value.c_str()));
    return scope.Close(retTickStr);
}
Handle<Value> NodeIbapi::TickEFP(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickEFPData newTickEFP;
    newTickEFP = obj->m_client.getTickEFP();

    Handle<Object> retTickEFP = Object::New();
    retTickEFP->Set(String::NewSymbol("tickerId"), Integer::New(newTickEFP.tickerId));
    retTickEFP->Set(String::NewSymbol("tickType"), Integer::New(newTickEFP.tickType));
    retTickEFP->Set(String::NewSymbol("basisPoints"), Number::New(newTickEFP.basisPoints));
    retTickEFP->Set(String::NewSymbol("formattedBasisPoints"), String::New(newTickEFP.formattedBasisPoints.c_str()));
    retTickEFP->Set(String::NewSymbol("totalDividends"), Number::New(newTickEFP.totalDividends));
    retTickEFP->Set(String::NewSymbol("holdDays"), Integer::New(newTickEFP.holdDays));
    retTickEFP->Set(String::NewSymbol("futureExpiry"), String::New(newTickEFP.futureExpiry.c_str()));
    retTickEFP->Set(String::NewSymbol("dividendImpact"), Number::New(newTickEFP.dividendImpact));
    retTickEFP->Set(String::NewSymbol("dividendsToExpiry"), Number::New(newTickEFP.dividendsToExpiry));
    return scope.Close(retTickEFP);
}
Handle<Value> NodeIbapi::TickSnapshotEnd(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickSnapshotEndData newTickSnapshotEnd;
    newTickSnapshotEnd = obj->m_client.getTickSnapshotEnd();
    Handle<Object> retTickSnapshotEnd = Object::New();
    retTickSnapshotEnd->Set(String::NewSymbol("reqId"), Integer::New(newTickSnapshotEnd.reqId));
    return scope.Close(retTickSnapshotEnd);
}
Handle<Value> NodeIbapi::MarketDataType(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    MarketDataTypeData newMarketDataType;
    newMarketDataType = obj->m_client.getMarketDataType();
    Handle<Object> retMarketDataType = Object::New();
    retMarketDataType->Set(String::NewSymbol("reqId"), Integer::New(newMarketDataType.reqId));
    retMarketDataType->Set(String::NewSymbol("marketDataType"), Integer::New(newMarketDataType.marketDataType));
    return scope.Close(retMarketDataType);
}
Handle<Value> NodeIbapi::OrderStatus(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    OrderStatusData newOrderStatus;
    newOrderStatus = obj->m_client.getOrderStatus();

    Handle<Object> retOrderStatus = Object::New();
    retOrderStatus->Set(String::NewSymbol("orderId"), Integer::New(newOrderStatus.orderId));
    retOrderStatus->Set(String::NewSymbol("status"), String::New(newOrderStatus.status.c_str()));
    retOrderStatus->Set(String::NewSymbol("filled"), Integer::New(newOrderStatus.filled));
    retOrderStatus->Set(String::NewSymbol("remaining"), Integer::New(newOrderStatus.remaining));
    retOrderStatus->Set(String::NewSymbol("avgFillPrice"), Number::New(newOrderStatus.avgFillPrice));
    retOrderStatus->Set(String::NewSymbol("permId"), Integer::New(newOrderStatus.permId));
    retOrderStatus->Set(String::NewSymbol("parentId"), Integer::New(newOrderStatus.parentId));
    retOrderStatus->Set(String::NewSymbol("lastFillPrice"), Number::New(newOrderStatus.lastFillPrice));
    retOrderStatus->Set(String::NewSymbol("clientId"), Integer::New(newOrderStatus.clientId));
    retOrderStatus->Set(String::NewSymbol("whyHeld"), String::New(newOrderStatus.whyHeld.c_str()));
    return scope.Close(retOrderStatus);
}
Handle<Value> NodeIbapi::OpenOrder(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    OpenOrderData newOpenOrder;
    newOpenOrder = obj->m_client.getOpenOrder();

    // TODO for the time being
    Handle<Object> retOpenOrder = Object::New();
    retOpenOrder->Set(String::NewSymbol("orderId"), Integer::New(newOpenOrder.orderId));
    retOpenOrder->Set(String::NewSymbol("status"), String::New(newOpenOrder.orderState.status.c_str()));
    retOpenOrder->Set(String::NewSymbol("initMargin"), String::New(newOpenOrder.orderState.initMargin.c_str()));
    retOpenOrder->Set(String::NewSymbol("maintMargin"), String::New(newOpenOrder.orderState.maintMargin.c_str()));
    retOpenOrder->Set(String::NewSymbol("equityWithLoan"), String::New(newOpenOrder.orderState.equityWithLoan.c_str()));
    retOpenOrder->Set(String::NewSymbol("commission"), Number::New(newOpenOrder.orderState.commission));
    retOpenOrder->Set(String::NewSymbol("minCommission"), Number::New(newOpenOrder.orderState.minCommission));
    retOpenOrder->Set(String::NewSymbol("maxCommission"), Number::New(newOpenOrder.orderState.maxCommission));
    retOpenOrder->Set(String::NewSymbol("commissionCurrency"), String::New(newOpenOrder.orderState.commissionCurrency.c_str()));
    retOpenOrder->Set(String::NewSymbol("warningText"), String::New(newOpenOrder.orderState.warningText.c_str()));
    return scope.Close(retOpenOrder);
}
Handle<Value> NodeIbapi::RealtimeBar(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    RealtimeBarData newRealtimeBar;
    newRealtimeBar = obj->m_client.getRealtimeBar();

    Handle<Object> retRealtimeBar = Object::New();
    retRealtimeBar->Set(String::NewSymbol("reqId"), Integer::New(newRealtimeBar.reqId));
    retRealtimeBar->Set(String::NewSymbol("time"), Integer::New(newRealtimeBar.time));
    retRealtimeBar->Set(String::NewSymbol("open"), Number::New(newRealtimeBar.open));
    retRealtimeBar->Set(String::NewSymbol("high"), Number::New(newRealtimeBar.high));
    retRealtimeBar->Set(String::NewSymbol("low"), Number::New(newRealtimeBar.low));
    retRealtimeBar->Set(String::NewSymbol("close"), Number::New(newRealtimeBar.close));
    retRealtimeBar->Set(String::NewSymbol("volume"), Integer::New(newRealtimeBar.volume));
    retRealtimeBar->Set(String::NewSymbol("wap"), Number::New(newRealtimeBar.wap));
    retRealtimeBar->Set(String::NewSymbol("count"), Integer::New(newRealtimeBar.count));
    return scope.Close(retRealtimeBar);
}

Handle<Value> NodeIbapi::WinError(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    WinErrorData newWinError;
    newWinError = obj->m_client.getWinError();

    Handle<Object> retWinError = Object::New();
    retWinError->Set(String::NewSymbol("str"), String::New(newWinError.str.c_str()));
    retWinError->Set(String::NewSymbol("lastError"), Integer::New(newWinError.lastError));

    return scope.Close(retWinError);
}
Handle<Value> NodeIbapi::Error(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    ErrorData newError;
    newError = obj->m_client.getError();

    Handle<Object> retError = Object::New();
    retError->Set(String::NewSymbol("id"), Integer::New(newError.id));
    retError->Set(String::NewSymbol("errorCode"), Integer::New(newError.errorCode));
    retError->Set(String::NewSymbol("errorString"), String::New(newError.errorString.c_str()));

    return scope.Close(retError);
}
Handle<Value> NodeIbapi::UpdateAccountValue(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    UpdateAccountValueData newUpdateAccountValue;
    newUpdateAccountValue = obj->m_client.getUpdateAccountValue();

    Handle<Object> retUpdateAccountValue = Object::New();
    retUpdateAccountValue->Set(String::NewSymbol("key"), String::New(newUpdateAccountValue.key.c_str()));
    retUpdateAccountValue->Set(String::NewSymbol("val"), String::New(newUpdateAccountValue.val.c_str()));
    retUpdateAccountValue->Set(String::NewSymbol("currency"), String::New(newUpdateAccountValue.currency.c_str()));
    retUpdateAccountValue->Set(String::NewSymbol("accountName"), String::New(newUpdateAccountValue.accountName.c_str()));
    return scope.Close(retUpdateAccountValue);
}


///////////////////////////////////////////////////////////////////////////////
//  Helper methods
///////////////////////////////////////////////////////////////////////////////

bool NodeIbapi::isWrongArgNumber(const Arguments& args, int argNum) {
    if (args.Length() != argNum ) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return true;
    }
    return false;
}

bool NodeIbapi::isWrongType(bool predicateRes, int argId) {
    if (predicateRes) {
        std::ostringstream ss;
        ss << "Argument " << argId << " is of wrong type.";
        ThrowException(Exception::TypeError(String::New(ss.str().c_str())));
        return true;
    } 
    return false;
}

// see http://stackoverflow.com/questions/10507323/shortest-way-one-liner-to-get-a-default-argument-out-of-a-v8-function
char *NodeIbapi::getChar(v8::Local<v8::Value> value, const char *fallback) {
    if (value->IsString()) {
        v8::String::AsciiValue string(value);
        char *str  = (char *) malloc(string.length() + 1);
        std::strcpy(str, *string);
        return str;
    }
    char *str = (char *) malloc(std::strlen(fallback) + 1);
    std::strcpy(str, fallback);
    return str;
}
