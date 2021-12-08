import logging
import os
import subprocess

import numpy as np
from pydantic import BaseModel, validator

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

    command = " ".join(["g++", *filenames_cc, "-o", filename_executable])

    msg_debug = "run command in subprocess: {}".format(command)
    logger.debug(msg=msg_debug)

    subprocess.check_output(command, shell=True, stderr=subprocess.DEVNULL)


def clean_folder_bin():
    folder_bin = get_folder_bin()
    for filename in os.listdir(folder_bin):
        if filename.endswith(".out"):
            filename_full = os.path.join(folder_bin, filename)
            os.remove(filename_full)


class InputParameters(BaseModel):
    r_left: float
    r_right: float
    u_left: float
    u_right: float
    p_left: float
    p_right: float
    t_end: float
    cfl: float

    @validator("r_left", "r_right", "p_left", "p_right", "t_end", "cfl")
    def check_positive(cls, v):
        if v <= 0:
            raise ValueError(f"{v} is not positive")
        return v


def solve(p: InputParameters) -> np.ndarray:

    filename_executable = get_filename_executable()
    if not os.path.isfile(filename_executable):
        compile()

    p_list = [p.r_left, p.r_right, p.u_left, p.u_right, p.p_left, p.p_right, p.t_end, p.cfl]
    args_strings = list(map(str, p_list))

    command = " ".join(["'" + filename_executable + "'"] + args_strings)

    msg_debug = "run command in subprocess: {}".format(command)
    logger.debug(msg=msg_debug)
    subprocess.check_output(command, shell=True)

    filename_solution = "solution.dat"
    solution = np.loadtxt(filename_solution)
    os.remove(filename_solution)

    if np.any(np.isnan(solution)):
        raise RuntimeError("solution contains NaN values")

    columns = "x", "r", "u", "p", "E"
    assert solution.shape == (100, len(columns))

    solution_lists = [v.tolist() for v in solution.T]
    solution_dict = dict(zip(columns, solution_lists))

    return solution_dict
