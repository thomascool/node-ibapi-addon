#define BUILDING_NODE_EXTENSION
#include <cstring>
#include <cstring>
#include <iostream>
#include <sstream>

#include <node.h>
#include "NodeIbapi.h"



#define IB_USE_STD_STRING
#include <cstdio>

#include "import/EPosixClientSocket.h"
#include "import/EPosixClientSocketPlatform.h"

#include "import/Contract.h"
#include "import/Order.h"

const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds

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

    // TODO need to write test, not sure what would be a good one..
    tpl->PrototypeTemplate()->Set(String::NewSymbol("processMsg"),
        FunctionTemplate::New(ProcessMsg)->GetFunction());

    // Prototype for requests
    // TODO need to write test   
    tpl->PrototypeTemplate()->Set(String::NewSymbol("reqCurrentTime"),
        FunctionTemplate::New(ReqCurrentTime)->GetFunction());

    // Prototype for events
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

    unsigned int port =  args[1]->Uint32Value();
    int clientId = (int)args[2]->IntegerValue();

    // trying to connect
    printf( "Connecting to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);

    bool bRes = obj->m_pClient->eConnect( host, port, clientId);

    if (bRes) {
        printf( "Connected to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);
    }
    else
        printf( "Cannot connect to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);

    return scope.Close(Boolean::New(bRes));
}

// TODO disconnect method should return something
Handle<Value> NodeIbapi::Disconnect(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    obj->m_pClient->eDisconnect();
    printf ( "Disconnected\n");
    return scope.Close(Integer::New(1));
}

Handle<Value> NodeIbapi::IsConnected(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    return scope.Close(Boolean::New(obj->m_pClient->isConnected()));
}

Handle<Value> NodeIbapi::ProcessMsg(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

    fd_set readSet, writeSet, errorSet;

    struct timeval tval;
    tval.tv_usec = 0;
    tval.tv_sec = 0;

    time_t now = time(NULL);

    switch (obj->m_state) {
        case ST_PLACEORDER:
            // placeOrder();
            break;
        case ST_PLACEORDER_ACK:
            break;
        case ST_CANCELORDER:
            // cancelOrder();
            break;
        case ST_CANCELORDER_ACK:
            break;
        case ST_PING:
            // reqCurrentTime();
            break;
        case ST_PING_ACK:
            if( obj->m_sleepDeadline < now) {
                obj->m_pClient->eDisconnect();
                printf ( "Disconnected\n");
                return scope.Close(Integer::New(1));
            }
            break;
        case ST_IDLE:
            if( obj->m_sleepDeadline < now) {
                obj->m_state = ST_PING;
                return scope.Close(Integer::New(1));
            }
            break;
    }

    if( obj->m_sleepDeadline > 0) {
        // initialize timeout with m_sleepDeadline - now
        tval.tv_sec = obj->m_sleepDeadline - now;
    }

    if( obj->m_pClient->fd() >= 0 ) {

        FD_ZERO( &readSet);
        errorSet = writeSet = readSet;

        FD_SET( obj->m_pClient->fd(), &readSet);

        if( !obj->m_pClient->isOutBufferEmpty())
            FD_SET( obj->m_pClient->fd(), &writeSet);

        FD_CLR( obj->m_pClient->fd(), &errorSet);

        int ret = select( obj->m_pClient->fd() + 1, &readSet, &writeSet, &errorSet, &tval);

        if( ret == 0) { // timeout
            return scope.Close(Integer::New(1));
        }

        if( ret < 0) {  // error
            obj->m_pClient->eDisconnect();
            printf ( "Disconnected\n");
            return scope.Close(Integer::New(1));
        }

        if( obj->m_pClient->fd() < 0)
            return scope.Close(Integer::New(1));

        if( FD_ISSET( obj->m_pClient->fd(), &errorSet)) {
            // error on socket
            obj->m_pClient->onError();
        }

        if( obj->m_pClient->fd() < 0)
            return scope.Close(Integer::New(1));

        if( FD_ISSET( obj->m_pClient->fd(), &writeSet)) {
            // socket is ready for writing
            obj->m_pClient->onSend();
        }

        if( obj->m_pClient->fd() < 0)
            return scope.Close(Integer::New(1));

        if( FD_ISSET( obj->m_pClient->fd(), &readSet)) {
            // socket is ready for reading
            obj->m_pClient->onReceive();
        }
    }
    return scope.Close(Integer::New(1));
}

Handle<Value> NodeIbapi::ReqCurrentTime(const Arguments& args) {
    HandleScope scope;
    NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
    
    printf( "Requesting Current Time\n");

    // set ping deadline to "now + n seconds"
    obj->m_sleepDeadline = time( NULL) + PING_DEADLINE;
    obj->m_state = ST_PING_ACK;
    obj->m_pClient->reqCurrentTime();

    return scope.Close(Integer::New(1));
}

// Handle<Value> NodeIbapi::ReqMktData(const Arguments& args) {
//     HandleScope scope;
//     NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());

//     // make tickerId

//     // make contract
//     Contract contract;
//     contract.symbol = "MSFT";
//     contract.secType = "STK";
//     contract.exchange = "SMART";
//     contract.currency = "USD";

//     // make geneticTicks

//     // determine whether it's a snapshot or not
//     obj->m_client->m_pClient->reqMktData(obj->m_tickerId,contract,,true);
//     obj->bumpTickerId();
//     return scope.close(Integer::New(1));
// }

// // events
// Handle<Value> NodeIbapi::CurrentTime(const Arguments& args) {
//     HandleScope scope;
//     NodeIbapi* obj = ObjectWrap::Unwrap<NodeIbapi>(args.This());
//     return scope.Close(String::New(obj->m_client.getCurrentTime().c_str()));
// }
/////////////////////// helper methods //////////////////////////////////

// void NodeIbapi::bumpTickerId() {
//     if (this->m_tickerId > 10000000000) {
//         this->m_tickerId = 0;
//     }
//     this->m_tickerId++;
// }

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


///////////////////////////////////////////////////////////////////
// events
void NodeIbapi::orderStatus( OrderId orderId, const IBString &status, int filled,
       int remaining, double avgFillPrice, int permId, int parentId,
       double lastFillPrice, int clientId, const IBString& whyHeld)

{
    if( orderId == m_orderId) {
        if( m_state == ST_PLACEORDER_ACK && (status == "PreSubmitted" || status == "Submitted"))
            m_state = ST_CANCELORDER;

        if( m_state == ST_CANCELORDER_ACK && status == "Cancelled")
            m_state = ST_PING;

        printf( "Order: id=%ld, status=%s\n", orderId, status.c_str());
    }
}

void NodeIbapi::nextValidId( OrderId orderId)
{
    m_orderId = orderId;

    m_state = ST_PLACEORDER;
}

void NodeIbapi::currentTime( long time)
{
    if ( m_state == ST_PING_ACK) {
        time_t t = ( time_t)time;
        struct tm * timeinfo = localtime ( &t);

        printf( "The current date/time is: %s", asctime( timeinfo));

        time_t now = ::time(NULL);
        m_sleepDeadline = now + SLEEP_BETWEEN_PINGS;

        m_state = ST_IDLE;
    }
}

void NodeIbapi::error(const int id, const int errorCode, const IBString errorString)
{
//  printf( "Error id=%d, errorCode=%d, msg=%s\n", id, errorCode, errorString.c_str());

    if( id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
    {
        m_pClient->eDisconnect();
        printf ( "Disconnected\n");
    }
}


void NodeIbapi::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {

    // std::string pricestring;
    // std::stringstream numStrStream;
    // numStrStream.precision(8);
    // numStrStream << price;
    // pricestring = numStrStream.str();

    // std::string tickerIdString;
    // std::stringstream tickIdStrStream;
    // tickIdStrStream << tickerId;
    // tickerIdString = tickIdStrStream.str();

    // this->m_tickPrice << tickerId << " " << priceString;
}
void NodeIbapi::tickSize( TickerId tickerId, TickType field, int size) {

}

void NodeIbapi::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
                                             double optPrice, double pvDividend,
                                             double gamma, double vega, double theta, double undPrice) {}
void NodeIbapi::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void NodeIbapi::tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
void NodeIbapi::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
                               double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
void NodeIbapi::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState& ostate) {}
void NodeIbapi::openOrderEnd() {}
void NodeIbapi::winError( const IBString &str, int lastError) {}
void NodeIbapi::connectionClosed() {}
void NodeIbapi::updateAccountValue(const IBString& key, const IBString& val,
                                          const IBString& currency, const IBString& accountName) {}
void NodeIbapi::updatePortfolio(const Contract& contract, int position,
        double marketPrice, double marketValue, double averageCost,
        double unrealizedPNL, double realizedPNL, const IBString& accountName){}
void NodeIbapi::updateAccountTime(const IBString& timeStamp) {}
void NodeIbapi::accountDownloadEnd(const IBString& accountName) {}
void NodeIbapi::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void NodeIbapi::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void NodeIbapi::contractDetailsEnd( int reqId) {}
void NodeIbapi::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void NodeIbapi::execDetailsEnd( int reqId) {}

void NodeIbapi::updateMktDepth(TickerId id, int position, int operation, int side,
                                      double price, int size) {}
void NodeIbapi::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
                                        int side, double price, int size) {}
void NodeIbapi::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
void NodeIbapi::managedAccounts( const IBString& accountsList) {}
void NodeIbapi::receiveFA(faDataType pFaDataType, const IBString& cxml) {}
void NodeIbapi::historicalData(TickerId reqId, const IBString& date, double open, double high,
                                      double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
void NodeIbapi::scannerParameters(const IBString &xml) {}
void NodeIbapi::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
       const IBString &distance, const IBString &benchmark, const IBString &projection,
       const IBString &legsStr) {}
void NodeIbapi::scannerDataEnd(int reqId) {}
void NodeIbapi::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
                                   long volume, double wap, int count) {}
void NodeIbapi::fundamentalData(TickerId reqId, const IBString& data) {}
void NodeIbapi::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void NodeIbapi::tickSnapshotEnd(int reqId) {}
void NodeIbapi::marketDataType(TickerId reqId, int marketDataType) {}
void NodeIbapi::commissionReport( const CommissionReport& commissionReport) {}
void NodeIbapi::position( const IBString& account, const Contract& contract, int position) {}
void NodeIbapi::positionEnd() {}
void NodeIbapi::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {}
void NodeIbapi::accountSummaryEnd( int reqId) {}
