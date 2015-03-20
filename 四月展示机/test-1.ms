--==============================================================================
--脚本意图：展示机造型设计最新工作文件和造型库
--版本 1.0
--日期 2015-2-13
--作者 吴飞林
--注意运行此脚本前，必须执行4x8球阵建模脚本
--==============================================================================

--为放样赋予变量名称
num = 4
LineArray = #($Loft001, $Loft002, $Loft003, $Loft004)

--创建球阵模型
fileIn "create_sphere_4x8_array.ms" quiet: true

--执行造型函数库
fileIn "frameLib.ms"
fileIn "sphereLib.ms"

--执行结合造型函数库
fileIn "show.ms"


--==================================================================================
--造型说明
--最大演示范围，1.4米
--==================================================================================

initial_pos = 0      --初始位置
middle_pos = -700    --中平面
down_limit_pos = -1400     --下限平面

FrameTime = 0
--球阵造型测试
animate on
(
	
	--球阵和框阵起始零位，停止0.5秒
	FrameTime += 15
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	FrameTime += 120
	horizSphereSynPos middle_pos
	--horizLineDisPos 0 -1400
	horizLinePos middle_pos
	
	--球阵，4周期，周期时长4秒，框阵同时奇偶分离
	--FrameTime = sinSphereSingleXPos 300 4 240 10 middle_pos 10     --sinSphereSingleYPos amp count dur delay hor da
	--FrameTime = sinSphereSingleYPos 300 4 240 10 middle_pos 10     --sinSphereSingleYPos amp count dur delay hor da
	--horizLineDisPos down_limit_pos initial_pos
	
	--001号节目
	FrameTime = CompositeShow001 middle_pos initial_pos 120 10  --CompositeShow001 pos1 pos2 range delay hor
	
	FrameTime
	
)

