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
	horizLineBasePos 400 middle_pos
	FrameTime += 5
	horizLineBasePos 400 middle_pos
	
	--框阵启动波动
	--奇偶组波动参数 振幅 次数 周期 延时 基准
	sinLineOddDelayPos 150 2 240 30 (run_limit_pos - 100)
	sinLineEvenDelayPos -150 2 240 30 (run_initial_pos + 100)
	
	------------------------------球阵中心波动---------------------------------------
	--sinSphereCPos 振幅 周期数 周期时间 基准面 振幅增量
	FrameTime = sinSphereCPos 200 2 240 middle_pos 0   
	horizLineDisPos (middle_pos + 450) (middle_pos - 450)
	
	--------------------------------球阵逐行波---------------------------------------
	--1、2框对称波动
	--sinFirstTwoLinePos 振幅 位置 次数 周期 基准高
	sinFirstTwoLinePos 50 450 2 160 middle_pos
	
	--逐行波
	FrameTime = sinSphereSingleXNPos 300 1 160 5 middle_pos      --sinSpherePos amp count dur delay hor
	horizLineDisPos (middle_pos+450) (middle_pos-450)

	
	--------------------------------球阵斜波---------------------------------------
	--3、4框对称波动
	--sinLastTwoLinePos 振幅 位置 次数 周期 基准高
	sinLastTwoLinePos 50 450 2 120 middle_pos
	
	--斜波
	FrameTime = sinSphereRatePos 200 2 120 10 middle_pos 100 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	

	---------------------------------球阵射线波后端---------------------------------------
	--奇数组框在中平面之上逐个波动，偶数组框在中平面之下逐个波动，方向相反
	
	--奇偶组波动参数 振幅 次数 周期 延时 基准
	sinLineOddDelayPos 100 2 240 15 (middle_pos + 400)        
	sinLineEvenDelayPos -100 2 240 15 (middle_pos - 400)
	
	--X轴向后端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 150 1    --横向变化振幅波形
	
	
	---------------------------------球阵射线波前端---------------------------------------
	--FrameTime += 120
	--球阵回到中平面后120帧，奇数组下行到中平面之下波动，偶数组上行至中平面之上波动
	
	--奇偶组波动参数 振幅 次数 周期 延时 基准
	--sinLineOddDelayPos -100 1 120 30  (run_initial_pos + 100)
	--sinLineEvenDelayPos 100 1 120 30 (run_limit_pos - 100)
	 
	--X轴向前端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 150 2    --横向变化振幅波形
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	---------------------------------球阵奇偶行波---------------------------------------
	--FrameTime += 120
	--球阵回到中平面后120帧，--奇数组框在中平面之上逐个波动，偶数组框在中平面之下逐个波动，方向相反
	--sinLineOddDelayPos 100 2 120 15 (middle_pos - 400)         
	--sinLineEvenDelayPos -100 2 120 15 (middle_pos + 400)
	
	--FrameTime = sinBXOESpherePos 100 2 120 10 middle_pos 100   	   --纵向平分两组反向波动
	sinBXOESpherePos 100 2 120 10 middle_pos 100   	   --纵向平分两组反向波动
	sinLineOddDelayPos 100 2 120 15 (middle_pos - 400)         
	FrameTime = sinLineEvenDelayPos -100 2 120 15 (middle_pos + 400)
	
	--球阵回到中平面后60帧框阵回到中平面
	FrameTime += 60
	horizLineDisPos middle_pos middle_pos
	
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 
	

	
	FrameTime
	
)