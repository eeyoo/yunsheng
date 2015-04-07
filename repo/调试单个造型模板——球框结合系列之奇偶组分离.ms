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
	--球框奇偶两组
	--==============================================================================
	--造型准备
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	------------------------------------哑铃型-------------------------------------
	--CompositeOEAPos high pos hor
	FrameTime += 200
	CompositeOEAPos 300 100 middle_pos
	
	FrameTime += 200
	CompositeOEAPos -300 -100 middle_pos
	

	------------------------------------贝壳型-------------------------------------
	FrameTime += 200
	CompositeOEBPos 300 100 middle_pos
	
	FrameTime += 200
	CompositeOEBPos -300 -100 middle_pos
	
	FrameTime += 200
	CompositeOEBPos 300 -100 middle_pos
	
	--回中平面
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	

	
	FrameTime
	
)