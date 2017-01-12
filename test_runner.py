# -*- coding: utf-8 -*-
import shlex,subprocess
import os
import urllib
import tarfile

test_msvc_vers = [("msvc2015","Visual Studio 14 2015","",True)
    ,("msvc2015win64","Visual Studio 14 2015 Win64","",True)
    ,("msvc2013","Visual Studio 12 2013","",False)
    ,("msvc2013win64","Visual Studio 12 2013 Win64","",False)
    ,("msvc2012","Visual Studio 11 2012","",False)
    ,("msvc2010","Visual Studio 10 2010","",False)
    ,("msvc2008","Visual Studio 9 2008","",True)
    ]

test_compilers = [
    ('gcc-3.3','g++-3.3','',False)
    ,('gcc-4.4','g++-4.4','',False)
    ,('gcc-4.5','g++-4.5','',False)
    ,('gcc-4.6','g++-4.6','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('gcc-4.7','g++-4.7','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('gcc-4.7','g++-4.7','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('gcc-4.8','g++-4.8','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('gcc-4.8','g++-4.8','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('gcc-4.9','g++-4.9','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('gcc-4.9','g++-4.9','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('gcc-5','g++-5','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('gcc-5','g++-5','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('gcc-6','g++-6','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('gcc-6','g++-6','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('gcc-6','g++-6','-DCMAKE_CXX_FLAGS=-std=c++14',False)
    ,('gcc','g++','-DCMAKE_CXX_FLAGS=-std=c++03',True)
    ,('gcc','g++','-DCMAKE_CXX_FLAGS=-std=c++11',True)
    ,('clang','clang++','-DCMAKE_CXX_FLAGS=-std=c++03',True)
    ,('clang','clang++','-DCMAKE_CXX_FLAGS=-std=c++11',True)
    ,('clang-3.5','clang++-3.5','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('clang-3.6','clang++-3.6','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('clang-3.7','clang++-3.7','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('clang-3.8','clang++-3.8','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('clang-3.9','clang++-3.9','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('clang-4.0','clang++-4.0','-DCMAKE_CXX_FLAGS=-std=c++03',False)
    ,('clang-3.5','clang++-3.5','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('clang-3.6','clang++-3.6','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('clang-3.7','clang++-3.7','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('clang-3.8','clang++-3.8','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('clang-3.9','clang++-3.9','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('clang-4.0','clang++-4.0','-DCMAKE_CXX_FLAGS=-std=c++11',False)
    ,('clang-3.8','clang++-3.8','-DCMAKE_CXX_FLAGS=-std=c++14',False)
    ,('clang-3.9','clang++-3.9','-DCMAKE_CXX_FLAGS=-std=c++14',False)
    ,('clang-4.0','clang++-4.0','-DCMAKE_CXX_FLAGS=-std=c++14',False)
    ]

def build_and_exec_test(compiler,build_type,dir_opt):
    ccompiler = compiler[0]
    cxxcompiler = compiler[1]
    addopt = compiler[2]
    if os.system(cxxcompiler+' -v 2> /dev/null')!=0: return

    buildpath = "_build/"+compiler[0]+"_"+build_type+"_"+dir_opt
    if not os.path.exists(buildpath):
        os.makedirs(buildpath)
    os.chdir(buildpath)
    ret = os.system('CC='+ccompiler+' CXX='+cxxcompiler+' cmake ../../ '+addopt+' -DCMAKE_BUILD_TYPE='+build_type)
    if ret != 0:#pass through cmake failed.
        os.chdir("../../")
        return
    ret = os.system('make -j 2')
    if ret != 0: raise Exception("build error at"+buildpath)
    ret = os.system('ctest --output-on-failure')
    if ret != 0: raise Exception("test error at"+buildpath)
    os.chdir("../../")

def build_with_target_compiler():
    for i,compiler in enumerate(test_compilers):
        build_and_exec_test(compiler,"Debug",str(i))
        build_and_exec_test(compiler,"Release",str(i))

def build_msvc_and_exec_test(msvcver,build_type):
    buildpath = '_build/'+msvcver[0]
    if not os.path.exists(buildpath):
        os.makedirs(buildpath)
    os.chdir(buildpath)
    ret = os.system('cmake ../../ -G "'+msvcver[1]+'" '+msvcver[2])
    if ret != 0:
        os.chdir("../../")
        return
    ret = os.system('cmake --build . --config '+build_type)
    if ret != 0: raise Exception("build error at"+buildpath)
    ret = os.system('ctest --output-on-failure -C '+build_type)
    if ret != 0: raise Exception("test error at"+buildpath)
    os.chdir("../../")

def build_with_msvc_ver():
    for msvcver in test_msvc_vers:
        build_msvc_and_exec_test(msvcver,'Debug')
        build_msvc_and_exec_test(msvcver,'Release')



if os.name == 'nt':
    build_with_msvc_ver()
else:
    build_with_target_compiler()
