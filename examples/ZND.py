from solver_utkin import handle_request

# Correct request ZND problem (hydrogen-air problem)
params = dict(
    Tf=290,
    pf=100000,
    g=1.17,
    m=0.021,
    Q=5.02e+6,
    E=113.0e+3,
    k=6.85e+9,
)

request = dict(problem="ZND", args=params)
response = handle_request(request)

# And now we will break things
# - - -
params["Tf"] = 1e9
response = handle_request(request)

# - - -
params["Tf"] = -1
response = handle_request(request)

# - - -
del params["Tf"]
response = handle_request(request)

# - - -
request["problem"] = "alien"
response = handle_request(request)
