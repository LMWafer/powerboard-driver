#! /usr/bin/python3

import argparse
import sys
import time

import actionlib
import rospy
from rospowerboard.msg import DisarmAction, DisarmGoal, SetSpeedAllAction, SetSpeedAllGoal, StopAllAction, StopAllGoal


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true", help="Output node processes information.")
    config = parser.parse_args(rospy.myargv(argv=sys.argv)[1:])

    rospy.init_node("client")
    if config.verbose:
        rospy.loginfo("Node started with name 'powerboard-cient'.")

    set_speed_client = actionlib.SimpleActionClient("SetSpeedAll", SetSpeedAllAction)
    if config.verbose:
        rospy.loginfo("Created action client.")
    set_speed_client.wait_for_server()
    if config.verbose:
        rospy.loginfo("Connected to action server.")
    goal = SetSpeedAllGoal()
    goal.speed = 255
    set_speed_client.send_goal(goal)
    set_speed_client.wait_for_result()
    print(set_speed_client.get_result())

    time.sleep(4)

    stop_client = actionlib.SimpleActionClient("StopAll", StopAllAction)
    stop_client.wait_for_server()
    goal = StopAllGoal()
    stop_client.send_goal(goal)
    stop_client.wait_for_result()
    print(stop_client.get_result())

    time.sleep(4)

    set_speed_client = actionlib.SimpleActionClient("SetSpeedAll", SetSpeedAllAction)
    set_speed_client.wait_for_server()
    goal = SetSpeedAllGoal()
    goal.speed = -255
    set_speed_client.send_goal(goal)
    set_speed_client.wait_for_result()
    print(set_speed_client.get_result())

    time.sleep(4)

    stop_client = actionlib.SimpleActionClient("StopAll", StopAllAction)
    stop_client.wait_for_server()
    goal = StopAllGoal()
    stop_client.send_goal(goal)
    stop_client.wait_for_result()
    print(stop_client.get_result())

    time.sleep(2)

    disarm_client = actionlib.SimpleActionClient("Disarm", DisarmAction)
    disarm_client.wait_for_server()
    goal = DisarmGoal()
    disarm_client.send_goal(goal)
    disarm_client.wait_for_result()
    print(disarm_client.get_result())

if __name__ == "__main__":
    main()