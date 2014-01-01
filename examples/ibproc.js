// This is a bare-bones setting for the scripts using node-ibapi-addon
//  if you were to use a whileloop instead
var addon = require('../build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

obj.connect('127.0.0.1',7496,1);

var validOrderId = -1;
var orderId = -1;
var counter = 0;
var ready = false;
var once = false;

var clientError;
var srvError;

var time = process.hrtime();
var diff = process.hrtime(time);
var funqueue = []; // function queue

var addReqId = function () {
  obj.reqIds(1);
}

while(obj.isConnected()) {
  diff = process.hrtime(time);
  
    // timed function queue
  if (diff[1] > 21000000) {
    time = process.hrtime();
    if (funqueue[0] != null) {
      (funqueue.shift())();
    }
  }

  obj.checkMessages();
  obj.processMsg();
  clientError = obj.getWinError();
  srvError = obj.getError();

  if (clientError[0] != "") {
    // do stuff with client error codes and messages
    console.log('Client error');
  }
  if (srvError[0] != -1) {
    // do stuff with server error codes and messages
    console.log('Error: ' + srvError[0].toString() + ' - ' + 
      srvError[1].toString() + ' - ' + srvError[2].toString());
  }

  // retrieve validOrderId
  validOrderId = obj.getNextOrderId();
  if (validOrderId < 0 && !once) {
    once = true;
    funqueue.push(addReqId);
  }
  if (validOrderId > 0 && !ready) {
      ready = true;
      orderId = validOrderId;
  }
  
  // implement your functionalities here
  if (ready) {
    console.log('Next valid order Id: %d',validOrderId);
    obj.disconnect();
  }
  counter = counter + 1;
}
