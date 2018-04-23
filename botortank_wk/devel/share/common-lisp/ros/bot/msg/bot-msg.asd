
(cl:in-package :asdf)

(defsystem "bot-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "lidar_array" :depends-on ("_package_lidar_array"))
    (:file "_package_lidar_array" :depends-on ("_package"))
    (:file "quad" :depends-on ("_package_quad"))
    (:file "_package_quad" :depends-on ("_package"))
    (:file "tetra" :depends-on ("_package_tetra"))
    (:file "_package_tetra" :depends-on ("_package"))
  ))