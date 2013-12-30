node-ibapi-addon
================

Interactive Brokers API addon for Node.js compatible with IB API 9.69

Author: Jae Yang - [dchem] (https://github.com/dchem/)

For direct JavaScript implementation of IB API for Node.js, please visit Pilwon Huh's [node-ib] (https://github.com/pilwon/node-ib).


### Change Notes:

* 2013-12-29 - 0.0.3 - Added EventEmitter support
* 2013-09-26 - 0.0.2 - EClientSocket hooks and EWrapper hooks
* 2013-09-02 - 0.0.1 - Initial commit - connect, disconnect, isConnected works

### Installation:

1. Make sure to have node-gyp installed
2. Get the IB API package from Interactive Brokers
3. Copy the contents of IB API package's 
    IBJts/source/PosixClient/Shared into /import directory
4. Copy the contents of IB API package's
    IBJts/source/PosixClient/src into /import directory
5. Add #define IB_USE_STD_STRING into the following files in /import directory:
    EClientSocketBase.cpp
    EPosixClientSocket.cpp
6. node-gyp configure build

### Addon Wrapper Commands
processMsg() is a POSIX implementation of network message handler
```js
.processMsg()
```
Following commands are used for getting the incoming data from the msg queue 
```js
.getNextOrderId()
.getTickPrice()
.getTickSize()
.getTickOptionComputation()
.getTickGeneric()
.getTickString()
.getTickEFP()
.getOrderStatus()
.getOpenOrder()
.getRealtimeBar()
.getWinError()
.getError()
.getUpdateAccountValue()
```

Following commands are used for requesting specific action through IB API
```js
.connect()
.disconnect()
.isConnected()
.reqMktData()
.cancelMktData()
.placeSimpleOrder()
.placeOrder()
.cancelOrder()
.reqOpenOrders()
.reqAccountUpdates()
.reqExecutions()
.reqIds()
.checkMessages()

.reqRealtimeBars()
.cancelRealTimeBars()
```

### JS Extended Wrapper Commands
The following commands are extended commands in nodeibapi.js if one were to use it.
```js
.addReqId()
.doReqFunc()
.processIbMsg()
.connectToIb()
```

### JS Extended Wrapper Events
```js
.on('clientError', function (clientError) {})
.on('srvError', function (srvError) {})
.on('disconnected', function () {})
.on('connected', function() {})
.on('connectionFail' function() {})
```

### Tests:
Uses mocha, so install it.

### Issues:
* See issues list in https://github.com/dchem/node-ibapi-addon/issues?state=open

### License
Copyright (c) 2013 Jae Yang. See LICENSE file for license rights and limitations (MIT).
