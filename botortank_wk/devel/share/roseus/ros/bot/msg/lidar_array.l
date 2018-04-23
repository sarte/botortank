;; Auto-generated. Do not edit!


(when (boundp 'bot::lidar_array)
  (if (not (find-package "BOT"))
    (make-package "BOT"))
  (shadow 'lidar_array (find-package "BOT")))
(unless (find-package "BOT::LIDAR_ARRAY")
  (make-package "BOT::LIDAR_ARRAY"))

(in-package "ROS")
;;//! \htmlinclude lidar_array.msg.html


(defclass bot::lidar_array
  :super ros::object
  :slots (_angles _distances _iter ))

(defmethod bot::lidar_array
  (:init
   (&key
    ((:angles __angles) (make-array 360 :initial-element 0.0 :element-type :float))
    ((:distances __distances) (make-array 360 :initial-element 0.0 :element-type :float))
    ((:iter __iter) 0)
    )
   (send-super :init)
   (setq _angles __angles)
   (setq _distances __distances)
   (setq _iter (round __iter))
   self)
  (:angles
   (&optional __angles)
   (if __angles (setq _angles __angles)) _angles)
  (:distances
   (&optional __distances)
   (if __distances (setq _distances __distances)) _distances)
  (:iter
   (&optional __iter)
   (if __iter (setq _iter __iter)) _iter)
  (:serialization-length
   ()
   (+
    ;; float32[360] _angles
    (* 4    360)
    ;; float32[360] _distances
    (* 4    360)
    ;; uint8 _iter
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[360] _angles
     (dotimes (i 360)
       (sys::poke (elt _angles i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[360] _distances
     (dotimes (i 360)
       (sys::poke (elt _distances i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; uint8 _iter
       (write-byte _iter s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[360] _angles
   (dotimes (i (length _angles))
     (setf (elt _angles i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; float32[360] _distances
   (dotimes (i (length _distances))
     (setf (elt _distances i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     )
   ;; uint8 _iter
     (setq _iter (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get bot::lidar_array :md5sum-) "a3ddce690af809517c1ac0a3e62abcfa")
(setf (get bot::lidar_array :datatype-) "bot/lidar_array")
(setf (get bot::lidar_array :definition-)
      "float32[360] angles
float32[360] distances
uint8  iter

")



(provide :bot/lidar_array "a3ddce690af809517c1ac0a3e62abcfa")


