造型库函数实现原则：
1. 新造型或者改进造型以新造型函数方式扩展
2. 库函数尽可能简单，造型分解越细越好
3. 不要在单个函数刻意实现复杂造型

框阵造型函数
==============

以下造型均为同动系列
函数名          参数
horizLinePos pos  在关键帧到达指定位置，传入位置参数
randomLinePos rmin rmax    在关键帧随机分布于指定上下限
horizLineDisPos pos1 pos2   对奇数偶数标号框分别指定位置pos1、位置pos2
linearForwardPos pos hor      形成间距相等的锥形造型，高度pos，基准高度hor
parabForwardPos a hor          抛物线间距分布，系数a决定高度，基准高度hor
sinForwardPos amp hor          1/4正弦分布，振幅高度amp，基准高度hor
linearSymAPos pos d hor       奇偶对称分布，偏距高度pos，单边框间距d，基准高hor(内凹外凸)
linearSymBPos pos d hor        奇偶对称分布，偏距高度pos，单边框间距d，基准高hor(内凸外凹)

以下造型为不同动系列
函数名          参数
horizLineDelayPos pos1 pos2 dur delay hold   整体位置pos1向位置pos2变化，单元运行时间dur，延时delay，保持最终造型时间hold
linearLineDelayPos pos1 pos2 dur delay hold  整体在位置pos1和pos2线性分布，单元运行时间dur，延时delay，保持最终造型时间hold
sinLineLoopDelayPos amp count dur delay hor 整体作周期性波动，波动幅度amp，波动周期dur，延时delay，基准高hor
LineSingleLoopDelayPos pos dur delay hor       由内部框开始跳动的效果，高度pos，上下跳动时间dur，延时delay，基准高hor


球阵造型函数
===========
以下为一些静态造型系列
函数名                       参数
horizSphereSynPos pos        球阵整体在关键帧到达指定平面pos
rateSpherePos pos hor flag   斜平面，高度pos，基准高hor，起点标记flag(1表示左侧，2表示右侧)
rateXSpherePos a hor            横向塔形造型，高度pos，基准高hor
rateYSpherePos a hor            纵向塔形造型，高度pos，基准高hor
pyramidSpherePos a b hor    金字塔造型
randomSpherePos rmin rmax    随机分布，上下限位rmax，rmin
paraboSpherePos a hor         抛物面（王工称之为网床面），系数a决定高度，基准高hor
horseSpherePos a hor           马鞍面
bossSpherePos a hor             凹凸面，球阵数目太少，效果不佳
chairSpherePos a hor           躺椅造型
warpSpherePos a hor            扭曲面
cornerSpherePos a hor flag     对角布悬面


以下为波动造型系列
sinSphereSingleXPos amp count dur delay hor da       球阵沿X轴向逐个延时启动正弦波动
sinSphereSingleYPos amp count dur delay hor da       球阵沿X轴向逐个延时启动正弦波动
球阵X轴行波
sinSphereXPos amp count dur delay hor da              
球阵X轴行波， 振幅与行号呈线性关系
sinSphereRateXPos amp count dur delay hor da direct 
球阵Y轴行波
sinSphereYPos amp count dur delay hor da              
球阵Y轴行波， 振幅与行号呈线性关系
sinSphereRateYPos amp count dur delay hor da direct 
球阵斜波
sinSphereRatePos amp count dur delay hor da direct
球阵由中心启动延时效果正弦波动
sinSphereCPos amp count dur hor da

rateXOESpherePos a range hor

rateYOESpherePos a range hor
球阵沿Y轴方向分为2部分作相反正弦波动
sinBXOESpherePos amp count dur delay hor da


sinXOESpherePos amp count dur hor

sinYOESpherePos amp count dur hor

sinXYOESpherePos amp count dur hor




延时效果
horizSphereASynDelayPos pos1 pos2 range delay







