#! /usr/bin/python3

import argparse
import sys

import rospy
from geometry_msgs.msg import Twist
from rospowerboard.msg import (SetSpeedAllAction, SetSpeedAllGoal,
                               SetSpeedM1Action, SetSpeedM1Goal,
                               SetSpeedM2Action, SetSpeedM2Goal,
                               StopAllAction, StopAllGoal)
import actionlib

config = argparse.Namespace()

def twist_callback(message: Twist, args):
    global config

    right_motor = args[0]
    action_clients = args[1]

    if message.linear.x == 1.0:
        client = action_clients["SetSpeedAll"]
        goal = SetSpeedAllGoal()
        goal.speed = 255
        if config.verbose:
            rospy.loginfo("Requesting a forward.")
        client.send_goal(goal)

    elif message.linear.x == -1.0:
        client = action_clients["SetSpeedAll"]
        goal = SetSpeedAllGoal()
        goal.speed = -255
        if config.verbose:
            rospy.loginfo("Requesting a backward.")
        client.send_goal(goal)

    elif message.angular.z == -1.0:
        if right_motor == 1:
            m1_speed, m2_speed = -255, 255
        elif right_motor == 2:
            m1_speed, m2_speed = 255, -255
        client_m1 = action_clients["SetSpeedM1"]
        goal_m1 = SetSpeedM1Goal()
        goal_m1.speed = m1_speed
        client_m1.send_goal(goal_m1)
        client_m2 = action_clients["SetSpeedM2"]
        goal_m2 = SetSpeedM2Goal()
        goal_m2.speed = m2_speed
        if config.verbose:
            rospy.loginfo("Requesting a clockwise rotation.")
        client_m2.send_goal(goal_m2)

    elif message.angular.z == 1.0:
        if right_motor == 1:
            m1_speed, m2_speed = 255, -255
        elif right_motor == 2:
            m1_speed, m2_speed = -255, 255
        client_m1 = action_clients["SetSpeedM1"]
        goal_m1 = SetSpeedM1Goal()
        goal_m1.speed = m1_speed
        client_m1.send_goal(goal_m1)
        client_m2 = action_clients["SetSpeedM2"]
        goal_m2 = SetSpeedM2Goal()
        goal_m2.speed = m2_speed
        if config.verbose:
            rospy.loginfo("Requesting a counter-clockwise rotation.")
        client_m2.send_goal(goal_m2)
    
    else:
        client = action_clients["StopAll"]
        goal = StopAllGoal()
        if config.verbose:
            rospy.loginfo("Requesting a stop.")
        client.send_goal(goal)

def main():
    global config

    parser = argparse.ArgumentParser()
    parser.add_argument("RIGHT_MOTOR", type=int, choices=[1, 2], help="Which motor is on the right of the robot. From powerboard POV, M1 is the furthest from the I2C pin.")
    parser.add_argument("-v", "--verbose", action="store_true", help="Output node processes information.")
    config = parser.parse_args(rospy.myargv(argv=sys.argv)[1:])

    rospy.init_node("teleop_client")
    if config.verbose:
        rospy.loginfo("Node started with name 'teleop_cient'.")

    action_clients = {}
    action_clients["SetSpeedAll"] = actionlib.SimpleActionClient("SetSpeedAll", SetSpeedAllAction)
    action_clients["SetSpeedM1"] = actionlib.SimpleActionClient("SetSpeedM1", SetSpeedM1Action)
    action_clients["SetSpeedM2"] = actionlib.SimpleActionClient("SetSpeedM2", SetSpeedM2Action)
    action_clients["StopAll"] = actionlib.SimpleActionClient("StopAll", StopAllAction)
    if config.verbose:
        rospy.loginfo("Created action clients, wainting for action servers (SetSpeeAll, SetSpeedM1, SetSpeedM2, StopAll)...")

    for client in action_clients.values():
        client.wait_for_server()
    if config.verbose:
        rospy.loginfo("All action servers seem started.")

    rospy.Subscriber("/cmd_vel", Twist, twist_callback, queue_size=1, callback_args=(config.RIGHT_MOTOR, action_clients))
    if config.verbose:
        rospy.loginfo("Subscribed to twist publisher.")

    while not rospy.is_shutdown():
        try:
            rospy.spin()
        except rospy.KeyboardInterrupt:
            pass

if __name__ == "__main__":
    main()
