var assert = require("assert")
var addon = require('../build/Release/NodeIbapiAddon');


var obj = new addon.NodeIbapi();

describe('obj', function() {
	describe('#connect()', function() {
		it('should return true when successfully connected', function() {
			assert.equal(true, obj.connect('127.0.0.1',7496,0));
		})
	})
})

describe('obj', function() {
	describe('#isConnected()', function() {
		it('should return true when client is currently connected', function() {
			assert.equal(true, obj.isConnected());
		})
	})
})

// test is not correct
describe('obj', function() {
	describe('#disconnect()', function() {
		it('should return nothing when successfully disconnected', function() {
			assert.equal(1, obj.disconnect());
		})
	})
})
