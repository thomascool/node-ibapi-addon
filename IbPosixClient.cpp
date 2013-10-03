
#define IB_USE_STD_STRING

#include <iostream>

#include "IbPosixClient.h"

#include "import/EPosixClientSocket.h"
#include "import/EPosixClientSocketPlatform.h"

#include "import/Contract.h"
#include "import/Order.h"

IbPosixClient::IbPosixClient()
    : m_pClient(new EPosixClientSocket(this))
    , m_orderId(0)
{
}

IbPosixClient::~IbPosixClient() 
{
}

/////////////////// Custom functions for node access //////////////////////////
bool IbPosixClient::connect(const char *host, unsigned int port, int clientId) {
    bool isConnected = m_pClient->eConnect(host, port, clientId);
    return isConnected;
}

void IbPosixClient::disconnect() const {
    m_pClient->eDisconnect();
}

bool IbPosixClient::isConnected() const {
    return m_pClient->isConnected();
}

void IbPosixClient::processMessages() {
    fd_set readfds, writefds, errorfds;

    struct timeval tval;
    tval.tv_usec = 0;
    tval.tv_sec = 0;
    time_t now = time(NULL);

    if( m_pClient->fd() >= 0 ) {
        FD_ZERO( &readfds);
        errorfds = writefds = readfds;
        FD_SET( m_pClient->fd(), &readfds);

        if( !m_pClient->isOutBufferEmpty())
            FD_SET( m_pClient->fd(), &writefds);

        FD_CLR( m_pClient->fd(), &errorfds);
        int ret = select( m_pClient->fd() + 1, &readfds, &writefds, &errorfds, &tval);
        
        if( ret == 0) // timeout
            return;
        if( ret < 0) // error
            disconnect();
            return;
        if( m_pClient->fd() < 0)
            return;
        if ( FD_ISSET( m_pClient->fd(), &errorfds)) 
            m_pClient->onError();
        if( m_pClient->fd() < 0)
            return;
        if ( FD_ISSET( m_pClient->fd(), &writefds)) 
            m_pClient->onSend();
        if( m_pClient->fd() < 0)
            return;
        if ( FD_ISSET( m_pClient->fd(), &readfds)) 
            m_pClient->onReceive();
    }
}

std::string IbPosixClient::getCurrentTime() {
    std::string retVal = this->m_currentTime;
    this->m_currentTime.clear();
    return retVal;
}

TickPriceData IbPosixClient::getTickPrice() {
    TickPriceData popped;
    if (!this->m_tickPrices.empty()) {
        popped = this->m_tickPrices.front();
        this->m_tickPrices.pop();
        return popped;
    }
    popped.tickerId = -1;
    return popped; 
}
TickSizeData IbPosixClient::getTickSize() {
    TickSizeData popped;
    if (!this->m_tickSizes.empty()) {
        popped = this->m_tickSizes.front();
        this->m_tickSizes.pop();
        return popped;
    }
    popped.tickerId = -1;
    return popped; 
}
TickOptionComputationData IbPosixClient::getTickOptionComputation() {
    TickOptionComputationData popped;
    if (!this->m_tickOptionComps.empty()) {
        popped = this->m_tickOptionComps.front();
        this->m_tickOptionComps.pop();
        return popped;
    }
    popped.tickerId = -1;
    return popped; 
}
TickGenericData IbPosixClient::getTickGeneric() {
    TickGenericData popped;
    if (!this->m_tickGenerics.empty()) {
        popped = this->m_tickGenerics.front();
        this->m_tickGenerics.pop();
        return popped;
    }
    popped.tickerId = -1;
    return popped;     
}
TickStringData IbPosixClient::getTickString() {
    TickStringData popped;
    if (!this->m_tickStrings.empty()) {
        popped = this->m_tickStrings.front();
        this->m_tickStrings.pop();
        return popped;
    }
    popped.tickerId = -1;
    return popped; 
}
TickEFPData IbPosixClient::getTickEFP() {
    TickEFPData popped;
    if (!this->m_tickEFPs.empty()) {
        popped = this->m_tickEFPs.front();
        this->m_tickEFPs.pop();
        return popped;
    }
    popped.tickerId = -1;
    return popped; 
}
OrderStatusData IbPosixClient::getOrderStatus() {
    OrderStatusData popped;
    if (!this->m_orderStatuses.empty()) {
        popped = this->m_orderStatuses.front();
        this->m_orderStatuses.pop();
        return popped;
    }
    popped.orderId = -1;
    return popped; 
}

OrderId IbPosixClient::getNextOrderId() {
    OrderId nextOrder = this->m_orderId;
    return nextOrder;
}

/////////////////// API EPosixClientSocket method for node access /////////////
void IbPosixClient::reqMktData( TickerId tickerId, const Contract &contract
    , const IBString &genericTick, bool snapShot ) {
    m_pClient->reqMktData(tickerId, contract, genericTick, snapShot);
}
void IbPosixClient::cancelMktData( TickerId tickerId) {
    m_pClient->cancelMktData(tickerId);
}
void IbPosixClient::placeOrder( OrderId id, const Contract &contract, const Order &order) {
    m_pClient->placeOrder( id, contract, order);
}
void IbPosixClient::cancelOrder( OrderId orderId) {
    m_pClient->cancelOrder( orderId);
}
void IbPosixClient::reqOpenOrders() {
    m_pClient->reqOpenOrders();
}
void IbPosixClient::reqAccountUpdates(bool subscribe, const IBString& acctCode) {
    m_pClient->reqAccountUpdates(subscribe, acctCode);
}
void IbPosixClient::reqExecutions( int reqId, const ExecutionFilter& filter) {
    m_pClient->reqExecutions( reqId, filter);
}
void IbPosixClient::reqIds(int numIds) {
    m_pClient->reqIds(numIds);    
}
bool IbPosixClient::checkMessages(){
    return m_pClient->checkMessages();
}
void IbPosixClient::reqContractDetails(int reqId, const Contract &contract) {
    m_pClient->reqContractDetails(reqId,contract);
}
void IbPosixClient::reqMktDepth(TickerId tickerId, const Contract &contract, int numRows) {
    m_pClient->reqMktDepth(tickerId, contract, numRows);
}
void IbPosixClient::cancelMktDepth(TickerId tickerId) {
    m_pClient->cancelMktDepth(tickerId);
}
void IbPosixClient::reqNewsBulletins(bool allMsgs) {
    m_pClient->reqNewsBulletins(allMsgs);
}
void IbPosixClient::cancelNewsBulletins() {
    m_pClient->cancelNewsBulletins();
}
void IbPosixClient::setServerLogLevel(int level) {
    m_pClient->setServerLogLevel(level);
}

void IbPosixClient::reqAutoOpenOrders(bool bAutoBind) {
    m_pClient->reqAutoOpenOrders(bAutoBind);
}
void IbPosixClient::reqAllOpenOrders() {
    m_pClient->reqAllOpenOrders();
}
void IbPosixClient::reqManagedAccts() {
    m_pClient->reqManagedAccts();
}
void IbPosixClient::requestFA(faDataType pFaDataType) {
    m_pClient->requestFA(pFaDataType);
}
void IbPosixClient::replaceFA(faDataType pFaDataType, const IBString& cxml) {
    m_pClient->replaceFA(pFaDataType, cxml);
}
void IbPosixClient::reqHistoricalData( TickerId id, const Contract &contract,
        const IBString &endDateTime, const IBString &durationStr,
        const IBString & barSizeSetting, const IBString &whatToShow,
        int useRTH, int formatDate) {
    m_pClient->reqHistoricalData(id, contract, endDateTime, durationStr, barSizeSetting,
        whatToShow, useRTH, formatDate);
}
void IbPosixClient::exerciseOptions(TickerId tickerId, const Contract &contract,
        int exerciseAction, int exerciseQuantity,
        const IBString &account, int override) {
    m_pClient->exerciseOptions(tickerId, contract, exerciseAction, exerciseQuantity,
        account, override);
}
void IbPosixClient::cancelHistoricalData(TickerId tickerId ) {
    m_pClient->cancelHistoricalData(tickerId);
}
void IbPosixClient::reqRealTimeBars(TickerId id, const Contract &contract, int barSize,
        const IBString &whatToShow, bool useRTH) {
    m_pClient->reqRealTimeBars(id, contract, barSize, whatToShow, useRTH);
}
void IbPosixClient::cancelRealTimeBars(TickerId tickerId ) {
    m_pClient->cancelRealTimeBars(tickerId);
}
void IbPosixClient::cancelScannerSubscription(int tickerId) {
    m_pClient->cancelScannerSubscription(tickerId);
}
void IbPosixClient::reqScannerParameters() {
    m_pClient->reqScannerParameters();
}
void IbPosixClient::reqScannerSubscription(int tickerId, 
        const ScannerSubscription &subscription) {
    m_pClient->reqScannerSubscription(tickerId, subscription);
}
void IbPosixClient::reqCurrentTime() {
    m_pClient->reqCurrentTime();
}
void IbPosixClient::reqFundamentalData(TickerId reqId, const Contract&, 
    const IBString &reportType) {
    Contract contract;
    m_pClient->reqFundamentalData(reqId, contract, reportType);
}
void IbPosixClient::cancelFundamentalData(TickerId reqId) {
    m_pClient->cancelFundamentalData(reqId);
}
void IbPosixClient::calculateImpliedVolatility(TickerId reqId, 
        const Contract &contract, double optionPrice, double underPrice) {
    m_pClient->calculateImpliedVolatility(reqId, contract, optionPrice, 
            underPrice);
}
void IbPosixClient::calculateOptionPrice(TickerId reqId, 
        const Contract &contract, double volatility, double underPrice) {
    m_pClient->calculateOptionPrice(reqId, contract, volatility, underPrice);
}
void IbPosixClient::cancelCalculateImpliedVolatility(TickerId reqId) {
    m_pClient->cancelCalculateImpliedVolatility(reqId);
}
void IbPosixClient::cancelCalculateOptionPrice(TickerId reqId) {
    m_pClient->cancelCalculateOptionPrice(reqId);
}
void IbPosixClient::reqGlobalCancel() {
    m_pClient->reqGlobalCancel();
}
void IbPosixClient::reqMarketDataType(int marketDataType) {
    m_pClient->reqMarketDataType(marketDataType);
}
void IbPosixClient::reqPositions() {
    m_pClient->reqPositions();
}
void IbPosixClient::cancelPositions() {
    m_pClient->cancelPositions();
}
void IbPosixClient::reqAccountSummary( int reqId, const IBString& groupName, 
        const IBString& tags) {
    m_pClient->reqAccountSummary(reqId, groupName, tags);
}
void IbPosixClient::cancelAccountSummary( int reqId) {
    m_pClient->cancelAccountSummary(reqId);
}


/////////////////// API EWrapper event methods ////////////////////////////////

void IbPosixClient::tickPrice( TickerId tickerId, TickType field, double price,
        int canAutoExecute) {
    TickPriceData newData;
    newData.tickerId = tickerId;
    newData.field = field;
    newData.price = price;
    newData.canAutoExecute = canAutoExecute;
    this->m_tickPrices.push(newData);
}
void IbPosixClient::tickSize( TickerId tickerId, TickType field, int size) {
    TickSizeData newData;
    newData.tickerId = tickerId;
    newData.field = field;
    newData.size = size;
    this->m_tickSizes.push(newData);
}
// TODO NOT TESTED
void IbPosixClient::tickOptionComputation( TickerId tickerId, 
        TickType tickType, double impliedVol, double delta, double optPrice, 
        double pvDividend, double gamma, double vega, double theta, 
        double undPrice) {
    TickOptionComputationData newData;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.impliedVol = impliedVol;
    newData.delta = delta;
    newData.optPrice = optPrice;
    newData.pvDividend = pvDividend;
    newData.gamma = gamma;
    newData.vega = vega;
    newData.theta = theta;
    newData.undPrice = undPrice;
    this->m_tickOptionComps.push(newData);
}
// TODO NOT TESTED
void IbPosixClient::tickGeneric(TickerId tickerId, TickType tickType, double value) {
    TickGenericData newData;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.value = value;
    this->m_tickGenerics.push(newData);
}
// TODO NOT TESTED
void IbPosixClient::tickString(TickerId tickerId, TickType tickType, 
        const IBString& value) {
    if (tickType == 48) {
        TickStringData newData;
        newData.tickerId = tickerId;
        newData.tickType = tickType;
        newData.value = value;
        this->m_tickStrings.push(newData);
    }
}
// TODO NOT TESTED
void IbPosixClient::tickEFP(TickerId tickerId, TickType tickType, 
        double basisPoints, const IBString& formattedBasisPoints, 
        double totalDividends, int holdDays, const IBString& futureExpiry, 
        double dividendImpact, double dividendsToExpiry) {
    TickEFPData newData;
    newData.tickerId = tickerId;
    newData.tickType = tickType;
    newData.basisPoints = basisPoints;
    newData.formattedBasisPoints = formattedBasisPoints;
    newData.totalDividends = totalDividends;
    newData.holdDays = holdDays;
    newData.futureExpiry = futureExpiry;
    newData.dividendImpact = dividendImpact;
    newData.dividendsToExpiry = dividendsToExpiry;
    this->m_tickEFPs.push(newData);

}
// TODO NOT TESTED
void IbPosixClient::orderStatus( OrderId orderId, const IBString &status, 
        int filled, int remaining, double avgFillPrice, int permId, 
        int parentId, double lastFillPrice, int clientId, 
        const IBString& whyHeld) {
    OrderStatusData newData;
    newData.orderId = orderId;
    newData.status = status;
    newData.filled = filled;
    newData.remaining = remaining;
    newData.avgFillPrice = avgFillPrice;
    newData.permId = permId;
    newData.parentId = parentId;
    newData.lastFillPrice = lastFillPrice;
    newData.clientId = clientId;
    newData.whyHeld = whyHeld;
    this->m_orderStatuses.push(newData);
}
void IbPosixClient::openOrder( OrderId orderId, const Contract&, const Order&, 
        const OrderState& ostate) {}
void IbPosixClient::openOrderEnd() {}
void IbPosixClient::winError( const IBString &str, int lastError) {}
void IbPosixClient::connectionClosed() {}
void IbPosixClient::updateAccountValue(const IBString& key, const IBString& val,
                                          const IBString& currency, const IBString& accountName) {}
void IbPosixClient::updatePortfolio(const Contract& contract, int position,
        double marketPrice, double marketValue, double averageCost,
        double unrealizedPNL, double realizedPNL, const IBString& accountName){}
void IbPosixClient::updateAccountTime(const IBString& timeStamp) {}
void IbPosixClient::accountDownloadEnd(const IBString& accountName) {}
void IbPosixClient::nextValidId( OrderId orderId) {
    m_orderId = orderId;
}
void IbPosixClient::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void IbPosixClient::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void IbPosixClient::contractDetailsEnd( int reqId) {}
void IbPosixClient::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void IbPosixClient::execDetailsEnd( int reqId) {}
void IbPosixClient::error( const int id, const int errorCode, const IBString errorString) {
    if (id == -1 && errorCode == 1100)
        disconnect();
}
void IbPosixClient::updateMktDepth(TickerId id, int position, int operation, int side,
                                      double price, int size) {}
void IbPosixClient::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
                                        int side, double price, int size) {}
void IbPosixClient::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch) {}
void IbPosixClient::managedAccounts( const IBString& accountsList) {}
void IbPosixClient::receiveFA(faDataType pFaDataType, const IBString& cxml) {}
void IbPosixClient::historicalData(TickerId reqId, const IBString& date, double open, double high,
                                      double low, double close, int volume, int barCount, double WAP, int hasGaps) {}
void IbPosixClient::scannerParameters(const IBString &xml) {}
void IbPosixClient::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
       const IBString &distance, const IBString &benchmark, const IBString &projection,
       const IBString &legsStr) {}
void IbPosixClient::scannerDataEnd(int reqId) {}
void IbPosixClient::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
                                   long volume, double wap, int count) {}
void IbPosixClient::currentTime( long time) {
    time_t t = (time_t)time;
    struct tm * timeinfo = localtime ( &t);
    this->m_currentTime.clear();
    std::string currTime(asctime(timeinfo));
    this->m_currentTime.append(currTime);
    time_t now = ::time(NULL);
}
void IbPosixClient::fundamentalData(TickerId reqId, const IBString& data) {}
void IbPosixClient::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void IbPosixClient::tickSnapshotEnd(int reqId) {}
void IbPosixClient::marketDataType(TickerId reqId, int marketDataType) {}
void IbPosixClient::commissionReport( const CommissionReport& commissionReport) {}
void IbPosixClient::position( const IBString& account, const Contract& contract, int position) {}
void IbPosixClient::positionEnd() {}
void IbPosixClient::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {}
void IbPosixClient::accountSummaryEnd( int reqId) {}

