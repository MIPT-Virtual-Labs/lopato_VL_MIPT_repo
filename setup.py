from setuptools import setup

setup(
    name="solver_gas_dynamics_1d",
    version="0.1",
    packages=["solver_gas_dynamics_1d"],
    url="https://github.com/MIPT-Virtual-Labs/lopato_VL_MIPT_repo.git",
    author="Aleksander Lopato",
    author_email="lopato2008@mail.ru",
    include_package_data=True,
    package_data={"": ["./bin/*"]},
)
