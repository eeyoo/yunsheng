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
down_limit_pos = -1300
middle_pos = (initial_pos + down_limit_pos)/2

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
	horizLineDisPos -200 -1100    
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLineDisPos -200 -1100
	
	--奇数框阵启动正弦波动
	sinLineOddDelayPos 100 4 240 30 -200   --sinLineOddDelayPos amp count dur delay hor
	--同时，偶数组框阵启动正弦波动
	FrameTime = sinLineEvenDelayPos -100 4 240 30 -1100
	
	/*
	--造型准备
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	
	
	--内圈球阵波动
	SphereRectInDelayPos  400 4 240 middle_pos    --SphereRectInDelayPos amp count dur hor 
	--延迟外圈球阵波动
	FrameTime += 15
	SphereRectOutDelayPos 400 4 240 middle_pos    --SphereRectInDelayPos amp count dur hor 
	--框阵延迟波动
	FrameTime += 15
	--FrameTime = sinLinePos 200 6 240 middle_pos   --sinLinePos 振幅 周期数 周期时间 中心高
	FrameTime = sinLineDelayPos 400 4 240 15 middle_pos  --sinLineDelayPos amp count dur delay hor
	*/
	
	FrameTime
	
)