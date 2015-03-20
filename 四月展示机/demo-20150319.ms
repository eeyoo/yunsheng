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
	
	/*
	--球阵随框阵一起打开，耗时8秒
	FrameTime += 240
	randomSpherePos initial_pos down_limit_pos
	horizLineDisPos initial_pos down_limit_pos
	
	--球阵随机分布0至-1400，耗时4秒
	FrameTime += 120
	randomSpherePos initial_pos down_limit_pos
	horizLineDisPos initial_pos down_limit_pos
	
	--球阵再次随机分布0至-1400，耗时4秒
	FrameTime += 120
	randomSpherePos initial_pos down_limit_pos
	horizLineDisPos initial_pos down_limit_pos
	
	--球阵和框阵回到中平面，耗时4秒
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--球阵启动波动
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	*/
	
	--球阵，4周期，周期时长4秒，框阵同时奇偶分离
	--FrameTime = sinSphereCPos 50 6 240 middle_pos 100     --sinSphereCPos amp count dur hor da
	--horizLineDisPos initial_pos down_limit_pos
	
	--球阵，4周期，周期时长4秒，框阵同时奇偶分离
	--FrameTime = sinSphereSingleYPos 300 4 240 middle_pos 10 10     --sinSphereSingleYPos amp count dur delay hor da
	--horizLineDisPos down_limit_pos initial_pos
	
	--球阵，4周期，周期时长4秒，框阵同时奇偶分离
	FrameTime = sinSphereSingleXPos 300 4 240 middle_pos 10 10     --sinSphereSingleYPos amp count dur delay hor da
	horizLineDisPos down_limit_pos initial_pos
	

	/*
	--==============================================================================
	--球阵启动逐个延时正弦波动，单个球运行1周期，耗时4秒
	--同时框阵奇偶上下交替
	--==============================================================================
	FrameTime = sinSpherePos 200 1 120 5 -800      --sinSpherePos amp count dur delay hor
	horizLineDisPos -1600 0
	
	--==============================================================================
	--球阵启动逐个延时正弦波动，单个球运行1周期，耗时4秒
	--同时框阵奇偶上下交替
	--==============================================================================
	FrameTime = sinSpherePos 400 1 180 5 -800      --sinSpherePos amp count dur delay hor
	horizLineDisPos 0 -1600
	
	--==============================================================================
	--球阵启动逐个延时正弦波动，单个球运行1周期，耗时4秒
	--同时框阵奇偶上下交替
	--==============================================================================
	FrameTime += 60
	horizSpherePos -800
	horizLinePos -800
	
	--==============================================================================
	--球阵启动逐个延时正弦波动运行6周期，耗时12秒
	--==============================================================================
	FrameTime = sinSphere3Pos 200 6 120 5 -800 50     --sinSphere3Pos amp count dur delay hor da
	horizLineDisPos 0 -1600
	
	--==============================================================================
	--球阵启动X轴延时正弦波动运行6周期，耗时12秒
	--==============================================================================
	FrameTime = sinSphereX1Pos 200 4 120 10 -800 100    --sinSpherePos amp count dur delay hor
	horizLineDisPos -1600 0
	
	--==============================================================================
	--球阵启动Y轴延时正弦波动运行6周期，耗时12秒
	--==============================================================================
	FrameTime = sinSphereY1Pos 600 4 120 10 -800 -100    --sinSpherePos amp count dur delay hor
	horizLinePos -800
	*/
	
	FrameTime
	
)

