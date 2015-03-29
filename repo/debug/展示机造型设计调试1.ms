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
--最大演示范围，1.3米
--==================================================================================

initial_pos = 0
limit_pos = 1300
middle_pos = (initial_pos+limit_pos)/2

--debug = newScript()
start1=0;	 end1=0
start2=0;	 end2=0
start3=0;	 end3=0
start4=0;	 end4=0

FrameTime = 0
animate on
(
	
	--==============================================================================
	--造型001 - 球阵和框阵保持同一平面
	--==============================================================================
	--球阵和框阵保持零位
	FrameTime += 5
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	
	--==============================================================================
	--造型002 - 框阵分为奇偶两组构成区间，同时球阵区间内随机分布
	--==============================================================================
	FrameTime += 240
	randomSpherePos initial_pos limit_pos
	horizLineDisPos limit_pos  initial_pos 
	FrameTime += 120
	randomSpherePos initial_pos limit_pos
	horizLineDisPos limit_pos  initial_pos 
	
	FrameTime += 120
	randomSpherePos (middle_pos+500) (middle_pos-500)
	horizLineDisPos (middle_pos+500) (middle_pos-500)
	FrameTime += 90
	randomSpherePos (middle_pos+500) (middle_pos-500)
	horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	FrameTime += 120
	randomSpherePos (middle_pos+300) (middle_pos-300)
	horizLineDisPos (middle_pos+300) (middle_pos-300)
	FrameTime += 90
	randomSpherePos (middle_pos+300) (middle_pos-300)
	horizLineDisPos (middle_pos+300) (middle_pos-300)
	
	FrameTime += 120
	randomSpherePos (middle_pos+100) (middle_pos-100)
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	FrameTime += 60
	randomSpherePos (middle_pos+100) (middle_pos-100)
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型003 - 球阵框阵上下对接
	--==============================================================================
	--中平面停止
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--球运行至顶端，框运行至底部
	FrameTime += 120
	horizSphereSynPos limit_pos 
	horizLinePos initial_pos
	
	--球框框阵向上运行呼应
	FrameTime += 120
	randomSpherePos middle_pos limit_pos
	linearForwardPos middle_pos initial_pos       --linearForwardPos h hor
	
	--球阵收回零位，框阵到达平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型004 - 球阵展翅造型
	--==============================================================================
	--框阵打开
	FrameTime += 120
	horizLineDisPos limit_pos initial_pos
	
	----------------------------------调试------------------------------------------
	start1 = FrameTime
	--format "start1: %\t" start1 to:debug
	
	--球阵启动波动
	FrameTime = sinSphereCPos 200 2 240 middle_pos 150    --sinSphereCPos 振幅 周期数 周期时间 基准面 振幅增量
	
	--==============================================================================
	--造型005 - 球阵波形展示
	--==============================================================================
	--逐行波
	FrameTime = sinSphereSingleXNPos 300 1 160 5 middle_pos      --sinSpherePos amp count dur delay hor
	
	--逐列波
	FrameTime = sinSphereSingleYNPos 300 1 160 5 middle_pos      --sinSpherePos amp count dur delay hor
		
	--斜波
	FrameTime = sinSphereRatePos 200 2 120 10 middle_pos 100 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	
	----------------------------------调试------------------------------------------
	end1 = FrameTime
	--format "end1: %\n" end1 to:debug
	
	--框静止不动
	horizLineDisPos limit_pos initial_pos
	
	--==============================================================================
	--造型006 - 弹簧系列之横向Z字形
	--==============================================================================
	-----------------------------------横向Z字形------------------------------------
	--1 同时到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 框阵打开，球阵横向X字形
	FrameTime += 120
	rateSphereCPos 92 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCPos 92 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos        
	
	--==============================================================================
	--造型007 - 弹簧系列之横向宝塔形
	--==============================================================================
	-----------------------------------横向宝塔形------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateXSpherePos 150 (initial_pos+250)        --球阵塔形造型，rateXSpherePos a hor 高度系数x7 基准
	horizLineBasePos middle_pos middle_pos
	FrameTime += 15   --停留0.5秒
	rateXSpherePos 150 (initial_pos+250)      
	horizLineBasePos middle_pos middle_pos
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos middle_pos         --球横向X交叉
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	--==============================================================================
	--造型008 - 弹簧系列之横向X字形
	--==============================================================================
	-----------------------------------横向X字形------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateXCOESpherePos 88 middle_pos            --球横向X交叉
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	FrameTime += 5
	rateXCOESpherePos 88 middle_pos 
	horizLineBasePos middle_pos middle_pos
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos middle_pos             --球横向X交叉
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	--==============================================================================
	--造型009 - 弹簧系列之侧向Z字形
	--==============================================================================
	-----------------------------------侧向Z字形------------------------------------
	--1 框阵打开，球阵侧向Z字形(系数为正则)
	FrameTime += 120
	rateSphereCYPos 130 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCYPos 130 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos middle_pos middle_pos      --horizLineBasePos 偏距 中心高
	
	--2 回到中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 1
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型010 - 交叉变换系列扭曲面
	--==============================================================================
	-----------------------------------扭曲面---------------------------------------
	--1 框阵打开，球阵向上呈扭曲面 
	FrameTime += 120
	warpSpherePos 80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos limit_pos initial_pos
	FrameTime += 15   --停留0.5秒
	warpSpherePos 80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos limit_pos initial_pos
	
	--2 球阵向上呈扭曲面，框奇偶颠倒
	FrameTime += 120
	warpSpherePos -80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos initial_pos limit_pos
	FrameTime += 15   --停留0.5秒
	warpSpherePos -80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos initial_pos limit_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 1
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	--==============================================================================
	--造型011 - 交叉变换系列抛物面
	--==============================================================================
	-----------------------------------抛物面---------------------------------------
	--1 框阵打开，球阵向上呈抛物面 
	FrameTime += 120
	paraboSpherePos 10 middle_pos         --paraboSpherePos a hor 高度系数x7 基准
	horizLineDisPos limit_pos initial_pos
	FrameTime += 15   --停留0.5秒
	paraboSpherePos 10 middle_pos       
	horizLineDisPos limit_pos initial_pos
	
	--2 球阵向上呈抛物面，框奇偶颠倒
	FrameTime += 120
	paraboSpherePos -10 middle_pos
	horizLineDisPos initial_pos limit_pos
	FrameTime += 15
	paraboSpherePos -10 middle_pos
	horizLineDisPos initial_pos limit_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 1
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型012 - 交叉变换系列躺椅面
	--==============================================================================
	-----------------------------------躺椅面---------------------------------------
	--1 框阵打开，球阵呈躺椅形
	FrameTime += 120
	chairSpherePos 8 middle_pos         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos limit_pos initial_pos
	FrameTime += 15   --停留0.5秒
	chairSpherePos 8 middle_pos          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos limit_pos initial_pos
	
	--2 框阵和球阵颠倒
	FrameTime += 120
	chairSpherePos -8 middle_pos         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos initial_pos limit_pos
	FrameTime += 15   --停留0.5秒
	chairSpherePos -8 middle_pos          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos initial_pos limit_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 1
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型013 - 交叉变换系列悬布面
	--==============================================================================
	-----------------------------------悬布面---------------------------------------
	--1 框阵向上打开，球阵呈悬布面
	FrameTime += 60
	cornerSpherePos 4 middle_pos 1        --cornerSpherePos 高度系数 基准 
	horizLineDisPos limit_pos middle_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos 4 middle_pos 1          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos limit_pos middle_pos
	
	--2 回到中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--3 框阵向下打开，球阵呈悬布面
	FrameTime += 60
	cornerSpherePos -4 middle_pos 1         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos initial_pos middle_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos -4 middle_pos 1          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos initial_pos middle_pos
	
	--4 回到中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型014 - 双向推动之列波
	--==============================================================================
	----------------------------------列波推动--------------------------------------
	--1 框阵奇偶分开
	FrameTime += 60
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	
	----------------------------------调试------------------------------------------
	start2 = FrameTime
	--format "start2: %\t" start2 to:debug
	
	--2 奇数组间歇性上升
	LineOddDelayPos  100 100 4 30 120 90 middle_pos   --LineOddDelayPos pos d count delay cycle hold hor
	LineEvenDelayPos 100 100 4 90 120 90 middle_pos    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--3 球阵启动列波
	FrameTime = sinSphereYPos 100 4 120 10 middle_pos 100
	
	----------------------------------调试------------------------------------------
	end2 = FrameTime
	--format "end2: %\t" end2 to:debug
	
	--FrameTime += 15
	--horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	--4 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型015 - 双向推动之行波
	--==============================================================================
	----------------------------------行波推动--------------------------------------
	--1 框阵奇偶分开
	FrameTime += 60
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	
	----------------------------------调试------------------------------------------
	start3 = FrameTime
	--format "start3: %\t" start3 to:debug
	
	--2 奇数组间歇性上升
	LineOddDelayPos  100 100 4 30 120 90 middle_pos   --LineOddDelayPos pos d count delay cycle hold hor
	LineEvenDelayPos 100 100 4 90 120 90 middle_pos    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--3 球阵启动列波
	FrameTime = sinSphereXPos 100 4 120 10 middle_pos 100
	
	----------------------------------调试------------------------------------------
	end3 = FrameTime
	--format "end3: %\t" end3 to:debug
	
	--FrameTime += 15
	--horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	--4 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 
	
	--==============================================================================
	--造型016 - 球框合二为一正弦波动
	--==============================================================================
	----------------------------------调试------------------------------------------
	start4 = FrameTime
	--format "start4: %\t" start4 to:debug
	
	--1 内圈球阵波动
	sinSphereRectInDelayPos  500 2 200 middle_pos    --SphereRectInDelayPos amp count dur hor 
	
	--2 延迟外圈球阵波动
	FrameTime += 15
	sinSphereRectOutDelayPos 500 2 200 middle_pos    --SphereRectInDelayPos amp count dur hor 
	
	--3框阵延迟波动
	FrameTime += 15
	FrameTime = sinLineDelayPos 500 2 200 15 middle_pos  --sinLineDelayPos 振幅 周期数 周期时间 延时时间 中心高
	
	----------------------------------调试------------------------------------------
	end4 = FrameTime
	--format "end4: %\t" end4 to:debug
	
	FrameTime += 15
	horizSphereSynPos middle_pos 
	horizLinePos middle_pos
	
	--==============================================================================
	--谢幕造型 - 球框阵回到零位
	--==============================================================================
	--回到零位
	FrameTime += 120
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	FrameTime
	
)

--输出关键帧信息
output_name = getSaveFileName caption:"Frame File" types:"FrameTime (*.txt)|*.txt|All Files (*.*)|*.*|"

if output_name != undefined then
(
	output_file = createfile output_name
	
	--波段1
	format "start1: %\t end1: %\n" start1 end1 to:output_file
	--波段2
	format "start2: %\t end2: %\n" start2 end2 to:output_file
	--波段3
	format "start3: %\t end3: %\n" start3 end3 to:output_file
	--波段4
	format "start4: %\t end4: %\n" start4 end4 to:output_file
	
	close output_file

	--打开输出文件
	edit output_name
)



