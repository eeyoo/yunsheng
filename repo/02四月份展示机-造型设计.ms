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
	
	--==============================================================================
	--造型009 - 弹簧系列之横向X字形
	--==============================================================================
	--------------------------------初始位置中平面----------------------------------
	---------------------------------基准面中平面-----------------------------------
	---------------------------------双向造型变化-----------------------------------
	--1 同时到达中平面
	--FrameTime += 120
	--horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	--horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 框阵打开，球阵横向X字形
	FrameTime += 120
	rateXCOESpherePos 100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	FrameTime += 15
	rateXCOESpherePos 100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	
	--4 再次弹开
	FrameTime += 120
	rateXCOESpherePos -100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	FrameTime += 15
	rateXCOESpherePos -100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	
	--5 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	
	
	--==============================================================================
	--造型010 - 弹簧系列之横向Z字形
	--==============================================================================
	--------------------------------初始位置中平面----------------------------------
	---------------------------------基准面中平面-----------------------------------
	---------------------------------双向造型变化-----------------------------------
	--1 同时到达中平面
	--FrameTime += 120
	--horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	--horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 框阵打开，球阵横向X字形
	FrameTime += 120
	rateSphereCPos 100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCPos 100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	
	--4 再次弹开
	FrameTime += 120
	rateSphereCPos -100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCPos -100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	
	--5 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	
	--==============================================================================
	--造型011 - 弹簧系列之横向宝塔形
	--==============================================================================
	--------------------------------初始位置上平面----------------------------------
	---------------------------------基准面中平面-----------------------------------
	---------------------------------单向造型变化-----------------------------------
	--造型准备
	FrameTime += 120
	horizSphereSynPos initial_pos   --球初始状态在最高位置 ，0位
	horizLinePos initial_pos        --框初始状态在最高位置 ，0位
	FrameTime += 15
	horizSphereSynPos initial_pos  --球初始状态在最高位置 ，0位
	horizLinePos initial_pos        --框初始状态在最高位置 ，0位
	
	--1 弹簧释放
	FrameTime += 120
	rateXSpherePos 100 -700          --球阵塔形造型，rateXSpherePos a hor 高度系数x7 基准
	horizLineDisPos 0 -700
	FrameTime += 15   --停留0.5秒
	rateXSpherePos 100 -700        
	horizLineDisPos 0 -700
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos -700         --球横向X交叉
	horizLinePos -700
	
	--3 弹簧再次释放
	FrameTime += 120
	rateXSpherePos 100 -700
	horizLineDisPos 0 -700
	FrameTime += 15
	rateXSpherePos 100 -700
	horizLineDisPos 0 -700
	
	--4 弹簧再次压缩
	FrameTime += 120
	horizSphereSynPos -700
	horizLinePos -700
	FrameTime += 15
	horizSphereSynPos -700
	horizLinePos -700
	
	--==============================================================================
	--造型012 - 交叉变换系列
	--==============================================================================
	-----------------------------------扭曲面---------------------------------------
	--1 框阵打开，球阵向上呈扭曲面 
	FrameTime += 120
	warpSpherePos 100 -700          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos 0 -1400
	FrameTime += 15   --停留0.5秒
	warpSpherePos 100 -700       
	horizLineDisPos 0 -1400
	
	--2 球阵向上呈扭曲面，框奇偶颠倒
	FrameTime += 120
	warpSpherePos -100 -700
	horizLineDisPos -1400 0
	FrameTime += 15
	warpSpherePos -100 -700
	horizLineDisPos -1400 0
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos -700
	horizLinePos -700
	FrameTime += 15
	horizSphereSynPos -700
	horizLinePos -700
	
	-----------------------------------抛物面---------------------------------------
	--1 框阵打开，球阵向上呈抛物面 
	FrameTime += 120
	paraboSpherePos 10 -700          --paraboSpherePos a hor 高度系数x7 基准
	horizLineDisPos 0 -1400
	FrameTime += 15   --停留0.5秒
	paraboSpherePos 10 -700        
	horizLineDisPos 0 -1400
	
	--2 球阵向上呈抛物面，框奇偶颠倒
	FrameTime += 120
	paraboSpherePos -10 -700
	horizLineDisPos -1400 0
	FrameTime += 15
	paraboSpherePos -10 -700
	horizLineDisPos -1400 0
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos -700
	horizLinePos -700
	FrameTime += 15
	horizSphereSynPos -700
	horizLinePos -700
	
	-----------------------------------躺椅面---------------------------------------
	--1 框阵打开，球阵呈躺椅形
	FrameTime += 120
	chairSpherePos 8 -700          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos 0 -1400
	FrameTime += 15   --停留0.5秒
	chairSpherePos 8 -700          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos 0 -1400
	
	--2 框阵和球阵颠倒
	FrameTime += 120
	chairSpherePos -8 -700          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos -1400 0
	FrameTime += 15   --停留0.5秒
	chairSpherePos -8 -700          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos -1400 0
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos -700
	horizLinePos -700
	FrameTime += 15
	horizSphereSynPos -700
	horizLinePos -700
	
	-----------------------------------悬布面---------------------------------------
	--1 框阵向上打开，球阵呈悬布面
	FrameTime += 120
	cornerSpherePos 4 -650 1        --cornerSpherePos 高度系数 基准 
	horizLineDisPos 0 -700
	FrameTime += 15   --停留0.5秒
	cornerSpherePos 4 -650 1          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos 0 -700
	
	--2 回到中平面
	FrameTime += 120
	horizSphereSynPos -700
	horizLinePos -700
	FrameTime += 15
	horizSphereSynPos -700
	horizLinePos -700
	
	--3 框阵向下打开，球阵呈悬布面
	FrameTime += 120
	cornerSpherePos -4 -750 1         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos -700 -1400
	FrameTime += 15   --停留0.5秒
	cornerSpherePos -4 -750 1          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos -700 -1400
	
	--4 回到中平面
	FrameTime += 120
	horizSphereSynPos -700
	horizLinePos -700
	FrameTime += 15
	horizSphereSynPos -700
	horizLinePos -700
	
	--==============================================================================
	--造型013 - 双向推动之列波
	--==============================================================================
	--1 框阵奇偶分开
	FrameTime += 60
	horizLineBasePos 100 -700
	
	--2 奇数组间歇性上升
	LineOddDelayPos  100 100 6 30 120 90 -700   --LineOddDelayPos pos d count delay cycle hold hor
	LineEvenDelayPos 100 100 6 90 120 90 -700    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--3 球阵启动列波
	FrameTime = sinSphereYPos 100 6 120 10 -700 100
	
	--==============================================================================
	--造型014 - 启动斜波
	--==============================================================================
	--启动两次斜波，起点为对角线
	FrameTime = sinSphereRatePos 100 4 120 10 -700 150 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	FrameTime = sinSphereRatePos 100 4 120 10 -700 150 4     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	horizLineDisPos 0 -1400
	
	--回到中平面
	FrameTime += 120
	horizLinePos -700
	FrameTime += 15
	horizLinePos -700
	
	
	
	FrameTime
	
)

