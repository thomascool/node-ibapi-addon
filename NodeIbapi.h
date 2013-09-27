#ifndef NODEIBAPI_H
#define NODEIBAPI_H

#define IB_USE_STD_STRING

#include <node.h>
#include "IbPosixClient.h"
#include "import/EWrapper.h"

class NodeIbapi : public node::ObjectWrap{
public:
    static void Init(v8::Handle<v8::Object> exports);

private:
    NodeIbapi();
    ~NodeIbapi();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> ProcessMsg(const v8::Arguments& args);

    // Getters
    static v8::Handle<v8::Value> GetNextOrderId(const v8::Arguments& args);

    // EClientSocket
    static v8::Handle<v8::Value> Connect(const v8::Arguments& args);
    static v8::Handle<v8::Value> Disconnect(const v8::Arguments& args);
    static v8::Handle<v8::Value> IsConnected(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqMktData(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelMktData(const v8::Arguments& args);
    static v8::Handle<v8::Value> PlaceOrder(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelOrder(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqOpenOrders(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqAccountUpdates(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqExecutions(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqIds(const v8::Arguments& args);
    static v8::Handle<v8::Value> CheckMessages(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqContractDetails(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqMktDepth(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelMktDepth(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqNewsBulletins(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelNewsBulletins(const v8::Arguments& args); 
    static v8::Handle<v8::Value> SetServerLogLevel(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqAutoOpenOrders(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqAllOpenOrders(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqManagedAccts(const v8::Arguments& args); 
    static v8::Handle<v8::Value> RequestFA(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReplaceFA(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqHistoricalData(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ExerciseOptions(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelHistoricalData(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqRealTimeBars(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelRealTimeBars(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelScannerSubscription(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqScannerParameters(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqScannerSubscription(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqCurrentTime(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqFundamentalData(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelFundamentalData(const v8::Arguments& args);
    static v8::Handle<v8::Value> CalculateImpliedVolatility(const v8::Arguments& args);
    static v8::Handle<v8::Value> CalculateOptionPrice(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelCalculateImpliedVolatility(const v8::Arguments& args);
    static v8::Handle<v8::Value> CancelCalculateOptionPrice(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqGlobalCancel(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqMarketDataType(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReqPositions(const v8::Arguments& args); 
    static v8::Handle<v8::Value> CancelPositions(const v8::Arguments& args); 
    static v8::Handle<v8::Value> ReqAccountSummary(const v8::Arguments& args); 
    static v8::Handle<v8::Value> CancelAccountSummary(const v8::Arguments& args); 

    // events
    static v8::Handle<v8::Value> TickPrice(const v8::Arguments& args);
    static v8::Handle<v8::Value> TickSize(const v8::Arguments& args);
    static v8::Handle<v8::Value> TickOptionComputation(const v8::Arguments& args);
    static v8::Handle<v8::Value> TickGeneric(const v8::Arguments& args);
    static v8::Handle<v8::Value> TickString(const v8::Arguments& args);
    static v8::Handle<v8::Value> TickEFP(const v8::Arguments& args);
    static v8::Handle<v8::Value> OrderStatus(const v8::Arguments& args);
    static v8::Handle<v8::Value> OpenOrder(const v8::Arguments& args);
    static v8::Handle<v8::Value> OpenOrderEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> WinError(const v8::Arguments& args);
    static v8::Handle<v8::Value> ConnectionClosed(const v8::Arguments& args);
    static v8::Handle<v8::Value> UpdateAccountValue(const v8::Arguments& args);
    static v8::Handle<v8::Value> UpdatePortfolio(const v8::Arguments& args);
    static v8::Handle<v8::Value> UpdateAccountTime(const v8::Arguments& args);
    static v8::Handle<v8::Value> AccountDownloadEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> NextValidId(const v8::Arguments& args);
    static v8::Handle<v8::Value> ContractDetails(const v8::Arguments& args);
    static v8::Handle<v8::Value> BondContractDetails(const v8::Arguments& args);
    static v8::Handle<v8::Value> ContractDetailsEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> ExecDetails(const v8::Arguments& args);
    static v8::Handle<v8::Value> ExecDetailsEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> Error(const v8::Arguments& args);
    static v8::Handle<v8::Value> UpdateMktDepth(const v8::Arguments& args);
    static v8::Handle<v8::Value> UpdateMktDepthL2(const v8::Arguments& args);
    static v8::Handle<v8::Value> UpdateNewsBulletin(const v8::Arguments& args);
    static v8::Handle<v8::Value> ManagedAccounts(const v8::Arguments& args);
    static v8::Handle<v8::Value> ReceiveFA(const v8::Arguments& args);
    static v8::Handle<v8::Value> HistoricalData(const v8::Arguments& args);
    static v8::Handle<v8::Value> ScannerParameters(const v8::Arguments& args);
    static v8::Handle<v8::Value> ScannerData(const v8::Arguments& args);
    static v8::Handle<v8::Value> ScannerDataEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> RealtimeBar(const v8::Arguments& args);
    static v8::Handle<v8::Value> CurrentTime(const v8::Arguments& args);
    static v8::Handle<v8::Value> FundamentalData(const v8::Arguments& args);
    static v8::Handle<v8::Value> DeltaNeutralValidation(const v8::Arguments& args);
    static v8::Handle<v8::Value> TickSnapshotEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> MarketDataType(const v8::Arguments& args);
    static v8::Handle<v8::Value> CommissionReport(const v8::Arguments& args);
    static v8::Handle<v8::Value> Position(const v8::Arguments& args);
    static v8::Handle<v8::Value> PositionEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> AccountSummary(const v8::Arguments& args);
    static v8::Handle<v8::Value> AccountSummaryEnd(const v8::Arguments& args);


private:
    static char *getChar(v8::Local<v8::Value> value, const char *fallback = "");

    IbPosixClient m_client;

};

#endif