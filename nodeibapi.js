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

  if (clientError[0] != "") {
    this.emit('clientError',clientError);
  }
  if (srvError[0] != -1) {
    this.emit('srvError',srvError);
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