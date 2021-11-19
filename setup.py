from setuptools import setup

setup(
    name="solver_1d_gas_dynamics",
    version="0.1",
    packages=["solver_1d_gas_dynamics"],
    url="https://github.com/MIPT-Virtual-Labs/lopato_VL_MIPT_repo.git",
    author="lopato2008",
    author_email="lopato2008@mail.ru",
    include_package_data=True,
    package_data={"": ["./bin/*"]},
)
