--==============================================================================
--脚本说明：球阵和框阵结合造型设计
--版本 1.0
--日期 2015-3-20
--作者 吴飞林
--==============================================================================

--加载框模型文件
fileName = "C:\Users\feilin\Documents\3dsMax\workspace\repo\00框阵模板.max"
loadMaxFile fileName 


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
	--球随机跳动，框上下分离不动
	--==============================================================================
	-----------------------------------行程起点-------------------------------------
	FrameTime += 60
	horizSphereSynPos run_initial_pos   
	horizLinePos run_initial_pos        	
	FrameTime += 15
	horizSphereSynPos run_initial_pos   
	horizLinePos run_initial_pos        
	
	
	--rateLineDelayPos pos dur delay hold hor
	--FrameTime = rateLineDelayPos 500 60 15 0 run_initial_pos
	
	----------------------------一个函数搞定球框-------------------------------------
	--rateCompositeDelayPos pos dur delay hold hor 最大位置 时间 单个延时  保持时间 基准
	FrameTime = rateCompositeADelayPos 600 60 15 30 (run_initial_pos)
	
	FrameTime = rateCompositeADelayPos 600 60 15 30 (run_initial_pos+600)
	
	FrameTime += 60
	horizSphereSynPos run_initial_pos   
	horizLinePos run_initial_pos        	
	FrameTime += 15
	horizSphereSynPos run_initial_pos   
	horizLinePos run_initial_pos
	
	FrameTime = rateCompositeBDelayPos 600 60 15 30 (run_initial_pos)
	
	FrameTime = rateCompositeBDelayPos -600 60 15 30 (run_initial_pos+600)
	
	FrameTime += 60
	horizSphereSynPos run_initial_pos   
	horizLinePos run_initial_pos        	
	FrameTime += 15
	horizSphereSynPos run_initial_pos   
	horizLinePos run_initial_pos

	
	FrameTime
	
)