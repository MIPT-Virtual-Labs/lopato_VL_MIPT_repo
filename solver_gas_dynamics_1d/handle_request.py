from logging import error
from typing import List, Optional

from pydantic import BaseModel, ValidationError, validator

from solver_gas_dynamics_1d import gas_dynamics_1d


class Error(BaseModel):
    error: str
    field: str


class Response(BaseModel):
    errors: Optional[List[Error]]
    description: Optional[str]
    solution: Optional[dict]
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

    if problem_name != "gas_dynamics_1d":

        errors = [Error(error=f"Unknown problem: {problem_name}", field="problem")]
        response = Response(status="error", errors=errors)
        return response.dict()

    args = request_json["args"]

    try:
        p = gas_dynamics_1d.InputParameters(**args)
    except ValidationError as ve:
        errors = [Error(error=e["msg"], field=e["loc"][0]) for e in ve.errors()]
        response = Response(status="error", errors=errors)
        return response.dict()

    try:
        solution_dict = gas_dynamics_1d.solve(p)
    except Exception as e:
        response = Response(status="failed", description=str(e))
        return response.dict()

    response = Response(status="done", solution=solution_dict)
    response_dict = response.dict()
    return response_dict
