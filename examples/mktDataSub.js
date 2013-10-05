// In this example, we will try to submit a market data subscription
//  to EUR/USD and get the TickPrice and TickSize events from the
//  IB Cash Data Server

var addon = require('../build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

var once = false;
obj.connect('127.0.0.1',7496,0);

var tickPrice;
var tickSize;
while (obj.isConnected()) {
  obj.checkMessages();
  obj.processMsg();
  if (!once) {
    obj.reqMktData(1,"EUR","CASH","IDEALPRO","USD","165",false);
    once = true;
    console.log("EUR Subscribed");
  }
  tickPrice = obj.getTickPrice();
  tickSize = obj.getTickSize();
  if (tickPrice[0] != -1) {
    console.log( "TickPrice: " + tickPrice[0].toString() + " " + 
      tickPrice[1].toString() + " " + tickPrice[2].toString());
  }
  if (tickSize[0] != -1) {
    console.log( "TickSize: " + tickSize[0].toString() + " " + 
      tickSize[1].toString() + " " + tickSize[2].toString());
  }

}
