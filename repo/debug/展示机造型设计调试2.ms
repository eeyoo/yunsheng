--==============================================================================
--脚本意图：修改0303代码的框架，兼容新的框架
--版本 1.0
--日期 2015-3-21
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
	--造型001 - 球阵和框阵保持同一平面
	--==============================================================================
	--球阵和框阵保持零位
	FrameTime += 5
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	
	--==============================================================================
	--造型003 - 球阵框阵上下对接
	--==============================================================================
	
	--球运行至顶端，框运行至底部
	FrameTime += 120
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	FrameTime += 15
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	
	--球框框阵向上运行呼应
	FrameTime += 120
	randomSpherePos run_initial_pos run_limit_pos
	linearForwardPos middle_pos run_initial_pos       --linearForwardPos h hor
	
	--球阵收回零位，框阵到达平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	
	FrameTime
	
)

