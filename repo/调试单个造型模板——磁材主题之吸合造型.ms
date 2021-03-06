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
run_end_pos = 1150
limit_pos = 1300
middle_pos = (initial_pos+limit_pos)/2


FrameTime = 0
animate on
(
	
	--==============================================================================
	--开始造型 - 球阵和框阵保持同一平面
	--==============================================================================
	--球阵和框阵保持零位
	FrameTime += 15
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	/*
	--==============================================================================
	--造型001 - 球框至中平面打开
	--==============================================================================
	--1 运行至中平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--2 框阵打开，球随机打开
	FrameTime += 120
	randomSpherePos (run_initial_pos+50) (run_end_pos-50)
	horizLineDisPos run_end_pos run_initial_pos
	FrameTime += 15
	horizLineDisPos run_end_pos run_initial_pos
	
	--3 框阵压缩，球随机跳动
	FrameTime += 120
	randomSpherePos (run_initial_pos+150) (run_end_pos-150)
	FrameTime += 90
	randomSpherePos (run_initial_pos+250) (run_end_pos-250)
	FrameTime += 60
	randomSpherePos (run_initial_pos+350) (run_end_pos-350)
	FrameTime += 60
	randomSpherePos (run_initial_pos+450) (run_end_pos-450)
	FrameTime += 30
	horizSphereSynPos middle_pos
	FrameTime += 60
	horizLinePos middle_pos
	*/
	
	--==============================================================================
	--造型002 - 球框至中平面打开
	--==============================================================================
	-----------------------------------球在中平面不动-------------------------------
	--准备
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLineDisPos run_end_pos run_initial_pos
	--FrameTime += 5
	--horizSphereSynPos middle_pos
	--horizLineDisPos run_end_pos run_initial_pos
	
	--1 升1
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+200) (middle_pos-200)
	
	FrameTime += 60
	randomSpherePos (middle_pos+200) (middle_pos-200)
	horizLineDisPos (middle_pos+450) (middle_pos-450)
	
	--框慢速吸合
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+150) (middle_pos-150)
	
	--框慢速吸合
	FrameTime += 60
	randomSpherePos (middle_pos+100) (middle_pos-100)
	horizLineDisPos (middle_pos+450) (middle_pos-450)
	
	--框慢速吸合
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+150) (middle_pos-150)
	
	--框慢速吸合
	FrameTime += 30
	randomSpherePos (middle_pos+50) (middle_pos-50)
	horizLineDisPos (middle_pos+300) (middle_pos-300)
	
	--框慢速吸合
	FrameTime += 30
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	
	--4 快速吸合
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	/*	
	--1 运行至中平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--2 框阵打开，球随机打开
	FrameTime += 120
	randomSpherePos (middle_pos+450) (middle_pos-450)
	horizLineDisPos run_end_pos run_initial_pos
	--FrameTime += 15
	--horizLineDisPos run_end_pos run_initial_pos
	

	--3 慢速吸合
	FrameTime += 120
	randomSpherePos (middle_pos+300) (middle_pos-300)
	horizLineDisPos (run_end_pos-200) (run_initial_pos+200)
	--FrameTime += 15
	--horizLineDisPos (run_end_pos-200) (run_initial_pos+200)
	
	--3 慢速吸合
	FrameTime += 120
	randomSpherePos (middle_pos+300) (middle_pos-300)
	horizLineDisPos (run_end_pos-400) (run_initial_pos+400)
	
	--4 快速吸合
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	*/
	
	-----------------------------------球在中平面不动------------------------------------
	
	FrameTime
	
)

