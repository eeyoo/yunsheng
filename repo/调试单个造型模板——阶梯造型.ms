
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
--fileIn "show.ms"

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
	--造型006 - 球阵阶梯造型
	--==============================================================================
	-----------------------------------横向Z字形------------------------------------
	--1 同时到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 球阵形成阶梯形
	FrameTime += 120
	stairSpherePos 600 middle_pos
	
	FrameTime += 120
	stairSpherePos -600 middle_pos
	
	
	--==============================================================================
	--造型006 - 球阵阶梯波动造型
	--==============================================================================
	--1 同时到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--stairSinXSpherePos amp count dur delay hor
	FrameTime = stairSinXSpherePos 300 4 120 20 middle_pos
	
	
	
	
)	