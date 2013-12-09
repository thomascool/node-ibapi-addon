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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getNextOrderId"),
        FunctionTemplate::New(GetNextOrderId)->GetFunction());
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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getOrderStatus"),
        FunctionTemplate::New(OrderStatus)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getOpenOrder"),
        FunctionTemplate::New(OpenOrder)->GetFunction());
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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqRealTimeBars"),
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

    TickerId tickerId = args[0]->IntegerValue();
    Contract contract;
 
    Handle<Object> ibContract = Handle<Object>::Cast(args[1]);
    contract.symbol = getChar(ibContract->Get(String::New("symbol")));
    contract.secType = getChar(ibContract->Get(String::New("secType")));
    contract.exchange = getChar(ibContract->Get(String::New("exchange")));
    contract.primaryExchange = getChar(ibContract->Get(String::New("primaryExchange")));
    contract.currency = getChar(ibContract->Get(String::New("currency")));

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

    TickerId tickerId = args[0]->IntegerValue();

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

    orderId = args[0]->IntegerValue();
    contract.symbol = getChar(args[1]);
    contract.secType = getChar(args[2]);
    contract.exchange = getChar(args[3]);
    contract.primaryExchange = getChar(args[4]);
    contract.currency = getChar(args[5]);

    order.action = getChar(args[6]);
    order.totalQuantity = args[7]->IntegerValue();
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

    orderId = args[0]->IntegerValue();
    Handle<Object> ibContract = Handle<Object>::Cast(args[1]);

    contract.symbol = getChar(ibContract->Get(String::New("symbol")));
    contract.secType = getChar(ibContract->Get(String::New("secType")));
    contract.exchange = getChar(ibContract->Get(String::New("exchange")));
    contract.primaryExchange = getChar(ibContract->Get(String::New("primaryExchange")));
    contract.currency = getChar(ibContract->Get(String::New("currency")));

    order.action = getChar(args[2]);
    order.totalQuantity = args[3]->IntegerValue();
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
    obj->m_client.cancelOrder(args[0]->IntegerValue());
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
    filter.m_clientId = args[1]->IntegerValue();
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
    // TODO: placeholder

    return scope.Close(Undefined());
}
Handle<Value> NodeIbapi::CancelRealTimeBars(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    // TODO: placeholder

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




Handle<Value> NodeIbapi::GetNextOrderId(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    return scope.Close(Integer::New(obj->m_client.getNextOrderId()));
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

    Handle<Array> retTickPrice = Array::New(4);
    retTickPrice->Set(0, Integer::New(newTickPrice.tickerId));
    retTickPrice->Set(1, Integer::New(newTickPrice.field));
    retTickPrice->Set(2, Number::New(newTickPrice.price));
    retTickPrice->Set(3, Integer::New(newTickPrice.canAutoExecute));
 
    return scope.Close(retTickPrice);
}
Handle<Value> NodeIbapi::TickSize(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickSizeData newTickSize;
    newTickSize = obj->m_client.getTickSize();

    Handle<Array> retTickSize = Array::New(3);
    retTickSize->Set(0, Integer::New(newTickSize.tickerId));
    retTickSize->Set(1, Integer::New(newTickSize.field));
    retTickSize->Set(2, Integer::New(newTickSize.size));

    return scope.Close(retTickSize);
}
Handle<Value> NodeIbapi::TickOptionComputation(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickOptionComputationData newTickOpt;
    newTickOpt = obj->m_client.getTickOptionComputation();

    Handle<Array> retTickOpt = Array::New(10);
    retTickOpt->Set(0, Integer::New(newTickOpt.tickerId));
    retTickOpt->Set(1, Integer::New(newTickOpt.tickType));
    retTickOpt->Set(2, Number::New(newTickOpt.impliedVol));
    retTickOpt->Set(3, Number::New(newTickOpt.delta));
    retTickOpt->Set(4, Number::New(newTickOpt.optPrice));
    retTickOpt->Set(5, Number::New(newTickOpt.pvDividend));
    retTickOpt->Set(6, Number::New(newTickOpt.gamma));
    retTickOpt->Set(7, Number::New(newTickOpt.vega));
    retTickOpt->Set(8, Number::New(newTickOpt.theta));
    retTickOpt->Set(9, Number::New(newTickOpt.undPrice));
    return scope.Close(retTickOpt);
}
Handle<Value> NodeIbapi::TickGeneric(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickGenericData newTickGen;
    newTickGen = obj->m_client.getTickGeneric();

    Handle<Array> retTickGen = Array::New(3);
    retTickGen->Set(0, Integer::New(newTickGen.tickerId));
    retTickGen->Set(1, Integer::New(newTickGen.tickType));
    retTickGen->Set(2, Number::New(newTickGen.value));
    return scope.Close(retTickGen);
}
Handle<Value> NodeIbapi::TickString(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    
    return scope.Close(String::New(obj->m_client.getTickString().value.c_str()));
}
Handle<Value> NodeIbapi::TickEFP(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    TickEFPData newTickEFP;
    newTickEFP = obj->m_client.getTickEFP();

    Handle<Array> retTickEFP = Array::New(9);
    retTickEFP->Set(0, Integer::New(newTickEFP.tickerId));
    retTickEFP->Set(1, Integer::New(newTickEFP.tickType));
    retTickEFP->Set(2, Number::New(newTickEFP.basisPoints));
    retTickEFP->Set(3, String::New(newTickEFP.formattedBasisPoints.c_str()));
    retTickEFP->Set(4, Number::New(newTickEFP.totalDividends));
    retTickEFP->Set(5, Integer::New(newTickEFP.holdDays));
    retTickEFP->Set(6, String::New(newTickEFP.futureExpiry.c_str()));
    retTickEFP->Set(7, Number::New(newTickEFP.dividendImpact));
    retTickEFP->Set(8, Number::New(newTickEFP.dividendsToExpiry));
    return scope.Close(retTickEFP);
}
Handle<Value> NodeIbapi::OrderStatus(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    OrderStatusData newOrderStatus;
    newOrderStatus = obj->m_client.getOrderStatus();

    Handle<Array> retOrderStatus = Array::New(10);
    retOrderStatus->Set(0, Integer::New(newOrderStatus.orderId));
    retOrderStatus->Set(1, String::New(newOrderStatus.status.c_str()));
    retOrderStatus->Set(2, Integer::New(newOrderStatus.filled));
    retOrderStatus->Set(3, Integer::New(newOrderStatus.remaining));
    retOrderStatus->Set(4, Number::New(newOrderStatus.avgFillPrice));
    retOrderStatus->Set(5, Integer::New(newOrderStatus.permId));
    retOrderStatus->Set(6, Integer::New(newOrderStatus.parentId));
    retOrderStatus->Set(7, Number::New(newOrderStatus.lastFillPrice));
    retOrderStatus->Set(8, Integer::New(newOrderStatus.clientId));
    retOrderStatus->Set(9, String::New(newOrderStatus.whyHeld.c_str()));
    return scope.Close(retOrderStatus);
}
Handle<Value> NodeIbapi::OpenOrder(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    OpenOrderData newOpenOrder;
    newOpenOrder = obj->m_client.getOpenOrder();

    // TODO for the time being
    Handle<Array> retOpenOrder = Array::New(10);
    retOpenOrder->Set(0, Integer::New(newOpenOrder.orderId));
    retOpenOrder->Set(1, String::New(newOpenOrder.orderState.status.c_str()));
    retOpenOrder->Set(2, String::New(newOpenOrder.orderState.initMargin.c_str()));
    retOpenOrder->Set(3, String::New(newOpenOrder.orderState.maintMargin.c_str()));
    retOpenOrder->Set(4, String::New(newOpenOrder.orderState.equityWithLoan.c_str()));
    retOpenOrder->Set(5, Number::New(newOpenOrder.orderState.commission));
    retOpenOrder->Set(6, Number::New(newOpenOrder.orderState.minCommission));
    retOpenOrder->Set(7, Number::New(newOpenOrder.orderState.maxCommission));
    retOpenOrder->Set(8, String::New(newOpenOrder.orderState.commissionCurrency.c_str()));
    retOpenOrder->Set(9, String::New(newOpenOrder.orderState.warningText.c_str()));
    return scope.Close(retOpenOrder);
}
Handle<Value> NodeIbapi::WinError(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    WinErrorData newWinError;
    newWinError = obj->m_client.getWinError();

    Handle<Array> retWinError = Array::New(2);
    retWinError->Set(0, String::New(newWinError.str.c_str()));
    retWinError->Set(1, Integer::New(newWinError.lastError));

    return scope.Close(retWinError);
}
Handle<Value> NodeIbapi::Error(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    ErrorData newError;
    newError = obj->m_client.getError();

    Handle<Array> retError = Array::New(3);
    retError->Set(0, Integer::New(newError.id));
    retError->Set(1, Integer::New(newError.errorCode));
    retError->Set(2, String::New(newError.errorString.c_str()));

    return scope.Close(retError);
}
Handle<Value> NodeIbapi::UpdateAccountValue(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    UpdateAccountValueData newUpdateAccountValue;
    newUpdateAccountValue = obj->m_client.getUpdateAccountValue();

    Handle<Array> retUpdateAccountValue = Array::New(4);
    retUpdateAccountValue->Set(0, String::New(newUpdateAccountValue.key.c_str()));
    retUpdateAccountValue->Set(1, String::New(newUpdateAccountValue.val.c_str()));
    retUpdateAccountValue->Set(2, String::New(newUpdateAccountValue.currency.c_str()));
    retUpdateAccountValue->Set(4, String::New(newUpdateAccountValue.accountName.c_str()));
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
