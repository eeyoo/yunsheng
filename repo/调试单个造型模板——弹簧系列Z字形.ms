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
	
	--==============================================================================
	--球阵被框阵压缩和释放，球阵斜面
	--==============================================================================
	-------------------------------中平面之上---------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateSpherePos 690 -700 1           --球阵斜面造型，rateSpherePos 高度 基准 方向：1左边，2右边
	horizLineDisPos 0 -700
	FrameTime += 15   --停留0.5秒
	rateSpherePos 690 -700  1        
	horizLineDisPos 0 -700
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos -700         --球横向X交叉
	horizLinePos -700
	
	--3 弹簧再次释放
	FrameTime += 120
	rateSpherePos 690 -700 2
	horizLineDisPos 0 -700
	FrameTime += 15
	rateSpherePos 690 -700 2
	horizLineDisPos 0 -700
	
	--4 弹簧再次压缩
	FrameTime += 120
	horizSphereSynPos -700           --球横向X交叉
	horizLinePos -700
	FrameTime += 5
	horizSphereSynPos -700           --球横向X交叉
	horizLinePos -700
	
	-------------------------------中平面以下-----------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateSpherePos 690 -1400 1
	horizLineDisPos -700 -1400
	FrameTime += 15
	rateSpherePos 690 -1400 1
	horizLineDisPos -700 -1400
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos -1400          --球至底部
	horizLinePos -1400
	
	--3 弹簧再次释放
	FrameTime += 120
	rateSpherePos 690 -1400 2
	horizLineDisPos -700 -1400
	FrameTime += 15
	rateSpherePos 690 -1400 2
	horizLineDisPos -700 -1400
	
	--4 弹簧再次压缩
	FrameTime += 120
	horizSphereSynPos -1400          --球至底部
	horizLinePos -1400
	
	---------------------------------中平面---------------------------------------
	--1 同时到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
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
	
	
	--==============================================================================
	--中平面打开并产生弹簧阻尼振动效果,注意需要手动改变速度曲线曲率，达到撞击反弹的效果
	--==============================================================================
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--1 打开
	FrameTime += 120
	rateSphereCPos 100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	
	FrameTime += 90
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	FrameTime += 80
	rateSphereCPos 60 -700       --rateSphereCPos a hor
	horizLineBasePos 500 -700
	
	FrameTime += 70
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	FrameTime += 60
	rateSphereCPos 40 -700       --rateSphereCPos a hor
	horizLineBasePos 300 -700
	
	FrameTime += 50
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	FrameTime += 50
	rateSphereCPos 15 -700       --rateSphereCPos a hor
	horizLineBasePos 100 -700
	
	FrameTime += 30
	rateSphereCPos 0 -700       --rateSphereCPos a hor
	horizLineBasePos 0 -700
	
	/*
	--斜面以中心轴转动
	--造型准备
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--1 打开
	FrameTime += 120
	rateSphereCXPos 100 -700       --rateSphereCPos ax7 hor
	horizLineBasePos 700 -700      --horizLineBasePos 偏距 中心高
	*/
	
	/*
	--1.框奇偶分离，球阵在中间
	FrameTime += 120
	horizSphereSynPos -700           --球到中间
	horizLinePos -700          --奇偶框上下分离（奇数框位置，pos2 - 偶数框位置） 
	
	--2.球阵横向X交叉，框阵奇偶分开
	FrameTime += 120
	rateXOESpherePos 50 -1400          --rateXOESpherePos a hor
	horizLineDisPos -300 -1100
	FrameTime += 15   --停留0.5秒
	rateXOESpherePos 80 -700          --rateXOESpherePos a hor
	horizLineDisPos -300 -1100
	
	--3.压缩
	FrameTime += 120
	horizSphereSynPos -700           --球到中间
	horizLinePos -700 
	
	--4.释放
	FrameTime += 120
	rateXOESpherePos 80 -700          --rateXOESpherePos a hor
	horizLineDisPos -100 -1300
	FrameTime += 15   --停留0.5秒
	rateXOESpherePos 80 -700          --rateXOESpherePos a hor
	horizLineDisPos -100 -1300
	
	--5.压缩
	FrameTime += 120
	horizSphereSynPos -700           --球到中间
	horizLinePos -700
	
	
	
	--球阵X、Y轴行波，振幅随完整波形的次数count逐次增加
	--FrameTime = sinSphereXPos 100 4 120 10 -700 50 --sinSphereXPos amp count dur delay hor da
	--FrameTime = sinSphereYPos 100 4 120 10 -700 50 --sinSphereXPos amp count dur delay hor da
	
	/*		
	--==============================================================================
	--球阵由中心启动正弦波动形成水滴涟漪造型，4周期，周期时长4秒
	--==============================================================================
	--FrameTime = sinSphereCPos 100 4 120 -700 50    --sinSphereCPos amp count dur hor da
	
	--==============================================================================
	--球阵启动开口向下抛物面造型
	--==============================================================================
	--FrameTime = paraboSpherePos 5 120 -700     --paraboSpherePos a hor
	FrameTime += 15
	horizSphereSynPos -700
	FrameTime += 120
	paraboSpherePos 5 -700
	FrameTime += 15
	paraboSpherePos 5 -700
	
	--==============================================================================
	--球阵启动开口向上抛物面造型，并停留0.5秒，耗时3.5秒
	--==============================================================================
	--FrameTime = paraboSpherePos -5 120 -700     --paraboSpherePos a hor
	FrameTime += 180
	paraboSpherePos -5 -700
	FrameTime += 15
	paraboSpherePos -5 -700
	FrameTime += 120
	horizSphereSynPos -700
	
	--==============================================================================
	--球阵由中心启动正弦波动形成水滴涟漪造型，4周期，周期时长4秒
	--==============================================================================
	FrameTime = sinSphereCPos 100 4 120 -700 50    --sinSphereCPos amp count dur hor da
	
	--==============================================================================
	--球阵启动逐个延时正弦波动，单个球运行2周期，耗时8秒
	--==============================================================================
	FrameTime = sinSphereSingleXPos 100 4 120 5 -700 50     --sinSpherePos amp count dur delay hor da
	FrameTime = sinSphereSingleYPos 100 4 120 10 -700 50
	
	--球阵X、Y轴行波，振幅随完整波形的次数count逐次增加
	FrameTime = sinSphereXPos 100 4 120 10 -700 50 --sinSphereXPos amp count dur delay hor da
	FrameTime = sinSphereYPos 100 4 120 10 -700 50 --sinSphereXPos amp count dur delay hor da
	
	--球阵X轴行波， 振幅与行号呈线性关系
	FrameTime =  sinSphereRateXPos 20 4 120 10  -700 10 1 --sinSphereRateXPos amp count dur delay hor da direct
	FrameTime =  sinSphereRateXPos 20 4 120 10  -700 10 2 --sinSphereRateXPos amp count dur delay hor da direct
	
	--球阵Y轴行波， 振幅与行号呈线性关系
	FrameTime =  sinSphereRateYPos 20 4 120 10  -700 10 1 --sinSphereRateXPos amp count dur delay hor da direct
	FrameTime =  sinSphereRateYPos 20 4 120 10  -700 10 2 --sinSphereRateXPos amp count dur delay hor da direct
	
	--球阵斜波
	FrameTime = sinSphereRatePos 100 4 120 10 -700 50 1      --sinSphereRatePos amp count dur delay hor da direct
	FrameTime = sinSphereRatePos 100 4 120 10 -700 50 2      --sinSphereRatePos amp count dur delay hor da direct
	FrameTime = sinSphereRatePos 100 4 120 10 -700 50 4      --sinSphereRatePos amp count dur delay hor da direct
	FrameTime = sinSphereRatePos 100 4 120 10 -700 50 3      --sinSphereRatePos amp count dur delay hor da direct
	
	--球阵沿Y轴方向分为2部分作相反正弦波动, 振幅随完整波形的次数count逐次增加
	FrameTime = sinBXOESpherePos 100 4 120 10 -700 50 --sinBXOESpherePos amp count dur delay hor da
	
	--沿X、Y轴线性交错
	FrameTime =  rateXOESpherePos 40  120 -700    --rateXSpherePos a range hor
	FrameTime =  rateYOESpherePos 100 120 -700    --rateXSpherePos a range hor
	
	--奇偶交错快速正弦波动
	FrameTime = sinXOESpherePos  50 4 40 -700              --sinOXSpherePos amp count dur hor
	FrameTime = sinYOESpherePos  50 4 40 -700              --sinOXSpherePos amp count dur hor
	FrameTime = sinXYOESpherePos 50 4 32 -700                --sinXYOESpherePos amp count dur hor
	
	
	---------------------------------2015-03-18-------------------------------------
	-------------------------------球阵定型造型-------------------------------------
	--中平面停止0.5秒
	FrameTime += 15
	horizSphereSynPos middle_pos


	--斜面
	FrameTime += 60
	rateSpherePos 490 middle_pos 1    --rateSpherePos 高度 中心高 起点
	FrameTime += 120
	rateSpherePos -490 middle_pos 1    --rateSpherePos 高度 中心高 起点
	FrameTime += 60
	horizSphereSynPos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	rateSpherePos 490 middle_pos 2    --rateSpherePos 高度 中心高 起点
	FrameTime += 120
	rateSpherePos -490 middle_pos 2    --rateSpherePos 高度 中心高 起点
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	--塔形斜面
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 60
	rateXSpherePos 60 middle_pos   --rate1SpherePos a hor
	FrameTime += 120
	rateXSpherePos -60 middle_pos
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 60
	rateYSpherePos 100 middle_pos   --rate1SpherePos a hor
	FrameTime += 120
	rateYSpherePos -100 middle_pos
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	--马鞍面
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	horseSpherePos 5 middle_pos  --horseSpherePos a hor
	FrameTime += 15
	horseSpherePos 5 middle_pos  --horseSpherePos a hor
	FrameTime += 120
	horseSpherePos -5 middle_pos  --horseSpherePos a hor
	FrameTime += 15
	horseSpherePos -5 middle_pos  --horseSpherePos a hor
	
	--凹凸面
	FrameTime += 60
	horizSphereSynPos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	bossSpherePos 1000 middle_pos    --bossSpherePos a hor
	FrameTime += 120
	bossSpherePos -1000 middle_pos    --bossSpherePos a hor
	
	--躺椅曲面
	FrameTime += 60
	horizSphereSynPos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	chairSpherePos 1 middle_pos    --chairSpherePos a hor
	FrameTime += 120
	chairSpherePos -1 middle_pos    --chairSpherePos a hor
	
	--扭曲面
	FrameTime += 60
	horizSphereSynPos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	warpSpherePos 100 middle_pos    --warpSpherePos a hor
	FrameTime += 120
	warpSpherePos -100 middle_pos    --warpSpherePos a hor
	
	--花的变体
	FrameTime += 60
	horizSphereSynPos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	flowerSpherePos 10000 middle_pos  --flowerSpherePos a hor
	FrameTime += 120
	flowerSpherePos -10000 middle_pos  --flowerSpherePos a hor
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	--网床面/抛物面
	--球阵启动开口向下抛物面造型
	FrameTime = paraboSphereDynamicPos 5 120 middle_pos 15    --paraboSphereDynamicPos a range hor hold

	--球阵启动开口向上抛物面造型
	FrameTime = paraboSphereDynamicPos -5 120 middle_pos 15    --paraboSphereDynamicPos a range hor hold
	
	--布悬曲面
	FrameTime += 60
	horizSphereSynPos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	cornerSpherePos  1 middle_pos 1   --bossSpherePos a hor
	FrameTime += 120
	cornerSpherePos -1 middle_pos 1   --bossSpherePos a hor
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	cornerSpherePos  1 middle_pos 2   --bossSpherePos a hor
	FrameTime += 120
	cornerSpherePos -1 middle_pos 2   --bossSpherePos a hor
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	cornerSpherePos  1 middle_pos 3   --bossSpherePos a hor
	FrameTime += 120
	cornerSpherePos -1 middle_pos 3   --bossSpherePos a hor
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	cornerSpherePos  1 middle_pos 4   --bossSpherePos a hor
	FrameTime += 120
	cornerSpherePos -1 middle_pos 4   --bossSpherePos a hor
	FrameTime += 60
	horizSphereSynPos middle_pos
	
	--金字塔造型
	FrameTime += 15
	horizSphereSynPos middle_pos
	FrameTime += 120
	pyramidSpherePos 50 100 middle_pos   --pyramidSpherePos a b hor
	FrameTime += 120
	pyramidSpherePos -50 -100 middle_pos   --pyramidSpherePos a b hor
	FrameTime += 120
	horizSphereSynPos middle_pos
	
	---------------------------------2015-03-20-------------------------------------
	-------------------------------球框阵定型造型-----------------------------------
	--球阵随框阵一起打开，耗时8秒
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--节目004
	--球阵，4周期，周期时长4秒，框阵同时奇偶分离
	--CompositeShow004 amp1 amp2 count range delay hor da
	FrameTime = CompositeShow004 100 500 4 120 15 middle_pos 50
	*/
	FrameTime
	
)