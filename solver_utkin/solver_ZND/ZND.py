import logging
import os
import subprocess

import numpy as np
from pydantic import BaseModel, validator
from typing import List
import pandas as pd
import plotly.express as px

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

def draw(solution: pd.DataFrame) -> List[dict]:
    fig = px.line(solution, x="x", y="r")
    fig_dict1 = fig.to_dict()
    fig = px.line(solution, x="x", y="u")
    fig_dict2 = fig.to_dict()
    fig = px.line(solution, x="x", y="p")
    fig_dict3 = fig.to_dict()
    fig = px.line(solution, x="x", y="T")
    fig_dict4 = fig.to_dict()
    fig = px.line(solution, x="x", y="Z")
    fig_dict5 = fig.to_dict() 
    return [fig_dict1, fig_dict2, fig_dict3, fig_dict4, fig_dict5]

def get_folder_bin():
    # ищет папку bin, относительно текущего файла
    folder_bin = os.path.join(os.path.split(__file__)[0], "bin")
    return folder_bin

def get_filename_executable():
    folder_bin = get_folder_bin()
    filename_executable = os.path.join(folder_bin, "ZND.out")
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
    Tf: float
    pf: float
    g: float
    m: float
    Q: float
    E: float
    k: float

    @validator("Tf", "pf", "g", "m", "Q", "E", "k")
    def check_positive(cls, v):
        if v <= 0:
            raise ValueError(f"{v} is not positive")
        return v

def solve(p: InputParameters) -> np.ndarray:

    filename_executable = get_filename_executable()
    if not os.path.isfile(filename_executable):
        compile()

    p_list = [
        p.Tf,
        p.pf,
        p.g,
        p.m,
        p.Q,
        p.E,
        p.k,
    ]
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

    columns = "x", "r", "u", "p", "T", "Z"
    assert solution.shape == (101, len(columns))

    solution_lists = [v.tolist() for v in solution.T]
    solution_dict = dict(zip(columns, solution_lists))

    return solution_dict

