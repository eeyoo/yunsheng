--==============================================================================
--脚本意图：框阵造型不同系列汇总
--版本 1.0
--日期 2015-3-17
--作者 吴飞林
--==============================================================================

--框阵造型调用球阵函数
fileIn "sphereLib.ms"

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
--框阵按奇偶分组线性对称分布
--参数： pos  - 相对基准高度
--参数： pos   - 框间距
--参数： hor  - 基准高度
--==============================================================================
fn setLinePos pos1 pos2 pos3 pos4 frame:FrameTime =
(
	
	at time frame (
		LineArray[1].pos.z = pos1
		LineArray[2].pos.z = pos2
		LineArray[3].pos.z = pos3
		LineArray[4].pos.z = pos4
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
--随机位置分布并hold住
--参数：rmin, rmax - 随机位置下限和上限
--参数：hold       - 保持位置时间
--==============================================================================
fn randomLineHoldPos rmin rmax hold frame:FrameTime n:num =
(
	pos_array = #()
	
	at time frame (
		for i = 1 to n do
		(
			rand = random rmin rmax
			append pos_array rand
			
			LineArray[i].pos.z = rand
		)
	)
	
	at time (frame+hold) (
		for i = 1 to n do
		(
			LineArray[i].pos.z = pos_array[i]
		)
	)
	
	return frame+hold
)

--==============================================================================
--框阵奇偶分离，
--参数：pos1 - 奇数框位置，pos2 - 偶数框位置
--==============================================================================
fn horizLineDisPos pos1 pos2 frame:FrameTime n:num =
(
	for i = 1 to n-1 by 2 do
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
	for i = 1 to n-1 by 2 do
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
--参数： pos  - 相对基准高度
--参数： d    - 框间距
--参数： hor  - 基准高度
--==============================================================================
fn linearSymAPos pos d hor frame:FrameTime n:num =
(
	--奇数组
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			x = (i+1)/2
			LineArray[i].pos.z = pos-d*(x-1) + hor
		)
	)
	--偶数组
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
--造型函数：逐个到达指定平面
--参数1：pos1   - 起始位置
--参数2：pos2   - 结束位置
--参数3：dur    - 单个环运行时间
--参数4：delay  - 延时时间 
--参数：hold   - 保持造型时间
--==============================================================================
fn horizLineDelay1Pos pos dur delay hold hor frame:FrameTime n:num =
(
	
	for i = 1 to n do
	(
		frame += delay
		at time frame ( LineArray[i].pos.z = hor )
		
		at time (frame + dur) ( LineArray[i].pos.z = pos )
		
		at time (frame + dur + hold) ( LineArray[i].pos.z = pos )
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
--造型函数：延时效果的锥形
--参数：pos    - 锥形总高度
--参数：dur    - 单个环运行时间
--参数：delay  - 单个环延时时间
--参数：hold   - 保持造型时间
--参数：hor    - 基准高度
--==============================================================================
fn rateLineDelayPos pos dur delay hold hor frame:FrameTime n:num =
(
	a = pos/(n-1)
	
	for i = 1 to n do
	(
		--frame += delay
		at time frame ( LineArray[i].pos.z = hor )
		
		at time (frame + dur) LineArray[i].pos.z = a*(n-i) + hor
		
		at time (frame + dur + hold) LineArray[i].pos.z = a*(n-i) + hor
		
		frame += delay
	)
	
	return (frame - delay + dur + hold)
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

------------------------------------分组------------------------------------
--==============================================================================
--造型函数：框阵奇数组位置
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn LineOddDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--1号框
		LineArray[1].pos.z = pos + hor 
		--3号框
		LineArray[3].pos.z = -pos + hor
	)

)

--==============================================================================
--造型函数：框阵偶数组位置
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn LineEvenDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--2号框
		LineArray[2].pos.z = pos + hor 
		--4号框
		LineArray[4].pos.z = -pos + hor
	)

)

--==============================================================================
--造型函数：1、2号框位置
--参数：pos    - 正弦振幅
--参数：hor    - 中心高
--==============================================================================
fn LineFirstTwoDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--1号框
		LineArray[1].pos.z = pos + hor 
		--2号框
		LineArray[2].pos.z = -pos + hor
	)

)

--==============================================================================
--造型函数：3、4号框位置
--参数：pos    - 正弦振幅
--参数：hor    - 中心高
--==============================================================================
fn LineLastTwoDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--3号框
		LineArray[3].pos.z = pos + hor 
		--4号框
		LineArray[4].pos.z = -pos + hor
	)

)


----------------------------------动态延时造型----------------------------------
--==============================================================================
--造型函数：整体正弦波动，框阵只用一个框
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLinePos amp count dur hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( for i = 1 to n do LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
		temp += df
	)

	return frame+count*dur
)

--==============================================================================
--造型函数：框阵4等分作正弦波动
--参数：pos    - 框阵分布高度
--参数：amp    - 正弦振幅
--参数：count  - 运行周期数
--参数：dur    - 单个运行一个周期时间
--参数：delay  - 延时时间
--参数：hor    - 中心高
--==============================================================================
fn sinRateLinePos pos amp count dur hor frame:FrameTime n:num =
(
	a = pos/(n-1)
	
	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( for i = 1 to n do LineArray[i].pos.z = amp*sin(dt*(t-1)) + a*(n-i) + hor )
		temp += df
	)

	return frame+count*dur
)


--==============================================================================
--造型函数：框阵逐个启动正弦波动
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineDelayPos amp count dur delay hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	for t = 1 to (c*count+1) do
	(
		temp = frame
		for i = 1 to n do
		(
			at time temp (  LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += delay
		)
		
		frame += df
	)

	return frame-df + (n-1)*delay
)

--==============================================================================
--造型函数：框阵奇数组内作正弦波动
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineOddDelayPos amp count dur delay hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	for t = 1 to (c*count+1) do
	(
		temp = frame
		for i = 1 to n-1 by 2 do
		(
			at time temp (  LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += delay
		)
		
		frame += df
	)

	return frame-df + (n-1)*delay
)


--==============================================================================
--造型函数：框阵偶数组内作正弦波动
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineEvenDelayPos amp count dur delay hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	for t = 1 to (c*count+1) do
	(
		temp = frame
		for i = 2 to n by 2 do
		(
			at time temp (  LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += delay
		)
		
		frame += df
	)

	return frame-df + (n-1)*delay
)

--==============================================================================
--造型函数：框阵分为奇偶两组，相对作正弦波动
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineOddEvenDelayPos amp pos count dur delay hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	start_odd = frame
	start_even = frame
	
	--奇数组逐个波动
	for i = 1 to (n-1) by 2 do
	(
		temp = start_odd
		for t = 1 to (c*count+1) do 
		(
			--temp = start_odd
			at time temp (
			
				LineArray[i].pos.z = amp*sin(dt*(t-1)) + pos + hor
			)
			temp += df
		)
		start_odd += delay
	)
	
	--偶数组逐个波动
	for i = 2 to n by 2 do
	(
		temp = start_even
		for t = 1 to (c*count+1) do 
		(
			--temp = start_even
			at time temp (
			
				LineArray[i].pos.z = -amp*sin(dt*(t-1)) - pos + hor
			)
			temp += df
		)
		start_even += delay
	)

	return frame + n*delay
)

--==============================================================================
--造型函数：1、2对称波动，3、4静止
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineFirstTwoPos amp pos count dur hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do 
	(
		at time temp (
			
			LineArray[1].pos.z = amp*sin(dt*(t-1)) + pos + hor
				
			LineArray[3].pos.z = pos + hor
				
			LineArray[2].pos.z = -amp*sin(dt*(t-1)) - pos + hor	
				
			LineArray[4].pos.z = -pos + hor
		)
		
		temp += df		
	)
	

	return frame + count*dur
)

--==============================================================================
--造型函数：1、2静止，3、4波动
--参数1：amp    - 正弦振幅
--参数2：count  - 运行周期数
--参数3：dur    - 单个运行一个周期时间
--参数4：delay  - 延时时间
--参数5：hor    - 中心高
--==============================================================================
fn sinLineLastTwoPos amp pos count dur hor frame:FrameTime n:num =
(

	c = 4  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = dur/c --周期划分一单位对应时间
	
	temp = frame
	for t = 1 to (c*count+1) do 
	(
		at time temp (
			
			LineArray[1].pos.z = pos + hor
				
			LineArray[3].pos.z = amp*sin(dt*(t-1)) + pos + hor
				
			LineArray[2].pos.z =  -pos + hor	
				
			LineArray[4].pos.z = -amp*sin(dt*(t-1)) - pos + hor
		)
		
		temp += df		
	)
	

	return frame + count*dur
)



--==============================================================================
--造型函数：框阵奇数组间歇性运动
--参数：pos    - 起始位置
--参数：d       - 位置增量
--参数：count   - 周期数
--参数：delay   - 周期延时启动时间
--参数：cycle   - 周期时间
--参数：hold    - 保持时间
--参数：hor     - 中心高
--说明：一个周期时间包括位置变化时间与保持终点位置时间
--==============================================================================
fn LineOddDelayPos pos d count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + hor )
	
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + hor )
		at time (start+dur+hold) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--造型函数：框阵奇数组间歇性运动，框分离
--参数：pos    - 起始位置
--参数：d       - 位置增量
--参数：count   - 周期数
--参数：delay   - 周期延时启动时间
--参数：cycle   - 周期时间
--参数：hold    - 保持时间
--参数：hor     - 中心高
--说明：一个周期时间包括位置变化时间与保持终点位置时间
--==============================================================================
fn LineOddDisDelayPos pos d dis count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
	
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		at time (start+dur+hold) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--造型函数：框阵奇数组间歇性运动，框分离
--参数：pos    - 起始位置
--参数：d       - 位置增量
--参数：count   - 周期数
--参数：delay   - 周期延时启动时间
--参数：cycle   - 周期时间
--参数：hold    - 保持时间
--参数：hor     - 中心高
--说明：一个周期时间包括位置变化时间与保持终点位置时间
--==============================================================================
fn LineOddDisHoldDelayPos pos d dis count delay delay1 cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
	
	
	for t = 1 to count do
	(
		pos += d
		--at time (start+dur) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		temp = start
		for i = 1 to n-1 by 2 do 
		( 
			at time (temp + dur) ( LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
			temp += delay1
		)
		
		for i = 1 to n-1 by 2 do 
		( 
			at time (temp + dur + hold) ( LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
			temp += delay1
		)
		 
		--at time (start+dur+hold) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--造型函数：框阵偶数组间歇性运动
--参数：pos    - 起始位置
--参数：d       - 位置增量
--参数：count   - 周期数
--参数：delay   - 周期延时启动时间
--参数：cycle   - 周期时间
--参数：hold    - 保持时间
--参数：hor     - 中心高
--说明：一个周期时间包括位置变化时间与保持终点位置时间
--==============================================================================
fn LineEvenDelayPos pos d count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos + hor )
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos + hor )
		at time (start+dur+hold) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--造型函数：框阵偶数组间歇性运动，框分离
--参数：pos    - 起始位置
--参数：d       - 位置增量
--参数：count   - 周期数
--参数：delay   - 周期延时启动时间
--参数：cycle   - 周期时间
--参数：hold    - 保持时间
--参数：hor     - 中心高
--说明：一个周期时间包括位置变化时间与保持终点位置时间
--==============================================================================
fn LineEvenDisDelayPos pos d dis count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos - dis*(n-i)/2 + hor )
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos - dis*(n-i)/2 + hor )
		at time (start+dur+hold) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos - dis*(n-i)/2 + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)


-----------------------------球框结合造型设计-----------------------------------
--==============================================================================
--球框复合造型函数：延时效果的锥形，框先动，球后动
--参数：pos    - 锥形总高度
--参数：dur    - 单个环运行时间
--参数：delay  - 单个环延时时间
--参数：hold   - 保持造型时间
--参数：hor    - 基准高度
--不得不佩服王工的见地，他说行得通，基本没有问题，剩下的是找方法
--==============================================================================
fn rateCompositeADelayPos pos dur delay hold hor frame:FrameTime n:6 =
(
	start = frame
	a = pos/(n-1)
	
	for i = 1 to n do
	(
		--运行起始帧
		start = frame +  delay*(i-1) --框4延时为0
		
		--等待启动
		at time start ( 
			if (i<=4) then
				LineArray[5-i].pos.z = hor 
			
			if (i==5) then   --外圈
				SphereRectOutHorizPos hor

			if (i==6) then   --内圈			
				SphereRectInHorizPos hor
		)
		
		--运行到目标位置
		at time (start + dur) (
			if (i<=4) then
				LineArray[5-i].pos.z = a*(i-1) + hor
			
			if (i==5) then   --外圈
				SphereRectOutHorizPos (a*(i-1) + hor)
			
			if (i==6) then   --内圈			
				SphereRectInHorizPos (a*(i-1) + hor)
		)
		
		--保持最终造型
		at time (start + dur + hold) (
			if (i<=4) then
				LineArray[5-i].pos.z = a*(i-1) + hor
			
			if (i==5) then   --外圈
				SphereRectOutHorizPos (a*(i-1) + hor)
			
			if (i==6) then   --内圈			
				SphereRectInHorizPos (a*(i-1) + hor)
		)		
	)

	return (start + dur + hold)
)

--==============================================================================
--球框复合造型函数：延时效果的锥形，球先动，框后动
--参数：pos    - 锥形总高度
--参数：dur    - 单个环运行时间
--参数：delay  - 单个环延时时间
--参数：hold   - 保持造型时间
--参数：hor    - 基准高度
--不得不佩服王工的见地，他说行得通，基本没有问题，剩下的是找方法
--==============================================================================
fn rateCompositeBDelayPos pos dur delay hold hor frame:FrameTime n:6 =
(
	start = frame
	a = pos/(n-1)
	
	for i = 1 to n do
	(
		--运行起始帧
		start = frame +  delay*(i-1) --框4延时为0
		
		--等待启动
		at time start (		
			if (i==1) then   --内圈			
				SphereRectInHorizPos hor
			
			if (i==2) then   --外圈
				SphereRectOutHorizPos hor
			
			if (i>=3) then
				LineArray[i-2].pos.z = hor
		)
		
		--运行到目标位置
		at time (start + dur) (
			if (i==1) then   --内圈			
				SphereRectInHorizPos (a*(n-i) + hor)
			
			if (i==2) then   --外圈
				SphereRectOutHorizPos (a*(n-i) + hor)
			
			if (i>=3) then
				LineArray[i-2].pos.z = a*(n-i) + hor
		)
		
		--保持最终造型
		at time (start + dur + hold) (
			if (i==1) then   --内圈			
				SphereRectInHorizPos (a*(n-i) + hor)
			
			if (i==2) then   --外圈
				SphereRectOutHorizPos (a*(n-i) + hor)
			
			if (i>=3) then
				LineArray[i-2].pos.z = a*(n-i) + hor
		)		
	)

	return (start + dur + hold)
)

--==============================================================================
--球框复合造型，基准对称分布，哑铃型
--参数：pos    - 锥形总高度
--参数：dur    - 单个环运行时间
--参数：delay  - 单个环延时时间
--参数：hold   - 保持造型时间
--参数：hor    - 基准高度
--不得不佩服王工的见地，他说行得通，基本没有问题，剩下的是找方法
--==============================================================================
fn CompositeOEAPos high pos hor frame:FrameTime n:6 =
(
	a = high/4
	
	at time frame (
		--奇数组
		for i = 1 to (n-1) by 2 do
		(
			if (i==1) then --球内圈
				SphereRectInHorizPos (a*(i-1)+pos+hor)
			if (i > 1) then (
				LineArray[i-2].pos.z = a*(i-1)+pos+hor
			)
		)
		
		--偶数组
		for i = 2 to n by 2 do
		(
			if (i==2) then --球外圈
			SphereRectOutHorizPos (-a*(i-2)-pos+hor)
			if (i > 2) then
				LineArray[i-2].pos.z = -a*(i-2)-pos+hor
		)
	)
	
)

--==============================================================================
--球框复合造型，基准对称分布，贝壳型
--参数：pos    - 锥形总高度
--参数：dur    - 单个环运行时间
--参数：delay  - 单个环延时时间
--参数：hold   - 保持造型时间
--参数：hor    - 基准高度
--不得不佩服王工的见地，他说行得通，基本没有问题，剩下的是找方法
--==============================================================================
fn CompositeOEBPos high pos hor frame:FrameTime n:6 =
(
	a = high/4
	
	at time frame (
		--奇数组
		for i = 1 to (n-1) by 2 do
		(
			if (i==1) then --球内圈
			SphereRectInHorizPos (a*(n-i-1)+pos+hor)
			if (i > 1) then (
				LineArray[i-2].pos.z = a*(n-i-1)+pos+hor
			)
		)
		
		--偶数组
		for i = 2 to n by 2 do
		(
			if (i==2) then --球外圈
			SphereRectOutHorizPos (-a*(n-i)-pos+hor)
			if (i > 2) then
				LineArray[i-2].pos.z = -a*(n-i)-pos+hor
		)
	)
	
)

--==============================================================================
--框爆炸造型，由中心向两边爆炸
--参数：pos    - 最大高度
--参数：d      - 最小高度
--参数：dur    - 爆炸时间
--参数：hor    - 基准高度
--不得不佩服王工的见地，他说行得通，基本没有问题，剩下的是找方法
--==============================================================================
fn boomLinePos pos d dur hor frame:FrameTime n:num =
(

	at time frame (
		--球框在基准位置
		for i = 1 to n do ( LineArray[i].pos.z = hor )
		horizSphereSynPos hor
	)
	
	at time (frame + dur) (
		--奇偶上下分离
		for i = 1 to (n-1) by 2 do ( LineArray[i].pos.z = random (hor+d) (hor+pos) )
		for i = 2 to n by 2 do ( LineArray[i].pos.z = random (hor-pos) (hor-d) )
	)
	
	return (frame+dur)
)

