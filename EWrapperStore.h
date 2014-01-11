#ifndef ewrapperstore_def
#define ewrapperstore_def


#include "import/Contract.h"
#include "import/Order.h"
#include "import/OrderState.h"
#include "import/Execution.h"
#include "import/CommissionReport.h"

struct TickPriceData {
    TickerId tickerId;
    TickType field;
    double price;
    int canAutoExecute;
};
struct TickSizeData {
    TickerId tickerId;
    TickType field;
    int size;
};
struct TickOptionComputationData {
   TickerId tickerId;
   TickType tickType;
   double impliedVol;
   double delta;
   double optPrice;
   double pvDividend;
   double gamma;
   double vega;
   double theta;
   double undPrice;
};
struct TickGenericData {
    TickerId tickerId;
    TickType tickType;
    double value;
};
struct TickStringData {
    TickerId tickerId;
    TickType tickType;
    IBString value;
};
struct TickEFPData {
    TickerId tickerId;
    TickType tickType;
    double basisPoints;
    IBString formattedBasisPoints;

    double totalDividends;
    int holdDays;
    IBString futureExpiry;
    double dividendImpact;
    double dividendsToExpiry;
};
struct OrderStatusData {
    OrderId orderId;
    IBString status;
    int filled;

    int remaining;
    double avgFillPrice;
    int permId;
    int parentId;

    double lastFillPrice;
    int clientId;
    IBString whyHeld;
};
struct OpenOrderData {
    OrderId orderId;
    Contract contract;
    Order order;
    OrderState orderState;
};
struct OpenOrderEndData {
    int ended;
};
struct WinErrorData {
    IBString str;
    int lastError;
};
struct ConnectionClosedData {
    int closed;
};
struct UpdateAccountValueData {
    IBString key;
    IBString val;
    IBString currency;
    IBString accountName;
};
struct UpdatePortfolioData {
    Contract contract;
    int position;
    double marketPrice;
    double marketValue;
    double averageCost;

    double unrealizedPNL;
    double realizedPNL;
    IBString accountName;
};
struct UpdateAccountTimeData {
    IBString timeStamp;
};
struct AccountDownloadEndData {
    IBString accountName;
};
struct NextValidIdData {
    OrderId orderId;
};
struct ContractDetailsData {
    int reqId;
    ContractDetails contractDetails;
};
struct BondContractDetailsData {
    int reqId;
    ContractDetails contractDetails;
};
struct ContractDetailsEndData {
    int reqId;
};
struct ExecDetailsData {
    int reqId;
    Contract contract;
    Execution execution;
};
struct ExecDetailsEndData {
    int reqId;
};
struct ErrorData {
    int id;
    int errorCode;
    IBString errorString;
};
struct UpdateMktDepthData {
    TickerId id;
    int position;
    int operation;
    int side;
    double price;
    int size;
};
struct UpdateMktDepthL2Data {
    TickerId id;
    int position;
    IBString marketMaker;
    int operation;
    int side;
    double price;
    int size;
};
struct UpdateNewsBulletinData {
    int msgId;
    int msgType;
    IBString newsMessage;
    IBString originExch;
};
struct ManagedAccountsData {
    IBString accountsList;
};
struct ReceiveFAData {
    faDataType pFaDataType;
    IBString cxml;
};
struct HistoricalDataData {
    TickerId reqId;
    IBString date;
    double open;
    double high;
    double low;
    double close;
    int volume;
    int barCount;
    double WAP;
    int hasGaps;
};
struct ScannerParametersData {
    IBString xml;
};
struct ScannerDataData {
    int reqId;
    int rank;
    ContractDetails contractDetails;
    IBString distance;
    IBString benchmark;
    IBString projection;
    IBString legsStr;
};
struct ScannerDataEndData {
    int reqId;
};
struct RealtimeBarData {
    TickerId reqId;
    long time;
    double open;
    double high;
    double low;
    double close;
    long volume;
    double wap;
    int count;
};
struct CurrentTimeData {
    long time;
};
struct FundamentalDataData {
    TickerId reqId;
    IBString data;
};
struct DeltaNeutralValidationData {
    int reqId;
    UnderComp underComp;
};
struct TickSnapshotEndData {
    int reqId;
};
struct MarketDataTypeData {
    TickerId reqId;
    int marketDataType;
};
struct CommissionReportData {
   CommissionReport commissionReport;
};
struct PositionData {
   IBString account;
   Contract contract;
   int position;
   double avgCost;
};
struct PositionEndData {
    int ended;
};
struct AccountSummaryData {
   int reqId;
   IBString account;
   IBString tag;
   IBString value;
   IBString curency;
};
struct AccountSummaryEndData {
   int reqId;
};



#endif // ewrapperstore_def
