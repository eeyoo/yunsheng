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
	--造型013 - 双向推动之行波
	--==============================================================================
	----------------------------------行波推动--------------------------------------
	--1 框阵奇偶分开
	FrameTime += 60
	--horizLineDisPos (middle_pos+100) (middle_pos-100)
	linearSymAPos 100 80 middle_pos
	
	--2 奇数组间歇性上升
	--LineOddDelayPos  100 100 4 30 120 90 middle_pos   --LineOddDelayPos pos d count delay cycle hold hor
	--LineEvenDelayPos 100 100 4 90 120 90 middle_pos    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--LineOddDisDelayPos pos d dis count delay cycle hold hor
	--LineOddDisDelayPos 100 100 80 4 30 120 90 middle_pos
	
	--LineOddDisHoldDelayPos pos d dis count delay delay1 cycle hold hor
	LineOddDisHoldDelayPos 100 100 80 4 30 30 120 90 middle_pos
	
	--LineEvenDisDelayPos pos d dis count delay cycle hold hor
	LineEvenDisDelayPos 100 100 80 4 90 120 90 middle_pos 
	
	
	--3 球阵启动列波
	FrameTime = sinSphereXPos 100 4 120 10 middle_pos 100
	
	--FrameTime += 15
	--horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	--4 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 
	
	
	

	
	FrameTime
	
)