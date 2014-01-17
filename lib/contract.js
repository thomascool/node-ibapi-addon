// var comboLeg = {
//   'conId' : 0,
//   'ratio' : 0,
//   'action' : '',
//   'exchange' : '',
//   'openClose' : 0,
//   'shortSaleSlot' : 0,
//   'designatedLocation' : '',
//   'exemptCode' : -1,

//   'operator' : function (other) {
//     return (this.conId == other.conId &&
//       this.ratio == other.ratio &&
//       this.openClose == other.openClose &&
//       this.shortSaleSlot == other.shortSaleSlot &&
//       this.action === other.action &&
//       this.exchange === other.exchange &&
//       this.designatedLocation === other.designatedLocation &&
//       this.exemptCode == other.exemptCode);
//   }
// }

// var underComp = {
//   'conId' : 0,
//   'delta' : 0, 
//   'price' : 0
// }

function contract() {
}

contract.prototype.conId = 0;
contract.prototype.symbol = '';
contract.prototype.secType = '';
contract.prototype.expiry = '';
contract.prototype.strike = 0.0;
contract.prototype.right = '';
contract.prototype.multiplier = '';
contract.prototype.exchange = '';
contract.prototype.primaryExchange = ''; // pick an actual (ie non-aggregate) exchange that the contract trades on.  DO NOT SET TO SMART.
contract.prototype.currency = '';
contract.prototype.localSymbol = '';
contract.prototype.tradingClass = '';
contract.prototype.includeExpired = false;
contract.prototype.secIdType = '';    // CUSIP;SEDOL;ISIN;RIC
contract.prototype.secId = '';

function underComp() {
}
underComp.prototype.conId = 0;
underComp.prototype.delta = 0;
underComp.prototype.price = 0;
// TODO: add combo legs

exports.createContract = function() {
  var newContract = new contract();
  return newContract;
}

exports.createUnderComp = function() {
  var newUnderComp = new underComp();
  return newUnderComp;
}