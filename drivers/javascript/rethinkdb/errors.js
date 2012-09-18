/**
 * @name rethinkdb.errors
 * @namespace Contains error classes for ReQL errors
 */
goog.provide('rethinkdb.errors');

goog.require('rethinkdb');

/**
 * An error generated by the ReQL runtime on the rethinkdb server
 * @param {?string=} opt_msg The error message
 * @constructor
 * @extends {Error}
 */
rethinkdb.errors.RuntimeError = function(opt_msg) {
    this.name = "Runtime Error";
    this.message = opt_msg || "The RDB runtime experienced an error";
};
goog.inherits(rethinkdb.errors.RuntimeError, Error);

/**
 * An error generated by the rethinkdb server indicating an error internal to the ReQL client library
 * @constructor
 * @extends {Error}
 */
rethinkdb.errors.BrokenClient = function(msg) {
    this.name = "Broken Client";
    this.message = msg || "The client sent the server an incorrectly formatted message";
};
goog.inherits(rethinkdb.errors.BrokenClient, Error);

/**
 * An error returned by the rethinkdb server signaling an incorrectly constructed message
 * @param {?string=} opt_msg The error message
 * @constructor
 * @extends {Error}
 */
rethinkdb.errors.BadQuery = function(opt_msg) {
    this.name = "Bad Query";
    this.message = opt_msg || "This query contains type errors";
};
goog.inherits(rethinkdb.errors.BadQuery, Error);

/**
 * An error generated by this client, not the rethinkdb server
 * @param {?string=} opt_msg The error message
 * @constructor
 * @extends {Error}
 */
rethinkdb.errors.ClientError = function(opt_msg) {
    this.name = "RDB Client Error";
    this.message = opt_msg || "The RDB client has experienced an error";
};
goog.inherits(rethinkdb.errors.ClientError, Error);
