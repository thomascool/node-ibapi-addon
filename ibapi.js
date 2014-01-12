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
  nextValidId = this.getNextValidId();
  
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

  if (clientError.isValid) {
    this.emit('clientError',clientError);
  }
  if (srvError.isValid) {
    this.emit('srvError',srvError);
  }
  if (tickPrice.isValid) {
    this.emit('tickPrice',tickPrice);
  }
  if (tickSize.isValid) {
    this.emit('tickSize',tickSize);
  }
  if (tickOptionComp.isValid) {
    this.emit('tickOptionComputation',tickOptionComp);
  }
  if (tickGeneric.isValid) {
    this.emit('tickGeneric',tickGeneric);
  }
  if (tickString.isValid) {
    this.emit('tickString', tickString);
  }
  if (tickEFP.isValid) {
    this.emit('tickEFP', tickEFP);
  }
  if (tickSnapshotEnd.isValid) {
    this.emit('tickSnapshotEnd', tickSnapshotEnd);
  }
  if (marketDataType.isValid) {
    this.emit('marketDataType', marketDataType);
  }

  if (orderStatus.isValid) {
    this.emit('orderStatus',orderStatus);
  }
  if (openOrder.isValid) {
    this.emit('openOrder',openOrder);
  }
  if (realtimeBar.isValid) {
    this.emit('realtimeBar', realtimeBar);
  }

  if (nextValidId.isValid) {
    this.emit('nextValidId', nextValidId);
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

exports = module.exports = addon;
