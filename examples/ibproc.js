var addon = require('./build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

obj.connect('127.0.0.1',7496,0);
var counter = 0;
var price = '';
var time = '';
var trackedOrder = [];
obj.processMsg();

var validOrderId = 0;
var orderId = -1;
var once = false;

while(obj.isConnected()) {
  obj.processMsg();
  price = obj.getTickPrice();
  time = obj.getCurrentTime();
  if (validOrderId > -1 && !once) {
    validOrderId = obj.getNextOrderId();
    console.log('Next valid order Id: %d',validOrderId);
    orderId = validOrderId + 1;
    once = true;
  }
  if (price != '') {
    console.log('The price is: %s', price);
    price = '';
  }
  if (time != '') {
    console.log('The time is: %s', time);
    time = '';
  }
  
  if (counter == 10000000 && orderId > -1) {
    console.log("Placing order for MSFT");
    obj.placeOrder(orderId,"MSFT", "STK", "SMART", "USD", 
      "BUY", 1000, "LMT", 0.11);
    orderId = orderId + 1;
  }
  if (counter == 20000000) {
    console.log('canceling order: %d', validorderid);
    obj.cancelorder(nextorder);
    counter = 0;
  }
  
  counter = counter + 1;

}
