// In this example, we will try to submit a realtimeBar request

var addon = require('../build/Release/NodeIbapiAddon');
var ibcontract = require('../lib/contract');

var obj = new addon.NodeIbapi();

var once = false;
obj.connect('127.0.0.1',7496,0);

var realtimeTrades;
var clientError;
var srvError;
var time = process.hrtime();
var diff = process.hrtime(time);
var funqueue = []; // function queue

var addEurUsd = function () {
    var eurusd = ibcontract.createContract();
    eurusd.symbol = 'EUR';
    eurusd.secType = 'CASH';
    eurusd.exchange = 'IDEALPRO';
    eurusd.primaryExchange = 'IDEALPRO';
    eurusd.currency = 'USD';
    obj.reqRealtimeBars(1,eurusd,5,"TRADES",false);
};

var addMsft = function () {
    var msftContract = ibcontract.createContract();
    msftContract.symbol = 'MSFT';
    msftContract.secType = 'STK';
    msftContract.exchange = 'SMART';
    msftContract.primaryExchange = 'NASDAQ';
    msftContract.currency = 'USD';
    obj.reqRealtimeBars(1,msftContract,5,"TRADES",false);
};

while (obj.isConnected()) {
  diff = process.hrtime(time);

    // timed function queue
  if (diff[1] > 210000000) {
    time = process.hrtime();
    if (funqueue[0] != null) {
      (funqueue.shift())();
    }
  }

  obj.checkMessages();
  obj.processMsg();
  clientError = obj.getWinError();
  srvError = obj.getError();

  if (!once) {
    // subscribe to MSFT realtimeBar
    funqueue.push(addMsft);
    once = true;
  }
  if (clientError[0] != "") {
    console.log('Client error');
  }
  if (srvError[0] != -1) {
    if (srvError[1] == 420) {
      funqueue.push(addMsft);
    }
    console.log('Error: ' + srvError[0].toString() + ' - ' + 
      srvError[1].toString() + ' - ' + srvError[2].toString());
  }

  realtimeTrades = obj.getRealtimeBar();
  if (realtimeTrades[0] != -1) {
    console.log( "RealtimeBar: " + realtimeTrades[0].toString() + " " + 
      realtimeTrades[1].toString() + " " + realtimeTrades[2].toString() + " " + 
      realtimeTrades[3].toString() + " " + realtimeTrades[4].toString() + " " + 
      realtimeTrades[5].toString() + " " + realtimeTrades[6].toString() + " " + 
      realtimeTrades[7].toString() + " " + realtimeTrades[8].toString());
  }
}
