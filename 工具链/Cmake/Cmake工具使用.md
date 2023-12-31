#Cmake
所有工具使用均基于Linux环境下，Windows环境同理。
# 1. 安装
```shell
[root@LamberttLiu bak]# yum install cmake -y

# 省略过程，最后回显
Installed:
  cmake-3.20.2-4.el8.x86_64             cmake-data-3.20.2-4.el8.noarch           cmake-filesystem-3.20.2-4.el8.x86_64
  cmake-rpm-macros-3.20.2-4.el8.noarch  emacs-filesystem-1:26.1-7.el8.noarch     libuv-1:1.41.1-1.el8_4.x86_64
  make-1:4.2.1-10.el8.x86_64            vim-filesystem-2:8.0.1763-16.el8.noarch

Complete!
```
查看版本:
```shell
[root@LamberttLiu /]# cmake --version
cmake version 3.20.2
```

# 2. 新建构建工程：一个简单的例子
目录如下：
```shell
.
├── build
├── CMakeLists.txt
└── main.cpp
```
CmakeLists.txt 这个名称是一般默认固定的，最基础的参数需要满足以下：
```cmake
# 指定最低执行的Cmake版本
cmake_minimum_required(VERSION 3.20)
# 指定工程名
project(ProjDemo)
# 指定构建
add_executable(ProjDemo main.cpp)
```

执行cmake构建：
```bash
# 执行将构建文件存放在 ./build/目录下
[root@LamberttLiu /]# cmake -B build
-- The C compiler identification is GNU 8.5.0
-- The CXX compiler identification is GNU 8.5.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/Proj_demo/build
```

进入构建目录下：
```shell
[root@LamberttLiu build]# tree -L 2
.
├── CMakeCache.txt
├── CMakeFiles
│   ├── 3.20.2
│   ├── cmake.check_cache
│   ├── CMakeDirectoryInformation.cmake
│   ├── CMakeOutput.log
│   ├── CMakeTmp
│   ├── Makefile2
│   ├── Makefile.cmake
│   ├── progress.marks
│   ├── ProjDemo.dir
│   ├── Proj.dir
│   └── TargetDirectories.txt
├── cmake_install.cmake
└── Makefile
```
执行`make`命令：
```shell
[root@LamberttLiu build]# make
Consolidate compiler generated dependencies of target ProjDemo
[ 50%] Building CXX object CMakeFiles/ProjDemo.dir/main.cpp.o
[100%] Linking CXX executable ProjDemo
[100%] Built target ProjDemo
```
即生成 `ProjDemo `可执行文件：
```shell
[root@LamberttLiu build]# ls
CMakeCache.txt  CMakeFiles  cmake_install.cmake  Makefile  ProjDemo

[root@LamberttLiu build]# file ProjDemo
ProjDemo: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=bfeff12d88398f4e7aae1adae8e8bddf5b33e9a2, not stripped

[root@LamberttLiu build]# ./ProjDemo
hello world!
```

# 3. 基本语法
Cmake工具由以下五个可执行文件组成：`cmake`、`ctest`、 `cpack`、 `cmake-gui`、 `ccmake`；  
`*.cmake` 文件，是可以直接被执行的文件，可以使用`.cmake`文件直接进行调试。
## message 打印输出
`cmake -P *.cmake` 可以直接执行命令：
demo.cmake：
```cmake
cmake_minimum_required(VERSION 3.20)

message("demo text")
message("hello

world")
message(${CMAKE_VERSION})
```
执行命令打印：
```shell
[root@LamberttLiu Proj_demo]# cmake -P demo.cmake
demo text
hello

world
3.20.2
```

## set 赋值
```cmake
# 给单个变量赋值
set (var_1 1)
message(${var_1})
set (list_1 a b c)
message("list_1: " ${list_1})
 
# 设置环境变量
set(ENV{CXX} "g++")
message($ENV{CXX})

# 取消设置
unset(ENV{CXX})
```

输出：
```shell
1
list_1: abc
g++
```

## 流程控制
```cmake
# 条件控制语法如下，满足条件的分支将会被执行
if(<condition>)
	<commands>
elseif(<condition>)
	<commands>
else()
	<commands>
endif()
```
举例：
```cmake
cmake_minimum_required(VERSION 3.20)

set(var 3)

if(${var}==1)
	message(“var == 1”)
elseif(${var}==2)
    message(“var == 2”)
else()
    message(“var == 3”)
endif()
```
打印输出：
```
“var==3”
```

