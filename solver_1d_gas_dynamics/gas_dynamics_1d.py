import os
import subprocess
import numpy as np


def gas_dynamics_1d(*args):

    if len(args) != 6:
        raise ValueError("Incorrect number of args")

    folder_bin = os.path.join(os.path.split(__file__)[0], "bin")  # ищет папку bin, относительно текущего файла
    
    filename_executable = os.path.join(folder_bin, "a.out")
    filename_solution = "solution.dat"

    args_strings = list(map(str, args))
    command = [filename_executable] + args_strings
    
    subprocess.check_output(command)
    result = np.loadtxt(filename_solution)

    os.remove(filename_solution)

    return result
