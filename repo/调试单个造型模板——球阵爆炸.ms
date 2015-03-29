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
	horizSphereSynPos initial_pos  --球初始状态在最高位置 ，0位
	horizLinePos initial_pos         --框初始状态在最高位置 ，0位

	-----------------------------------框炸开---------------------------------------
	--到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos         	
	FrameTime += 15
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos

	--球框爆炸
	FrameTime += 10
	randomLinePos run_limit_pos run_initial_pos
	randomSpherePos run_limit_pos run_initial_pos
	
	--下落
	FrameTime += 180
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	-----------------------------------框不炸开---------------------------------------
	--到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	--horizLinePos middle_pos  
	horizLinePos run_initial_pos	
	FrameTime += 15
	horizSphereSynPos middle_pos   
	--horizLinePos middle_pos

	--球框爆炸
	FrameTime += 10
	randomSpherePos run_limit_pos run_initial_pos
	--randomLinePos run_limit_pos run_initial_pos
	
	--下落
	FrameTime += 180
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	-----------------------------------球底部炸开---------------------------------------
	--球爆炸
	FrameTime += 10
	--randomLinePos run_limit_pos run_initial_pos
	--randomSpherePos run_limit_pos run_initial_pos
	--boomDownSpherePos pos dur delay hor 爆炸高度 下落时间 基准
	FrameTime = boomDownSpherePos run_limit_pos 180 60 run_initial_pos
	
	
	--造型准备
	--球运行至顶端，框运行至底部
	
	--球阵炸开
	--FrameTime += 10  --球阵爆炸时间
	--boomDownSpherePos pos vel hor
	--boomDownSpherePos run_limit_pos 10 middle_pos
	--horizLineDisPos run_limit_pos run_initial_pos
	--FrameTime = randomHoldSpherePos run_limit_pos run_initial_pos 10
	--horizLineDisPos run_limit_pos run_initial_pos
	
	--球框全部落下
	--FrameTime += 240
	--horizSphereSynPos run_initial_pos
	--horizLinePos run_initial_pos
	--randomSpherePos run_limit_pos run_initial_pos
	--horizLineDisPos run_limit_pos run_initial_pos
	
	--FrameTime += 30
	--randomSpherePos run_limit_pos run_initial_pos
	--horizLineDisPos run_limit_pos run_initial_pos
	
	--FrameTime += 120
	--horizSphereSynPos middle_pos
	--horizLinePos middle_pos

	
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