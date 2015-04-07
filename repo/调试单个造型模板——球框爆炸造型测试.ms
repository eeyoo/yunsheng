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
	--造型016 - 球框爆炸，球至中平面炸开随机延时下落，框在底部不动
	--==============================================================================
	--到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	--horizLinePos middle_pos  
	horizLinePos run_initial_pos	
	FrameTime += 15
	horizSphereSynPos middle_pos   
	--horizLinePos middle_pos

	--球框爆炸
	FrameTime += 30
	--60帧时间随机分布于整个行程，并hold住30帧
	FrameTime = randomHoldSpherePos run_initial_pos run_limit_pos 15
	
	--下落
	FrameTime += 180
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	--==============================================================================
	--节目2造型013 - 球框爆炸，球框在中平面一起炸开
	--==============================================================================
	--回中平面
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos         	
	FrameTime += 15
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos

	--球框爆炸
	FrameTime += 30
	--60帧时间框阵随机分布于整个行程，并hold住15帧
	--randomLineHoldPos rmin rmax hold 框阵随机分布 - 参数：最小位置 最大位置 保持时间
	randomLineHoldPos run_initial_pos run_limit_pos 15
	
	--60帧时间球阵随机分布于整个行程，并hold住15帧
	FrameTime = randomHoldSpherePos run_initial_pos run_limit_pos 15
	
	--下落
	FrameTime += 180
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos


	
	FrameTime
	
)