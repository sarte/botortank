; Auto-generated. Do not edit!


(cl:in-package bot-msg)


;//! \htmlinclude quad.msg.html

(cl:defclass <quad> (roslisp-msg-protocol:ros-message)
  ((motor1
    :reader motor1
    :initarg :motor1
    :type cl:float
    :initform 0.0)
   (motor2
    :reader motor2
    :initarg :motor2
    :type cl:float
    :initform 0.0)
   (motor3
    :reader motor3
    :initarg :motor3
    :type cl:float
    :initform 0.0)
   (motor4
    :reader motor4
    :initarg :motor4
    :type cl:float
    :initform 0.0))
)

(cl:defclass quad (<quad>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <quad>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'quad)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bot-msg:<quad> is deprecated: use bot-msg:quad instead.")))

(cl:ensure-generic-function 'motor1-val :lambda-list '(m))
(cl:defmethod motor1-val ((m <quad>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:motor1-val is deprecated.  Use bot-msg:motor1 instead.")
  (motor1 m))

(cl:ensure-generic-function 'motor2-val :lambda-list '(m))
(cl:defmethod motor2-val ((m <quad>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:motor2-val is deprecated.  Use bot-msg:motor2 instead.")
  (motor2 m))

(cl:ensure-generic-function 'motor3-val :lambda-list '(m))
(cl:defmethod motor3-val ((m <quad>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:motor3-val is deprecated.  Use bot-msg:motor3 instead.")
  (motor3 m))

(cl:ensure-generic-function 'motor4-val :lambda-list '(m))
(cl:defmethod motor4-val ((m <quad>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:motor4-val is deprecated.  Use bot-msg:motor4 instead.")
  (motor4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <quad>) ostream)
  "Serializes a message object of type '<quad>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'motor1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'motor2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'motor3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'motor4))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <quad>) istream)
  "Deserializes a message object of type '<quad>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'motor1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'motor2) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'motor3) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'motor4) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<quad>)))
  "Returns string type for a message object of type '<quad>"
  "bot/quad")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'quad)))
  "Returns string type for a message object of type 'quad"
  "bot/quad")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<quad>)))
  "Returns md5sum for a message object of type '<quad>"
  "7870b959b33d58fdf72aa92aca4c8520")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'quad)))
  "Returns md5sum for a message object of type 'quad"
  "7870b959b33d58fdf72aa92aca4c8520")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<quad>)))
  "Returns full string definition for message of type '<quad>"
  (cl:format cl:nil "float32 motor1~%float32 motor2~%float32 motor3~%float32 motor4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'quad)))
  "Returns full string definition for message of type 'quad"
  (cl:format cl:nil "float32 motor1~%float32 motor2~%float32 motor3~%float32 motor4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <quad>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <quad>))
  "Converts a ROS message object to a list"
  (cl:list 'quad
    (cl:cons ':motor1 (motor1 msg))
    (cl:cons ':motor2 (motor2 msg))
    (cl:cons ':motor3 (motor3 msg))
    (cl:cons ':motor4 (motor4 msg))
))
