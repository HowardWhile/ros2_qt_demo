# Readme

package 名稱為 `ros2_qt_demo`



**建立ros包**

```shell
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake ros2_qt_demo
```



**編譯測試**

```shell
cd ~/ros2_ws/
#colcon build
colcon build --packages-select=ros2_qt_demo
```



**用qt建立簡單的ui**

![image-20230524101307336](pic/readme/image-20230524101307336.png)

編譯系統記得選cmake

![image-20230524100800867](pic/readme/image-20230524100800867.png)

![image-20230524101719779](pic/readme/image-20230524101719779.png)



**UI檔案搬移**

![image-20230524111535853](pic/readme/image-20230524111535853.png)

