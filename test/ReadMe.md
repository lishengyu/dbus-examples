# 参考记录

# 1 编译依赖

​	如果在编译过程中出现报错信息，例如：

```c
No package 'dbus-glib-1' found
dbus-signal.c:13:10: fatal error: glib.h: 没有那个文件或目录
 #include <glib.h>
```

​	说明有编译依赖需要安装

```c
apt-cache search dbus-glib
sudo apt-get install libdbus-glib-1-dev
```

# 2 函数说明

## 2.1 The Main Event Loop

### 2.1.1 g_main_loop_new()

#### 2.1.1.1 函数原型

```c
GMainLoop * g_main_loop_new(GMainContext *context, gboolean is_running);
```

#### 2.1.1.2 参数说明

| 参数       | 说明                                                         |
| ---------- | ------------------------------------------------------------ |
| context    | 一个GMainContext（如果是NULL，将会使用默认的context）；      |
| is_running | 设置成TRUE表示循环正在运行，这不是很重要，因为调用g_main_loop_run()会将其设置为TRUE。 |
| return     | 一个新的GMainLoop结构；                                      |

#### 2.1.1.3 函数说明

​	创建一个新的GMainLoop结构；

### 2.1.2 g_main_loop_run()

#### 2.1.2.1 函数原型

```c
void                g_main_loop_run                     (GMainLoop *loop);
```

#### 2.1.2.2 函数参数

| 参数 | 说明      |
| ---- | --------- |
| loop | GMainLoop |

#### 2.1.2.3 函数说明

​	运行一个主循环，直到在循环中调用g_main_loop_quit()。如果在循环的GMainContext的线程中调用这个函数，它将处理来自循环的事件，否则它将只是等待。

### 2.1.3 g_main_loop_quit()

#### 2.1.3.1 函数原型

```c
void                g_main_loop_quit                    (GMainLoop *loop);
```

#### 2.1.3.2 函数参数

| 参数 | 说明      |
| ---- | --------- |
| loop | GMainLoop |

#### 2.1.3.3 函数说明

​	停止GMainLoop运行。任何对g_main_loop_run()的调用都会返回。注意，在调用g_main_loop_quit()时已经分派的源仍然会被执行。

### 2.1.4 g_timeout_add()

#### 2.1.4.1 函数原型

```c
guint g_timeout_add (guint interval, GSourceFunc function, gpointer data);	
```

#### 2.1.4.2 函数参数

| 参数     | 说明                           |
| -------- | ------------------------------ |
| interval | 调用函数的时间间隔，单位为ms； |
| function | 调用的函数；                   |
| data     | 传递给function的参数；         |
| Return   | 事件源ID（大于0）；            |

#### 2.1.4.3 函数说明

​	设置需要周期调用的函数，使用默认的优先级G_PRIORITY_DEFAULT。函数将被反复调用，直到返回FALSE，这个时候超时将自动侧小并且这个函数不会再被调用。第一次的函数调用将会等待一个超时时间。

​	注意由于处理其他事件源，超时函数可能超时。所以不应依赖他们来做准确的事件。每次调用timeout函数后，将根据当前时间和给定的间隔重新计算下一个超时的时间(它不会试图“追赶”由于延迟而丢失的时间)。如果你想让计时器在“秒”范围内并且不关心第一次调用计时器的确切时间，可以使用g_timeout_add_seconds()函数;这个功能允许更多的优化和更有效的系统电源使用。这将使用g_timeout_source_new()在内部创建一个主循环源，并使用g_source_attach()将其附加到主循环上下文。如果需要更好的控制，您可以手动执行这些步骤。

