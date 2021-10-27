# YBB 语言解释器
本repo包含了一个YBB语言的REPL。

![](ybb.png)

## 简述
YBB语言一种简单的、可以用最小的编译器来实现的、符合图灵完全思想的编程语言（变种`brainfuck`）。这种语言由八种运算符构成：

| 指令  | 含义                                                          |
|------|---------------------------------------------------------------|
|`yby` | 指针加一                                                      |
|`byb` | 指针减一                                                      |
|`yyb` | 指针指向的字节的值加一                                        |
|`bby` | 指针指向的字节的值减一                                        |
|`ybb` | 输出指针指向的单元内容（ASCII码）                             |
|`byy` | 输入内容到指针指向的单元（ASCII码）                           |
|`yyy` | 如果指针指向的单元值为零，向后跳转到对应的bbb指令的次一指令处   |
|`bbb` | 如果指针指向的单元值不为零，向前跳转到对应的yyy指令的次一指令处 |

YBB程序可以用下面的替换方法翻译成C语言（假设ptr是char *类型）：

| YBB   | C                   |
|-------|---------------------|
| `yby` | `++ptr;`            |
| `byb` | `--ptr;`            |
| `yyb` | `++*ptr`            |
| `bby` | `--*ptr;`           |
| `ybb` | `putchar(*ptr);`    |
| `byy` | `*ptr = getchar();` |
| `yyy` | `while (*ptr) {`    |
| `bbb` | `}`                 |

## 如何编译（UNIX-like环境）
```shell
> mkdir build
> cd build && cmake .. && make
```

## Hello World 程序
下面是一个示例程序
```ybb
yby yby yby yby yby yby yby yby yby yby yyy yyb yby yby yby yby yby yby yby yby yby yby yby yby yyb yby yby yby yby yby yby yby yby yby bby bby byb bbb yyb yby ybb yyb yby yby yby yby yby yby yby yby ybb ybb 
```

输入ybb REPL后得到下面的输出:

```
ybb
```

## 运行方法

直接运行可执行程序，将以REPL模式运行。

后跟文件名，解释可执行ybb语言程序。

```shell
> ./ybb ybb.ybb
ybb
```