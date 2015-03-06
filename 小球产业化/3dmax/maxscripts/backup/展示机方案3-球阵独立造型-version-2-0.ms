--==============================================================================
--脚本意图：4x8球阵和框阵结合的造型设计
--版本 1.0
--日期 2015-2-13
--作者 吴飞林
--注意运行此脚本前，必须执行4x8球阵建模脚本
--==============================================================================


row = 2*row - 1
column = 2*column - 1

/*
--==============================================================================
--为放样赋予变量名称
num = 4
LineArray = #($Loft001, $Loft002, $Loft003, $Loft004)

-------------------------------框阵造型函数-------------------------------------
--==============================================================================
--同步达到指定位置
--参数：pos - 指定Z轴位置值
--参数：delay  - 保持pod位置时间
--==============================================================================
fn horizLinePos pos frame:FrameTime n:num =
(
	at time frame (
		for i = 1 to n do LineArray[i].pos.z = pos
	)

)

--==============================================================================
--随机位置分布
--参数：rmin, rmax - 随机位置下限和上限
--==============================================================================
fn randomLinePos rmin rmax frame:FrameTime n:num =
(
	for i = 1 to n do
	(
		at time frame (
			pos = random rmin rmax
			LineArray[i].pos.z = pos
		)
	)
)


--==============================================================================
--框阵奇偶分离
--参数：pos - 指定Z轴位置值
--==============================================================================
fn horizLineDisPos pos1 pos2 frame:FrameTime n:num =
(
	for i = 1 to 3 by 2 do
	(
		at time frame (
			LineArray[i].pos.z = pos1
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			LineArray[i].pos.z = pos2
		)
	)

)
*/
-------------------------------球阵造型函数-------------------------------------
--==============================================================================
--创建Z轴位置矩阵
--参数：pos    - 指定Z轴位置值
--参数：hold   - 保持时间
--==============================================================================
fn horizSpherePos pos frame:FrameTime row:row col:column =
(
	at time frame (
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = pos
			)
		)
	)
)

--==============================================================================
--Z轴随机位置矩阵
--参数：rmin,rmax - 指定Z轴随机位置下限和上限
--==============================================================================
fn randomSpherePos rmin rmax frame:FrameTime row:row col:column =
(
	at time frame (
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = random rmin rmax
			)
		)
	)
)

--==============================================================================
--球阵形成抛物面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：h      - 弓高
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--==============================================================================
fn paraboSpherePos a hor cx:8 cy:4 frame:FrameTime row:row col:column =
(

	rmax2 = 49+9
	
	at time frame (
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				rx = cx - i
				ry = cy - j
				r2 = rx*rx+ry*ry
				BallArray[i][j].pos.z = a*(rmax2 - r2) + hor
			)
		)
	)
)


--==============================================================================
--球阵逐个延时启动正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSpherePos amp count dur delay hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			frame += delay
			temp = frame
			for t = 1 to (c*count+1) do
			(
				
				at time temp ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
				temp += df
			)
		)
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵沿X轴逐列延时启动正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereXPos amp count dur delay hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for i = 1 to row by 2 do
	(
		frame += delay
		temp = frame
		for t = 1 to (c*count+1) do
		(
			at time temp 
			(
				for j = 1 to col by 2 do ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor  )
			)
			temp += df
		)
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵沿Y轴逐列延时启动正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereYPos amp count dur delay hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for j = 1 to col by 2 do
	(
		frame += delay
		temp = frame
		for t = 1 to (c*count+1) do
		(
			at time temp 
			(
				for i = 1 to row by 2 do ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor  )
			)
			temp += df
		)
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵由中心启动延时效果正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereCPos amp count dur hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	enter = frame
	rc2 = 64+16
	rmax2 = 49+9
	rmin2 = 1+1
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			rx = cx - i
			ry = cy - j
			r2 = rx*rx+ry*ry
			
			frame = enter + r2
			temp = frame
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
				temp += df
			)
			
		)
	)

	return (enter + rmax2 + dur*count)
)






--==================================================================================
--造型说明
--最大演示范围，1.6米
--距离地面最大高度，1.5米
--最长演示时间，5min
--==================================================================================

FrameTime = 0


--以下为球阵独立造型
animate on
(
	--==============================================================================
	--球阵起始零位，停止0.5秒
	--==============================================================================
	FrameTime += 15
	horizSphereSynPos 0     --horizSphereSynPos pos
	horizLinePos 0
	
	--==============================================================================
	--球阵随机分布变于0至-1600
	--==============================================================================
	FrameTime += 120
	randomSpherePos 0 -1600
	horizLineDisPos 0 -1600
	
	--==============================================================================
	--球阵随机分布变于0至-1600
	--==============================================================================
	FrameTime += 120
	horizSphereSynPos -1600
	
	--==============================================================================
	--球阵整体下降至-800，耗时2秒
	--==============================================================================
	FrameTime += 120
	horizSphereASynPos -800 30        --horizSphereASynPos pos delay
	
	--==============================================================================
	--球阵整体下降至-800，暂停0.5秒
	--==============================================================================
	FrameTime += 15
	horizSphereSynPos -800
	
	--==============================================================================
	--球阵由中心启动正弦波动形成水滴涟漪造型，4周期，周期时长4秒
	--==============================================================================
	FrameTime = sinSphereC1Pos 100 4 120 -800 100    --sinSphereCPos amp count dur hor da
	
	--==============================================================================
	--球阵启动开口向下抛物面造型，并停留0.5秒，耗时3.5秒
	--==============================================================================
	FrameTime += 90
	paraboSpherePos 5 -800     --paraboSpherePos a hor
	
	--==============================================================================
	--球阵启动开口向下抛物面造型，并停留0.5秒
	--==============================================================================
	FrameTime += 15
	paraboSpherePos 5 -800     --paraboSpherePos a hor
	
	--==============================================================================
	--球阵启动开口向上抛物面造型，并停留0.5秒，耗时3.5秒
	--==============================================================================
	FrameTime += 90
	paraboSpherePos -5 -800     --paraboSpherePos a hor
	
	--==============================================================================
	--球阵启动开口向上抛物面造型，并停留0.5秒
	--==============================================================================
	FrameTime += 15
	paraboSpherePos -5 -800     --paraboSpherePos a hor
	
	--==============================================================================
	--球阵启动逐个延时正弦波动，单个球运行2周期，耗时8秒
	--==============================================================================
	FrameTime = sinSphereSingleXPos 100 4 120 5 -800 100     --sinSpherePos amp count dur delay hor da
	FrameTime = sinSphereSingleYPos 100 4 120 5 -800 100
	
	
	--==============================================================================
	--球阵沿X轴启动延时正弦波动运行5周期，耗时20秒，同时框阵全部回到-500
	--周期参数dur越大波形周期跨度越大
	--延时参数delay越大波形显得越僵硬
	--==============================================================================
	FrameTime = sinSphereX1Pos 100 4 90 10 -800 100  --sinSpherePos amp count dur delay hor   
	
	--==============================================================================
	--球阵沿Y轴启动延时正弦波动运行5周期，耗时20秒，同时框阵全部回到-500
	--周期参数dur越大波形周期跨度越大
	--延时参数delay越大波形显得越僵硬
	--==============================================================================
	FrameTime = sinSphereY1Pos 100 4 90 10 -800 100  --sinSpherePos amp count dur delay hor   
	
	--==============================================================================
	--球阵斜波造型运行4周期，耗时20秒，同时框阵全部回到-500
	--==============================================================================
	--左下方开始
	FrameTime = sinSphereZ1Pos 100 4 120 10 -800 100 1  --sinSphereZ1Pos amp count dur delay hor da direct
	--左上方开始
	FrameTime = sinSphereZ1Pos 100 4 120 10 -800 100 2  --sinSphereZ1Pos amp count dur delay hor da direct
	--右上方开始
	FrameTime = sinSphereZ1Pos 100 4 120 10 -800 100 4  --sinSphereZ1Pos amp count dur delay hor da direct
	--右下方开始
	FrameTime = sinSphereZ1Pos 100 4 120 10 -800 100 3  --sinSphereZ1Pos amp count dur delay hor da direct
	
	--==============================================================================
	--球阵奇偶区别造型运行4周期，耗时20秒，同时框阵全部回到-500
	--==============================================================================
	--横向
	FrameTime = sinXOESpherePos 50  4 32 -800              --sinOXSpherePos amp count dur hor
	FrameTime = sinXOESpherePos 100 4 40 -800              --sinOXSpherePos amp count dur hor
	FrameTime = sinXOESpherePos 200 4 80 -800              --sinOXSpherePos amp count dur hor
	--纵向
	FrameTime = sinYOESpherePos 50  4 32 -800              --sinOXSpherePos amp count dur hor
	FrameTime = sinYOESpherePos 100 4 40 -800              --sinOXSpherePos amp count dur hor
	FrameTime = sinYOESpherePos 200 4 80 -800              --sinOXSpherePos amp count dur hor
	--横向和纵向同时变化
	FrameTime = sinXYOESpherePos 50  4 32 -800              --sinOXSpherePos amp count dur hor
	FrameTime = sinXYOESpherePos 100 4 40 -800              --sinOXSpherePos amp count dur hor
	FrameTime = sinXYOESpherePos 200 4 80 -800              --sinOXSpherePos amp count dur hor
	
	FrameTime
)