# Compiler và flags
CC = gcc
CFLAGS = -Wall -std=c11 -I$(INCLUDE_DIR)
LDFLAGS = 

# Phát hiện hệ điều hành
ifeq ($(OS),Windows_NT)
    # Windows
    RM = del /Q /F
    RMDIR = rmdir /S /Q
    MKDIR = if not exist
    MKDIR_CMD = mkdir
    PATH_SEP = \\
    EXE_EXT = .exe
else
    # Linux/Mac
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
    MKDIR_CMD = 
    PATH_SEP = /
    EXE_EXT = 
endif

# Thư mục
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin
RESOURCE_DIR = resources

# Tên file thực thi
TARGET = $(BIN_DIR)/student_manager$(EXE_EXT)

# Tìm tất cả file .c trong thư mục src
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Chuyển .c thành .o trong thư mục build
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Tìm tất cả file .h trong include
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# Màu sắc cho output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m # No Color

# Target mặc định
all: $(TARGET)
	@echo "$(GREEN)✓ Build thành công!$(NC)"
	@echo "$(YELLOW)Chạy chương trình: ./$(TARGET)$(NC)"

# Tạo file thực thi
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "$(YELLOW)Linking...$(NC)"
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Biên dịch file .c thành .o (phụ thuộc vào headers)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# Tạo các thư mục cần thiết
$(BUILD_DIR):
	@echo "$(BLUE)Creating $(BUILD_DIR)/$(NC)"
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	@mkdir -p $(BUILD_DIR)
endif

$(BIN_DIR):
	@echo "$(BLUE)Creating $(BIN_DIR)/$(NC)"
ifeq ($(OS),Windows_NT)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
else
	@mkdir -p $(BIN_DIR)
endif

# Khởi tạo cấu trúc project
init:
	@echo "$(BLUE)Initializing project structure...$(NC)"
ifeq ($(OS),Windows_NT)
	@if not exist $(SRC_DIR) mkdir $(SRC_DIR)
	@if not exist $(INCLUDE_DIR) mkdir $(INCLUDE_DIR)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	@if not exist docs mkdir docs
	@if not exist $(RESOURCE_DIR) mkdir $(RESOURCE_DIR)
	@if not exist $(RESOURCE_DIR)\data mkdir $(RESOURCE_DIR)\data
	@if not exist $(RESOURCE_DIR)\docs mkdir $(RESOURCE_DIR)\docs
	@if not exist tests mkdir tests
	@if not exist scripts mkdir scripts
else
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(INCLUDE_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p docs
	@mkdir -p $(RESOURCE_DIR)/data
	@mkdir -p $(RESOURCE_DIR)/docs
	@mkdir -p tests
	@mkdir -p scripts
endif
	@echo "$(GREEN)✓ Project structure created!$(NC)"

# Dọn dẹp file biên dịch
clean:
	@echo "$(RED)Cleaning build artifacts...$(NC)"
ifeq ($(OS),Windows_NT)
	@if exist $(BUILD_DIR) $(RMDIR) $(BUILD_DIR)
	@if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
else
	@$(RMDIR) $(BUILD_DIR) $(BIN_DIR)
endif
	@echo "$(GREEN)✓ Cleaned!$(NC)"

# Dọn dẹp toàn bộ (bao gồm cả file data tạm)
distclean: clean
	@echo "$(RED)Deep cleaning...$(NC)"
	find . -name "*.o" -delete
	find . -name "*.exe" -delete
	find . -name "*.out" -delete
	find . -name "*~" -delete
	@echo "$(GREEN)✓ Deep cleaned!$(NC)"

# Build lại từ đầu
rebuild: clean all

# Chạy chương trình
run: $(TARGET)
	@echo "$(GREEN)Running student manager...$(NC)"
	@echo "$(BLUE)================================$(NC)"
	./$(TARGET)

# Debug mode (thêm flag -g)
debug: CFLAGS += -g -DDEBUG
debug: clean $(TARGET)
	@echo "$(GREEN)✓ Debug build completed!$(NC)"
	@echo "$(YELLOW)Run with GDB: gdb ./$(TARGET)$(NC)"

# Release mode (tối ưu hóa)
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)
	@echo "$(GREEN)✓ Release build completed!$(NC)"

# Kiểm tra cú pháp
check:
	@echo "$(YELLOW)Checking syntax...$(NC)"
	$(CC) $(CFLAGS) -fsyntax-only $(SOURCES)
	@echo "$(GREEN)✓ No syntax errors!$(NC)"

# Kiểm tra memory leaks (cần valgrind)
valgrind: debug
	@echo "$(YELLOW)Running valgrind...$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Đếm số dòng code
count:
	@echo "$(BLUE)=== Code Statistics ===$(NC)"
	@echo "$(YELLOW)Source files:$(NC)"
	@find $(SRC_DIR) -name "*.c" | wc -l
	@echo "$(YELLOW)Header files:$(NC)"
	@find $(INCLUDE_DIR) -name "*.h" | wc -l
	@echo "$(YELLOW)Total lines of code:$(NC)"
	@find $(SRC_DIR) $(INCLUDE_DIR) -name "*.[ch]" | xargs wc -l | tail -1

# Tạo backup
backup:
	@echo "$(YELLOW)Creating backup...$(NC)"
	tar -czf backup_$(shell date +%Y%m%d_%H%M%S).tar.gz \
		$(SRC_DIR) $(INCLUDE_DIR) $(RESOURCE_DIR) docs Makefile README.md
	@echo "$(GREEN)✓ Backup created!$(NC)"

# Hiển thị cấu trúc thư mục
tree:
	@echo "$(BLUE)=== Project Structure ===$(NC)"
	@tree -L 2 -I 'build|bin' || ls -R

# Hiển thị thông tin
info:
	@echo "$(BLUE)=== Project Information ===$(NC)"
	@echo "$(YELLOW)Project:$(NC) Student Manager"
	@echo "$(YELLOW)Sources:$(NC) $(SOURCES)"
	@echo "$(YELLOW)Headers:$(NC) $(HEADERS)"
	@echo "$(YELLOW)Objects:$(NC) $(OBJECTS)"
	@echo "$(YELLOW)Target:$(NC) $(TARGET)"
	@echo "$(YELLOW)Compiler:$(NC) $(CC)"
	@echo "$(YELLOW)Flags:$(NC) $(CFLAGS)"

# Cài đặt (copy binary vào /usr/local/bin - Linux/Mac)
install: release
	@echo "$(YELLOW)Installing...$(NC)"
	sudo cp $(TARGET) /usr/local/bin/
	@echo "$(GREEN)✓ Installed to /usr/local/bin/$(NC)"

# Gỡ cài đặt
uninstall:
	@echo "$(RED)Uninstalling...$(NC)"
	sudo rm -f /usr/local/bin/student_manager
	@echo "$(GREEN)✓ Uninstalled!$(NC)"

# Hiển thị trợ giúp
help:
	@echo "$(GREEN)=== Student Manager Makefile ===$(NC)"
	@echo ""
	@echo "$(YELLOW)Build Commands:$(NC)"
	@echo "  make             - Build project"
	@echo "  make run         - Build và chạy"
	@echo "  make debug       - Build phiên bản debug"
	@echo "  make release     - Build phiên bản release (tối ưu)"
	@echo "  make rebuild     - Build lại từ đầu"
	@echo ""
	@echo "$(YELLOW)Clean Commands:$(NC)"
	@echo "  make clean       - Xóa build artifacts"
	@echo "  make distclean   - Xóa toàn bộ file tạm"
	@echo ""
	@echo "$(YELLOW)Development:$(NC)"
	@echo "  make check       - Kiểm tra lỗi cú pháp"
	@echo "  make valgrind    - Kiểm tra memory leaks"
	@echo "  make count       - Đếm số dòng code"
	@echo ""
	@echo "$(YELLOW)Project:$(NC)"
	@echo "  make init        - Khởi tạo cấu trúc project"
	@echo "  make tree        - Hiển thị cấu trúc thư mục"
	@echo "  make info        - Hiển thị thông tin"
	@echo "  make backup      - Tạo backup"
	@echo ""
	@echo "$(YELLOW)Install (Linux/Mac):$(NC)"
	@echo "  make install     - Cài đặt vào hệ thống"
	@echo "  make uninstall   - Gỡ cài đặt"

# Phony targets
.PHONY: all clean distclean rebuild run debug release check valgrind \
        count backup tree info install uninstall help init