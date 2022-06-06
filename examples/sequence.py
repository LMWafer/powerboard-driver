from pypowerboard import Board
import time

board = Board(112, "/dev/i2c-1")
# time.sleep(1)
# board.arm()
# time.sleep(1)
# board.set_speed_m1(255)
# board.set_speed_m2(-128)
# time.sleep(3)
# board.stop_all()
# time.sleep(1)
# board.disarm()
# time.sleep(2)


# print(board.buck.enable_regulator())
buck = board.buck()
buck.enable_regulator()
# print(buck)
# buck.enable_regulator()
