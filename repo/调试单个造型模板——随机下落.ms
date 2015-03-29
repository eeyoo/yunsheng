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
	
	
	---------------------------------------------------------------------------------
	--造型准备
	--球运行至顶端，框运行至底部
	FrameTime += 120
	horizSphereSynPos run_limit_pos
	--horizLinePos middle_pos
	horizLinePos run_initial_pos
	
	--球随机下落
	--randomDownNumSpherePos amp num dur delay hor 振幅 时长 次数 最长延时 基准 
	FrameTime = randomDownSpherePos 1000 400 100 run_initial_pos
	
	/*
	--造型准备
	--球运行至顶端，框运行至底部
	FrameTime += 120
	horizSphereSynPos run_limit_pos
	--horizLinePos middle_pos
	horizLinePos run_initial_pos
	
	--球随机下落
	--randomDownNumSpherePos amp num dur delay hor 振幅 时长 次数 最长延时 基准 
	FrameTime = randomDownSpherePos 1000 400 100 run_initial_pos
	--FrameTime = randomDownNumSpherePos 1000 200 8 100 run_initial_pos
	*/
	/*
	FrameTime += 90
	randomSpherePos run_initial_pos (run_limit_pos-200) 
	
	FrameTime += 90
	randomSpherePos run_initial_pos  (run_limit_pos-400) 
	
	FrameTime += 90
	randomSpherePos (run_limit_pos-200) run_initial_pos
	--randomDownSpherePos pos dur delay 高度 时间 逐个延时
	--downSpherePos 1000 120 5
	*/
	


	FrameTime
	
)