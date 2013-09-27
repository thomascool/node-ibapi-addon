var addon = require('./build/Release/NodeIbapiAddon');
var obj = new addon.NodeIbapi();

var once = false;
obj.connect('127.0.0.1',7496,0);

var tickString = '';

while (obj.isConnected()) {
  obj.processMsg();
  if (!once) {
    obj.reqMktData(1,"MSFT","STK","SMART","USD","233,mdoff",false);
    once = true;
  }
  tickString = obj.getTickString();

  if (tickString != '') {
    console.log(tickString);
  }

}