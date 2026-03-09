# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -g

# 所有源文件
SRCS = \
    main.c \
    userInfo.c \
    rest.c \
    admin_list.c \
    admin_biz.c \
    admin_ui.c \
    yxl_daka.c \
    yxl_user_use.c \
	IO.c

# 目标文件（自动生成）
OBJS = $(SRCS:.c=.o)

# 最终可执行文件名
TARGET = project

# 默认目标：编译所有
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# 编译每个 .c 为 .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译产物
clean:
	rm -f $(OBJS) $(TARGET)
