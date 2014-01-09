mkdir import
pushd import
wget http://interactivebrokers.github.io/downloads/twsapi_unixmac_969.02.jar
jar xf twsapi_unixmac_969.02.jar
cp ./IBJts/source/PosixClient/shared/* .
cp ./IBJts/source/PosixClient/src/* .
sed -i '4i#define IB_USE_STD_STRING' EClientSocketBase.cpp
sed -i '4i#define IB_USE_STD_STRING' EPosixClientSocket.cpp
popd
node-gyp rebuild
