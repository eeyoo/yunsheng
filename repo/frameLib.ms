--==============================================================================
--脚本意图：框阵造型不同系列汇总
--版本 1.0
--日期 2015-3-17
--作者 吴飞林
--==============================================================================


-------------------------------框阵造型函数-------------------------------------
--==============================================================================
--所有框同步达到指定位置
--参数：pos - 指定Z轴位置值
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
--框阵奇偶分离，
--参数：pos1 - 奇数框位置，pos2 - 偶数框位置
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

--==============================================================================
--框阵奇偶分离，定基准面
--参数：pos - 正，奇数上偶数下，负，奇数下偶数上
--参数：hor - 中心高
--==============================================================================
fn horizLineBasePos pos hor frame:FrameTime n:num =
(
	for i = 1 to 3 by 2 do
	(
		at time frame (
			LineArray[i].pos.z = pos + hor
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			LineArray[i].pos.z = -pos + hor
		)
	)

)

--==============================================================================
--正向线性锥形
--参数1 pos - 锥形高度
--参数2 hor  - 中心高
--==============================================================================
fn linearForwardPos pos hor frame:FrameTime n:num =
(
	dh = pos/(n-1)
	
	for i = 1 to n do
	(
		at time frame (
			
			LineArray[i].pos.z = dh*(n-i) + hor
		)
	)
)

--==============================================================================
--正向抛物面
--参数1 a - 比例系数
--参数2 hor  - 中心高
--==============================================================================
fn parabForwardPos a hor frame:FrameTime n:num =
(
	for i = 1 to n do
	(
		at time frame (
			x = n-i
			pos = a*x*x + hor
			LineArray[i].pos.z = pos
		)
	)
)

--==============================================================================
--正向正弦面
--参数1 amp - 波动幅度
--参数2 hor - 中心高
--==============================================================================
fn sinForwardPos amp hor frame:FrameTime n:num =
(
	for i = 1 to n do
	(
		at time frame (
			
			x = 120*(n-i)/n  --最小值0，最大值90
			LineArray[i].pos.z = amp*sin(x) + hor
		)
	)
)

--------------------------------------------------------------------------------
-----------------------------上下对称静态造型-----------------------------------
--------------------------------------------------------------------------------
--==============================================================================
--框阵按奇偶分组线性对称分布
--参数： amp - 对称锥形幅度，正数奇数在上，负数奇数在下
--参数： d   - 框间距
--参数： hor  - 中心高
--==============================================================================
fn linearSymAPos pos d hor frame:FrameTime n:num =
(
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			x = (i+1)/2
			LineArray[i].pos.z = pos-d*(x-1) + hor
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			x = i/2
			LineArray[i].pos.z = -pos+d*(x-1) + hor
		)
	)
	
)

--==============================================================================
--框阵按奇偶分组线性对称分布
--参数： amp - 对称锥形幅度，正数奇数在上，负数奇数在下
--参数： d   - 框间距
--参数： hor  - 中心高
--==============================================================================
fn linearSymBPos pos d hor frame:FrameTime n:num =
(
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			x = (n-i+1)/2
			LineArray[i].pos.z = pos-d*(x-1) + hor
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			x = (n-i)/2
			LineArray[i].pos.z = -pos+d*x + hor
		)
	)
	
)

--------------------------------------------------------------------------------
----------------------------带延时效果----------------------------------------
--------------------------------------------------------------------------------
--==============================================================================
--造型函数：逐个到达指定平面
--参数1：pos1   - 起始位置
--参数2：pos2   - 结束位置
--参数3：dur    - 单个环运行时间
--参数4：delay  - 延时时间 
--参数：hold   - 保持造型时间
--==============================================================================
fn horizLineDelayPos pos1 pos2 dur delay hold frame:FrameTime n:num =
(

	for i = 1 to n do
	(
		frame += delay
		at time frame ( LineArray[i].pos.z = pos1 )
		
		at time (frame + dur) ( LineArray[i].pos.z = pos2 )
		
		at time (frame + dur + hold) ( LineArray[i].pos.z = pos2 )
	)
	
	return (frame + dur + hold)
)

--==============================================================================
--造型函数：延时效果的锥形
--参数1：pos1   - 起始位置
--参数2：pos2   - 结束位置
--参数3：dur    - 单个环运行时间
--参数4：delay  - 延时时间
--参数：hold   - 保持造型时间
--==============================================================================
fn linearLineDelayPos pos1 pos2 dur delay hold frame:FrameTime n:num =
(

	h = pos2-pos1
	dh = h/(n-1)
	
	for i = 1 to n do
	(
		frame += delay
		at time frame ( LineArray[i].pos.z = pos1 )
		
		at time (frame + dur) LineArray[i].pos.z = pos2 - dh*(i-1)
		
		at time (frame + dur + hold) LineArray[i].pos.z = pos2 - dh*(i-1)
	)
	
	return (frame + dur + hold)
)


--==============================================================================
--造型函数：延时效果的正弦波动
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineLoopDelayPos amp count dur delay hor frame:FrameTime n:num =
(
	enter = frame
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	for i = 1 to n do
	(
		temp = frame
		for t = 1 to (c*count+1) do
		(
			at time temp ( LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += df	
		)
		frame += delay
	)

	return (enter + (n-1)*delay + count*dur)
)

--==============================================================================
--造型函数：中间开始逐个跳动
--参数1：pos    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn LineSingleLoopDelayPos pos dur delay hor frame:FrameTime n:num =
(
	start = frame
	for i = 1 to n do
	(
		--start += delay
		at time start ( LineArray[i].pos.z = hor )
		at time (start+dur/2) ( LineArray[i].pos.z = pos+hor )
		at time (start+dur) ( LineArray[i].pos.z = hor )
		start += delay
	)

	return (frame + n*delay + dur)
)


----------------------------------动态延时造型--------------------------------------
--==============================================================================
--造型函数：框阵为周期性变化，在周期时间内静止
--参数：pos    - 起始位置
--参数：d       - 位置增量
--参数：count   - 周期数
--参数：cycle   - 周期时间
--参数：hold    - 保持时间
--说明：一个周期时间包括位置变化时间与保持终点位置时间
--==============================================================================
fn LineDelayPos pos d count cycle hold frame:FrameTime n:num =
(
	--pos1 = pos
	for t = 1 to count do
	(	
		pos += d
		
		at time frame ( for i = 1 to n do LineArray[i].pos.z = pos )
		at time (frame + hold) ( for i = 1 to n do LineArray[i].pos.z = pos )
		
		frame += cycle
	)
	
	return frame
)	


