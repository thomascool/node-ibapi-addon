var addon = require('../build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

var once = false;
obj.connect('127.0.0.1',7496,0);

var orderStatus;
var orderId;
var counter = 0;

while (obj.isConnected()) {
  obj.checkMessages();
  obj.processMsg();
  orderStatus = obj.getOrderStatus();

  if (!once && counter == 500000) {
    validOrderId = obj.getNextOrderId();
    orderId = validOrderId + 1;
    console.log('Next valid order Id: %d',validOrderId);
    once = true;
  }
  if (orderStatus[0] > -1) {
    console.log("OrderID, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld");
    console.log( 
      orderStatus[0].toString() + " " + orderStatus[1].toString() + " " +
      orderStatus[2].toString() + " " + orderStatus[3].toString() + " " +
      orderStatus[4].toString() + " " + orderStatus[5].toString() + " " +
      orderStatus[6].toString() + " " + orderStatus[7].toString() + " " +
      orderStatus[8].toString() + " " + orderStatus[9].toString()
      );
  }
  
  if (counter == 5000000 && orderId > -1) {
    console.log('Next valid order Id: %d',validOrderId);
    console.log("Placing order for MSFT");
    obj.placeOrder(orderId,"MSFT", "STK", "SMART", "USD", 
      "BUY", 1000, "LMT", 0.11);
    orderId = orderId + 1;
  }  
  if (counter == 10000000) {
    console.log('canceling order: %d', orderId-1);
    obj.cancelOrder(orderId-1);
    counter = 0;
  }
  counter = counter + 1;

}
