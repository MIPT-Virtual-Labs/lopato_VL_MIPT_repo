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

## Examples
Check out [examples](./examples) folder.

## (Pre-)commit
1. Install:
```sh
pip install pre-commit && pre-commit install
```
2. Run:
```sh
git add <FILES>
pre-commit run
git add <FIXED FILES>  # if necessary
git commit -m "MESSAGE"
```
