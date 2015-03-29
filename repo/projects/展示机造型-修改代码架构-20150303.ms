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
--最大演示范围，1.4米
--==================================================================================

initial_pos = 0
middle_pos = -700
down_limit_pos = -1400

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
	
	
	--==============================================================================
	--造型002 - 框阵分为奇偶两组构成区间，同时球阵区间内随机分布
	--==============================================================================
	FrameTime += 240
	randomSpherePos initial_pos down_limit_pos
	horizLineDisPos initial_pos down_limit_pos
	
	FrameTime += 120
	randomSpherePos -200 -1200
	horizLineDisPos -200 -1200
	
	FrameTime += 120
	randomSpherePos -400 -1000
	horizLineDisPos -400 -1000
	
	FrameTime += 120
	randomSpherePos -600 -800
	horizLineDisPos -600 -800
	
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型003 - 球阵在顶端随机落下，框阵在底部向上运行，与球阵产生呼应
	--==============================================================================
	--中平面停止
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--球运行至顶端，框运行至底部
	FrameTime += 120
	horizSphereSynPos initial_pos
	horizLinePos down_limit_pos
	
	--框阵向上运行呼应
	FrameTime += 60
	randomSpherePos 0 -1100
	linearForwardPos 300 -1400        --linearForwardPos h hor
	
	--球阵收回零位，框阵到达平面
	FrameTime += 120
	horizSphereSynPos initial_pos
	horizLinePos -1100
	
	--框阵向上运行呼应
	FrameTime += 60
	randomSpherePos initial_pos down_limit_pos
	linearForwardPos -300 -1100                --linearBackwardPos h hor
	
	--球阵与框阵运行至-800，耗时1秒
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型004 - 框阵分为奇偶两组构成区间，球阵在区间内由中心启动正弦波动形成水滴涟漪
	--==============================================================================
	--1 球阵和框由中平面启动
	FrameTime = sinSphereCNPos 100 2 120 middle_pos     --sinSphereCPos amp count dur hor
	horizLineDisPos -400 -1000
	
	--2 球阵再次运行2周期，振幅加大，周期时间加长，框阵逐渐打开
	FrameTime = sinSphereCNPos 200 2 180 middle_pos     --sinSphereCPos amp count dur hor
	horizLineDisPos -200 -1200
	
	--3 球阵第3次运行2周期，振幅加大，周期时间加长
	FrameTime = sinSphereCNPos 400 2 240 middle_pos     --sinSphereCPos amp count dur hor
	horizLineDisPos 0 -1400
	
	--==============================================================================
	--造型005 - 球阵启动逐个延时正弦波动，框阵在全程范围内奇偶两组上下交替
	--==============================================================================
	--球阵启动逐个延时正弦波动，单个球运行1周期，耗时4秒
	FrameTime = sinSphereSingleXNPos 200 1 120 5 middle_pos      --sinSpherePos amp count dur delay hor
	horizLineDisPos -1400 0
	
	--球阵启动逐个延时正弦波动，单个球运行1周期，耗时4秒
	FrameTime = sinSphereSingleXNPos 400 1 180 5 middle_pos      --sinSpherePos amp count dur delay hor
	horizLineDisPos 0 -1400
		
	--球阵框阵回到中平面
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型006 - 球阵启动逐个延时正弦波动，振幅周期性线性变化
	--==============================================================================
	--球阵启动逐个延时正弦波动运行6周期，耗时12秒
	FrameTime = sinSphereSingleXPos 200 6 120 5 middle_pos 50     --sinSphere3Pos amp count dur delay hor da
	horizLineDisPos 0 -1400
	
	--==============================================================================
	--造型007 - 球阵启动行波，振幅周期性线性变化
	--==============================================================================	
	--球阵启动振幅周期性线性增加行波，框阵在全程范围内奇偶两组上下交替
	FrameTime = sinSphereXPos 200 4 120 10 middle_pos 100    --sinSpherePos amp count dur delay hor
	horizLineDisPos -1400 0
	
	--==============================================================================
	--造型008 - 球阵启动列波，振幅周期性线性变化
	--==============================================================================
	--球阵启动振幅周期性线性增加列波，框阵回到中平面
	FrameTime = sinSphereYPos 600 4 120 10 middle_pos -100    --sinSpherePos amp count dur delay hor
	horizLinePos middle_pos
	
	
	FrameTime
	
)

