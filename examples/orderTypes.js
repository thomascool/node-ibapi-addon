// In this example, we will submit orders through different ways
var addon = require('../nodeibapi').addon;
var obj = new addon.NodeIbapi();
var ibcontract = require('../lib/contract');

var orderId = -1;

var processIbMsg = function () {
  obj.processIbMsg();
}
var addReqId = function () {
  obj.addReqId(1);
}
var doReqFunc = function () {
  obj.doReqFunc();
}

var msftContract1 = ibcontract.createContract();
msftContract1.symbol = 'MSFT';
msftContract1.secType = 'STK';
msftContract1.exchange = 'SMART';
msftContract1.primaryExchange = 'NASDAQ';
msftContract1.currency = 'USD';

var msftContract2 = ibcontract.createContract();
msftContract2.conId = 272093; // you can look this up from Contract Details in TWS
msftContract2.exchange = 'SMART';

var placeMsftOrder = function (contract, oId) {
  console.log('Next valid order Id: %d',oId);
  console.log("Placing order for MSFT");
  obj.placeOrder(oId,contract, 
    "BUY", 1000, "LMT", 0.11);
}
var cancelPrevOrder = function (oId) {
  console.log('canceling order: %d', oId);
  obj.cancelOrder(oId);
}

obj.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
})
.on('clientError', function (data) {
  console.log('Client error' + data[1].toString());
})
.on('srvError', function (data) {
  console.log('Error: ' + data[0].toString() + ' - ' + 
    data[1].toString() + ' - ' + data[2].toString());
})
.once('nextValidId', function (data) {
  orderId = data;
  setInterval(doReqFunc,100);
  setInterval(function () {
    obj.funcQueue.push(placeMsftOrder(msftContract1, orderId));
    obj.funcQueue.push(cancelPrevOrder(orderId));
    orderId = orderId + 1;
    obj.funcQueue.push(placeMsftOrder(msftContract2, orderId));
    obj.funcQueue.push(cancelPrevOrder(orderId));
    orderId = orderId + 1;
  },5000);
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})


obj.connectToIb('127.0.0.1',7496,0);