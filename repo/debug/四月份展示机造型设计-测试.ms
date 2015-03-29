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
	--造型001 - 球阵和框阵保持同一平面
	--==============================================================================
	--球阵和框阵保持零位
	FrameTime += 15
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+500) (middle_pos-500)
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	
	--==============================================================================
	--造型006 - 弹簧系列之横向Z字形
	--==============================================================================
	
	
	
	--斜波
	FrameTime = sinSphereRatePos 200 2 120 10 middle_pos 100 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	FrameTime += 60
	horizLinePos middle_pos
	FrameTime += 30
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	-----------------------------------横向Z字形------------------------------------
	
	--2 框阵打开，球阵横向Z字形
	FrameTime += 120
	rateSphereCPos 92 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCPos 92 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime +=5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos        
	
	
	
	
	FrameTime
	
)

