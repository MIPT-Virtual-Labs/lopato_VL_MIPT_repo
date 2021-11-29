> Пробный репозиторий, созданный Лопато АИ, который может стать рабочим для некоторых проектов С/python в рамках данной лаборатории.

# README (for Linux)

## Clone
```shell
# bash
git clone https://github.com/MIPT-Virtual-Labs/lopato_VL_MIPT_repo.git
cd lopato_VL_MIPT_repo/
```

## Virtual environment
```shell
# bash
# only once
python -m venv ./venv
# every time
. venv/bin/activate
```

## Install
```shell
# bash
pip install -r requirements.txt
pip install -e .
```

## Use
```python
# python
from solver_1d_gas_dynamics.gas_dynamics_1d import gas_dynamics_1d
result = gas_dynamics_1d(1, 0.25, 0, 0, 1, 0.1)
```
