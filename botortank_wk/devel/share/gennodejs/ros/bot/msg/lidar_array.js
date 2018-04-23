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

class lidar_array {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.angles = null;
      this.distances = null;
      this.iter = null;
    }
    else {
      if (initObj.hasOwnProperty('angles')) {
        this.angles = initObj.angles
      }
      else {
        this.angles = new Array(360).fill(0);
      }
      if (initObj.hasOwnProperty('distances')) {
        this.distances = initObj.distances
      }
      else {
        this.distances = new Array(360).fill(0);
      }
      if (initObj.hasOwnProperty('iter')) {
        this.iter = initObj.iter
      }
      else {
        this.iter = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lidar_array
    // Check that the constant length array field [angles] has the right length
    if (obj.angles.length !== 360) {
      throw new Error('Unable to serialize array field angles - length must be 360')
    }
    // Serialize message field [angles]
    bufferOffset = _arraySerializer.float32(obj.angles, buffer, bufferOffset, 360);
    // Check that the constant length array field [distances] has the right length
    if (obj.distances.length !== 360) {
      throw new Error('Unable to serialize array field distances - length must be 360')
    }
    // Serialize message field [distances]
    bufferOffset = _arraySerializer.float32(obj.distances, buffer, bufferOffset, 360);
    // Serialize message field [iter]
    bufferOffset = _serializer.uint8(obj.iter, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lidar_array
    let len;
    let data = new lidar_array(null);
    // Deserialize message field [angles]
    data.angles = _arrayDeserializer.float32(buffer, bufferOffset, 360)
    // Deserialize message field [distances]
    data.distances = _arrayDeserializer.float32(buffer, bufferOffset, 360)
    // Deserialize message field [iter]
    data.iter = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2881;
  }

  static datatype() {
    // Returns string type for a message object
    return 'bot/lidar_array';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a3ddce690af809517c1ac0a3e62abcfa';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[360] angles
    float32[360] distances
    uint8  iter
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new lidar_array(null);
    if (msg.angles !== undefined) {
      resolved.angles = msg.angles;
    }
    else {
      resolved.angles = new Array(360).fill(0)
    }

    if (msg.distances !== undefined) {
      resolved.distances = msg.distances;
    }
    else {
      resolved.distances = new Array(360).fill(0)
    }

    if (msg.iter !== undefined) {
      resolved.iter = msg.iter;
    }
    else {
      resolved.iter = 0
    }

    return resolved;
    }
};

module.exports = lidar_array;
