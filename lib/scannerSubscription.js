function scannerSubscription() {
}

scannerSubscription.prototype.numberOfRows = -1; //int 
scannerSubscription.prototype.instrument = ''; //IBString 
scannerSubscription.prototype.locationCode = ''; //IBString 
scannerSubscription.prototype.scanCode = ''; //IBString 
scannerSubscription.prototype.abovePrice = -1; //double 
scannerSubscription.prototype.belowPrice = -1; //double 
scannerSubscription.prototype.aboveVolume = -1; //int 
scannerSubscription.prototype.marketCapAbove = -1; //double 
scannerSubscription.prototype.marketCapBelow = -1; //double 
scannerSubscription.prototype.moodyRatingAbove = ''; //IBString 
scannerSubscription.prototype.moodyRatingBelow = ''; //IBString 
scannerSubscription.prototype.spRatingAbove = ''; //IBString 
scannerSubscription.prototype.spRatingBelow = ''; //IBString 
scannerSubscription.prototype.maturityDateAbove = ''; //IBString 
scannerSubscription.prototype.maturityDateBelow = ''; //IBString 
scannerSubscription.prototype.couponRateAbove = -1; //double 
scannerSubscription.prototype.couponRateBelow = -1; //double 
scannerSubscription.prototype.excludeConvertible = 0; //int 
scannerSubscription.prototype.averageOptionVolumeAbove = 0; //int 
scannerSubscription.prototype.scannerSettingPairs = ''; //IBString 
scannerSubscription.prototype.stockTypeFilter = ''; //IBString 

exports.createScannerSub = function() {
  var newScanSub = new scannerSubscription();
  return newScanSub;
}