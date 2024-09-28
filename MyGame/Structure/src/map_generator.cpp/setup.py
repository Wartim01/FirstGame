from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        'map_generator',
        ['map_generator.cpp', 'map_generator_wrapper.cpp'],
        include_dirs=[pybind11.get_include()],
        language='c++'
    ),
]

setup(
    name='map_generator',
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.5.0'],
    setup_requires=['pybind11>=2.5.0'],
)