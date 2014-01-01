// In this example, we will submit orders through different ways
var addon = require('../nodeibapi').addon;
var obj = new addon.NodeIbapi();
var ibcontract = require('../lib/contract');

var orderId = -1;
var validOrderId = -1;
var once = false;
var ready = false;

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
  if (oId > -1 && ready) {
    console.log('Next valid order Id: %d',oId);
    console.log("Placing order for MSFT");
    obj.placeOrder(oId,contract, 
      "BUY", 1000, "LMT", 0.11);
  } 
}

var cancelPrevOrder = function (oId) {
    console.log('canceling order: %d', oId);
    obj.cancelOrder(oId);
}

var doLoop = function () {
  // retrieve validOrderId
  validOrderId = obj.getNextOrderId();
  if (validOrderId < 0 && !once) {
    once = true;
    obj.funcQueue.push(addReqId);
  }
  if (validOrderId > 0 && !ready) {
      ready = true;
      orderId = validOrderId;
  }
}

obj.on('clientError', function (data) {
  console.log('Client error' + data[1].toString());
})
obj.on('srvError', function (data) {
  console.log('Error: ' + data[0].toString() + ' - ' + 
    data[1].toString() + ' - ' + data[2].toString());
})
obj.on('connected', function () {
   console.log('connected');
})
obj.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})

setInterval(processIbMsg,0.1);
setInterval(doLoop,1);
setInterval(doReqFunc,100);
setInterval(function () {
  obj.funcQueue.push(placeMsftOrder(msftContract1, orderId));
  obj.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
  obj.funcQueue.push(placeMsftOrder(msftContract2, orderId));
  obj.funcQueue.push(cancelPrevOrder(orderId));
  orderId = orderId + 1;
},5000);

obj.connectToIb('127.0.0.1',7496,0);