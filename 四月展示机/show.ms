-----------------------------球阵组合的节目单-----------------------------------





--==============================================================================
--节目编号：001
--节目说明：球阵进行回字形编组与框阵一起由初始位置到达终点位置
--参数：pos1    - 初始位置
--参数：pos2    - 终点位置
--参数：range   - 单元动作时间
--参数：delay  - 逐个延时时间
--==============================================================================
fn CompositeShow001 pos1 pos2 range delay frame:FrameTime row:row col:column n:num =
(
	start = frame
	
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			at time start
			(
				if ((i>1)and(i<15)and((j>1)and(j<7))) then
					BallArray[i][j].pos.z = pos1
			)
			
			at time (start+range)
			(
				if ((i>1)and(i<15)and((j>1)and(j<7))) then
					BallArray[i][j].pos.z = pos2
			)
		)
	)
	
	start += delay
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			at time start
			(

				if (((i==1)or(i==15))or((j==1)or(j==7))) then
					BallArray[i][j].pos.z = pos1
			)
			
			at time (start+range)
			(
				if (((i==1)or(i==15))or((j==1)or(j==7))) then
					BallArray[i][j].pos.z = pos2
			)
		)
	)
	
	
	for t = 1 to n do 
	(
		start += delay
		at time start ( LineArray[t].pos.z = pos1 )
		--start += delay
		at time (start+range) ( LineArray[t].pos.z = pos2 )
	)
	
	
	return frame+5*delay+range
)

--==============================================================================
--节目编号：002
--节目说明：球阵进行回字形编组与框阵一起由初始位置到达终点位置
--参数：pos1    - 初始位置
--参数：pos2    - 终点位置
--参数：range   - 单元动作时间
--参数：delay  - 逐个延时时间
--==============================================================================
fn CompositeShow002 pos1 pos2 range delay frame:FrameTime row:row col:column n:num =
(
	height = pos2 - pos1
	dh = height/5
	
	start = frame
	
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			at time start
			(
				if ((i>1)and(i<15)and((j>1)and(j<7))) then
					BallArray[i][j].pos.z = pos1
			)
			
			at time (start+range)
			(
				if ((i>1)and(i<15)and((j>1)and(j<7))) then
					BallArray[i][j].pos.z = pos1+dh
			)
		)
	)
	
	start += delay
	for i = 1 to row by 2 do
	(
		for j = 1 to col by 2 do
		(
			at time start
			(
				if (((i==1)or(i==15))or((j==1)or(j==7))) then
					BallArray[i][j].pos.z = pos1
			)
			
			at time (start+range)
			(
				if (((i==1)or(i==15))or((j==1)or(j==7))) then
					BallArray[i][j].pos.z = pos1+2*dh
			)
		)
	)
	
	
	for t = 1 to n do 
	(
		start += delay
		at time start ( LineArray[t].pos.z = pos1 + hor )
		--start += delay
		at time (start+range) ( LineArray[t].pos.z = pos1+(t+2)*dh )
	)
	
	
	return frame+5*delay+range
)

--==============================================================================
--节目编号：003
--节目说明：球阵与框阵起始处于同一水平面，球阵活动范围逐渐扩大框阵始终作为其动态变化的边界
--参数：pos1    - 初始位置
--参数：pos2    - 终点位置
--参数：range   - 单元动作时间
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--==============================================================================
fn CompositeShow003 amp count range delay hor da frame:FrameTime row:row col:column n:num =
(
	start = frame
	
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = range/c --周期划分一单位对应时间


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
	
	at time start
	(
		for i = 1 to 3 by 2 do
		(
			at time frame (
				LineArray[i].pos.z = hor
			)
		)
		
		for i = 2 to n by 2 do
		(
			at time frame (
				LineArray[i].pos.z = hor
			)
		)
	)
	
	frame += count*range
	at time frame
	(
		for i = 1 to 3 by 2 do
		(
			at time frame (
				LineArray[i].pos.z = amp+count*da + hor
			)
		)
		
		for i = 2 to n by 2 do
		(
			at time frame (
				LineArray[i].pos.z = -(amp+count*da) + hor
			)
		)
	)
	
	return frame
)

--==============================================================================
--节目编号：004
--节目说明：球阵与框阵一起波动
--参数：amp1    - 球单元波幅值
--参数：amp2    - 框单元波幅值
--参数：range   - 单元动作时间
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--==============================================================================
fn CompositeShow004 amp1 amp2 count range delay hor da frame:FrameTime row:row col:column n:num =
(
	start1 = frame
	start2 = frame
	
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = range/c --周期划分一单位对应时间

	--球行波
	for i = 1 to row by 2 do
	(
		start1 += delay
		temp = start1
		
		temp1 = amp1 - da   --让小球起始振幅为amp的权宜之计
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
	
	--框逐个波动
	for i = 1 to n do
	(
		start2 += delay
		temp = start2
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( LineArray[i].pos.z = amp2*sin(dt*(t-1)) + hor )
			temp += df	
		)
	)
	
	return (frame+ row*delay + count*range) 
)


--==============================================================================
--节目编号：005
--节目说明：球阵与框阵一起波动，中间小球运动为列向波动，振幅共有三个，逐渐增大，每个振幅波动一次。外框四个一起运动，每次必振幅高一点。
--参数：amp1    - 球单元波幅值
--参数：amp2    - 框单元波幅值
--参数：range   - 单元动作时间
--参数：delay  - 逐个延时时间
--参数：hor    - 中心高
--==============================================================================
fn CompositeShow005 amp1 amp2 count range delay hor da frame:FrameTime row:row col:column n:num =
(
	start1 = frame
	start2 = frame
	
	c = 8  --周期划分单位数
	dt = 360/c --周期划分一单位对应圆周度数
	df = range/c --周期划分一单位对应时间

	--球列波
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
	
	--框逐个波动
	for i = 1 to n do
	(
		start2 += delay
		temp = start2
		
		for t = 1 to (c*count+1) do
		(
			at time temp ( LineArray[i].pos.z = amp2*sin(dt*(t-1)) + hor )
			temp += df	
		)
	)
	
	return (frame+ row*delay + count*range) 
)


