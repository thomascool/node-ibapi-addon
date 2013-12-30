// In this example, we will try to submit a market data subscription
//  to EUR/USD and get the TickPrice and TickSize events from the
//  IB Cash Data Server
// Also, in this example we will submit a market data subscription 
//  to MSFT.
// 

var addon = require('../nodeibapi').addon;
var obj = new addon.NodeIbapi();

var ibcontract = require('../lib/contract');

var processIbMsg = function () {
  obj.processIbMsg();
}
var addReqId = function () {
  obj.addReqId(1);
}
var doReqFunc = function () {
  obj.doReqFunc();
}

var tickPrice;
var tickSize;
var clientError;
var srvError;

var eurusd = ibcontract.createContract();
eurusd.symbol = 'EUR';
eurusd.secType = 'CASH';
eurusd.exchange = 'IDEALPRO';
eurusd.primaryExchange = 'IDEALPRO';
eurusd.currency = 'USD';

var msftContract = ibcontract.createContract();
msftContract.symbol = 'MSFT';
msftContract.secType = 'STK';
msftContract.exchange = 'SMART';
msftContract.primaryExchange = 'NASDAQ';
msftContract.currency = 'USD';

var subscribeEurUsd = function () {
  obj.reqMktData(1,eurusd,"165",false);
}
var subscribeMsft = function () {
  obj.reqMktData(3,msftContract,"165",false);
}

var doLoop = function () {
  tickPrice = obj.getTickPrice();
  tickSize = obj.getTickSize();
  if (tickPrice[0] != -1) {
    obj.emit('tickPrice',tickPrice);
  }
  if (tickSize[0] != -1) {
    obj.emit('tickSize',tickSize);
  }
};

obj.on('tickPrice', function (data) {
  console.log( "TickPrice: " + tickPrice[0].toString() + " " + 
    tickPrice[1].toString() + " " + tickPrice[2].toString());
})
obj.on('tickSize', function (data) {
  console.log( "TickSize: " + tickSize[0].toString() + " " + 
    tickSize[1].toString() + " " + tickSize[2].toString());
})
obj.on('clientError', function (data) {
  console.log('Client error' + data[1].toString());
})
obj.on('srvError', function (data) {
  console.log('Error: ' + data[0].toString() + ' - ' + 
    data[1].toString() + ' - ' + data[2].toString());
})
obj.on('connected', function () {
  console.log('connected');
  obj.funcQueue.push(subscribeEurUsd);
  obj.funcQueue.push(subscribeMsft);
})
obj.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})
setInterval(processIbMsg,0.1);
setInterval(doLoop,1);
setInterval(doReqFunc,100);

obj.connectToIb('127.0.0.1',7496,0);