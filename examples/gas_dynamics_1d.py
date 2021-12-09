from solver_gas_dynamics_1d import handle_request

# Correct request
params = dict(r_left=1, r_right=0.25, u_left=0, u_right=0, p_left=1, p_right=0.1, t_end=0.25, cfl=0.1)

request = dict(problem="gas_dynamics_1d", args=params)
response = handle_request(request)

# And now we will break things
# - - -
params["r_left"] = 1e9
response = handle_request(request)

# - - -
params["r_left"] = -1
response = handle_request(request)

# - - -
del params["r_left"]
response = handle_request(request)

# - - -
request["problem"] = "alien"
response = handle_request(request)
