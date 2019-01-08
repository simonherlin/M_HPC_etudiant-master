from setuptools import setup, Extension


exts = [
    Extension(
        'hpcThreads',
        [
            'cpp/Hello.cpp',
            'cpp/Fibo.cpp',
            'cpp/Wrapper.cpp'])]


setup(
    name='hpcThreads',
    version='0.1.0',
    ext_modules=exts,
    scripts=[
        'scripts/hpcThreadsHello.py',
        'scripts/hpcThreadsFiboTest.py',
        'scripts/hpcThreadsFiboTime.py',
        'scripts/hpcThreadsFiboPlot.py']
)
