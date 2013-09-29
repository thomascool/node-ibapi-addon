var addon = require('../build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

var once = false;
obj.connect('127.0.0.1',7496,0);

var tickPrice = '';

while (obj.isConnected()) {
  obj.checkMessages();
  obj.processMsg();
  if (!once) {
    obj.reqMktData(1,"EUR","CASH","IDEALPRO","USD","165",false);
    once = true;
    console.log("EUR Subscribed");
  }
  tickPrice = obj.getTickPrice();

  if (tickPrice != '') {
    console.log(tickPrice);
    tickPrice = '';
  }

}
