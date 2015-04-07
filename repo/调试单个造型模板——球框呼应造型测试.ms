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
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	--==============================================================================
	--节目1造型003 - 球阵框阵上下对接
	--==============================================================================
	--造型准备
	FrameTime += 120
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	
	--球框框阵向上运行呼应
	FrameTime += 120
	linearForwardPos 300 run_initial_pos       --linearForwardPos h hor
	
	--暂停15帧
	FrameTime = randomHoldSpherePos (run_initial_pos + 300) run_limit_pos 30
	linearForwardPos 300 run_initial_pos       --linearForwardPos h hor
	
	--球阵收回零位，框阵到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	
	--==============================================================================
	--节目2造型003 - 球阵框阵上下对接
	--==============================================================================
	--框上下至顶端
	FrameTime += 120
	horizLinePos run_limit_pos
	horizSphereSynPos run_initial_pos
	FrameTime += 5
	horizLinePos run_limit_pos
	horizSphereSynPos run_initial_pos
	
	
	--框阵向下运行
	--球框120帧完成造型
	FrameTime += 120
	linearForwardPos -300 run_limit_pos        --linearForwardPos h hor
	FrameTime = randomHoldSpherePos run_initial_pos (run_initial_pos + 700) 30
	--球框保持30帧
	linearForwardPos -300 run_limit_pos        --linearForwardPos h hor
	
	--球阵收回零位，框阵到达平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	

	
	FrameTime
	
)