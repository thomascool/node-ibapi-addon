function execution() {
}

execution.prototype.execId = ''; // IBString
execution.prototype.time = ''; // IBString
execution.prototype.acctNumber = ''; // IBString
execution.prototype.exchange = ''; // IBString
execution.prototype.side = ''; // IBString
execution.prototype.shares = 0; // int
execution.prototype.price = 0.0; // double
execution.prototype.permId = 0; // int
execution.prototype.clientId = 0; // long
execution.prototype.orderId = 0; // long
execution.prototype.liquidation = 0; // int
execution.prototype.cumQty = 0; // int
execution.prototype.avgPrice = 0.0; // double
execution.prototype.orderRef = ''; // IBString
execution.prototype.evRule = ''; // IBString
execution.prototype.evMultiplier = 0.0; // double

exports.createExecution = function() {
  var newExecution = new execution();
  return newExecution;
}