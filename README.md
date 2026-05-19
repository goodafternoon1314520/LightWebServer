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
