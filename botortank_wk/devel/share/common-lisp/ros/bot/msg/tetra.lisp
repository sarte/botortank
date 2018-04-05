; Auto-generated. Do not edit!


(cl:in-package bot-msg)


;//! \htmlinclude tetra.msg.html

(cl:defclass <tetra> (roslisp-msg-protocol:ros-message)
  ((a
    :reader a
    :initarg :a
    :type cl:boolean
    :initform cl:nil)
   (b
    :reader b
    :initarg :b
    :type cl:boolean
    :initform cl:nil)
   (c
    :reader c
    :initarg :c
    :type cl:boolean
    :initform cl:nil)
   (d
    :reader d
    :initarg :d
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass tetra (<tetra>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <tetra>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'tetra)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bot-msg:<tetra> is deprecated: use bot-msg:tetra instead.")))

(cl:ensure-generic-function 'a-val :lambda-list '(m))
(cl:defmethod a-val ((m <tetra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:a-val is deprecated.  Use bot-msg:a instead.")
  (a m))

(cl:ensure-generic-function 'b-val :lambda-list '(m))
(cl:defmethod b-val ((m <tetra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:b-val is deprecated.  Use bot-msg:b instead.")
  (b m))

(cl:ensure-generic-function 'c-val :lambda-list '(m))
(cl:defmethod c-val ((m <tetra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:c-val is deprecated.  Use bot-msg:c instead.")
  (c m))

(cl:ensure-generic-function 'd-val :lambda-list '(m))
(cl:defmethod d-val ((m <tetra>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:d-val is deprecated.  Use bot-msg:d instead.")
  (d m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <tetra>) ostream)
  "Serializes a message object of type '<tetra>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'a) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'b) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'c) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'd) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <tetra>) istream)
  "Deserializes a message object of type '<tetra>"
    (cl:setf (cl:slot-value msg 'a) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'b) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'c) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'd) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<tetra>)))
  "Returns string type for a message object of type '<tetra>"
  "bot/tetra")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'tetra)))
  "Returns string type for a message object of type 'tetra"
  "bot/tetra")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<tetra>)))
  "Returns md5sum for a message object of type '<tetra>"
  "a10316242c9f6651bd3958b5cd4982fa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'tetra)))
  "Returns md5sum for a message object of type 'tetra"
  "a10316242c9f6651bd3958b5cd4982fa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<tetra>)))
  "Returns full string definition for message of type '<tetra>"
  (cl:format cl:nil "bool a~%bool b~%bool c~%bool d~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'tetra)))
  "Returns full string definition for message of type 'tetra"
  (cl:format cl:nil "bool a~%bool b~%bool c~%bool d~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <tetra>))
  (cl:+ 0
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <tetra>))
  "Converts a ROS message object to a list"
  (cl:list 'tetra
    (cl:cons ':a (a msg))
    (cl:cons ':b (b msg))
    (cl:cons ':c (c msg))
    (cl:cons ':d (d msg))
))
