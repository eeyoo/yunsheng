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
--参数：pos    - 基准最大偏距
--参数：hor    - 基准面
--==============================================================================
fn rateSphereCXPos pos hor cx:8 frame:FrameTime row:row col:column =
(
	a = pos/(cx-1)
	at time frame (
		for i = 1 to row by 2 do
		(
			x = i - cx  --绝对值最大7
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = -a*x + hor
			)
		)
	)
)

--==============================================================================
--Y轴向斜面造型，基准在中心
--参数：pos    - 基准最大偏距
--参数：hor    - 基准面
--==============================================================================
fn rateSphereCYPos pos hor cy:4 frame:FrameTime row:row col:column =
(
	a = pos/(cy-1)
	at time frame (
		for j = 1 to col by 2 do
		(
			y = j - cy  --绝对值最大3
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
--X轴向平行双斜面造型
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--==============================================================================
fn rateCXASpherePos pos hor cx:8 frame:FrameTime row:row col:column =
(
	a = pos/3
	
	at time frame (
		for j = 1 to col by 2 do
		(

			for i = 1 to row by 2 do
			(
				if (i<9) then 
				(
					x = i - 4
					BallArray[i][j].pos.z = a*x + hor
				)
				
				if (i>7) then
				(
					x = i - 12
					BallArray[i][j].pos.z = a*x + hor
				)
			)
		)
	)

)

--==============================================================================
--X轴向塔形斜面造型
--参数：pos    - 斜面高度
--参数：hor    - 基准面
--==============================================================================
fn rateCXBSpherePos pos hor cx:8 frame:FrameTime row:row col:column =
(
	a = pos/3
	
	at time frame (
		for j = 1 to col by 2 do
		(

			for i = 1 to row by 2 do
			(
				if (i<9) then 
				(
					x = i - 4
					BallArray[i][j].pos.z = a*x + hor
				)
				
				if (i>7) then
				(
					x = i - 12
					BallArray[i][j].pos.z = -a*x + hor
				)
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
--Z轴随机位置矩阵
--参数：rmin,rmax - 指定Z轴随机位置下限和上限
--==============================================================================
fn randomOddXYSpherePos rmin rmax frame:FrameTime row:row col:column =
(
	at time frame (
		for i = 1 to (row-2) by 4 do
		(
			for j = 1 to (col-2) by 4 do
			(
				
				BallArray[i][j].pos.z = random rmin rmax
			)
		)
	)
)

--==============================================================================
--Z轴随机位置矩阵
--参数：rmin,rmax - 指定Z轴随机位置下限和上限
--==============================================================================
fn randomOddXSpherePos rmin rmax frame:FrameTime row:row col:column =
(
	at time frame (
		for i = 1 to (row-2) by 4 do
		(
			for j = 1 to col by 2 do
			(
				
				BallArray[i][j].pos.z = random rmin rmax
			)
		)
	)
)

--==============================================================================
--Z轴随机位置矩阵
--参数：rmin,rmax - 指定Z轴随机位置下限和上限
--==============================================================================
fn randomEvenXYSpherePos rmin rmax frame:FrameTime row:row col:column =
(
	at time frame (
		for i = 3 to row by 4 do
		(
			for j = 3 to col by 4 do
			(
				
				BallArray[i][j].pos.z = random rmin rmax
			)
		)
	)
)

--==============================================================================
--Z轴随机位置矩阵
--参数：rmin,rmax - 指定Z轴随机位置下限和上限
--==============================================================================
fn randomEvenXSpherePos rmin rmax frame:FrameTime row:row col:column =
(
	at time frame (
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				
				BallArray[i][j].pos.z = random rmin rmax
			)
		)
	)
)

--==============================================================================
--Z轴随机位置矩阵
--参数：rmin,rmax - 指定Z轴随机位置下限和上限
--参数：hold      - 保持最终位置时间/帧
--==============================================================================
fn randomHoldSpherePos rmin rmax hold frame:FrameTime row:row col:column =
(
	rand_pos = #()
	at time frame (
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				append rand_pos (random rmin rmax)
				x = (i+1)/2
				y = (j+1)/2
				index = 4*(x-1) + y  --4x8二维转成一维
				BallArray[i][j].pos.z = rand_pos[index]
			)
		)
	)
	
	frame += hold
	at time frame (
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				--append rand_pos (random rmin rmax)
				x = (i+1)/2
				y = (j+1)/2
				index = 4*(x-1) + y  --4x8二维转成一维
				BallArray[i][j].pos.z = rand_pos[index]
			)
		)
	)
	
	return frame
)

--==============================================================================
--随机下落
--参数：amp   - 随机下落高度
--参数：dur   - 停止跳动时间
--参数：delay - 延时时间
--参数：hor   - 基准高
--==============================================================================
fn randomDownSpherePos amp dur delay hor frame:FrameTime row:row col:column =
(
	n = 8    --越大弹跳次数越多
	dt = 360/n
	df = dur/n
	a = amp/n
	
	--创建延时矩阵
	delay_array = #()
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			rand = random 0 delay
			append delay_array rand
			
			temp = frame + rand
			
			for t = 1 to (n+1) do
			(
				temp1 = amp - a*(t-1)
				at time temp ( BallArray[i][j].pos.z = temp1*abs(cos(dt*(t-1))) + hor )
				temp += df
			)
		)
	)
	--延时矩阵排序找到最长延时时间
	sort delay_array
	index = delay_array.count
	max_delay = delay_array[index]
	
	return frame + max_delay + dur
)


--==============================================================================
--随机向上弹跳
--参数：amp   - 随机下落高度
--参数：dur   - 停止跳动时间
--参数：delay - 延时时间
--参数：hor   - 基准高
--==============================================================================
fn randomUpSpherePos amp dur delay hor frame:FrameTime row:row col:column =
(
	n = 4
	dt = 360/n
	df = dur/n
	a = amp/n
	
	--创建延时矩阵
	delay_array = #()
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			rand = random 0 delay
			append delay_array rand
			
			temp = frame + rand
			
			for t = 1 to (n+1) do
			(
				temp1 = amp - a*(t-1)
				at time temp ( BallArray[i][j].pos.z = temp1*abs(sin(dt*(t-1))) + hor )
				temp += df
			)
		)
	)
	--延时矩阵排序找到最长延时时间
	sort delay_array
	index = delay_array.count
	max_delay = delay_array[index]
	
	return frame + max_delay + dur
)

--==============================================================================
--随机向上弹跳
--参数：pmin  - 最小随机位置
--参数：pmax  - 最大随机位置
--参数：dur   - 停止跳动时间
--参数：dmin  - 最小延时时间
--参数：dmax  - 最大延时时间
--参数：hor   - 基准高
--==============================================================================
fn randomUpHorizSpherePos pmin pmax dur dmin dmax hor frame:FrameTime row:row col:column =
(
	--位置矩阵
	pos_array = #()
	--创建延时矩阵
	delay_array = #()
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			x = (i+1)/2
			y = (j+1)/2
			index = 4*(x-1) + y  --4x8二维转成一维
			
			rand = random dmin dmax
			append delay_array rand
			
			pos = random pmin pmax
			append pos_array pos
			
			temp = frame + rand

			at time temp ( BallArray[i][j].pos.z = hor )
			
			at time (temp+dur) ( BallArray[i][j].pos.z = pos_array[index] + hor )
			
		)
	)
	--延时矩阵排序找到最长延时时间
	sort delay_array
	index = delay_array.count
	max_delay = delay_array[index]
	
	return frame + max_delay + dur
)

--==============================================================================
--随机向上形成凸面
--参数：amp   - 随机下落高度
--参数：dur   - 停止跳动时间
--参数：delay - 延时时间
--参数：hor   - 基准高
--==============================================================================
fn randomUpParaboSpherePos pmin pmax dur delay hor cx:8 cy:4 frame:FrameTime row:row col:column =
(
	--位置矩阵
	pos_array = #()
	--创建延时矩阵
	delay_array = #()
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			x = (i+1)/2
			y = (j+1)/2
			index = 4*(x-1) + y  --4x8二维转成一维
			
			rand = random (delay-30) delay
			append delay_array rand
			
			pos = random pmin pmax
			append pos_array pos
			
			temp = frame + rand

			at time temp ( BallArray[i][j].pos.z = hor )
			
			at time (temp+dur) ( BallArray[i][j].pos.z = pos_array[index] + hor )
			
		)
	)
	--延时矩阵排序找到最长延时时间
	sort delay_array
	index = delay_array.count
	max_delay = delay_array[index]
	
	return frame + max_delay + dur
)

--==============================================================================
--爆炸造型，随机下落时速度恒定
--参数：amp   - 随机下落高度
--参数：vel   - 随机下落速度
--参数：dur   - 停止跳动时间
--参数：delay - 延时时间
--参数：hor   - 爆炸点
--==============================================================================
fn boomDownSpherePos pos dur delay hor frame:FrameTime row:row col:column =
(
	--n = 4
	--dt = 360/n
	--df = dur/n
	--a = amp/n
	
	--创建延时矩阵
	delay_array = #()
	--创建位置矩阵
	pos_array = #()
	
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			x = (i+1)/2
			y = (j+1)/2
			index = 4*(x-1)+y
			
			rand = random 0 delay
			append delay_array (random 5 delay)
			
			append pos_array (random hor pos)
			
			--temp = frame + rand
			
			at time frame ( BallArray[i][j].pos.z = pos_array[index] )
			at time (frame+rand) ( BallArray[i][j].pos.z = pos_array[index] )
			at time (frame+rand+dur) ( BallArray[i][j].pos.z = hor )
		
		)
	)

	--延时矩阵排序找到最长延时时间
	sort delay_array
	index = delay_array.count
	max_delay = delay_array[index]
	
	return frame + max_delay + dur
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
--参数：pos    - 造型高度
--参数：hor    - 中心高
--参数：flag   - 1 2 3 4数字区分四个角落
--==============================================================================
fn cornerSpherePos pos hor flag frame:FrameTime row:row col:column =
(
	pos_max = (8+4)^2
	a = pos/pos_max
	
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
				2: pos = (x+5-y)^2
				3: pos = (9-x+5-y)^2
				4: pos = (9-x+y)^2
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
--球阵笑脸造型
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileSpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--奇数形成咧嘴
		for j = 1 to (col-2) by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = (i-cx)^2   --49
				BallArray[i][j].pos.z = -pos1 - a*(max_pos - x) + hor
			)
		)
			
		
		--偶数形成眼睛
		for j = 3 to col by 4 do
		(			
			for i = 1 to row by 2 do
			(
				if (i<9) then 
				(
					y = (i-4)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
				
				if (i>7) then 
				(
					y = (i-12)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
			)
		)
	)
	
)

--==============================================================================
--球阵笑脸造型B
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileBSpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--全部形成咧嘴
		for j = 1 to col by 2 do
		(
			for i = 1 to row by 2 do
			(
				x = (i-cx)^2   --49
				BallArray[i][j].pos.z = -pos1 - a*(max_pos - x) + hor
			)
		)
			
		
		--偶数部分球形成眼睛
		for j = 3 to col by 4 do
		(			
			for i = 1 to row by 2 do
			(
				if (i<7)and(i>1) then 
				(
					y = (i-4)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
				
				if (i>9)and(i<row) then 
				(
					y = (i-12)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
			)
		)
	)
	
)

--==============================================================================
--球阵笑脸造型B
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileBSpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--全部形成咧嘴
		for j = 1 to col by 2 do
		(
			for i = 1 to row by 2 do
			(
				x = (i-cx)^2   --49
				BallArray[i][j].pos.z = -pos1 - a*(max_pos - x) + hor
			)
		)
			
		
		--偶数部分球形成眼睛
		for j = 3 to col by 4 do
		(			
			for i = 1 to row by 2 do
			(
				if (i<7)and(i>1) then 
				(
					y = (i-4)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
				
				if (i>9)and(i<row) then 
				(
					y = (i-12)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
			)
		)
	)
	
)

--==============================================================================
--球阵笑脸造型C，一个点
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileCSpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--全部形成咧嘴
		for j = 1 to col by 2 do
		(
			for i = 1 to row by 2 do
			(
				x = (i-cx)^2   --49
				BallArray[i][j].pos.z = -pos1 - a*(max_pos - x) + hor
			)
		)
			
		
		--偶数部分球形成眼睛
		for j = 3 to col by 4 do
		(			
			for i = 1 to row by 2 do
			(
				if (i==3) then 
				(
					y = (i-4)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
				
				if (i==13) then 
				(
					y = (i-12)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
			)
		)
	)
	
)

--==============================================================================
--球阵笑脸造型D，两个点
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileDSpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--全部形成咧嘴
		for j = 1 to col by 2 do
		(
			for i = 1 to row by 2 do
			(
				x = (i-cx)^2   --49
				BallArray[i][j].pos.z = -pos1 - a*(max_pos - x) + hor
			)
		)
			
		
		--偶数部分球形成眼睛
		for j = 3 to col by 4 do
		(			
			for i = 1 to row by 2 do
			(
				if (i<9)and(j==3) then 
				(
					y = (i-4)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
				
				if (i<9)and(j==col) then 
				(
					y = (i-4)^2   --9
					BallArray[i][j].pos.z = pos2 - b*(max_pos1 - y) + hor
				)
				
				if (i>7)and(j==3) then 
				(
					y = (i-12)^2   --9
					BallArray[i][j].pos.z = pos2 + b*(max_pos1 - y) + hor
				)
				
				if (i>7)and(j==col) then 
				(
					y = (i-12)^2   --9
					BallArray[i][j].pos.z = pos2 - b*(max_pos1 - y) + hor
				)
			)
		)
		
		
	)
	
)

--==============================================================================
--球阵笑脸造型E，一个点
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileESpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--第1行形成咧嘴
		for i = 1 to row by 2 do
		(
			x = (i-cx)^2   --49
			BallArray[i][1].pos.z = -pos1 - a*(max_pos - x) + hor
		)
			
		
		--第2行球形成眼睛
		--y = (i-4)^2   --9
		BallArray[3][3].pos.z = pos2 + b*(max_pos1 - 1) + hor
		BallArray[13][3].pos.z = pos2 + b*(max_pos1 - 1) + hor			
	)
	
)

--==============================================================================
--球阵笑脸造型E1，一个点
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileE1SpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	--max_pos = a*(cx-1)^2
	
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--第1行形成咧嘴
		for i = 1 to row by 2 do
		(
			x = (i-cx)^2   --49
			BallArray[i][1].pos.z = -pos1 - a*(max_pos - x) + hor
		)
			
		
		--第2行球形成眼睛
		--y = (i-4)^2   --9
		BallArray[5][3].pos.z = pos2 + b*(max_pos1 - 1) + hor
		BallArray[11][3].pos.z = pos2 + b*(max_pos1 - 1) + hor			
	)
	
)

--==============================================================================
--球阵笑脸造型F，两个点
--参数：pos1   - 眼睛高度
--参数：pos2   - 咧嘴高度
--参数：hor    - 中心高
--==============================================================================
fn smileFSpherePos a pos1 b pos2 hor cx:8 frame:FrameTime row:row col:column =
(
	max_pos = (1-cx)^2  --7x7=49
	max_pos1 = 9
	
	at time frame
	(
		--第1行形成咧嘴
		for i = 1 to row by 2 do
		(
			x = (i-cx)^2   --49
			BallArray[i][1].pos.z = -pos1 - a*(max_pos - x) + hor
		)
			
		
		--第2行球形成眼睛
		--y = (i-4)^2   --9
		BallArray[3][3].pos.z = pos2 + b*(max_pos1 - 1) + hor
		BallArray[5][3].pos.z = pos2 + b*(max_pos1 - 1) + hor
		BallArray[11][3].pos.z = pos2 + b*(max_pos1 - 1) + hor
		BallArray[13][3].pos.z = pos2 + b*(max_pos1 - 1) + hor			
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
--逐个环形启动，回字形形如蛇形
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--说明：振幅随完整波形的次数count逐次增加
--==============================================================================
fn sinSphereSnakePos amp count dur delay hor da frame:FrameTime row:row col:column =
(
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	--前端1
	for i = 1 to row by 2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][1].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--右端1
	for j = 3 to col by 2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[row][j].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--后端1
	for i = (row-2) to 1 by -2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][col].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--左端1
	for j = (col-2) to 3 by -2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[1][j].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--前端2
	for i = 3 to (row-2) by 2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][3].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--后端2
	for i = (row-2) to 3 by -2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][col-2].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	return frame+count*dur
)

/**********************************************************************************
--==============================================================================
--逐个环形启动，终点随机
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--说明：振幅随完整波形的次数count逐次增加
--==============================================================================
fn sinSphereSnakeRandomPos pmin pmax dur delay hor frame:FrameTime row:row col:column =
(
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	pos_array = #()
	--前端1
	for i = 1 to row by 2 do
	(
		x = (i+1)/2
		y = (1+1)/2
		index = 4*(x-1)+y
	
		pos = random pmin pmax
		append pos_array pos
		
		frame += delay
		temp = frame
		
		at time temp ( BallArray[i][1].pos.z =  hor )
		
		at time (temp+dur) ( BallArray[i][1].pos.z = pos + hor )
		
	)
	
	--右端1
	for j = 3 to col by 2 do
	(
		x = (row+1)/2
		y = (1+1)/2
		index = 4*(x-1)+y
	
		pos = random pmin pmax
		append pos_array pos
		
		frame += delay
		temp = frame
		
		at time temp ( BallArray[row][j].pos.z = hor )
		at time temp ( BallArray[row][j].pos.z = pos + hor )
	)
	
	--后端1
	for i = (row-2) to 1 by -2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][col].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--左端1
	for j = (col-2) to 3 by -2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[1][j].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--前端2
	for i = 3 to (row-2) by 2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][3].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	--后端2
	for i = (row-2) to 3 by -2 do
	(
		frame += delay
		temp = frame
		temp1 = amp
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( BallArray[i][col-2].pos.z = temp1*sin(dt*(t-1)) + hor )
			temp += df

			if ((mod (t-1) c) == 0) then temp1 += da
		)
	)
	
	return frame+count*dur
)
************************************************************************************/

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
--球阵X轴浮动行波
--参数：amp    - 振幅
--参数：amp1    - 基准浮动振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinSphereXFPos amp amp1 count dur delay hor frame:FrameTime row:row col:column =
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
			pos = amp1*sin(dt*(t-1)) + hor
			
			at time temp
			(
				BallArray[i][1].pos.z = amp*sin(dt*(t-1)) + pos
			)

			temp += df
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

	a = amp/(col-1)
	
	for i = 1 to row by 2 do
	(
		frame += delay
		temp = frame
		temp1 = a
		
		for t = 1 to c*count+1 do
		(
			at time temp
			(
				for j = 1 to col by 2 do 
				( 
					case direct of
					(
					1: y = col - j
					2: y = j - 1		
					)

					temp1 = a*y
					
					BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor  
				)
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
--球阵Y轴列波，振幅与行号呈线性关系
--参数：amp    - 最大振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：delay  - 逐列延时时间
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--参数：direct    - 起始方向
--==============================================================================
fn sinSphereRateYPos amp count dur delay hor da direct frame:FrameTime row:row col:column =
(
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	a = amp/(row-1)
	
	for j = 1 to col by 2 do
	(
		frame += delay
		temp = frame
		temp1 = a
		
		for t = 1 to (c*count+1) do
		(
			at time temp 
			(
				for i = 1 to row by 2 do 
				( 
					case direct of
					(
					1: x = row - i
					2: x = i - 1	
					)
					
					temp1 = a*x
					
					BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor  
				)
			)
			temp += df
			--每隔一个周期振幅增加da
			if ((mod (t-1) c) == 0) then temp1 += da
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
--参数：pos    - 基准单向高度
--参数：hor - 中心高
--==============================================================================
fn rateXCOESpherePos pos hor cx:8 frame:FrameTime row:row col:column =
(
	n = cx - 1
	a = pos/n
	
	at time frame (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = i - cx  -- 绝对值最大为7
				BallArray[i][j].pos.z = a*x + hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				x = i - cx  -- 绝对值最大为7
				BallArray[i][j].pos.z = -a*x + hor
			)
		)
	)

)

--==============================================================================
--沿X轴线性交错
--参数：pos   - 高度
--参数：hor - 中心高
--==============================================================================
fn rateXOESpherePos pos hor frame:FrameTime row:row col:column =
(
	a = pos/row
	
	at time frame (
		for j = 1 to col-2 by 4 do
		(
			for i = 1 to row by 2 do
			(
				BallArray[i][j].pos.z = a*i + hor
			)
		)
		
		for j = 3 to col by 4 do
		(
			for i = 1 to row by 2 do
			(
				BallArray[i][j].pos.z = -a*i + hor
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
	a = pos/(cy-1)
	
	at time frame (
		for i = 1 to row-2 by 4 do
		(
			for j = 1 to col by 2 do
			(
				y = j - cy  --绝对值最大为3
				BallArray[i][j].pos.z = a*y + hor
			)
		)
		
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				y = j - cy  --绝对值最大为3
				BallArray[i][j].pos.z = -a*y + hor
			)
		)
	)

)

--==============================================================================
--沿Y轴线性交错
--参数：pos    - 高度
--参数：hor - 中心高
--==============================================================================
fn rateYOESpherePos pos range hor frame:FrameTime row:row col:column =
(
	
	a = pos/col
	
	at time frame (
		for i = 1 to row-2 by 4 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = a*j + hor
			)
		)
		
		for i = 3 to row by 4 do
		(
			for j = 1 to col by 2 do
			(
				BallArray[i][j].pos.z = -a*j + hor
			)
		)
	)

)

--==============================================================================
--球阵Y轴方向奇偶同时启动正弦波动，方向相反
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinBXOESpherePos amp count dur delay hor da frame:FrameTime row:row col:column =
(
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	
	for i =1 to row by 2 do
	(
		frame += delay
		
		--Y轴奇数
		for j = 1 to (col-2) by 4 do 
		( 
			temp = frame
			temp1 = amp-da
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + hor )
				temp += df
					
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
		
		--Y轴偶数
		for j = 3 to col by 4 do 
		( 
			temp = frame
			temp1 = amp-da
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = -temp1*sin(dt*(t-1)) + hor )
				temp += df
					
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
	)
	
	return (frame + dur*count)
)

--==============================================================================
--球阵Y轴方向分层波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinXRateYSpherePos amp count dur delay hor high da cy:4 frame:FrameTime row:row col:column =
(
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	a = high /(cy-1)
	
	for i =1 to row by 2 do
	(
		frame += delay
		
		--行基准线性变化
		for j = 1 to col by 2 do
		(
			y = j - cy
			temp = frame
			temp1 = amp-da
			
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + a*y + hor )
				temp += df
					
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
		
	)
	
	return (frame + dur*count)
)

--==============================================================================
--球阵Y轴方向分层波动
--参数：amp    - 振幅
--参数：count  - 波形周期数
--参数：dur    - 周期帧长
--参数：hor    - 中心高
--参数：da     - 振幅的变化值
--==============================================================================
fn sinXRateYBSpherePos amp count dur delay hor high da cy:4 frame:FrameTime row:row col:column =
(
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	a = high /(cy-1)
	
	for i =1 to row by 2 do
	(
		--frame += delay
		
		--行基准线性变化
		for j = 1 to col by 2 do
		(
			y = j - cy
			temp = frame
			temp1 = amp-da
			
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = temp1*sin(dt*(t-1)) + a*y + hor )
				temp += df
					
				if ((mod (t-1) c) == 0) then temp1 += da
			)
		)
		frame += delay
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
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( 
			--X轴奇数
			for i = 1 to (row-2) by 4 do
			(
				for j = 1 to col by 2 do ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
			)
			
			--X轴偶数
			for i = 3 to row by 4 do
			(
				for j = 1 to col by 2 do ( BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor )
			)
		)
		temp += df
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
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( 
			--Y轴奇数
			for j = 1 to (col-2) by 4 do
			(
				for i = 1 to row by 2 do ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
			)
			
			--Y轴偶数
			for j = 3 to col by 4 do
			(
				for i = 1 to row by 2 do ( BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor )
			)
		)
		temp += df
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
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( 
			--X轴奇数
			for i = 1 to (row-2) by 4 do
			(
				--Y轴奇数
				for j = 1 to (col-2) by 4 do 
				( 
					BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor
				)
				
				--Y轴偶数
				for j = 3 to col by 4 do 
				( 
					BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor
				)
			)
			
			--X轴偶数
			for i = 3 to row by 4 do
			(
				--Y轴奇数
				for j = 1 to (col-2) by 4 do 
				( 
					BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor
				)
				
				--Y轴偶数
				for j = 3 to col by 4 do 
				( 
					BallArray[i][j].pos.z = -amp*sin(dt*(t-1)) + hor
				)
			)
		)
		temp += df
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
--参数：amp    - 振幅
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
--球阵内圈整体运行
--参数：pos    - 位置
--参数：hor    - 中心高
--==============================================================================
fn SphereRectInHorizPos pos row:row col:column =
(

	--内圈
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			if ((i>1)and(i<15)and((j>1)and(j<7))) then
				BallArray[i][j].pos.z = pos
		)
		
	)
	
)

--==============================================================================
--球阵内圈延时整体运行
--参数：pos    - 位置
--参数：hor    - 中心高
--==============================================================================
fn horizSphereRectInDelayPos pos delay hor frame:FrameTime row:row col:column =
(
	frame +=
	at time frame (
		--内圈
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				if ((i>1)and(i<15)and((j>1)and(j<7))) then
					BallArray[i][j].pos.z = pos + hor
			)
		)
	)
)

--==============================================================================
--球阵内圈上下波动
--参数：amp    - 振幅
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
--球阵内圈定型
--参数：pos    - 位置
--参数：hor    - 中心高
--==============================================================================
fn rateSphereRectInPos pos hor cy:4 frame:FrameTime row:row col:column =
(
	at time frame (
		--内圈形成斜面
		for i = 3 to (row-2) by 2 do
		(
				for j = 3 to (col-2) by 2 do
				(
					y = j - cy
					BallArray[i][j].pos.z = pos*y + hor
				)
		)
		
	)
	
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

--==============================================================================
--球阵外圈整体位置
--参数：pos    - 位置
--参数：hor    - 中心高
--==============================================================================
fn horizSphereRectOutPos pos hor frame:FrameTime row:row col:column =
(

	at time frame (
		--外圈
		for i = 1 to row by 2 do
		(
			for j = 1 to col by 2 do
			(
				if (((i==1)or(i==15))or((j==1)or(j==7))) then
					BallArray[i][j].pos.z = pos + hor
			)
		)
	)
)

--==============================================================================
--球阵外圈整合为一个函数
--参数：pos    - 位置
--==============================================================================
fn SphereRectOutHorizPos pos row:row col:column =
(

	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			if (((i==1)or(i==15))or((j==1)or(j==7))) then
					BallArray[i][j].pos.z = pos
		)
	)
	
)



--==============================================================================
--球阵内外圈整体延时运行
--参数：pos    - 位置
--参数：hor    - 中心高
--==============================================================================
fn rateSphereRectDelayPos pos d dur delay hor frame:FrameTime =
(
	start = frame

	--内圈
	FrameTime = start+dur
	horizSphereRectInPos pos hor
	
	--外圈
	FrameTime = start+delay
	horizSphereRectOutPos 0 hor
	
	FrameTime = start+delay+dur
	horizSphereRectOutPos (pos-d) hor
	
	
	return frame+delay+dur
)

--==============================================================================
--球阵外圈定型
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn rateSphereRectOutPos pos hor cy:4 frame:FrameTime row:row col:column =
(
	a = pos/3

	at time frame (
		--外圈造型
		for i = 1 to row by 2 do
		(
			--左侧
			if (i==1) then
			(
				for j = 1 to col by 2 do
				(
					y = j - cy
					BallArray[i][j].pos.z = a*y + hor
				)
			)
			--右侧
			if (i==row) then
			(
				for j = 1 to col by 2 do
				(
					y = j - cy
					BallArray[i][j].pos.z = a*y + hor
				)
			)
			
			--前后端
			if (i>1)and(i<row) then
			(
				for j = 1 to col by 6 do
				(
					y = j - cy
					BallArray[i][j].pos.z = a*y + hor
				)
			)
		)
	)


)


--==============================================================================
--球阵阶梯造型
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn stairSpherePos pos hor frame:FrameTime row:row col:column =
(
	a = pos/6

	at time frame 
	(
		for j = 1 to col by 2 do
		(
			for i = 1 to row by 2 do
			(
				x = (i+1)/2 - 1  --0 1 2 3 ... 7
				BallArray[i][j].pos.z = a*(x - (mod x 2)) + hor
			)
		)
	)
)

--==============================================================================
--球阵X轴向阶梯波动
--参数：pos    - 振幅
--参数：dur    - 时间
--参数：hor    - 中心高
--==============================================================================
fn stairSinXSpherePos amp count dur delay hor frame:FrameTime row:row col:column =
(
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	
	for j = 1 to col by 2 do
	(
		for i = 1 to row by 2 do
		(
			x = (i+1)/2 - 1
			--delay = a*(x - (mod x 2))
			temp = frame + delay*(x - (mod x 2))/2
				
			for t = 1 to (c*count+1) do
			(
				at time temp ( BallArray[i][j].pos.z = amp*sin(dt*(t-1)) + hor )
				temp += df
			)
		)
	)
	
	return frame+delay+count*dur
)














