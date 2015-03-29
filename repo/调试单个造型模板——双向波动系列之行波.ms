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
--最大演示范围，1.3米
--==================================================================================

initial_pos = 0
run_initial_pos = 150
run_limit_pos = 1150
limit_pos = 1300
middle_pos = (initial_pos+limit_pos)/2

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
	
	--框阵基于中平面双侧间歇性运动
	--LineDisDelayPos 150 4 40 90 -700   --LineDisDelayPos d count dur hold hor 偏距位置增量 变化次数 运行时间  保持时间 中心高
	--球阵基于中平面启动行波
	--FrameTime = sinSphereXPos 150 6 120 10 -700 120     --ssinSphereYPos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量
	
	--LineAsyDisDelayPos 100 6 130 100 90 60 -700     --LineAsyDisDelayPos 偏距位置增量 变化次数 奇数组周期 偶数组周期  奇数组保持时间 偶数组保持时间 中心高
	--FrameTime = sinSphereYPos 100 6 120 10 -700 100     --sinSphereYPos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量
	
	--1 框阵奇偶分开
	FrameTime += 60
	horizLineBasePos 300 middle_pos 


	FrameTime += 30
	--sinLineOddDelayPos  100 6 120 30 (middle_pos+350)   --奇数框正弦波动 振幅 周期数 周期 延时启动时间 基准
	--sinLineEvenDelayPos 100 6 120 90 (middle_pos-350)
	sinLineAllOddDelayPos  100 6 240 30  (middle_pos+300)      --奇数框整体作正弦波动 amp count dur delay hor
	sinLineAllEvenDelayPos -100 6 240 90  (middle_pos-300)      --奇数框整体作正弦波动 amp count dur delay hor
	
	--3 球阵启动列波
	FrameTime = sinSphereXNPos 300 6 120 10 middle_pos
	

	FrameTime
	
)