;; Auto-generated. Do not edit!


(when (boundp 'bot::tetra)
  (if (not (find-package "BOT"))
    (make-package "BOT"))
  (shadow 'tetra (find-package "BOT")))
(unless (find-package "BOT::TETRA")
  (make-package "BOT::TETRA"))

(in-package "ROS")
;;//! \htmlinclude tetra.msg.html


(defclass bot::tetra
  :super ros::object
  :slots (_a _b _c _d ))

(defmethod bot::tetra
  (:init
   (&key
    ((:a __a) nil)
    ((:b __b) nil)
    ((:c __c) nil)
    ((:d __d) nil)
    )
   (send-super :init)
   (setq _a __a)
   (setq _b __b)
   (setq _c __c)
   (setq _d __d)
   self)
  (:a
   (&optional __a)
   (if __a (setq _a __a)) _a)
  (:b
   (&optional __b)
   (if __b (setq _b __b)) _b)
  (:c
   (&optional __c)
   (if __c (setq _c __c)) _c)
  (:d
   (&optional __d)
   (if __d (setq _d __d)) _d)
  (:serialization-length
   ()
   (+
    ;; bool _a
    1
    ;; bool _b
    1
    ;; bool _c
    1
    ;; bool _d
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _a
       (if _a (write-byte -1 s) (write-byte 0 s))
     ;; bool _b
       (if _b (write-byte -1 s) (write-byte 0 s))
     ;; bool _c
       (if _c (write-byte -1 s) (write-byte 0 s))
     ;; bool _d
       (if _d (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _a
     (setq _a (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _b
     (setq _b (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _c
     (setq _c (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _d
     (setq _d (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get bot::tetra :md5sum-) "a10316242c9f6651bd3958b5cd4982fa")
(setf (get bot::tetra :datatype-) "bot/tetra")
(setf (get bot::tetra :definition-)
      "bool a
bool b
bool c
bool d
")



(provide :bot/tetra "a10316242c9f6651bd3958b5cd4982fa")


