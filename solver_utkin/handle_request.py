from typing import List, Optional

from pydantic import BaseModel, ValidationError, validator

from solver_utkin import ZND, gas_dynamics_1d


class Error(BaseModel):
    error: str
    field: str


class Response(BaseModel):
    errors: Optional[List[Error]]
    description: Optional[str]
    solution: Optional[dict]
    figures: Optional[List[dict]]
    status: str

    @validator("status")
    def validate_status(cls, st, values):
        if st == "error":
            if "errors" not in values:
                raise ValueError("status is set to `error` but no errors provided")
        else:
            if "errors" in values and values["errors"]:
                raise ValueError(f"status is not {st} but errors were found")
        if st == "failed" and "description" not in values:
            raise ValueError("status is set to `failed` but no description provided")
        return st


def handle_request(request_json: dict) -> dict:

    problem_name = request_json["problem"]

    problems = {"gas_dynamics_1d": gas_dynamics_1d, "ZND": ZND}

    if problem_name not in problems:

        errors = [Error(error=f"Unknown problem: `{problem_name}`", field="problem")]
        response = Response(status="error", errors=errors)
        return response.dict()

    solver = problems[problem_name]
    args = request_json["args"]

    try:
        p = solver.InputParameters(**args)
    except ValidationError as ve:
        errors = [Error(error=e["msg"], field=e["loc"][0]) for e in ve.errors()]
        response = Response(status="error", errors=errors)
        return response.dict()

    try:
        solution_dict = solver.solve(p)
        figures = solver.draw(solution_dict)
    except Exception as e:
        response = Response(status="failed", description=str(e))
        return response.dict()

    response = Response(status="done", figures=figures, solution=solution_dict)
    response_dict = response.dict()
    return response_dict
