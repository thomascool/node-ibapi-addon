// This is a bare-bones setting for the scripts using node-ibapi-addon
var addon = require('../build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

obj.connect('127.0.0.1',7496,0);

var orderId = -1;
var counter = 0;
var once = false;

var clientError;
var srvError;

while(obj.isConnected()) {
  obj.checkMessages();
  obj.processMsg();
  clientError = obj.getWinError();
  srvError = obj.getError();

  if (!once && counter == 50000) {
    validOrderId = obj.getNextOrderId();
    orderId = validOrderId;
    console.log('Next valid order Id: %d',validOrderId);
    once = true;
    counter = 0;
  }
  if (clientError[0] != "") {
    console.log('Client error');
  }
  if (srvError[0] != -1) {
    console.log('Error: ' + srvError[0].toString() + ' - ' + 
      srvError[1].toString() + ' - ' + srvError[2].toString());
  }
  
  // implement your functionalities here
  if (counter == 20000) {
    obj.reqIds(1);
  }
  if (counter == 50000) {
    validOrderId = obj.getNextOrderId();
    orderId = validOrderId;
    console.log('Next valid order Id: %d',validOrderId);
    counter = 0;
  }
  counter = counter + 1;
}
