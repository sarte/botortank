BOT
===

This is the main brain of botortank, everything happens here!

1. To get something useful to _move_ just open one terminal and type:
`roslaunch bot bot_openloop.launch`

2. Now, open another terminal and put the velocity command you want

´rostopic pub -l /velocity_ref geometry_msgs/Twist -- '[1, 0, 0]' '[0, 0, 0]'´
_NB_: The message

3. To confirm active nodes, topics, subscriptions, publishers:
`rostopic list -v`
