;; Auto-generated. Do not edit!


(when (boundp 'bot::quad)
  (if (not (find-package "BOT"))
    (make-package "BOT"))
  (shadow 'quad (find-package "BOT")))
(unless (find-package "BOT::QUAD")
  (make-package "BOT::QUAD"))

(in-package "ROS")
;;//! \htmlinclude quad.msg.html


(defclass bot::quad
  :super ros::object
  :slots (_motor1 _motor2 _motor3 _motor4 ))

(defmethod bot::quad
  (:init
   (&key
    ((:motor1 __motor1) 0.0)
    ((:motor2 __motor2) 0.0)
    ((:motor3 __motor3) 0.0)
    ((:motor4 __motor4) 0.0)
    )
   (send-super :init)
   (setq _motor1 (float __motor1))
   (setq _motor2 (float __motor2))
   (setq _motor3 (float __motor3))
   (setq _motor4 (float __motor4))
   self)
  (:motor1
   (&optional __motor1)
   (if __motor1 (setq _motor1 __motor1)) _motor1)
  (:motor2
   (&optional __motor2)
   (if __motor2 (setq _motor2 __motor2)) _motor2)
  (:motor3
   (&optional __motor3)
   (if __motor3 (setq _motor3 __motor3)) _motor3)
  (:motor4
   (&optional __motor4)
   (if __motor4 (setq _motor4 __motor4)) _motor4)
  (:serialization-length
   ()
   (+
    ;; float32 _motor1
    4
    ;; float32 _motor2
    4
    ;; float32 _motor3
    4
    ;; float32 _motor4
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _motor1
       (sys::poke _motor1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _motor2
       (sys::poke _motor2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _motor3
       (sys::poke _motor3 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _motor4
       (sys::poke _motor4 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _motor1
     (setq _motor1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _motor2
     (setq _motor2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _motor3
     (setq _motor3 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _motor4
     (setq _motor4 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get bot::quad :md5sum-) "7870b959b33d58fdf72aa92aca4c8520")
(setf (get bot::quad :datatype-) "bot/quad")
(setf (get bot::quad :definition-)
      "float32 motor1
float32 motor2
float32 motor3
float32 motor4

")



(provide :bot/quad "7870b959b33d58fdf72aa92aca4c8520")


