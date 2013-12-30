// In this example, we will try to place a limit order and to 
//  receive the orderStatus, as well as to poll for openOrders.
// This example will use Node.js's built in event handlers

var addon = require('../nodeibapi').addon;
var obj = new addon.NodeIbapi();

var orderStatus;
var openOrder;
var orderId = -1;
var counter = 0;
var validOrderId;
var ready = false;

var isOrderPlaced = false;

var processIbMsg = function () {
  obj.processIbMsg();
}
var addReqId = function () {
  obj.addReqId(1);
}
var doReqFunc = function () {
  obj.doReqFunc();
}
var doOpenOrderReq = function () {
  obj.reqOpenOrders();
}

var placeThatOrder = function () {
  if (orderId > -1 && !isOrderPlaced) {
    console.log('Next valid order Id: %d',orderId);
    console.log("Placing order for MSFT");
    obj.placeSimpleOrder(orderId,"MSFT", "STK", "SMART", "NASDAQ", "USD", 
      "BUY", 1000, "LMT", 0.11);
    orderId = orderId + 1;
    isOrderPlaced = true;
  } 
}

var cancelPrevOrder = function () {
  if (isOrderPlaced) {
    console.log('canceling order: %d', orderId-1);
    obj.cancelOrder(orderId-1);
    isOrderPlaced = false;
  }
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

  orderStatus = obj.getOrderStatus();
  openOrder = obj.getOpenOrder();

  // order status right after submittal
  if (orderStatus[0] > -1) {
    obj.emit('orderStatus',orderStatus);
  }

  // check open order
  if (openOrder[0] > -1) {
    obj.emit('openOrder',openOrder);
  }
}

obj.on('orderStatus',function (data) { 
  console.log("OrderID, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld");
  console.log( 
    data[0].toString() + " " + data[1].toString() + " " +
    data[2].toString() + " " + data[3].toString() + " " +
    data[4].toString() + " " + data[5].toString() + " " +
    data[6].toString() + " " + data[7].toString() + " " +
    data[8].toString() + " " + data[9].toString()
  );
})
obj.on('openOrder', function (data) {
  console.log("OrderId, status, initMargin, maintMargin, equityWithLoan, Commission, minCommission, maxCommission, commissionCurrency, warningText");
  console.log(
    data[0].toString() + " " + data[1].toString() + " " + 
    data[2].toString() + " " + data[3].toString() + " " + 
    data[4].toString() + " " + data[5].toString() + " " + 
    data[6].toString() + " " + data[7].toString() + " " + 
    data[8].toString() + " " + data[9].toString()
  );
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
})
obj.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})

setInterval(processIbMsg,0.1);
setInterval(doLoop,1);
setInterval(doReqFunc,200);
setInterval(function () {obj.funcQueue.push(doOpenOrderReq);},200);
setInterval(function () {obj.funcQueue.push(placeThatOrder);},1000);
setInterval(function () {obj.funcQueue.push(cancelPrevOrder);},1000);


obj.connectToIb('127.0.0.1',7496,0);