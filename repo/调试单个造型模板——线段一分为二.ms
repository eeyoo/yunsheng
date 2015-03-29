
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
	--造型006 - 弹簧系列之横向Z字形
	--==============================================================================
	-----------------------------------横向Z字形------------------------------------
	--1 同时到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 框阵打开，球阵横向Z字形
	FrameTime += 120
	rateSphereCXPos -500 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos -500 middle_pos      --horizLineBasePos 偏距 中心高
	
	
	--==============================================================================
	--造型007 - 弹簧系列之横向宝塔形
	--==============================================================================
	-----------------------------------横向宝塔形------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateCXSpherePos 400 middle_pos         --球阵塔形造型，rateXSpherePos a hor 高度系数x7 基准
	horizLineBasePos 500 middle_pos 
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos middle_pos         --球横向宝塔形
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	
	
	
	
)	