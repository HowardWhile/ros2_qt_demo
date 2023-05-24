cmake_minimum_required(VERSION 3.8)
project(ros2_qt_demo)

# ------------------------------------------
# 使用 C++ 14
# ------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# ------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ------------------------------------------
# 設定編譯類型和相依套件 
# ------------------------------------------
# ros
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# ------------------------------------------
# 添加可執行文件 
# ------------------------------------------
add_executable(demo 
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
)

# ------------------------------------------
# 鏈接依賴項
# ------------------------------------------
# ros

# qt
target_link_libraries(demo 
  ${rclcpp_LIBRARIES} 
  Qt5::Core 
  Qt5::Gui
  Qt5::Widgets
)

# ------------------------------------------
# 包含其他包的標頭檔路徑
# ------------------------------------------
ament_target_dependencies(demo 
  rclcpp
  std_msgs
)

# ------------------------------------------
# 設置自動MOC、UIC和RCC (與QT相關)
# ------------------------------------------
set_target_properties(demo PROPERTIES AUTOMOC ON)
set_target_properties(demo PROPERTIES AUTOUIC ON)
set_target_properties(demo PROPERTIES AUTORCC ON)
# ------------------------------------------

# 安装可执行文件
install(TARGETS demo
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
