{
  "targets": [
    {
      "target_name": "NodeIbapiAddon",
      "sources": [ "NodeIbapiAddon.cpp"
                  ,"NodeIbapi.cpp"
                  ,"IbPosixClient.cpp"
                  ,"import/EPosixClientSocket.cpp"
                  ,"import/EClientSocketBase.cpp" ],
      "cflags":  ['-fexceptions', '-O2'],
      "cflags_cc": ['-fexceptions', '-O2']
    }
  ]
}
