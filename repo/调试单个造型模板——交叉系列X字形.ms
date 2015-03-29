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
	--球阵X交叉
	--==============================================================================
	--到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	
	-----------------------------------横向X交叉-----------------------------------
	--1 打开
	FrameTime += 120
	rateXCOESpherePos 500 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 交叉
	FrameTime += 120
	rateXCOESpherePos -500 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--3 交叉
	FrameTime += 120
	rateXCOESpherePos 500 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--4 交叉
	FrameTime += 120
	rateXCOESpherePos -500 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	
	--5 弹簧再次压缩
	FrameTime += 60
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	
	-----------------------------------纵向X交叉-----------------------------------
	--1 打开
	FrameTime += 120
	rateYCOESpherePos 500 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 交叉
	FrameTime += 120
	rateYCOESpherePos -500 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--3 交叉
	FrameTime += 120
	rateYCOESpherePos 500 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--4 交叉
	FrameTime += 120
	rateYCOESpherePos -500 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--5 弹簧再次压缩
	FrameTime += 60
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	
	-----------------------------------横向X交叉-----------------------------------
	--1 打开
	FrameTime += 120
	rateXCOESpherePos 400 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 交叉
	FrameTime += 120
	rateXCOESpherePos -400 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--3 交叉
	FrameTime += 120
	rateXCOESpherePos 400 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--4 交叉
	FrameTime += 120
	rateXCOESpherePos -400 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	
	--5 弹簧再次压缩
	FrameTime += 60
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	--FrameTime += 5
	--horizSphereSynPos middle_pos           --球横向X交叉
	--horizLinePos middle_pos 
	
	-----------------------------------纵向X交叉-----------------------------------
	--1 打开
	FrameTime += 120
	rateYCOESpherePos 400 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 交叉
	FrameTime += 120
	rateYCOESpherePos -400 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--3 交叉
	FrameTime += 120
	rateYCOESpherePos 400 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--4 交叉
	FrameTime += 120
	rateYCOESpherePos -400 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--5 弹簧再次压缩
	FrameTime += 60
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	
	FrameTime
	
)