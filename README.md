# NeoCrowd
一个用来统计视频监控下的人流量的Demo，使用YOLO或SSD或Vibe的方法进行识别人体，再用OpenCV Contrib的Tracking模块的MIL追踪器进行跟踪，并执行Reid。

### 运行环境
*OpenCV 3.4.7*

*OpenCV Contrib 3.4.7*

*QT 5.14.2*

*Python 3.7*

*Ubuntu 18.04*

### 目录说明
1. NeoCrowdLib 可以编译成so库的project
2. NeoCrowdClient 可以编译成桌面应用的project
3. Reid_Demo 行人Re-Identification的模块（Python代码，其中部分开源代码来源不可考）
4. TestVideo 来自 ```https://groups.inf.ed.ac.uk/vision/CAVIAR/CAVIARDATA1/``` 的测试视频
