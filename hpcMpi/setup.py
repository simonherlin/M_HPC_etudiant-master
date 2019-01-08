from setuptools import setup, Extension
import pkgconfig

exts = [
    Extension(
        'hpcMpi',
        [
            'cpp/Integral.cpp',
            'cpp/Image.cpp',
            'cpp/Wrapper.cpp'],
        extra_compile_args=[pkgconfig.cflags('eigen3')],
        language='c++'
        )]

setup(
    name='hpcMpi',
    version='0.1.0',
    ext_modules=exts,
    scripts=[
        'scripts/hpcMpiImageRun.sh',
        'scripts/hpcMpiImageSeq.py',
        'scripts/hpcMpiPlot.py',
        'scripts/hpcMpiIntegralRun.sh',
        'scripts/hpcMpiIntegralSeq.py',
        'scripts/hpcMpiHello2.py',
        'scripts/hpcMpiHello1.py']
)
