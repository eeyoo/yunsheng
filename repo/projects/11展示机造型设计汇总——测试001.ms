--==============================================================================
--脚本意图：修改0303代码的框架，兼容新的框架
--版本 1.0
--日期 2015-3-21
--作者 吴飞林
--==============================================================================

--加载框模型文件
--fileName = "C:\Users\feilin\Documents\3dsMax\workspace\repo\00框阵模板.max"
--loadMaxFile fileName 

--为放样赋予变量名称
num = 4
LineArray = #($Loft001, $Loft002, $Loft003, $Loft004)

--创建球阵模型
fileIn "create_sphere_4x8_array.ms" quiet: true

--执行造型函数库
fileIn "frameLib.ms"
fileIn "sphereLib.ms"



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
	--==============================节目1=========================================--
	
	--==============================================================================
	--造型001 - 球阵被框随机拉开
	--==============================================================================
	--启动
	FrameTime += 240
	--randomSpherePos (run_limit_pos-50)  (run_initial_pos+50 )
	horizLineDisPos run_limit_pos  run_initial_pos 
	--停止5帧
	FrameTime = randomHoldSpherePos (run_limit_pos-50)  (run_initial_pos+50) 5
	horizLineDisPos run_limit_pos  run_initial_pos
	
	
	FrameTime
	
)

