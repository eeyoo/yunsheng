--==============================================================================
--脚本说明：球阵的造型库
--版本 1.0
--日期 2015-2-13
--作者 吴飞林
--==============================================================================


--------------------------------------------------------------------------------
-------------------------------球阵造型函数-------------------------------------
--------------------------------------------------------------------------------

-------------------------------同动定型系列-------------------------------------
--==============================================================================
--球阵同步达到指定位置
--参数：pos    - 指定Z轴位置值
--==============================================================================
fn horizSphereSynPos pos frame:FrameTime row:row col:column =
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
--斜面造型
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--参数：flag    - 起点方向，1，2区分不同起点
--==============================================================================
fn rateSpherePos pos hor flag frame:FrameTime row:row col:column =
(
	n = (row+1)/2
	dh = pos/(n-1)
	at time frame (
		for i = 1 to row by 2 do
		(
			x = (i+1)/2
			for j = 1 to col by 2 do
			(
				case flag of
				(
				1: y = x-1
				2: y = n-x				
				)
				BallArray[i][j].pos.z = dh*y + hor
			)
		)
	)
)

--==============================================================================
--斜面造型，基准在中心
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--==============================================================================
fn rateSphereCPos a hor cx:8 frame:FrameTime row:row col:column =
(

	at time frame (
		for i = 1 to row by 2 do
		(
			x = cx-i  -- -3 -2 -1 1 2 3
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = -a*x + hor
			)
		)
	)
)

--==============================================================================
--X轴向斜面造型，基准在中心
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--==============================================================================
fn rateSphereCXPos a hor cx:8 frame:FrameTime row:row col:column =
(

	at time frame (
		for i = 1 to row by 2 do
		(
			x = cx-i  -- -3 -2 -1 1 2 3
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = -a*x + hor
			)
		)
	)
)

--==============================================================================
--Y轴向斜面造型，基准在中心
--参数：rang    - 斜面高度
--参数：hor    - 基准面
--==============================================================================
fn rateSphereCYPos rang hor cy:4 frame:FrameTime row:row col:column =
(
	d = rang/2
	a = d/3
	at time frame (
		for j = 1 to col by 2 do
		(
			y = j - cy  -- -3 -2 -1 1 2 3
			for i = 1 to row by 2 do
			(
				BallArray[i][j].pos.z = a*y + hor
			)
		)
	)
)

--==============================================================================
--X轴向塔形斜面造型
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--==============================================================================
fn rateXSpherePos a hor cx:8 frame:FrameTime row:row col:column =
(
	pos_max = a*abs(cx-1)
	at time frame (
		for i = 1 to row by 2 do
		(
			pos = pos_max - a*abs(cx-i)
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = pos + hor
			)
		)
	)
)

--==============================================================================
--Y轴向塔形斜面造型
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--参数：flag    - 起点方向，1，2区分不同起点
--==============================================================================
fn rateYSpherePos a hor cy:4 frame:FrameTime row:row col:column =
(
	pos_max = a*abs(cy-1)
	at time frame (
		for j = 1 to col by 2 do
		(
			pos = pos_max - a*abs(cy-j)
			for i = 1 to row by 2 do
			(
				BallArray[i][j].pos.z = pos + hor
			)
		)
	)
)

--==============================================================================
--金字塔造型
--参数：a    - 横向坡度系数
--参数：b    - 纵向坡度系数
--参数：hor  - 中心高
--说明：球数量限制，造型不佳
--==============================================================================
fn pyramidSpherePos a b hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	pos_max_x = a*abs(cx-1)
	pos_max_y = b*abs(cy-1)
	
	at time frame (
		for i = 1 to row by 2 do
		(
			pos_x = pos_max_x - a*abs(cx-i)
			for j = 1 to col by 2 do
			(
				pos_y = pos_max_y - b*abs(cy-j)
				BallArray[i][j].pos.z = pos_x + pos_y + hor
			)
		)
	)
)

--==============================================================================
--球阵指定时间内随机异步达到指定位置
--参数：pos1     - 指定Z轴位置值
--参数：pos2     - 指定Z轴位置值
--参数：range     - 指定Z轴位置值
--参数：delay     - 随机分布范围
--==============================================================================
fn horizSphereASynDelayPos pos1 pos2 range delay frame:FrameTime row:row col:column =
(

	for i = 1 to row by 2 do
	(
		frame += delay
		
		at time frame
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = pos1
			)
		)
		
		at time (frame+range)
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = pos2
			)
		)

	)
	
	return frame+range
)

--==============================================================================
--球阵横向延时水平面变换
--参数：pos1     - 指定Z轴位置值
--参数：pos2     - 指定Z轴位置值
--参数：range     - 指定Z轴位置值
--参数：delay     - 随机分布范围
--==============================================================================
fn horizSphereXDelayPos pos1 pos2 range delay frame:FrameTime row:row col:column =
(

	for i = 1 to row by 2 do
	(
		frame += delay
		
		at time frame
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = pos1
			)
		)
		
		at time (frame+range)
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = pos2
			)
		)

	)
	
	return frame+range
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
--参数：pos      - 高度
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--==============================================================================
fn paraboSpherePos pos hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	rmax2 = (cx-1)^2+(cy-1)^2  --49+9 = 58
	a = pos/rmax2
	
	at time frame
	(
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
--球阵形成马鞍形曲面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--==============================================================================
fn horseSpherePos a hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				rx = cx - i
				ry = cy - j
				r2 = rx*rx-ry*ry
				BallArray[i][j].pos.z = a*r2 + hor
			)
		)
	)
	
)

--==============================================================================
--球阵形成凹凸面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--说明：4x8球阵形成凹凸面效果不好
--==============================================================================
fn bossSpherePos a hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				x = i - cx
				y = j - cy
				r2 = -(x^2 + y^2)
				pos = a*x*exp(r2)
				BallArray[i][j].pos.z = pos + hor
			)
		)
	)
	
)

--==============================================================================
--球阵形成花变体
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--说明：效果不好
--==============================================================================
fn flowerSpherePos a hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				x = i - cx
				y = j - cy
				r = sqrt(x^2 + y^2)
				pos = a*sin(r)/r
				BallArray[i][j].pos.z = pos + hor
			)
		)
	)
	
)

--==============================================================================
--球阵形成躺椅曲面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--==============================================================================
fn chairSpherePos a hor cx:8 cy:4 frame:FrameTime row:row col:column =
(

	--rmax2 = (cx-1)^2-(cy-1)^2
	
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				x = i - cx
				y = j - cy
				r2 = -sqrt(x^2 + y^2)
				pos = a*x*r2
				BallArray[i][j].pos.z = pos + hor
			)
		)
	)
	
)

--==============================================================================
--球阵形成扭曲面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--==============================================================================
fn warpSpherePos a hor cx:8 cy:4 frame:FrameTime row:row col:column =
(

	--rmax2 = (cx-1)^2-(cy-1)^2
	
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				x = i - cx
				y = j - cy
				r2 = sqrt(x^2 + y^2)
				pos = a*x*y/r2
				BallArray[i][j].pos.z = pos + hor
			)
		)
	)
	
)

--==============================================================================
--球阵形成对角布悬曲面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：hor    - 中心高
--参数：flag    - 1 2 3 4数字区分四个角落
--==============================================================================
fn cornerSpherePos a hor flag frame:FrameTime row:row col:column =
(

	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				x = (i+1)/2  --1 2 3 ... 8
				y = (j+1)/2  --1 2 3 4
				case flag of
				(
				1: pos = (x+y)^2
				2: pos = (x+4-y)^2
				3: pos = (8-x+4-y)^2
				4: pos = (8-x+y)^2
				)
				BallArray[i][j].pos.z = a*pos + hor
			)
		)
	)
	
)


--==============================================================================
--球阵横向弧面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：flag    - 1 2 3 4数字区分四个角落
--==============================================================================
fn camberXSpherePos a hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = 49
	at time frame
	(
		for i = 1 to row by 2 do
		(
			x = (cx - i)^2

			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = a*(max_pos - x) + hor
			)
		)
	)
	
)

--==============================================================================
--球阵纵向弧面
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：flag    - 1 2 3 4数字区分四个角落
--==============================================================================
fn camberYSpherePos a hor cy:4 frame:FrameTime row:row col:column =
(
	max_pos = a*(cy-1)^2
	at time frame
	(
		for j = 1 to col by 2 do
		(
			y = (cy - j)^2

			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = a*(max_pos - y) + hor
			)
		)
	)
	
)

--==============================================================================
--球阵抛物面动态造型
--参数：a      - 系数（正开口向上，负开口向下）
--参数：cx,cy  - 中心点坐标
--参数：hor    - 中心高
--参数：hold   - 保持时间
--==============================================================================
fn paraboSphereDynamicPos a range hor hold cx:8 cy:4 frame:FrameTime row:row col:column =
(

	rmax2 = (cx-1)^2+(cy-1)^2
	
	start = frame
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				rx = cx - i
				ry = cy - j
				r2 = rx*rx+ry*ry
				BallArray[i][j].pos.z = hor
			)
		)
	)
	
	frame += range/2
	at time frame
	(
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
	
	frame += hold
	at time frame
	(
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
	
	frame += range/2
	at time frame
	(
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				rx = cx - i
				ry = cy - j
				r2 = rx*rx+ry*ry
				BallArray[i][j].pos.z = hor
			)
		)
	)
	
	
	return frame
)
/*
--==============================================================================
--逐个环形启动，回字形
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--说明：振幅随完整波形的次数count逐次增加
--==============================================================================
fn sinSphereSinglePos amp count dur delay hor da frame:FrameTime row:row col:column =
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
			
			temp1 = amp - da   --让小球起始振幅为amp的权宜之计
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor )
				temp += df
				--每隔一个周期振幅增加da
				if ((mod (t-1) c) == 0) then temp1 += da
			)
			
		)
		
	)

	return (frame + dur*count)
)
*/

--==============================================================================
--球阵沿X轴向逐个延时启动正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereSingleXNPos amp count dur delay hor frame:FrameTime row:row col:column =
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
--球阵沿X轴向逐个延时启动正弦波动，振幅周期性线性变化
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--说明：振幅随完整波形的次数count逐次增加
--==============================================================================
fn sinSphereSingleXPos amp count dur delay hor da frame:FrameTime row:row col:column =
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
			
			temp1 = amp - da   --让小球起始振幅为amp的权宜之计
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor )
				temp += df
				--每隔一个周期振幅增加da
				if ((mod (t-1) c) == 0) then temp1 += da
			)
			
		)
		
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵沿Y轴向逐个延时启动正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereSingleYNPos amp count dur delay hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for j = 1 to col by 2 do
	(
		for i = 1 to row by 2 do
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
--球阵沿Y轴向逐个延时启动正弦波动，振幅周期性线性变化
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--说明：振幅随完整波形的次数count逐次增加
--==============================================================================
fn sinSphereSingleYPos amp count dur delay hor da frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for j = 1 to col by 2 do
	(
		for i = 1 to row by 2 do
		(
			frame += delay
			temp = frame
			
			temp1 = amp - da   --让小球起始振幅为amp的权宜之计
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor )
				temp += df
				--每隔一个周期振幅增加da
				if ((mod (t-1) c) == 0) then temp1 += da
			)
			
		)
		
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵X轴行波
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereXNPos amp count dur delay hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for i = 1 to row by 2 do
	(
		frame += delay
		temp = frame

		for t = 1 to c*count+1 do
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
--球阵X轴行波，横向方向振幅线性变化
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinSphereXPos amp count dur delay hor da frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for i = 1 to row by 2 do
	(
		frame += delay
		temp = frame
		
		temp1 = amp - da   --让小球起始振幅为amp的权宜之计
		for t = 1 to c*count+1 do
		(
			at time temp
			(
				for j = 1 to col by 2 do ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor  )
			)
			temp += df
			--每隔一个周期振幅增加da
			if ((mod (t-1) c) == 0) then temp1 += da
		)
		
	)
		
	return (frame + dur*count)
)

--==============================================================================
--球阵X轴行波，纵向方向振幅线性变化
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--参数：direct    - 起始方向
-- 振幅与行号呈线性关系
--==============================================================================
fn sinSphereRateXPos amp count dur delay hor da direct frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for i = 1 to row by 2 do
	(
		frame += delay
		temp = frame
		
		temp2 = amp
		for t = 1 to c*count+1 do
		(
			at time temp
			(
				for j = 1 to col by 2 do 
				( 
					case direct of
					(
					1: y = 4 - (j+1)/2
					2: y = (j+1)/2 - 1			
					)
					--y = (j+1)/2
					temp1 = temp2*y
					BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor  
				)
			)
			temp += df
			--每隔一个周期振幅增加da
			if ((mod (t-1) c) == 0) then temp2 += da
		)
		
	)
		
	return (frame + dur*count)
)

--==============================================================================
--球阵Y轴列波
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereYNPos amp count dur delay hor frame:FrameTime row:row col:column =
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
--球阵Y轴列波，振幅周期性线性变化
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinSphereYPos amp count dur delay hor da frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for j = 1 to col by 2 do
	(
		frame += delay
		temp = frame
		
		temp1 = amp - da   --让小球起始振幅为amp的权宜之计
		for t = 1 to (c*count+1) do
		(
			at time temp 
			(
				for i = 1 to row by 2 do ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor  )
			)
			temp += df
			--每隔一个周期振幅增加da
			if ((mod (t-1) c) == 0) then temp1 += da
		)
		
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵Y轴列波
--参数：a    - 振幅相关系数
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--参数：direct    - 起始方向
-- 振幅与行号呈线性关系
--==============================================================================
fn sinSphereRateYPos a count dur delay hor da direct frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	for j = 1 to col by 2 do
	(
		frame += delay
		temp = frame
		
		temp2 = a
		for t = 1 to (c*count+1) do
		(
			at time temp 
			(
				for i = 1 to row by 2 do 
				( 
					case direct of
					(
					1: x = 8 - (i+1)/2
					2: x = (i+1)/2 - 1			
					)
					
					temp1 = temp2*x
					BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor  
				)
			)
			temp += df
			--每隔一个周期振幅增加da
			if ((mod (t-1) c) == 0) then temp2 += da
		)
		
	)
	
	return (frame + dur*count)
)


--==============================================================================
--球阵斜波
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--参数：direct     - 造型起点，1表示左下方，2表示左上方，3表示右下方，4表示右上方
--从白翠霞的脚本得到启发：抓住每个小球起始运行的时刻，不要被多重嵌套循环迷惑
--==============================================================================
fn sinSphereRatePos amp count dur delay hor da direct frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	flag = direct
	
	for i = 1 to row by 2 do
	(
		start = frame
		for j = 1 to col by 2 do
		(
			case flag of
			(
			1: start = frame + ((i+j)/2-1)*delay
			2: start = frame + ((i+col+1-j)/2-1)*delay
			3: start = frame + ((row+1-i+j)/2-1)*delay
			4: start = frame + ((row+1-i+col+1-j)/2-1)*delay
			defalut: undefined
			)
			
			temp = start
			temp1 = amp - da   --让小球起始振幅为amp的权宜之计
			for t = 1 to (c*count+1) do
			(
				at time temp
				(
					BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor
				)
				temp += df
				--每隔一个周期振幅增加da
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
	)
	
	return (frame + 10*delay + dur*count)
)

--==============================================================================
--球阵由中心启动延时效果正弦波动，振幅不变
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereCNPos amp count dur hor cx:8 cy:4 frame:FrameTime row:row col:column =
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

--==============================================================================
--球阵由中心启动延时效果正弦波动，振幅周期性线性变化
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinSphereCPos amp count dur hor da cx:8 cy:4 frame:FrameTime row:row col:column =
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
			temp1 = amp - da   --让小球起始振幅为amp的权宜之计
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor )
				temp += df
				--每隔一个周期振幅增加da
				if ((mod (t-1) c) == 0) then temp1 += da
			)
			
		)
	)

	return (enter + rmax2 + dur*count)
)

-------------------------------球阵区别奇偶造型-----------------------------------

--==============================================================================
--沿X轴线性交错，基准在X轴中心
--参数：a    - 位置相关系数
--参数：hor - 中心高
--==============================================================================
fn rateXCOESpherePos a hor cx:8 frame:FrameTime row:row col:column =
(

	at time frame (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = cx - i  -- 最大为7
				BallArray[i][j].pos.z = a*x + hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = cx - i
				BallArray[i][j].pos.z = -a*x + hor
			)
		)
	)

)

--==============================================================================
--沿Y轴线性交错，基准在Y轴中心
--参数：pos    - 基准单向高度
--参数：hor    - 中心高
--==============================================================================
fn rateYCOESpherePos pos hor cy:4 frame:FrameTime row:row col:column =
(
	a = pos/7
	at time frame (
		for i = 1 to row-2 by 4 do
		(
			for j = 1 to col by 2 do
			(
				y = j - cy  -- 最大为7
				BallArray[i][j].pos.z = a*y + hor
			)
		)
		
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				y = j - cy
				BallArray[i][j].pos.z = -a*y + hor
			)
		)
	)

)

--==============================================================================
--沿X轴线性交错
--参数：a    - 位置相关系数
--参数：hor - 中心高
--==============================================================================
fn rateXOESpherePos a  hor frame:FrameTime row:row col:column =
(
	start = frame

	
	at time frame (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = (i+1)/2 - 1
				BallArray[i][j].pos.z = a*x + hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = 8 - (i+1)/2
				BallArray[i][j].pos.z = a*x + hor
			)
		)
	)
	

	return frame
)

--==============================================================================
--沿X轴线性交错
--参数：a    - 位置相关系数
--参数：hor - 中心高
--==============================================================================
fn rateXOESphereTestPos a range hor frame:FrameTime row:row col:column =
(
	start = frame
	
	at time start (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				BallArray[i][j].pos.z = hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				BallArray[i][j].pos.z = hor
			)
		)
	)
	
	frame += range/2
	at time frame (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = (i+1)/2 - 1
				BallArray[i][j].pos.z = a*x + hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = 8 - (i+1)/2
				BallArray[i][j].pos.z = a*x + hor
			)
		)
	)
	
	frame += range/2
	at time frame (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = (i+1)/2 - 1
				BallArray[i][j].pos.z = hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = 8 - (i+1)/2
				BallArray[i][j].pos.z = hor
			)
		)
	)
	

	return frame
)

--==============================================================================
--沿Y轴线性交错
--参数：a    - 位置相关系数
--参数：hor - 中心高
--==============================================================================
fn rateYOESpherePos a range hor frame:FrameTime row:row col:column =
(
	start = frame
	
	at time start (
		for i = 1 to row-2 by 4 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = hor
			)
		)
		
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = hor
			)
		)
	)
	
	frame += range/2
	at time frame (
		for i = 1 to row-2 by 4 do
		(
			for j = 1 to col by 2 do
			(
				y = (j+1)/2 - 1
				BallArray[i][j].pos.z = a*y + hor
			)
		)
		
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				y = 4 - (j+1)/2
				BallArray[i][j].pos.z = a*y + hor
			)
		)
	)
	
	frame += range/2
	at time frame (
		for i = 1 to row-2 by 4 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = hor
			)
		)
		
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = hor
			)
		)
	)

	return frame
)

--==============================================================================
--球阵沿Y轴方向分为2部分作相反正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinBXOESpherePos amp count dur delay hor da frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	start = frame
	
	for j = 1 to col-4 by 2 do
	(
		frame = start
		for i = 1 to row by 2 do
		(
			frame += delay
			temp = frame
			temp1 = amp
			for t = 1 to (c*count+1) do
			(
				at time temp 
				( 
					BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor
				)
				temp += df
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
	)
	
	for j = 5 to col by 2 do
	(
		frame = start
		for i = 1 to row by 2 do
		(
			frame += delay
			temp = frame
			temp1 = amp
			for t = 1 to (c*count+1) do
			(
				at time temp 
				( 
					BallArray[i][j].pos.z = -temp1*sin(dt*(t-1)) + hor
				)
				temp += df
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
	)

	return (frame + dur*count)
)

----------------------------------跳动造型--------------------------------------
--==============================================================================
--球阵X轴向奇偶不同列互为反向正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinXOESpherePos amp count dur hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	start = frame
	
	for i = 1 to row-2 by 4 do
	(

			temp = start
		
			for t = 1 to (c*count+1) do
			(
				at time temp ( 
					for j = 1 to col by 2 do ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
				)
				temp += df
			)

	)
	
	for i = 3 to row by 4 do
	(

			temp = start
		
			for t = 1 to (c*count+1) do
			(
				at time temp ( 
					for j = 1 to col by 2 do ( BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor )
				)
				temp += df

			)
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵Y轴向奇偶不同列互为反向正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinYOESpherePos amp count dur hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	start = frame
	
	for j = 1 to col-2 by 4 do
	(

			temp = start
		
			for t = 1 to (c*count+1) do
			(
				at time temp ( 
					for i = 1 to row by 2 do ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
				)
				temp += df
			)

	)
	
	for j = 3 to col by 4 do
	(

			temp = start
		
			for t = 1 to (c*count+1) do
			(
				at time temp ( 
					for i = 1 to row by 2 do ( BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor )
				)
				temp += df

			)
	)

	return (frame + dur*count)
)

--==============================================================================
--球阵XY轴向奇偶不同列互为反向正弦波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinXYOESpherePos amp count dur hor frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	start = frame
	
	for i = 1 to row-2 by 4 do
	(

		temp = start
		
			for t = 1 to (c*count+1) do
			(
				at time temp ( 
					for j = 1 to col-2 by 4 do 
					( 
						BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor 
					)
					
					for j = 3 to col by 4 do 
					( 
						BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor 
					)
				)
				temp += df
			)	

	)
	
	for i = 3 to row by 4 do
	(

			temp = start
		
			for t = 1 to (c*count+1) do
			(
				at time temp ( 
					for j = 1 to col-2 by 4 do 
					( 
						BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor 
					)
					
					for j = 3 to col by 4 do 
					( 
						BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor 
					)
				)
				temp += df
			)
	)

	return (frame + dur*count)
)

----------------------------------非同动造型--------------------------------------
--==============================================================================
--球阵逐列延时到达指定平面
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn SphereXDelayPos pos dur delay hor frame:FrameTime row:row col:column =
(
	for i = 1 to row by 2 do
	(
		frame += delay
		
		at time frame ( for j = 1 to col by 2 do BallArray[i][j].pos.z = hor )

		
		at time (frame+dur) ( for j = 1 to col by 2 do BallArray[i][j].pos.z = pos + hor )
	
	)

	return (frame + dur)
)

--==============================================================================
--球阵逐列延时到达指定平面
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn horizSphereXDelayPos pos dur delay hor frame:FrameTime row:row col:column =
(
	for i = 1 to row by 2 do
	(
		frame += delay
		
		at time frame ( for j = 1 to col by 2 do BallArray[i][j].pos.z = hor )

		
		at time (frame+dur) ( for j = 1 to col by 2 do BallArray[i][j].pos.z = pos + hor )
	
	)

	return (frame + dur)
)

--==============================================================================
--球阵逐行延时到达指定平面
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn SphereYDelayPos pos dur delay hor frame:FrameTime row:row col:column =
(
	for j = 1 to col by 2 do
	(
		frame += delay
		
		at time frame ( for i = 1 to row by 2 do BallArray[i][j].pos.z = hor )

		
		at time (frame+dur) ( for i = 1 to row by 2 do BallArray[i][j].pos.z = pos + hor )
	
	)

	return (frame + dur)
)

--==============================================================================
--球阵逐行延时到达指定平面
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn horizSphereYDelayPos pos dur delay hor frame:FrameTime row:row col:column =
(
	for j = 1 to col by 2 do
	(
		frame += delay
		
		at time frame ( for i = 1 to row by 2 do BallArray[i][j].pos.z = hor )

		
		at time (frame+dur) ( for i = 1 to row by 2 do BallArray[i][j].pos.z = pos + hor )
	
	)

	return (frame + dur)
)


--==============================================================================
--球阵内圈上下波动
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereRectInDelayPos amp count dur hor frame:FrameTime row:row col:column =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp (
			--内圈
			for i = 1 to row by 2 do
			(
				for j = 1 to col by 2 do
				(
					if ((i>1)and(i<15)and((j>1)and(j<7))) then
						BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor
				)
			)
		)
		temp += df
	)
	
	return frame+count*dur
)

--==============================================================================
--球阵外圈上下波动
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereRectOutDelayPos amp count dur hor frame:FrameTime row:row col:column =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间

	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp (
			--外圈
			for i = 1 to row by 2 do
			(
				for j = 1 to col by 2 do
				(
					if (((i==1)or(i==15))or((j==1)or(j==7))) then
						BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor
				)
			)
		)
		temp += df
	)
	
	return frame+count*dur
)
