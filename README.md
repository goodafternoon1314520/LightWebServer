# LightWebServer

一个基于 Linux + epoll 的轻量级 HTTP Server，使用 C++ 开发。

## 项目介绍

这是一个从零开始实现的 Linux 高并发服务器项目，目标是深入理解：

- Linux 网络编程
- epoll 高并发模型
- HTTP 协议
- Reactor 模型
- C++ 后端工程开发

当前项目已实现：

- socket 网络编程
- epoll IO复用
- ET模式（边缘触发）
- 非阻塞 socket
- HTTP 请求解析
- 多客户端连接
- C++ 模块化开发
- CMake 工程化

---

## 当前已实现功能

### 1. epoll 事件驱动

使用：

```cpp
epoll_create
epoll_ctl
epoll_wait
```

实现 IO复用。

---

### 2. ET 模式

服务器使用：

```cpp
EPOLLIN | EPOLLET
```

提高高并发性能。

---

### 3. 非阻塞 socket

使用：

```cpp
fcntl(fd, F_SETFL, O_NONBLOCK)
```

避免线程阻塞。

---

### 4. HTTP 请求解析器

当前支持解析：

```http
GET /hello HTTP/1.1
```

已实现：

- method
- path
- version

解析结果示例：

```text
Method: GET
Path: /hello
Version: HTTP/1.1
```

---

### 5. 简单路由

当前支持：

| URL | 返回 |
|---|---|
| / | Welcome 页面 |
| /hello | Hello 页面 |
| 其他 | 404 页面 |

---

## 项目结构

```text
LightWebServer/
├── include/
│
│   ├── http/
│   │   ├── HttpConn.h
│   │   └── parser/
│   │       └── HttpRequest.h
│   │
│   └── server/
│       └── HttpServer.h
│
├── src/
│
│   ├── http/
│   │   ├── HttpConn.cpp
│   │   └── parser/
│   │       └── HttpRequest.cpp
│   │
│   ├── server/
│   │   └── HttpServer.cpp
│   │
│   └── main.cpp
│
├── build/
├── CMakeLists.txt
└── README.md
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

```text
http://127.0.0.1:8080
```

---

## 测试

### 首页

```text
http://127.0.0.1:8080
```

返回：

```html
<h1>Welcome LightWebServer</h1>
```

---

### hello 页面

```text
http://127.0.0.1:8080/hello
```

返回：

```html
<h1>Hello Page</h1>
```

---

### 404 页面

```text
http://127.0.0.1:8080/test
```

返回：

```html
<h1>404 Not Found</h1>
```

---

## 技术栈

- C++
- Linux Socket
- epoll
- ET模式
- 非阻塞 IO
- HTTP
- CMake
- Git

---

## 当前核心模块

| 模块 | 功能 |
|---|---|
| HttpServer | 管理 epoll 和事件循环 |
| HttpConn | 管理客户端连接 |
| HttpRequest | HTTP 请求解析 |

---

## 下一步计划

接下来准备实现：

- 静态文件服务器
- HTML 文件返回
- MIME 类型
- keep-alive
- HTTP 状态机
- ThreadPool
- Reactor 模型
- MySQL连接池
- 日志系统

---

## 学习目标

通过该项目深入理解：

- Linux 高并发服务器原理
- epoll ET模式
- HTTP协议
- Reactor模型
- C++ 后端开发
- Linux 工程化开发




