--清除场景
--hide geometry

actionMan.executeAction 0 "16"  -- File: 新建场景,清除全部

row = 11
column = 6
BallNum = row * column

--创建所有小球
BallMatrix = #()
for i = 1 to row do
(
	append BallMatrix #()
	for j = 1 to column do
	(
		BallMatrix[i][j] = Sphere radius: 27.5 position: [(i - 1) * 110, (j - 1) * 110, 0] wirecolor: [255, 255, 20]
	)
)

----------------------------------------------------------------------------
--形成 目标水平面 造型
--TargetPosition 目标位置
----------------------------------------------------------------------------
fn HorizontalTarPos TargetPosition row:row col:column  =  --非默认参数置前
(
	zPos = #()
	for i = 1 to row do
	(
		append zPos #()
		for j = 1 to col do
		(
			zPos[i][j] = -TargetPosition
		)
	)
	return zPos
)

----------------------------------------------------------------------------
--形成 随机数 造型
-- rmin rmax 随机数的 最小 最大 范围值
----------------------------------------------------------------------------
fn RandomPos  rmin rmax row:row col:column = --非默认参数置前
(
	Pos = #()
	for i = 1 to row do
	(
		append Pos #()
		for j = 1 to col do
		(
			Pos[i][j] = random -rmin -rmax
		)
	)
	return Pos
)

----------------------------------------------------------------------------
--设置特定帧(时间)的特定位置
--BallMatrix     小球矩阵     
----------------------------------------------------------------------------
fn SetFramePosition FrameTime BallMatrix PositionArray row:row col:column = --非默认参数置前
(
	set animate on
	at time FrameTime(
		for i = 1 to row do
		(
			for j = 1 to col do
			(
				BallMatrix[i][j].pos.z = PositionArray[i][j]
			)
		)
	)
	set animate off
)

----------------------------------------------------------------------------
--形成 一行正弦波 造型 
--RowIndex     行序列号
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数
--Range        震动幅度
--ReferencePos 参考平面 
--RefFrameTime 起始参考帧
----------------------------------------------------------------------------
fn SinSingleRowFramePos RowIndex SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime row:row col:column = --非默认参数置前
(
	for WN = 1 to WaveNum do
	(
		FrameTime = (WN - 1) * RunFrame + RefFrameTime
		for i = 1 to column do
		(
			j = SpaceFrame * (i - 1)
			k = j + RunFrame		
		
			for t = j to k by SpaceFrame do
			(
				set animate on
				at time (FrameTime  + t)				
				BallMatrix[RowIndex][i].pos.z = Range * sin(360.0 * (t - j)/RunFrame) - ReferencePos 
				set animate off
			)
		)
	)
)

----------------------------------------------------------------------------
--形成 一列正弦波 造型 
--ColIndex     列序列号
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数
--Range        震动幅度
--ReferencePos 参考平面 
--RefFrameTime 起始参考帧
----------------------------------------------------------------------------
fn SinSingleColFramePos ColIndex SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime row:row col:column = --非默认参数置前
(
	for WN = 1 to WaveNum do
	(
		FrameTime = (WN - 1) * RunFrame + RefFrameTime
		for i = 1 to row do
		(
			j = SpaceFrame * (i - 1)
			k = j + RunFrame		
		
			for t = j to k by SpaceFrame do
			(
				set animate on
				at time (FrameTime  + t)				
				BallMatrix[i][ColIndex].pos.z = Range * sin(360.0 * (t - j)/RunFrame) - ReferencePos 
				set animate off
			)
		)
	)
)

----------------------------------------------------------------------------
--形成 行正弦波 造型 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数
--Range        震动幅度
--ReferencePos 参考平面 
--RefFrameTime 起始参考帧
--Direction    方向 0自左向右  1自右向左
----------------------------------------------------------------------------
fn SinRowFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction row:row col:column = --非默认参数置前
(
	for WN = 1 to WaveNum do
	(
		FrameTime = (WN - 1) * RunFrame + RefFrameTime
		if Direction == 0 do
		(
			row1 = 1 
			row2 = row 
			rowSpace = 1
		)
		if Direction == 1 do
		(
			row1 = row
			row2 = 1
			rowSpace = -1
		)
		for i = 1 to row do
		(
			for j = 1 to column do
		    (
				if Direction == 0 do
				(
					SpaceTime0 = SpaceFrame * (i - 1)
				)
				if Direction == 1 do
				(
					SpaceTime0 = SpaceFrame * (row - i)
				)
				SpaceTimeAll = SpaceTime0 + RunFrame		
		
			   for t = SpaceTime0 to SpaceTimeAll by SpaceFrame do
			   (
				   set animate on
				   at time (FrameTime  + t)	
				   BallMatrix[i][j].pos.z = Range * sin(360.0 * (t - SpaceTime0)/RunFrame) - ReferencePos 
				   set animate off
			   )
		   )
		)
	)
)

----------------------------------------------------------------------------
--形成 列正弦波 造型 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数
--Range        震动幅度
--ReferencePos 参考平面 
--RefFrameTime 起始参考帧
--Direction    方向 0自前向后  1自后向前
----------------------------------------------------------------------------
fn SinColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction row:row col:column = --非默认参数置前
(
	for WN = 1 to WaveNum do
	(
		FrameTime = (WN - 1) * RunFrame + RefFrameTime
		
        for i = 1 to row do
		(
			for j = 1 to column do
		    (
				if Direction == 0 do
				(
					SpaceTime0 = SpaceFrame * (j - 1)
				)
				if Direction == 1 do
				(
					SpaceTime0 = SpaceFrame * (column - j)
				)

				SpaceTimeAll = SpaceTime0 + RunFrame		
		
			   for t = SpaceTime0 to SpaceTimeAll by SpaceFrame do
			   (
				   set animate on
				   at time (FrameTime  + t)	
				   BallMatrix[i][j].pos.z = Range * sin(360.0 * (t - SpaceTime0)/RunFrame) - ReferencePos 
				   set animate off
			   )
		   )
		)
	)
)

----------------------------------------------------------------------------
--等待 正弦波 时间 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数 
--RefFrameTime 起始参考帧
--RowOrCol     行或者列总数
----------------------------------------------------------------------------
fn SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol = --非默认参数置前
( 
	RunTime = RefFrameTime + WaveNum * RunFrame + SpaceFrame * (RowOrCol - 1) 
	
	return RunTime
)

----------------------------------------------------------------------------
--形成 对角正弦波 造型 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数
--Range        震动幅度
--ReferencePos 参考平面 
--RefFrameTime 起始参考帧
--Direction    方向 0左前启动  1右前启动 2右后启动 3左后启动
----------------------------------------------------------------------------
fn SinRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction row:row col:column = --非默认参数置前
(
	for WN = 1 to WaveNum do
	(
		FrameTime = (WN - 1) * RunFrame + RefFrameTime
		
        for i = 1 to row do
		(
			for j = 1 to column do
		    (
				if Direction == 0 do
				(
					SpaceTime0 = SpaceFrame * (i + j - 2)
				)
				if Direction == 1 do
				(
					SpaceTime0 = SpaceFrame * (row - i + j - 1)
				)
				if Direction == 2 do
				(
					SpaceTime0 = SpaceFrame * (column + row - i - j)
				)
				if Direction == 3 do
				(
					SpaceTime0 = SpaceFrame * (column + i - j - 1)
				)
				SpaceTimeAll = SpaceTime0 + RunFrame		
		
			   for t = SpaceTime0 to SpaceTimeAll by SpaceFrame do
			   (
				   set animate on
				   at time (FrameTime + t)	
				   BallMatrix[i][j].pos.z = Range * sin(360.0 * (t - SpaceTime0)/RunFrame) - ReferencePos 
				   set animate off
			   )
		   )
		)
	)
)

----------------------------------------------------------------------------
--等待 对角正弦波 时间 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数 
--RefFrameTime 起始参考帧
----------------------------------------------------------------------------
fn SinRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime row:row col:column = --非默认参数置前
( 
	RunTime = RefFrameTime + WaveNum * RunFrame + SpaceFrame * (row + column) 
	
	return RunTime
)

----------------------------------------------------------------------------
--形成 中间正弦波 造型 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数
--Range        震动幅度
--ReferencePos 参考平面 
--RefFrameTime 起始参考帧
----------------------------------------------------------------------------
fn SinMidRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime row:row col:column = --非默认参数置前
(
	for WN = 1 to WaveNum do
	(
		FrameTime0 = (WN - 1) * RunFrame + RefFrameTime
		
        for i = 1 to row do
		(
			for j = 1 to column by 2 do
		    (
				SpaceTime0 = SpaceFrame * abs(row/2 - i + 1)
				SpaceTimeAll = SpaceTime0 + RunFrame		
		
			   for t = SpaceTime0 to SpaceTimeAll by SpaceFrame do
			   (
				   set animate on
				   at time (FrameTime0 + t)	
				   BallMatrix[i][j].pos.z = Range * sin(360.0 * (t - SpaceTime0)/RunFrame) - ReferencePos 
				   set animate off
			   )
		   )
		)
		for i = 1 to row do
		(
			for j = 2 to column by 2 do
		    (
				SpaceTime0 = SpaceFrame * abs(row/2 - i + 1)
				SpaceTimeAll = SpaceTime0 + RunFrame		
		
			   for t = SpaceTime0 to SpaceTimeAll by SpaceFrame do
			   (
				   set animate on
				   at time (FrameTime0 + SpaceFrame * 3 + t)	
				   BallMatrix[i][j].pos.z = -Range * sin(360.0 * (t - SpaceTime0)/RunFrame) - ReferencePos 
				   set animate off
			   )
		   )
		)
	)
)

----------------------------------------------------------------------------
--等待 中间正弦波 时间 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--WaveNum      波形个数 
--RefFrameTime 起始参考帧
----------------------------------------------------------------------------
fn SinMidRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime row:row = --非默认参数置前
( 
	RunTime = RefFrameTime + WaveNum * RunFrame + SpaceFrame * (row/2.0) 
	
	return RunTime
)

--------------------------------------------------------------------
--逐渐衰减振动波
--ReferencePos 参考平面 
--Range        震动幅度
--Radian       步进角度
----------------------------------------------------------------------------
fn PosGradualAttenuationWave SpaceFrame RunFrame VibrateRange ReferencePos RefFrameTime Direction row:row col:column = --非默认参数置前
(	
	FrameTime =  RefFrameTime
	AngleGrad = 45.0/row 
	for i = 1 to row do
	(
		if (Direction == 0) do
		(
			rowIndex =  row - i
		)
		if (Direction == 1) do
		(
			rowIndex = i - 1
		)
					
		for j = 1 to column do
		(
			FrameTime0 =  (i - 1) * SpaceFrame + FrameTime + (j - 1) * RunFrame
			set animate on
			at time (FrameTime0  +  SpaceFrame)
			BallMatrix[i][j].pos.z = - VibrateRange * (tan(rowIndex * AngleGrad)) - ReferencePos
			set	animate off
		)
		for j = 1 to column do
		(
			FrameTime1 =  (i - 1) * SpaceFrame + FrameTime + (j - 1) * RunFrame + 3 * RunFrame 
			set animate on
			at time (FrameTime1  + SpaceFrame)
			BallMatrix[i][j].pos.z = VibrateRange * (tan(rowIndex * AngleGrad)) - ReferencePos
			set	animate off
		)
		for j = 1 to column do
		(
			FrameTime2 =  (i - 1) * SpaceFrame + FrameTime + (j - 1) * RunFrame + 6 * RunFrame 
			set animate on
			at time (FrameTime2  + SpaceFrame)
			BallMatrix[i][j].pos.z = - ReferencePos
			set	animate off
		)
	) 
)

----------------------------------------------------------------------------
--等待 --逐渐衰减振动波 时间 
--SpaceFrame   间隔帧数
--RunFrame     运行帧数
--RefFrameTime 起始参考帧
----------------------------------------------------------------------------
fn GradualAttenuationWaveTime SpaceFrame RunFrame RefFrameTime  row:row col:column = --非默认参数置前
( 
	RunTime = RefFrameTime + (column + 7) * RunFrame + SpaceFrame * row 
	
	return RunTime
)


FrameTime = 0

----================================= 0 起点零位=============================================
-- 	--起点零位
	PositionArray = HorizontalTarPos 0                           --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray          --SetFramePosition FrameTime BallMatrix PositionArray
			
----================================== 1 随机下落 过渡 [下平面] =================================
-- 	--runtime:3s
-- 	--造型：随机110-2510
	FrameTimeTemp = 90                                           --30 * 3s = 90		
	FrameTime +=  FrameTimeTemp
	PositionArray = RandomPos 110 1510                           --RandomPos  rmin rmax
	SetFramePosition FrameTime BallMatrix PositionArray  

----================================= 2 平面=============================================
-- 	--runtime:3s
-- 	--过度平面
	FrameTimeTemp = 90                                           --30 * 3s = 90	
	FrameTime +=  FrameTimeTemp
	PositionArray = HorizontalTarPos 1000                        --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray          --SetFramePosition FrameTime BallMatrix PositionArray

    FrameTimeTemp = 15                                           --30 * 0.5s = 15	
	FrameTime +=  FrameTimeTemp
	PositionArray = HorizontalTarPos 1000                        --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray          --SetFramePosition FrameTime BallMatrix PositionArray
	
----================================== 3 正弦波 ============================================
-- 	--runtime:3s
-- 	--造型：逐渐衰减的振动波
    RefFrameTime = FrameTime
    PosGradualAttenuationWave 5 50 500 1000 RefFrameTime  0           --PosGradualAttenuationWave SpaceFrame RunFrame VibrateRange ReferencePos RefFrameTime Direction
	FrameTime = GradualAttenuationWaveTime 5 50  RefFrameTime  --GradualAttenuationWaveTime SpaceFrame RunFrame RefFrameTime

    RefFrameTime = FrameTime
    PosGradualAttenuationWave 5 50 500 1000 RefFrameTime  1           --PosGradualAttenuationWave SpaceFrame RunFrame VibrateRange ReferencePos RefFrameTime Direction
	FrameTime = GradualAttenuationWaveTime 5 50  RefFrameTime  --GradualAttenuationWaveTime SpaceFrame RunFrame RefFrameTime

-- 	--造型：中间正弦波
    RefFrameTime = FrameTime
    SinMidRowColFramePos 5 100 2 500 1000 RefFrameTime             --SinMidRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime
	FrameTime = SinMidRowAndColFramePosTime 5 100 2  RefFrameTime  --SinMidRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime 

-- 	--造型：对角正弦波
    RefFrameTime = FrameTime
    SinRowColFramePos 5 100 3 300 1000 RefFrameTime 0            --SinRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowAndColFramePosTime 5 100 3  RefFrameTime   --SinRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime 
-- 	--造型：对角正弦波
    RefFrameTime = FrameTime
    SinRowColFramePos 5 100 3 300 1000 RefFrameTime 1            --SinRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowAndColFramePosTime 5 100 3  RefFrameTime   --SinRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime 
-- 	--造型：对角正弦波
    RefFrameTime = FrameTime
    SinRowColFramePos 5 100 3 300 1000 RefFrameTime 2            --SinRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowAndColFramePosTime 5 100 3  RefFrameTime   --SinRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime 
-- 	--造型：对角正弦波
    RefFrameTime = FrameTime
    SinRowColFramePos 5 100 3 300 1000 RefFrameTime 3            --SinRowColFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowAndColFramePosTime 5 100 3  RefFrameTime   --SinRowAndColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime 

-- 	--造型：单行正弦波
    RefFrameTime = FrameTime
    SinSingleRowFramePos 1 5 100 2 600 1000 RefFrameTime          --SinSingleColFramePos ColIndex SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime 
	FrameTime = SinRowOrColFramePosTime 5 100 2  RefFrameTime row    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol
-- 	--造型：单列正弦波
    RefFrameTime = FrameTime
    SinSingleColFramePos 1 5 100 2 600 1000 RefFrameTime          --SinSingleColFramePos ColIndex SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime 
	FrameTime = SinRowOrColFramePosTime 5 100 2  RefFrameTime column    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol

-- 	--造型：行正弦波
    RefFrameTime = FrameTime
    SinRowFramePos  5 100 3 600 1000 RefFrameTime 0               --SinRowFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowOrColFramePosTime 5 100 3  RefFrameTime row    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol
-- 	--造型：行正弦波
    RefFrameTime = FrameTime
    SinRowFramePos  5 100 3 600 1000 RefFrameTime 1               --SinRowFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowOrColFramePosTime 5 100 3  RefFrameTime row    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol

-- 	--造型：列正弦波
    RefFrameTime = FrameTime
    SinColFramePos  5 100 3 600 1000 RefFrameTime 0               --SinRowFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowOrColFramePosTime 5 100 3  RefFrameTime column    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol
-- 	--造型：列正弦波 
    RefFrameTime = FrameTime
    SinColFramePos  5 100 3 600 1000 RefFrameTime 1               --SinRowFramePos SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime Direction
	FrameTime = SinRowOrColFramePosTime 5 100 3  RefFrameTime column    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol

-- 	--造型：正弦波 过度平面
	PositionArray = HorizontalTarPos 1000                         --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray           --SetFramePosition FrameTime BallMatrix PositionArray
	

----================================== 4 随机下落 过渡 [下平面] ============================================
-- 	--runtime:6s
-- 	--造型：随机110-2510
    FrameTimeTemp = 180                                           --30 * 6s = 180	
	FrameTime +=  FrameTimeTemp
	PositionArray = RandomPos 10 2510                             --RandomPos  rmin rmax
	SetFramePosition FrameTime BallMatrix PositionArray  


----================================= 5 平面=============================================
-- 	--runtime:3s
-- 	--过度平面
	FrameTimeTemp = 30                                             --30 * 1s = 30	
	FrameTime +=  FrameTimeTemp
	PositionArray = HorizontalTarPos 1000                          --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray            --SetFramePosition FrameTime BallMatrix PositionArray

    FrameTimeTemp = 15                                             --30 * 0.5s = 15	
	FrameTime +=  FrameTimeTemp
	PositionArray = HorizontalTarPos 1000                          --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray            --SetFramePosition FrameTime BallMatrix PositionArray


----================================== 3 正弦波 ============================================
-- 	--runtime:3s
-- 	--造型：行正弦波
	RefFrameTime = FrameTime
	SinSingleRowFramePos 1 5 200 3 600 1000 RefFrameTime          --SinSingleRowFramePos RowIndex SpaceFrame RunFrame WaveNum Range ReferencePos RefFrameTime
	FrameTime = SinRowOrColFramePosTime 5 100 2  RefFrameTime row    --SinRowOrColFramePosTime SpaceFrame RunFrame WaveNum  RefFrameTime RowOrCol

-- 	--正弦波 过度平面
	PositionArray = HorizontalTarPos 1000                         --HorizontalTarPos TargetPosition
	SetFramePosition FrameTime BallMatrix PositionArray           --SetFramePosition FrameTime BallMatrix PositionArray










