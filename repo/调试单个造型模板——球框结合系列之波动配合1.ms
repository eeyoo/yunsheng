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
	--造型003 - 球阵波形展示
	--==============================================================================
	--框阵打开
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLineBasePos 400 middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLineBasePos 400 middle_pos
	
	
	------------------------------球阵中心波动---------------------------------------
	--框阵奇偶上下逐个波动
	--sinLineOddEvenDelayPos amp pos count dur delay hor
	sinLineOddEvenDelayPos 100 400 2 240 30 middle_pos
	
	--sinSphereCPos 振幅 周期数 周期时间 基准面 振幅增量
	FrameTime = sinSphereCPos 200 2 240 middle_pos 0   
	horizLineBasePos 400 middle_pos
	
	--------------------------------球阵逐行波---------------------------------------
	--框阵奇偶交换上下位置逐个波动
	--sinLineOddEvenDelayPos amp pos count dur delay hor
	sinLineFirstTwoPos 100 400 2 160 middle_pos                --运行时间 = 次数 x 周期 320

	--逐行波
	--sinSpherePos amp count dur delay hor
	FrameTime = sinSphereSingleXNPos 300 1 160 5 middle_pos    --运行时间 = 总延迟时间 + 次数 x 周期  320
	--horizLineBasePos 400 middle_pos
	
	--------------------------------球阵斜波---------------------------------------
	--1、2波动，3、4静止
	--sinLineFirstTwoPos amp pos count dur hor
	sinLineLastTwoPos 100 400 2 160 middle_pos
	
	--斜波
	FrameTime = sinSphereRatePos 200 2 120 10 middle_pos 100 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	

	---------------------------------球阵射线波后端---------------------------------------
	sinLineOddEvenDelayPos 100 400 2 120 30 middle_pos
	
	--X轴向后端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 150 1    --横向变化振幅波形
	--horizSphereSynPos middle_pos

	FrameTime += 60
	horizLineBasePos -400 middle_pos
	
	sinLineOddEvenDelayPos -100 -400 2 120 30 middle_pos
	
	--X轴向前端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 150 2    --横向变化振幅波形
	
	
	---------------------------------球阵奇偶行波---------------------------------------
	sinLineOddEvenDelayPos -100 -400 2 120 30 middle_pos
	
	
	FrameTime = sinBXOESpherePos 100 2 120 10 middle_pos 100   	   --纵向平分两组反向波动

	--球阵回到中平面后60帧框阵回到中平面
	FrameTime += 60
	horizSphereSynPos middle_pos 
	
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 
	

	
	FrameTime
	
)