
#define IB_USE_STD_STRING
#include <cstdio>
#include "IbPosixClient.h"

#include "import/EPosixClientSocket.h"
#include "import/EPosixClientSocketPlatform.h"

const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds

// member funcs
IbPosixClient::IbPosixClient()
	: m_pClient(new EPosixClientSocket(this))
	, m_state(ST_CONNECT)
	, m_sleepDeadline(0)
	, m_orderId(0)
{
}

IbPosixClient::~IbPosixClient()
{
}

bool IbPosixClient::connect(const char *host, unsigned int port, int clientId)
{
	// trying to connect
	printf( "Connecting to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);

	bool bRes = m_pClient->eConnect( host, port, clientId);

	if (bRes) {
		printf( "Connected to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);
	}
	else
		printf( "Cannot connect to %s:%d clientId:%d\n", !( host && *host) ? "127.0.0.1" : host, port, clientId);

	return bRes;
}

void IbPosixClient::disconnect() const
{
	m_pClient->eDisconnect();

	printf ( "Disconnected\n");

}

bool IbPosixClient::isConnected() const
{
	return m_pClient->isConnected();
}

///////////////////////////////////////////////////////////////////
// events
void IbPosixClient::orderStatus( OrderId orderId, const IBString &status, int filled,
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

void IbPosixClient::nextValidId( OrderId orderId)
{
	m_orderId = orderId;

	m_state = ST_PLACEORDER;
}

void IbPosixClient::currentTime( long time)
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

void IbPosixClient::error(const int id, const int errorCode, const IBString errorString)
{
//	printf( "Error id=%d, errorCode=%d, msg=%s\n", id, errorCode, errorString.c_str());

	if( id == -1 && errorCode == 1100) // if "Connectivity between IB and TWS has been lost"
		disconnect();
}


void IbPosixClient::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) {}
void IbPosixClient::tickSize( TickerId tickerId, TickType field, int size) {}
void IbPosixClient::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
											 double optPrice, double pvDividend,
											 double gamma, double vega, double theta, double undPrice) {}
void IbPosixClient::tickGeneric(TickerId tickerId, TickType tickType, double value) {}
void IbPosixClient::tickString(TickerId tickerId, TickType tickType, const IBString& value) {}
void IbPosixClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
							   double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
void IbPosixClient::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState& ostate) {}
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
void IbPosixClient::contractDetails( int reqId, const ContractDetails& contractDetails) {}
void IbPosixClient::bondContractDetails( int reqId, const ContractDetails& contractDetails) {}
void IbPosixClient::contractDetailsEnd( int reqId) {}
void IbPosixClient::execDetails( int reqId, const Contract& contract, const Execution& execution) {}
void IbPosixClient::execDetailsEnd( int reqId) {}

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
void IbPosixClient::fundamentalData(TickerId reqId, const IBString& data) {}
void IbPosixClient::deltaNeutralValidation(int reqId, const UnderComp& underComp) {}
void IbPosixClient::tickSnapshotEnd(int reqId) {}
void IbPosixClient::marketDataType(TickerId reqId, int marketDataType) {}
void IbPosixClient::commissionReport( const CommissionReport& commissionReport) {}
void IbPosixClient::position( const IBString& account, const Contract& contract, int position) {}
void IbPosixClient::positionEnd() {}
void IbPosixClient::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency) {}
void IbPosixClient::accountSummaryEnd( int reqId) {}
