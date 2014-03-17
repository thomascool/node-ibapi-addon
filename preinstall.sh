DIR="./import"
PDIR="../"

if [ ! -d "$DIR" ]
then
    mkdir $DIR
fi
cd $DIR
wget http://interactivebrokers.github.io/downloads/twsapi_unixmac_969.02.jar
unzip twsapi_unixmac_969.02.jar
cp ./IBJts/source/PosixClient/shared/* .
cp ./IBJts/source/PosixClient/src/* .

if [ "$(uname)" == "Darwin" ]; then
sed -ie $'4i\\\n#define IB_USE_STD_STRING\n' ./EClientSocketBase.cpp
sed -ie $'4i\\\n#define IB_USE_STD_STRING\n' ./EPosixClientSocket.cpp
sed -ie 's_// LINUX_#include <unistd.h>_g' ./EPosixClientSocketPlatform.h
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
sed -i '4i#define IB_USE_STD_STRING' ./EClientSocketBase.cpp
sed -i '4i#define IB_USE_STD_STRING' ./EPosixClientSocket.cpp
sed -i 's_// LINUX_#include <unistd.h>_g' ./EPosixClientSocketPlatform.h
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
sed -i '4i#define IB_USE_STD_STRING' ./EClientSocketBase.cpp
sed -i '4i#define IB_USE_STD_STRING' ./EPosixClientSocket.cpp
sed -i 's_// LINUX_#include <unistd.h>_g' ./EPosixClientSocketPlatform.h
fi
cd $PDIR
