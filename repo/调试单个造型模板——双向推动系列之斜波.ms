--==============================================================================
--脚本说明：球阵和框阵结合造型设计
--版本 1.0
--日期 2015-3-20
--作者 吴飞林
--==============================================================================



--为放样赋予变量名称
num = 4
LineArray = #($Loft001, $Loft002, $Loft003, $Loft004)

--创建球阵模型
fileIn "create_sphere_4x8_array.ms" quiet: true

--执行造型函数库
fileIn "frameLib.ms"
fileIn "sphereLib.ms"


--执行节目单
fileIn "show.ms"

--==================================================================================
--造型说明
--最大演示范围，1.4米
--==================================================================================

initial_pos = 0
middle_pos = -700
down_limit_pos = -1400

FrameTime = 0

animate on
(
	--==============================================================================
	--球阵和框阵起始零位，停止0.5秒
	--==============================================================================
	FrameTime += 15
	horizSphereSynPos initial_pos   --球初始状态在最高位置 ，0位
	horizLinePos initial_pos         --框初始状态在最高位置 ，0位	
	
	--==============================================================================
	--球随机跳动，框上下分离不动
	--==============================================================================
	--造型准备
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	
	
	LineDisDelayPos 250 4 40 90 -700   --LineDisDelayPos d count dur hold hor 偏距位置增量 变化次数 运行时间  保持时间 中心高
	FrameTime = sinSphereRatePos 200 4 120 10 -700 200 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	
	/*
	--1.球阵逐行向上运行，同时框阵向上运行相同距离
	hor = middle_pos
	pos = middle_pos + 200
	FrameTime = SphereYDelayPos 200 60 15 hor   --SphereYDelayPos 高度 运行时间 延时时间 基准高
	horizLinePos pos
	
	--2.球阵逐行向下运行，同时框阵静止在上一位置
	hor += 200
	FrameTime = SphereYDelayPos -200 60 15 hor   --SphereYDelayPos 高度 运行时间 延时时间 基准高
	horizLinePos pos
	
	--3.球阵逐行向上运行，同时框阵静止在上一位置
	hor -= 200
	pos += 200
	FrameTime = SphereYDelayPos 400 90 15 hor   --SphereYDelayPos 高度 运行时间 延时时间 基准高
	horizLinePos pos
	
	--4.球阵逐行向下运行，同时框阵静止在上一位置
	hor += 400
	FrameTime = SphereYDelayPos -400 90 15 hor   --SphereYDelayPos 高度 运行时间 延时时间 基准高
	horizLinePos pos
	
	--5.球阵逐行向上运行，同时框阵静止在上一位置
	hor -= 400
	pos += 200
	FrameTime = SphereYDelayPos 600 120 15 hor   --SphereYDelayPos 高度 运行时间 延时时间 基准高
	horizLinePos pos
	
	--6.球阵逐行向下运行，同时框阵静止在上一位置
	hor += 600
	FrameTime = SphereYDelayPos -600 120 15 hor   --SphereYDelayPos 高度 运行时间 延时时间 基准高
	horizLinePos pos
	*/
	FrameTime
	
)