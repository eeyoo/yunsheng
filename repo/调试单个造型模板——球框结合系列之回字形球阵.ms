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
	
	--FrameTime = LineDelayPos -700 200 6 240 120   --LineDelayPos 起始位置 位置增量 变化次数 延时时间  保持时间
	--LineDelayPos -700 250 4 40 90   --LineDelayPos 起始位置 位置增量 变化次数 延时时间  保持时间
	--FrameTime = sinSphereYPos 200 4 120 10 -700 200      --sinSphereYNPos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量
	
	--FrameTime = SphereRectDelayPos 400 60 15 -700       --SphereRectDelayPos 位置 运行时间 延时时间 中心高
	
	--FrameTime += 120
	--SphereRectDelayPos 700 -700
	FrameTime = SphereRectInDelayPos 400 6 120 -700  --SphereRectInDelayPos amp count dur hor 
	
	
	FrameTime
	
)