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
--最大演示范围，1.4米
--==================================================================================

initial_pos = 0
middle_pos = -700
down_limit_pos = -1400

FrameTime = 0

animate on
(
	--==============================================================================
	--球阵和框阵起始零位，停止0.5秒
	--==============================================================================
	FrameTime += 15
	horizSphereSynPos initial_pos   --球初始状态在最高位置 ，0位
	horizLinePos initial_pos         --框初始状态在最高位置 ，0位	
	
	
	--Z字形弹簧
	--==============================================================================
	--中平面打开并产生弹簧阻尼振动效果,注意需要手动改变速度曲线曲率，达到撞击反弹的效果
	--==============================================================================
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--1 第1次弹开和回落
	FrameTime += 120
	rateSphereCPos 100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	FrameTime += 90
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	--2 第2次弹开和回落
	FrameTime += 80
	rateSphereCPos 60 -700       --rateSphereCPos a hor
	horizLineBasePos 500 -700
	FrameTime += 70
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	--3 第3次弹开和回落
	FrameTime += 60
	rateSphereCPos 40 -700       --rateSphereCPos a hor
	horizLineBasePos 300 -700
	FrameTime += 50
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	--4 第4次弹开和回落
	FrameTime += 50
	rateSphereCPos 15 -700       --rateSphereCPos a hor
	horizLineBasePos 100 -700
	FrameTime += 30
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	FrameTime
	
)