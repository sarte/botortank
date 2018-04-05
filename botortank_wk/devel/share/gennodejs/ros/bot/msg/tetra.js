// Auto-generated. Do not edit!

// (in-package bot.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class tetra {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.a = null;
      this.b = null;
      this.c = null;
      this.d = null;
    }
    else {
      if (initObj.hasOwnProperty('a')) {
        this.a = initObj.a
      }
      else {
        this.a = false;
      }
      if (initObj.hasOwnProperty('b')) {
        this.b = initObj.b
      }
      else {
        this.b = false;
      }
      if (initObj.hasOwnProperty('c')) {
        this.c = initObj.c
      }
      else {
        this.c = false;
      }
      if (initObj.hasOwnProperty('d')) {
        this.d = initObj.d
      }
      else {
        this.d = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type tetra
    // Serialize message field [a]
    bufferOffset = _serializer.bool(obj.a, buffer, bufferOffset);
    // Serialize message field [b]
    bufferOffset = _serializer.bool(obj.b, buffer, bufferOffset);
    // Serialize message field [c]
    bufferOffset = _serializer.bool(obj.c, buffer, bufferOffset);
    // Serialize message field [d]
    bufferOffset = _serializer.bool(obj.d, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type tetra
    let len;
    let data = new tetra(null);
    // Deserialize message field [a]
    data.a = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [b]
    data.b = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [c]
    data.c = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [d]
    data.d = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'bot/tetra';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a10316242c9f6651bd3958b5cd4982fa';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool a
    bool b
    bool c
    bool d
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new tetra(null);
    if (msg.a !== undefined) {
      resolved.a = msg.a;
    }
    else {
      resolved.a = false
    }

    if (msg.b !== undefined) {
      resolved.b = msg.b;
    }
    else {
      resolved.b = false
    }

    if (msg.c !== undefined) {
      resolved.c = msg.c;
    }
    else {
      resolved.c = false
    }

    if (msg.d !== undefined) {
      resolved.d = msg.d;
    }
    else {
      resolved.d = false
    }

    return resolved;
    }
};

module.exports = tetra;
