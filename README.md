node-ibapi-addon
================

Interactive Brokers API addon for Node.js

Author: Jae Yang


Change Notes:
-------------

2013-09-02 - 0.0.1 - Initial commit - connect, disconnect, isConnected works

Installation:
-------------

1. Make sure to have node-gyp installed
2. Make sure to have v8.h and node.h in the work directory
3. Get the IB API package from Interactive Brokers
4. Copy the contents of IB API package's 
    IBJts/cpp/Shared into /import directory
5. Copy the contents of IB API package's
    IBJts/cpp/PosixSocketClient into /import directory
6. Add #define IB_USE_STD_STRING into the following files in /import directory:
    EClientSocketBase.cpp
    EPosixClientSocket.cpp
7. node-gyp configure build


TODO:
-----

* Implement additional methods in IbPosixClient and wrap it for node in NodeIbapi
* Better way to pull external dependencies
* Better way to handle IB_USE_STD_STRING
* Write more tests

License
-------
Copyright (c) 2013 Jae Yang. See LICENSE file for license rights and limitations (MIT).
