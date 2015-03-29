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
run_initial_pos = 150
run_limit_pos = 1150
limit_pos = 1300
middle_pos = (initial_pos+limit_pos)/2


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
	randomSpherePos (run_limit_pos-100)  (run_initial_pos+100 )
	horizLineDisPos run_limit_pos  run_initial_pos 
	FrameTime += 120
	randomSpherePos run_limit_pos  run_initial_pos 
	horizLineDisPos run_limit_pos  run_initial_pos 
	
	FrameTime += 120
	randomSpherePos (middle_pos+300) (middle_pos-300)
	horizLineDisPos (middle_pos+350) (middle_pos-350)
	FrameTime += 90
	randomSpherePos (middle_pos+300) (middle_pos-300)
	horizLineDisPos (middle_pos+350) (middle_pos-350)
	
	FrameTime += 90
	randomSpherePos (middle_pos+150) (middle_pos-150)
	horizLineDisPos (middle_pos+200) (middle_pos-200)
	FrameTime += 90
	randomSpherePos (middle_pos+150) (middle_pos-150)
	horizLineDisPos (middle_pos+200) (middle_pos-200)
	
	FrameTime += 60
	randomSpherePos (middle_pos+50) (middle_pos-50)
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	FrameTime += 60
	randomSpherePos (middle_pos+50) (middle_pos-50)
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	
	FrameTime += 30
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
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	
	--球框框阵向上运行呼应
	FrameTime += 120
	randomSpherePos (run_initial_pos+300) run_limit_pos
	linearForwardPos (run_initial_pos+300) run_initial_pos       --linearForwardPos h hor
	
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
	horizLineDisPos (middle_pos+300) (middle_pos-300)
	FrameTime += 5
	horizLineDisPos (middle_pos+300) (middle_pos-300)
	
	--球阵启动波动
	FrameTime = sinSphereCPos 200 2 240 middle_pos 150    --sinSphereCPos 振幅 周期数 周期时间 基准面 振幅增量
	horizLineDisPos (middle_pos+500) (middle_pos-500)
	
	--==============================================================================
	--造型005 - 球阵波形展示
	--==============================================================================
	--逐行波
	FrameTime = sinSphereSingleXNPos 300 1 160 5 middle_pos      --sinSpherePos amp count dur delay hor
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	--逐列波
	FrameTime = sinSphereSingleYNPos 300 1 160 5 middle_pos      --sinSpherePos amp count dur delay hor
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	--斜波
	FrameTime = sinSphereRatePos 200 2 120 10 middle_pos 100 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	--horizLineDisPos middle_pos middle_pos
	
	--框静止不动
	--horizLineDisPos limit_pos initial_pos
	
	--蛇形波
	--sinSphereSnakePos amp count dur delay hor da 振幅 次数 周期 延时 基准 振幅增量
	FrameTime = sinSphereSnakePos 150 2 120 5 middle_pos 50  
	
	
	--振幅线性变化波动
	--1 X轴向后端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 100 1    --横向变化振幅波形
	
	--2 Y轴向右端
	FrameTime = sinSphereRateYPos 200 2 120 10 middle_pos 100 1    --横向变化振幅波形
	
	--3 X轴向前端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 100 2    --横向变化振幅波形
	
	--4 Y轴向左端
	FrameTime = sinSphereRateYPos 200 2 120 10 middle_pos 100 2    --横向变化振幅波形
	
	--分组波动
	FrameTime = sinBXOESpherePos 200 2 120 10 middle_pos 100   	   --纵向平分两组反向波动
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	--==============================================================================
	--造型006 - 弹簧系列之横向Z字形
	--==============================================================================
	-----------------------------------横向Z字形------------------------------------
	--1 同时到达中平面
	--FrameTime += 120
	--horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	--horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 框阵打开，球阵横向Z字形
	FrameTime += 120
	rateSphereCPos 70 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos 500 middle_pos      --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCPos 70 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos 500 middle_pos      --horizLineBasePos 偏距 中心高
	
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
	rateXSpherePos 120 (run_initial_pos+100)        --球阵塔形造型，rateXSpherePos a hor 高度系数x7 基准
	horizLineBasePos 500 middle_pos 
	FrameTime += 15   --停留0.5秒
	rateXSpherePos 120 (run_initial_pos+100)      
	horizLineBasePos 500 middle_pos 
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos middle_pos         --球横向宝塔形
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
	rateXCOESpherePos 400 middle_pos            --球横向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	FrameTime += 5
	rateXCOESpherePos 400 middle_pos 
	horizLineBasePos 500 middle_pos 
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos middle_pos             --球横向X交叉
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	-----------------------------------纵向X字形------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateYCOESpherePos 400 middle_pos            --球纵向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	FrameTime += 5
	rateYCOESpherePos 400 middle_pos 
	horizLineBasePos 500 middle_pos 
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos middle_pos             --球纵向X交叉
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
	rateSphereCYPos 650 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	FrameTime += 15
	rateSphereCYPos 650 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	
	--2 回到中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型010 - 交叉变换系列扭曲面
	--==============================================================================
	-----------------------------------扭曲面---------------------------------------
	--1 框阵打开，球阵向上呈扭曲面 
	FrameTime += 120
	warpSpherePos 80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15   --停留0.5秒
	warpSpherePos 80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 球阵向上呈扭曲面，框奇偶颠倒
	FrameTime += 120
	warpSpherePos -80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_initial_pos run_limit_pos
	FrameTime += 15   --停留0.5秒
	warpSpherePos -80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_initial_pos run_limit_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	--==============================================================================
	--造型011 - 交叉变换系列抛物面
	--==============================================================================
	-----------------------------------抛物面---------------------------------------
	--1 框阵打开，球阵向上呈抛物面 
	FrameTime += 120
	paraboSpherePos 450 (middle_pos+50)         --paraboSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos middle_pos
	FrameTime += 15   --停留0.5秒
	paraboSpherePos 450 (middle_pos+50)       
	horizLineDisPos run_limit_pos middle_pos
	
	--2 球阵向上呈抛物面，框奇偶颠倒
	FrameTime += 120
	paraboSpherePos -450 (middle_pos-50)
	horizLineDisPos run_initial_pos middle_pos
	FrameTime += 15
	paraboSpherePos -450 (middle_pos-50)
	horizLineDisPos run_initial_pos middle_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型012 - 交叉变换系列躺椅面
	--==============================================================================
	-----------------------------------躺椅面---------------------------------------
	--1 框阵打开，球阵呈躺椅形
	FrameTime += 120
	chairSpherePos 8 middle_pos         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15   --停留0.5秒
	chairSpherePos 8 middle_pos          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 框阵和球阵颠倒
	FrameTime += 120
	chairSpherePos -8 middle_pos         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_initial_pos run_limit_pos
	FrameTime += 15   --停留0.5秒
	chairSpherePos -8 middle_pos          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_initial_pos run_limit_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型013 - 交叉变换系列悬布面
	--==============================================================================
	-----------------------------------悬布面---------------------------------------
	--1 框阵向上打开，球阵呈悬布面
	FrameTime += 90
	cornerSpherePos 3 middle_pos 1        --cornerSpherePos 高度系数 基准 
	horizLineDisPos run_limit_pos middle_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos 3 middle_pos 1          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos middle_pos
	
	FrameTime += 90
	cornerSpherePos 4 middle_pos 2        --cornerSpherePos 高度系数 基准 
	horizLineDisPos run_limit_pos middle_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos 4 middle_pos 2          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_limit_pos middle_pos
	
	FrameTime += 90
	cornerSpherePos 4 middle_pos 3        --cornerSpherePos 高度系数 基准 
	horizLineDisPos  middle_pos run_limit_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos 4 middle_pos 3          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos  middle_pos run_limit_pos
	
	FrameTime += 90
	cornerSpherePos 4 middle_pos 4        --cornerSpherePos 高度系数 基准 
	horizLineDisPos  middle_pos run_limit_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos 4 middle_pos 4          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos  middle_pos run_limit_pos
	
	/*
	--2 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--3 框阵向下打开，球阵呈悬布面
	FrameTime += 90
	cornerSpherePos -4 middle_pos 1         --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_initial_pos middle_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos -4 middle_pos 1          --球阵躺椅造型，chairSpherePos a hor 高度系数x7 基准
	horizLineDisPos run_initial_pos middle_pos
	*/
	
	--4 回到中平面
	FrameTime += 90
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
	
	--2 奇数组间歇性上升
	LineOddDelayPos  100 100 4 30 120 90 middle_pos   --LineOddDelayPos pos d count delay cycle hold hor
	LineEvenDelayPos 100 100 4 90 120 90 middle_pos    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--3 球阵启动列波
	FrameTime = sinSphereYPos 100 4 120 10 middle_pos 100
	
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
	
	--2 奇数组间歇性上升
	LineOddDelayPos  100 100 4 30 120 90 middle_pos   --LineOddDelayPos pos d count delay cycle hold hor
	LineEvenDelayPos 100 100 4 90 120 90 middle_pos    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--3 球阵启动列波
	FrameTime = sinSphereXPos 100 4 120 10 middle_pos 100
	
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
	--1 内圈球阵波动
	sinSphereRectInDelayPos  500 2 200 middle_pos    --SphereRectInDelayPos amp count dur hor 
	
	--2 延迟外圈球阵波动
	FrameTime += 15
	sinSphereRectOutDelayPos 500 2 200 middle_pos    --SphereRectInDelayPos amp count dur hor 
	
	--3框阵延迟波动
	FrameTime += 15
	FrameTime = sinLineDelayPos 500 2 200 15 middle_pos  --sinLineDelayPos 振幅 周期数 周期时间 延时时间 中心高
	
	FrameTime += 15
	horizSphereSynPos middle_pos 
	horizLinePos middle_pos
	
	--==============================================================================
	--造型017 - 磁材吸合造型
	--==============================================================================
	--准备
	FrameTime += 120
	--horizSphereSynPos middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--1 升1
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+200) (middle_pos-200)
	
	FrameTime += 60
	randomSpherePos (middle_pos+200) (middle_pos-200)
	horizLineDisPos (middle_pos+450) (middle_pos-450)
	
	--框慢速吸合
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+150) (middle_pos-150)
	
	--框慢速吸合
	FrameTime += 60
	randomSpherePos (middle_pos+100) (middle_pos-100)
	horizLineDisPos (middle_pos+450) (middle_pos-450)
	
	--框慢速吸合
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+150) (middle_pos-150)
	
	--框慢速吸合
	FrameTime += 30
	randomSpherePos (middle_pos+50) (middle_pos-50)
	horizLineDisPos (middle_pos+300) (middle_pos-300)
	
	--框慢速吸合
	FrameTime += 30
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+100) (middle_pos-100)
	
	--4 快速吸合
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--谢幕造型 - 球框阵回到零位
	--==============================================================================
	--回到零位
	FrameTime += 60
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	FrameTime
	
)

