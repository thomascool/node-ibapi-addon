node-ibapi-addon
================

Interactive Brokers API addon for Node.js compatible with IB API 9.69

This addon uses the latest stable Interactive Brokers POSIX C++ API.

Author: Jae Yang - [dchem] (https://github.com/dchem/)

For direct JavaScript implementation of IB API for Node.js, please visit Pilwon Huh's [node-ib] (https://github.com/pilwon/node-ib).


### Change Notes:

* 2013-01-09 - 0.0.4 - get commands outputs JS objects
* 2013-12-29 - 0.0.3 - Added EventEmitter support
* 2013-09-26 - 0.0.2 - EClientSocket hooks and EWrapper hooks
* 2013-09-02 - 0.0.1 - Initial commit - connect, disconnect, isConnected works

### Installation:

1. Make sure to have node-gyp installed
2. Run the install.sh which does the following:
 * Copy the contents of IB API package's 
    IBJts/source/PosixClient/Shared into /import directory
 * Copy the contents of IB API package's
    IBJts/source/PosixClient/src into /import directory
 * Add #define IB_USE_STD_STRING into the following files in /import directory:
    EClientSocketBase.cpp
    EPosixClientSocket.cpp
3. ```node-gyp rebuild```
4. If build fails because you have VS2012, use ```node-gyp --msvs_version=2012 rebuild```

### Usage
```js
var addon = require('ibapi');
var obj = new addon.NodeIbapi();

var orderId = -1;
var processIbMsg = function () {
  obj.processIbMsg();
}
var addReqId = function () {
  obj.addReqId(1);
}
var doReqFunc = function () {
  obj.doReqFunc();
}
obj.on('connected', function () {
  console.log('connected');
  setInterval(processIbMsg,0.1);
  obj.funcQueue.push(addReqId);
})
.once('nextValidId', function (data) {
  orderId = data;
  console.log('nextValidId: ' + orderId);
  setInterval(doReqFunc,100);
})
.on('disconnected', function () {
  console.log('disconnected');
  process.exit(1);
})

obj.connectToIb('127.0.0.1',7496,0);

```
### Module Wrapper Commands
The following commands are extended commands in ibapi.js if one were to use it.
```js
.addReqId()
.doReqFunc()
.processIbMsg()
.connectToIb()
```

### Module Wrapper Events
```js
// processIbMsg events - returns arrays
.on('clientError', function (clientError))
.on('srvError', function (srvError))
.on('nextValidId' function (nextValidId))
.on('tickPrice', function (tickPrice))
.on('tickSize', function (tickSize))
.on('tickOptionComputation', function(tickOptionComputation))
.on('tickGeneric', function(tickGeneric))
.on('tickString', function(tickString))
.on('tickEFP', function(tickEFP))
.on('tickSnapshotEnd', function(tickSnapshotEnd))
.on('marketDataType', function(marketDataType))
.on('orderStatus', function(orderStatus))
.on('openOrder', function(openOrder))
.on('realtimeBar', function(realtimeBar))
.on('disconnected', function ())

// connectToIb events
.on('connected', function())
.on('connectionFail' function())
```

### Addon Wrapper Commands
```js
// Msg processor
//  a POSIX implementation of network message handler
.processMsg()

// Getters
//  Following commands are used for getting the incoming data from 
//  the msg queue 
.getNextValidId()
.getTickPrice()
.getTickSize()
.getTickOptionComputation()
.getTickGeneric()
.getTickString()
.getTickEFP()
.getTickSnapshotEnd()
.getMarketDataType()
.getOrderStatus()
.getOpenOrder()
.getRealtimeBar()
.getWinError()
.getError()
.getUpdateAccountValue()

// IB API Commands
//  Following commands are used for requesting specific action 
//  through IB API
.connect(host,port,clientId)
.disconnect()
.isConnected()
.reqMktData(reqId, contract, genericTickType, snapShot)
.cancelMktData(reqId)
.placeSimpleOrder(orderId, symbol, secType, exchange, primaryExchange, currency, action, quantity, orderType, price)
.placeOrder(orderId, contract, action, quantity, orderType, price)
.cancelOrder(orderId)
.reqOpenOrders()
.reqAccountUpdates(subscribe, acctCode)
.reqExecutions(reqId, clientId, acctCode, time, symbol, secType, exchange, side)
.reqIds(1)
.checkMessages()

.reqRealtimeBars(tickerId, contract, barSize, whatToShow, useRTH)
.cancelRealTimeBars(tickerId)
```



### Tests:
Uses mocha, so install it.

### Issues:
* See issues list in https://github.com/dchem/node-ibapi-addon/issues?state=open

### License
Copyright (c) 2013 Jae Yang. See LICENSE file for license rights and limitations (MIT).
