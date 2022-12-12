import argparse
import sys

import rospy
import actionlib
from rospowerboard.msg import (
    SetSpeedAllAction, SetSpeedAllResult, SetSpeedAllGoal,
    SetSpeedM1Action, SetSpeedM1Result, SetSpeedM1Goal,
    SetSpeedM2Action, SetSpeedM2Result, SetSpeedM2Goal,
    BrakeAllAction, BrakeAllResult, BrakeAllGoal,
    BrakeM1Action, BrakeM1Result, BrakeM1Goal,
    BrakeM2Action, BrakeM2Result, BrakeM2Goal,
    ReverseAllAction, ReverseAllResult, ReverseAllGoal,
    ReverseM1Action, ReverseM1Result, ReverseM1Goal,
    ReverseM2Action, ReverseM2Result, ReverseM2Goal,
    StopAllAction, StopAllResult, StopAllGoal,
    StopM1Action, StopM1Result, StopM1Goal,
    StopM2Action, StopM2Result, StopM2Goal,
    ArmAction, ArmResult, ArmGoal,
    DisarmAction, DisarmResult, DisarmGoal)
from pypowerboard import Board


board = None
server_arm, server_disarm = None, None
server_set_speed_all, server_set_speed_m1, server_set_speed_m2 = None, None, None
server_brake_all, server_brake_m1, server_brake_m2 = None, None, None
server_reverse_all, server_reverse_m1, server_reverse_m2 = None, None, None
server_stop_all, server_stop_m1, server_stop_m2 = None, None, None


def callback_arm(goal: ArmGoal):
    global board, server_arm
    board.arm()

    result = ArmResult()
    result.done = True
    server_arm.set_succeeded(result)

def callback_disarm(goal: DisarmGoal):
    global board, server_disarm
    board.disarm()

    result = DisarmResult()
    result.done = True
    server_disarm.set_succeeded(result)

def callback_set_speed_all(goal: SetSpeedAllGoal):
    global board, server_set_speed_all
    board.set_speed_all(goal.speed)
    
    result = SetSpeedAllResult()
    result.done = True
    server_set_speed_all.set_succeeded(result)

def callback_set_speed_m1(goal: SetSpeedM1Goal):
    global board, server_set_speed_m1
    board.set_speed_m1(goal.speed)
    
    result = SetSpeedM1Result()
    result.done = True
    server_set_speed_m1.set_succeeded(result)

def callback_set_speed_m2(goal: SetSpeedM2Goal):
    global board, server_set_speed_m2
    board.set_speed_m2(goal.speed)
    
    result = SetSpeedM2Result()
    result.done = True
    server_set_speed_m2.set_succeeded(result)

def callback_stop_all(goal: StopAllGoal):
    global board, server_stop_all
    board.stop_all()

    result = StopAllResult()
    result.done = True
    server_stop_all.set_succeeded(result)

def callback_stop_m1(goal: StopM1Goal):
    global board, server_stop_m1
    board.stop_m1()

    result = StopM1Result()
    result.done = True
    server_stop_m1.set_succeeded(result)

def callback_stop_m2(goal: StopM2Goal):
    global board, server_stop_m2
    board.stop_m2()

    result = StopM2Result()
    result.done = True
    server_stop_m1.set_succeeded(result)

def callback_brake_all(goal: BrakeAllGoal):
    global board, server_brake_all
    board.bake_all()

    result = BrakeAllResult()
    result.done = True
    server_brake_all.set_succeeded(result)

def callback_brake_m1(goal: BrakeM1Goal):
    global board, server_brake_m1
    board.bake_m1()

    result = BrakeM1Result()
    result.done = True
    server_brake_m1.set_succeeded(result)

def callback_brake_m2(goal: BrakeM2Goal):
    global board, server_brake_m2
    board.bake_m2()

    result = BrakeM2Result()
    result.done = True
    server_brake_m2.set_succeeded(result)

def callback_reverse_all(goal: ReverseAllGoal):
    global board, server_reverse_all
    board.reverse_all()

    result = ReverseAllResult()
    result.done = True
    server_reverse_all.set_succeeded(result)

def callback_reverse_m1(goal: ReverseM1Goal):
    global board, server_reverse_m1
    board.reverse_m1()

    result = ReverseM1Result()
    result.done = True
    server_reverse_m1.set_succeeded(result)

def callback_reverse_m2(goal: ReverseM2Goal):
    global board, server_reverse_m2
    board.reverse_m2()

    result = ReverseM2Result()
    result.done = True
    server_reverse_m2.set_succeeded(result)


def main():
    global board, server_arm, server_disarm, server_set_speed_all, server_set_speed_m1, server_set_speed_m2, server_stop_all, server_stop_m1, server_stop_m2, server_brake_all, server_brake_m1, server_brake_m2, server_reverse_all, server_reverse_m1, server_reverse_m2
    parser = argparse.ArgumentParser()
    parser.add_argument("address", type=int, help="I2C Address of the powerboard to control.")
    parser.add_argument("-v", "--verbose", action="store_true", help="Output node processes information.")
    config = parser.parse_args(rospy.myargv(argv=sys.argv)[1:])

    board = Board(config.address, "/dev/i2c-1")
    rospy.on_shutdown(board.disarm)
    board.arm()

    rospy.init_node("powerboard")
    rospy.loginfo("Initializing node with name detector.")
    if config.verbose:
        rospy.loginfo("Node verbose required. Further logs will be outputed.")

    server_arm = actionlib.SimpleActionServer("Arm", ArmAction, execute_cb=callback_arm, auto_start=False)
    server_arm.start()
    if config.verbose:
        rospy.loginfo("'Arm' action server started.")

    server_disarm = actionlib.SimpleActionServer("Disarm", DisarmAction, execute_cb=callback_disarm, auto_start=False)
    server_disarm.start()
    if config.verbose:
        rospy.loginfo("'Disarm' action server started.")

    server_set_speed_all = actionlib.SimpleActionServer("SetSpeedAll", SetSpeedAllAction, execute_cb=callback_set_speed_all, auto_start=False)
    server_set_speed_all.start()
    if config.verbose:
        rospy.loginfo("'SetSpeelAll' action server started.")

    server_set_speed_m1 = actionlib.SimpleActionServer("SetSpeedM1", SetSpeedM1Action, execute_cb=callback_set_speed_m1, auto_start=False)
    server_set_speed_m1.start()
    if config.verbose:
        rospy.loginfo("'SetSpeedM1' action server started.")

    server_set_speed_m2 = actionlib.SimpleActionServer("SetSpeedM2", SetSpeedM2Action, execute_cb=callback_set_speed_m2, auto_start=False)
    server_set_speed_m2.start()
    if config.verbose:
        rospy.loginfo("'SetSpeedM2' action server started.")

    server_stop_all = actionlib.SimpleActionServer("StopAll", StopAllAction, execute_cb=callback_stop_all, auto_start=False)
    server_stop_all.start()
    if config.verbose:
        rospy.loginfo("'StopAll' action server started.")

    server_stop_m1 = actionlib.SimpleActionServer("StopM1", StopM1Action, execute_cb=callback_stop_m1, auto_start=False)
    server_stop_m1.start()
    if config.verbose:
        rospy.loginfo("'StopM1' action server started.")

    server_stop_m2 = actionlib.SimpleActionServer("StopM2", StopM2Action, execute_cb=callback_stop_m2, auto_start=False)
    server_stop_m2.start()
    if config.verbose:
        rospy.loginfo("'StopM2' action server started.")

    server_brake_all = actionlib.SimpleActionServer("BrakeAll", BrakeAllAction, execute_cb=callback_brake_all, auto_start=False)
    server_brake_all.start()
    if config.verbose:
        rospy.loginfo("'BrakeAll' action server started.")

    server_brake_m1= actionlib.SimpleActionServer("BrakeM1", BrakeM1Action, execute_cb=callback_brake_m1, auto_start=False)
    server_brake_m1.start()
    if config.verbose:
        rospy.loginfo("'BrakeM1' action server started.") 

    server_brake_m2 = actionlib.SimpleActionServer("BrakeM2", BrakeM2Action, execute_cb=callback_brake_m2, auto_start=False)
    server_brake_m2.start()
    if config.verbose:
        rospy.loginfo("'BrakeM2' action server started.")

    server_reverse_all = actionlib.SimpleActionServer("ReverseAll", ReverseAllAction, execute_cb=callback_reverse_all, auto_start=False)
    server_reverse_all.start()
    if config.verbose:
        rospy.loginfo("'ReverseAll' action server started.")

    server_reverse_m1 = actionlib.SimpleActionServer("ReverseM1", ReverseM1Action, execute_cb=callback_reverse_m1, auto_start=False)
    server_reverse_m1.start()
    if config.verbose:
        rospy.loginfo("'ReverseM1' action server started.")

    server_reverse_m2 = actionlib.SimpleActionServer("ReverseM2", ReverseM2Action, execute_cb=callback_reverse_m2, auto_start=False)
    server_reverse_m2.start()
    if config.verbose:
        rospy.loginfo("'ReverseM2' action server started.")

    while not rospy.is_shutdown():
        try:
            rospy.spin()
        except rospy.ROSInterruptException:
            return

if __name__ == "__main__":
    main()
