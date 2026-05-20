# LightWebServer

一个基于 Linux + epoll 的轻量级 HTTP 服务器

## 项目介绍

本项目基于C++11实现，采用epoll + 非阻塞IO 的 Reactor 模型，
支持 HTTP 请求解析，静态资源访问，多线程处理等功能。

项目目标：
- 学习 Linux 高并法网络编程
- 理解 Reactor 服务器模型
- 实践 epoll + 线程池 + HTTP 协议
- 实现一个轻量化 WebServer

项目持续迭代中

---

## 当前已实现：

- socket 网络编程
- epoll IO复用
- 非阻塞 socket
- ET （边缘触发）模式
- HTTP 响应
- 多客户端连接
- CMake工程化
- Git/GitHub 版本管理

---

## 后续计划实现：

- HttpConn 连接封装
- 静态资源服务器
- ThreadPool 线程池
- Reactor 模型
- HTTP 请求解析
- 定时器
- 登陆注册功能
- MySQL 连接池
- 日志系统
- 压力测试

---

## 技术栈

- C++11
- Linux
- epoll
- 非阻塞 socket
- ThreadPool
- HTTP
- CMake
- Git
- ET/LT

--- 

## 项目结构

```text
LightWebServer/
│
├── src/            # 源码
├── include/        # 头文件
├── webroot/        # 静态资源
├── logs/           # 日志
├── build/          # 编译目录
│
├── README.md
├── CMakeLists.txt
└── .gitignore
```

--- 

## 环境

- Ubuntu 22.04
- g++
- CMake

---

## 编译

```bash
mkdir build
cd build

cmake ..
make
```

---

## 运行

```bash
./server
```

浏览器访问：

```test
http://127.0.0.1:8080
```

---




