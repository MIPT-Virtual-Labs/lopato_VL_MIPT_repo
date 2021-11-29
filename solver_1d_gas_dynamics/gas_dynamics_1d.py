import os
import subprocess
import numpy as np

import logging
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)


def get_folder_bin():
    # ищет папку bin, относительно текущего файла
    folder_bin = os.path.join(os.path.split(__file__)[0], "bin")  
    return folder_bin


def get_filename_executable():
    folder_bin = get_folder_bin()
    filename_executable = os.path.join(folder_bin, "gas_dynamics_1d.out")
    return filename_executable


def compile():
    
    folder_bin = get_folder_bin()
    filename_executable = "'" + get_filename_executable() + "'"

    filenames_cc = [
        "'" + os.path.join(folder_bin, filename_cc) + "'"
        for filename_cc in os.listdir(folder_bin)
        if filename_cc.endswith(".cc")
    ]

    command = " ".join([
        "g++",
        *filenames_cc,
            "-o",
            filename_executable
    ])

    msg_debug = "run command in subprocess: {}".format(command)
    logger.debug(msg=msg_debug)

    subprocess.check_output(command, shell=True, stderr=subprocess.DEVNULL)


def clean_folder_bin():
    folder_bin = get_folder_bin()
    for filename in os.listdir(folder_bin):
        if filename.endswith(".out"):
            filename_full = os.path.join(folder_bin, filename)
            os.remove(filename_full)


def gas_dynamics_1d(*args):

    if len(args) != 6:
        raise ValueError("Incorrect number of args")

    filename_executable = get_filename_executable()
    if not os.path.isfile(filename_executable):
        compile()

    filename_solution = "solution.dat"

    args_strings = list(map(str, args))
    command = " ".join(["'" + filename_executable + "'"] + args_strings)
    
    msg_debug = "run command in subprocess: {}".format(command)
    logger.debug(msg=msg_debug)
    
    subprocess.check_output(command, shell=True)
    result = np.loadtxt(filename_solution)

    os.remove(filename_solution)

    return result
