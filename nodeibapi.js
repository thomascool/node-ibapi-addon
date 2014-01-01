// module for event driven methods
var addon = require('./build/Release/NodeIbapiAddon');
var events = require ("events");
var util = require ("util");

for (var key in events.EventEmitter.prototype) {
  addon.NodeIbapi.prototype[key] = events.EventEmitter.prototype[key];
}

addon.NodeIbapi.prototype.funcQueue = [];

addon.NodeIbapi.prototype.addReqId = function () {
  this.reqIds(1);
}

addon.NodeIbapi.prototype.doReqFunc = function () {
  if (this.funcQueue[0] != null) {
      (this.funcQueue.shift())();
  } 
}

addon.NodeIbapi.prototype.processIbMsg = function () {
  this.checkMessages();
  this.processMsg();
  
  clientError = this.getWinError();
  srvError = this.getError();
  
  tickPrice = this.getTickPrice();
  tickSize = this.getTickSize();
  tickOptionComp = this.getTickOptionComputation();
  tickGeneric = this.getTickGeneric();
  tickString = this.getTickString();
  tickEFP = this.getTickEFP();
  tickSnapshotEnd = this.getTickSnapshotEnd();
  marketDataType = this.getMarketDataType();

  orderStatus = this.getOrderStatus();
  openOrder = this.getOpenOrder();
  realtimeBar = this.getRealtimeBar();

  if (clientError[0] != "") {
    this.emit('clientError',clientError);
  }
  if (srvError[0] != -1) {
    this.emit('srvError',srvError);
  }
  if (tickPrice[0] != -1) {
    this.emit('tickPrice',tickPrice);
  }
  if (tickSize[0] != -1) {
    this.emit('tickSize',tickSize);
  }
  if (tickOptionComp[0] != -1) {
    this.emit('tickOptionComputation',tickOptionComp);
  }
  if (tickGeneric[0] != -1) {
    this.emit('tickGeneric',tickGeneric);
  }
  if (tickString[0] != -1) {
    this.emit('tickString', tickString);
  }
  if (tickEFP[0] != -1) {
    this.emit('tickEFP', tickEFP);
  }
  if (tickSnapshotEnd[0] != -1) {
    this.emit('tickSnapshotEnd', tickSnapshotEnd);
  }
  if (marketDataType[0] != -1) {
    this.emit('marketDataType', marketDataType);
  }

  if (orderStatus[0] > -1) {
    this.emit('orderStatus',orderStatus);
  }
  if (openOrder[0] > -1) {
    this.emit('openOrder',openOrder);
  }
  if (realtimeBar[0] > -1) {
    this.emit('realtimeBar', realtimeBar);
  }

  if (!this.isConnected())
    this.emit('disconnected');
}

addon.NodeIbapi.prototype.connectToIb = function (host,port,clientId) {
  if (this.connect(host,port,clientId))
    this.emit('connected');
  else
    this.emit('connectionFail');
}

exports.addon = addon;