from setuptools import find_packages, setup

setup(
    name="solver_utkin",
    version="0.2",
    packages=find_packages(),
    url="https://github.com/MIPT-Virtual-Labs/lopato_VL_MIPT_repo.git",
    author="Aleksander Lopato",
    author_email="lopato2008@mail.ru",
    include_package_data=True,
    package_data={"": ["./bin/*"]},
    install_requires=["numpy", "pandas", "plotly-express", "pydantic"],
)
