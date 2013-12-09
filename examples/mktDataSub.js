// In this example, we will try to submit a market data subscription
//  to EUR/USD and get the TickPrice and TickSize events from the
//  IB Cash Data Server
// Also, in this example we will submit a market data subscription 
//  to MSFT.

var addon = require('../build/Release/NodeIbapiAddon');
var ibcontract = require('../lib/contract');

var obj = new addon.NodeIbapi();

var once = false;
obj.connect('127.0.0.1',7496,0);

var tickPrice;
var tickSize;
var clientError;
var srvError;

while (obj.isConnected()) {
  obj.checkMessages();
  obj.processMsg();
  clientError = obj.getWinError();
  srvError = obj.getError();

  if (!once) {
    // subscribe to EUR-USD pair
    var eurusd = ibcontract.createContract();
    eurusd.symbol = 'EUR';
    eurusd.secType = 'CASH';
    eurusd.exchange = 'IDEALPRO';
    eurusd.primaryExchange = 'IDEALPRO';
    eurusd.currency = 'USD';
    obj.reqMktData(1,eurusd,"165",false);

    // subscribe to Microsoft
    var msftContract = ibcontract.createContract();
    msftContract.symbol = 'MSFT';
    msftContract.secType = 'STK';
    msftContract.exchange = 'SMART';
    msftContract.primaryExchange = 'NASDAQ';
    msftContract.currency = 'USD';

    obj.reqMktData(3,msftContract,"165",false);
    once = true;
  }
  if (clientError[0] != "") {
    console.log('Client error');
  }
  if (srvError[0] != -1) {
    console.log('Error: ' + srvError[0].toString() + ' - ' + 
      srvError[1].toString() + ' - ' + srvError[2].toString());
  }

  tickPrice = obj.getTickPrice();
  tickSize = obj.getTickSize();
  if (tickPrice[0] != -1) {
    console.log( "TickPrice: " + tickPrice[0].toString() + " " + 
      tickPrice[1].toString() + " " + tickPrice[2].toString());
  }
  if (tickSize[0] != -1) {
    console.log( "TickSize: " + tickSize[0].toString() + " " + 
      tickSize[1].toString() + " " + tickSize[2].toString());
  }

}
