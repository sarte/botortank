; Auto-generated. Do not edit!


(cl:in-package bot-msg)


;//! \htmlinclude lidar_array.msg.html

(cl:defclass <lidar_array> (roslisp-msg-protocol:ros-message)
  ((angles
    :reader angles
    :initarg :angles
    :type (cl:vector cl:float)
   :initform (cl:make-array 360 :element-type 'cl:float :initial-element 0.0))
   (distances
    :reader distances
    :initarg :distances
    :type (cl:vector cl:float)
   :initform (cl:make-array 360 :element-type 'cl:float :initial-element 0.0))
   (iter
    :reader iter
    :initarg :iter
    :type cl:fixnum
    :initform 0))
)

(cl:defclass lidar_array (<lidar_array>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <lidar_array>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'lidar_array)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bot-msg:<lidar_array> is deprecated: use bot-msg:lidar_array instead.")))

(cl:ensure-generic-function 'angles-val :lambda-list '(m))
(cl:defmethod angles-val ((m <lidar_array>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:angles-val is deprecated.  Use bot-msg:angles instead.")
  (angles m))

(cl:ensure-generic-function 'distances-val :lambda-list '(m))
(cl:defmethod distances-val ((m <lidar_array>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:distances-val is deprecated.  Use bot-msg:distances instead.")
  (distances m))

(cl:ensure-generic-function 'iter-val :lambda-list '(m))
(cl:defmethod iter-val ((m <lidar_array>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bot-msg:iter-val is deprecated.  Use bot-msg:iter instead.")
  (iter m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <lidar_array>) ostream)
  "Serializes a message object of type '<lidar_array>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'angles))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'distances))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'iter)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <lidar_array>) istream)
  "Deserializes a message object of type '<lidar_array>"
  (cl:setf (cl:slot-value msg 'angles) (cl:make-array 360))
  (cl:let ((vals (cl:slot-value msg 'angles)))
    (cl:dotimes (i 360)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'distances) (cl:make-array 360))
  (cl:let ((vals (cl:slot-value msg 'distances)))
    (cl:dotimes (i 360)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'iter)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<lidar_array>)))
  "Returns string type for a message object of type '<lidar_array>"
  "bot/lidar_array")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'lidar_array)))
  "Returns string type for a message object of type 'lidar_array"
  "bot/lidar_array")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<lidar_array>)))
  "Returns md5sum for a message object of type '<lidar_array>"
  "a3ddce690af809517c1ac0a3e62abcfa")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'lidar_array)))
  "Returns md5sum for a message object of type 'lidar_array"
  "a3ddce690af809517c1ac0a3e62abcfa")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<lidar_array>)))
  "Returns full string definition for message of type '<lidar_array>"
  (cl:format cl:nil "float32[360] angles~%float32[360] distances~%uint8  iter~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'lidar_array)))
  "Returns full string definition for message of type 'lidar_array"
  (cl:format cl:nil "float32[360] angles~%float32[360] distances~%uint8  iter~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <lidar_array>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'angles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'distances) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <lidar_array>))
  "Converts a ROS message object to a list"
  (cl:list 'lidar_array
    (cl:cons ':angles (angles msg))
    (cl:cons ':distances (distances msg))
    (cl:cons ':iter (iter msg))
))
