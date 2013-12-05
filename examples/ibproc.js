var addon = require('../build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

obj.connect('127.0.0.1',7496,0);

var orderId = -1;
var counter = 0;
var trackedOrder = [];
var once = false;

while(obj.isConnected()) {
  obj.checkMessages();
  obj.processMsg();

  if (!once && counter == 50000) {
    validOrderId = obj.getNextOrderId();
    orderId = validOrderId;
    console.log('Next valid order Id: %d',validOrderId);
    once = true;
  }
  
  if (counter == 20000) {
    obj.reqIds(1);
  }
  if (counter == 1000000 && orderId > -1) {
    validOrderId = obj.getNextOrderId();
    console.log('Next valid order Id: %d',validOrderId);
    console.log('Next order Id: %d',orderId);
    console.log("Placing order for MSFT");
    obj.placeSimpleOrder(orderId,"MSFT", "STK", "SMART", "NASDAQ", "USD", 
      "BUY", 1000, "LMT", 0.11);
    orderId = orderId + 1;
  }
  if (counter == 2000000 && orderId > -1) {
    counter = 0;
  }
  
  counter = counter + 1;

}
