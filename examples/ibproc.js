var addon = require('../build/Release/NodeIbapiAddon');
var ibcontract = require('../lib/contract');
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
  if (counter == 100000 && orderId > -1) {
    validOrderId = obj.getNextOrderId();
    console.log('Next valid order Id: %d',validOrderId);
    console.log('Next order Id: %d',orderId);
    console.log("Placing order for MSFT");
    var newContract = ibcontract.createContract();
    newContract.symbol = 'MSFT';
    newContract.secType = 'STK';
    newContract.exchange = 'SMART';
    newContract.primaryExchange = 'NASDAQ';
    newContract.currency = 'USD';
    obj.placeOrder(orderId,newContract, 
      "BUY", 1000, "LMT", 0.11);
    orderId = orderId + 1;
  }
  if (counter == 200000 && orderId > -1) {
    counter = 0;
  }
  
  counter = counter + 1;

}
