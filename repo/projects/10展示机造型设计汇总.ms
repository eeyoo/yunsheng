--==============================================================================
--脚本意图：修改0303代码的框架，兼容新的框架
--版本 1.0
--日期 2015-3-21
--作者 吴飞林
--==============================================================================

--加载框模型文件
--fileName = "C:\Users\feilin\Documents\3dsMax\workspace\repo\00框阵模板.max"
--loadMaxFile fileName 

--为放样赋予变量名称
num = 4
LineArray = #($Loft001, $Loft002, $Loft003, $Loft004)

--创建球阵模型
fileIn "create_sphere_4x8_array.ms" quiet: true

--执行造型函数库
fileIn "frameLib.ms"
fileIn "sphereLib.ms"



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
	--==============================节目1=========================================--
	--FrameTime += 5
	--horizSphereSynPos run_initial_pos
	--horizLinePos run_initial_pos
	
	
	--==============================================================================
	--造型001 - 球阵被框随机拉开
	--==============================================================================
	--启动
	FrameTime += 240
	randomSpherePos (run_limit_pos-50)  (run_initial_pos+50 )
	horizLineDisPos run_limit_pos  run_initial_pos 
	--停止5帧
	FrameTime = randomHoldSpherePos (run_limit_pos-50)  (run_initial_pos+50) 5
	horizLineDisPos run_limit_pos  run_initial_pos
	
	--==============================================================================
	--造型002 - 框阵上下压缩球阵
	--==============================================================================
	FrameTime += 120
	randomSpherePos (run_limit_pos-250)  (run_initial_pos+250 )
	horizLineDisPos (run_limit_pos-200)  (run_initial_pos+200 )
	FrameTime += 120
	randomSpherePos (run_limit_pos-250)  (run_initial_pos+250 )
	horizLineDisPos (run_limit_pos-200)  (run_initial_pos+200 )
	
	FrameTime += 120
	randomSpherePos (run_limit_pos-450)  (run_initial_pos+450 )
	horizLineDisPos (run_limit_pos-400)  (run_initial_pos+400 )
	FrameTime += 120
	randomSpherePos (run_limit_pos-450)  (run_initial_pos+450 )
	horizLineDisPos (run_limit_pos-400)  (run_initial_pos+400 )
	
	FrameTime += 90
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型003 - 球阵框阵上下对接
	--==============================================================================
	--造型准备
	FrameTime += 120
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	
	--球框框阵向上运行呼应
	FrameTime += 120
	randomSpherePos (run_initial_pos + 300) run_limit_pos
	linearForwardPos 300 run_initial_pos       --linearForwardPos h hor
	
	--暂停15帧
	FrameTime = randomHoldSpherePos (run_initial_pos + 300) run_limit_pos 15
	linearForwardPos 300 run_initial_pos       --linearForwardPos h hor
	
	--球阵收回零位，框阵到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型004 - 球阵中心波动
	--==============================================================================
	--框阵打开
	FrameTime += 120
	horizLineBasePos 400 middle_pos
	FrameTime += 5
	horizLineBasePos 400 middle_pos
	
	--框阵奇偶上下逐个波动
	--sinLineOddEvenDelayPos amp pos count dur delay hor
	sinLineOddEvenDelayPos 100 400 2 240 30 middle_pos
	
	--sinSphereCPos 振幅 周期数 周期时间 基准面 振幅增量
	FrameTime = sinSphereCPos 200 2 240 middle_pos 0   
	horizLineBasePos 400 middle_pos
	
	--==============================================================================
	--造型005 - 球阵逐行波
	--==============================================================================
	--框阵奇偶交换上下位置逐个波动
	--sinLineOddEvenDelayPos amp pos count dur delay hor
	sinLineFirstTwoPos 100 400 2 160 middle_pos                --运行时间 = 次数 x 周期 320

	--逐行波
	--sinSpherePos amp count dur delay hor
	FrameTime = sinSphereSingleXNPos 300 1 160 5 middle_pos    --运行时间 = 总延迟时间 + 次数 x 周期  320
	--horizLineBasePos 400 middle_pos
	
	--==============================================================================
	--造型006 - 球阵斜波
	--==============================================================================
	--1、2框波动，3、4框静止
	--sinLineFirstTwoPos amp pos count dur hor
	sinLineLastTwoPos 100 400 2 160 middle_pos
	
	--斜波
	FrameTime = sinSphereRatePos 200 2 120 10 middle_pos 100 1     --sinSphereRatePos 振幅 振幅变化次数 变化周期 逐行延时 中心高 振幅增量 起点
	
	--==============================================================================
	--造型007 - 球阵射线波
	--==============================================================================
	sinLineOddEvenDelayPos 100 400 2 120 30 middle_pos
	
	--X轴向后端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 150 1    --横向变化振幅波形
	--horizSphereSynPos middle_pos

	FrameTime += 60
	horizLineBasePos -400 middle_pos
	
	sinLineOddEvenDelayPos -100 -400 2 120 30 middle_pos
	
	--X轴向前端
	FrameTime = sinSphereRateXPos 200 2 120 10 middle_pos 150 2    --横向变化振幅波形
	
	--==============================================================================
	--造型008 - 球阵奇偶行波
	--==============================================================================
	sinLineOddEvenDelayPos -100 -400 2 120 30 middle_pos
	
	
	FrameTime = sinBXOESpherePos 100 2 120 10 middle_pos 100   	   --纵向平分两组反向波动

	--球阵回到中平面后60帧框阵回到中平面
	FrameTime += 60
	horizLinePos middle_pos 
	
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 
	
	--==============================================================================
	--造型009 - 弹簧系列之横向X字形
	--==============================================================================
	-----------------------------------横向X字形------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateXCOESpherePos 500 middle_pos            --球横向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	FrameTime += 5
	rateXCOESpherePos 500 middle_pos 
	horizLineBasePos 500 middle_pos 
	
	--2 弹簧压缩
	FrameTime += 60
	rateXCOESpherePos 200 middle_pos            --球横向X交叉
	horizLineBasePos 200 middle_pos       --horizLineBasePos 偏距 中心高
	
	--3 弹簧释放
	FrameTime += 60
	rateXCOESpherePos 500 middle_pos            --球横向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	
	--4 弹簧压缩
	FrameTime += 60
	rateXCOESpherePos 200 middle_pos            --球横向X交叉
	horizLineBasePos 200 middle_pos       --horizLineBasePos 偏距 中心高

	--5 弹簧释放
	FrameTime += 60
	rateXCOESpherePos 500 middle_pos            --球横向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高

	--6 弹簧压缩
	FrameTime += 60
	rateXCOESpherePos 100 middle_pos            --球横向X交叉
	horizLineBasePos 100 middle_pos       --horizLineBasePos 偏距 中心高
	
	--6 弹簧压缩
	FrameTime += 30
	rateXCOESpherePos 150 middle_pos            --球横向X交叉
	horizLineBasePos 150 middle_pos       --horizLineBasePos 偏距 中心高
 
	--7 回到中平面
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 

	--==============================================================================
	--造型010 - 一个斜线分成两段，并交叉一次
	--==============================================================================
	--1 同时到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 横向Z字形
	FrameTime += 120
	rateSphereCXPos -500 middle_pos       --rateSphereCPos ax7 hor
	horizLineBasePos -500 middle_pos      --horizLineBasePos 偏距 中心高
	
	--1 横向平行双斜线
	FrameTime += 120
	rateCXASpherePos 400 middle_pos        
	horizLineBasePos 500 middle_pos 
	FrameTime += 5
	rateCXASpherePos 400 middle_pos        
	horizLineBasePos 500 middle_pos 
	
	FrameTime += 120
	rateCXASpherePos -400 middle_pos        
	horizLineBasePos -500 middle_pos 
	FrameTime += 5
	rateCXASpherePos -400 middle_pos        
	horizLineBasePos -500 middle_pos
	
	--2 反向平行双斜线
	FrameTime += 120
	horizSphereSynPos middle_pos      
	horizLinePos middle_pos
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	--==============================================================================
	--造型011 - 正面X交叉1次
	--==============================================================================
	--1 打开
	FrameTime += 120
	rateXCOESpherePos 400 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 交叉
	FrameTime += 120
	rateXCOESpherePos -400 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	--弹簧再次压缩
	FrameTime += 60
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	
	
	--==============================================================================
	--造型012 - 蝴蝶结交叉，框阵打开
	--==============================================================================
	--1 框阵打开，球阵向上呈扭曲面 
	FrameTime += 120
	warpSpherePos 80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	--horizLineDisPos run_limit_pos run_initial_pos
	linearSymBPos 500 100 middle_pos
	
	FrameTime += 15   --停留0.5秒
	warpSpherePos 80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	--horizLineDisPos run_limit_pos run_initial_pos
	linearSymBPos 500 100 middle_pos
	
	--2 球阵向上呈扭曲面，框奇偶颠倒
	FrameTime += 120
	warpSpherePos -80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	linearSymBPos -500 -100 middle_pos
	FrameTime += 15   --停留0.5秒
	warpSpherePos -80 middle_pos          --warpSpherePos a hor 高度系数x7 基准
	linearSymBPos -500 -100 middle_pos
	
	--3 回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos  
	
	
	--==============================================================================
	--造型013 - 双向推动之行波
	--==============================================================================
	----------------------------------行波推动--------------------------------------
	--1 框阵奇偶分开
	FrameTime += 60
	--horizLineDisPos (middle_pos+100) (middle_pos-100)
	linearSymAPos 100 80 middle_pos
	
	--2 奇数组间歇性上升
	--LineOddDelayPos  100 100 4 30 120 90 middle_pos   --LineOddDelayPos pos d count delay cycle hold hor
	--LineEvenDelayPos 100 100 4 90 120 90 middle_pos    --LineOddDelayPos 偏距位置增量 变化次数 运行时间  保持时间 中心高
	
	--LineOddDisDelayPos pos d dis count delay cycle hold hor
	LineOddDisDelayPos 100 100 80 4 30 120 90 middle_pos
	--LineEvenDisDelayPos pos d dis count delay cycle hold hor
	LineEvenDisDelayPos 100 100 80 4 90 120 90 middle_pos 
	
	
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
	--造型014 - 6框一起上下波动
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
	--造型015 - 珍珠落盘
	--==============================================================================
	--造型准备
	--球运行至顶端，框运行至底部
	FrameTime += 60
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_limit_pos
	horizLinePos run_initial_pos
	
	--球随机下落
	--randomDownNumSpherePos amp num dur delay hor 振幅 时长 次数 最长延时 基准 
	FrameTime = randomDownSpherePos 1000 400 100 run_initial_pos
	
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	
	--==============================================================================
	--造型016 - 球框爆炸，球至中平面炸开随机延时下落，框在底部不动
	--==============================================================================
	--到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   
	--horizLinePos middle_pos  
	horizLinePos run_initial_pos	
	FrameTime += 15
	horizSphereSynPos middle_pos   
	--horizLinePos middle_pos

	--球框爆炸
	FrameTime += 20
	randomSpherePos run_limit_pos run_initial_pos
	--randomLinePos run_limit_pos run_initial_pos
	
	--下落
	FrameTime += 180
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	
	--==============================================================================
	--造型017 - 笑脸造型
	--==============================================================================
	--smileSpherePos a pos1 b pos2 hor 咧嘴幅度系数 咧嘴距离基准高度 眼睛幅度系数 眼睛距离基准高度 基准
	FrameTime += 120
	smileFSpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileFSpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达起始平面
	FrameTime += 120
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	
	--节目1结束停顿15秒
	FrameTime += 450
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	
	
	
	
	--==============================节目2=========================================--
	
	--==============================================================================
	--造型001 - 球阵和框阵保持同一平面
	--==============================================================================
	FrameTime += 120
	--框等分打开
	FrameTime = randomHoldSpherePos run_initial_pos (run_initial_pos + 900) 30
	linearForwardPos 1000 run_initial_pos
	
	--球随机延时上升
	--randomUpHorizSpherePos pmin pmax dur dmin dmax hor 最小位置 最大位置 单个时间 最短延时 最长延时 基准
	--FrameTime = randomUpHorizSpherePos run_initial_pos run_limit_pos 90 -30 200 run_initial_pos
	--linearForwardPos 1000 run_initial_pos
	

	--==============================================================================
	--造型002 - 磁材吸合造型
	--==============================================================================
	--准备
	FrameTime += 120
	randomSpherePos (middle_pos+400) (middle_pos-400)
	horizLineDisPos run_limit_pos run_initial_pos
	
	--1 压缩
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+200) (middle_pos-200)
	
	--2 弹开
	FrameTime += 60
	randomSpherePos (middle_pos+200) (middle_pos-200)
	horizLineDisPos (middle_pos+450) (middle_pos-450)
	
	--框慢速吸合
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+150) (middle_pos-150)
	
	--框慢速吸合
	FrameTime += 60
	randomSpherePos (middle_pos+200) (middle_pos-200)
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	--框慢速吸合
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLineDisPos (middle_pos+150) (middle_pos-150)
	
	--框慢速吸合
	FrameTime += 30
	randomSpherePos (middle_pos+50) (middle_pos-50)
	horizLineDisPos (middle_pos+200) (middle_pos-200)
	
	
	--快速吸合
	FrameTime += 10
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	
	--==============================================================================
	--造型003 - 球阵框阵上下对接
	--==============================================================================
	--框上下至顶端
	FrameTime += 120
	horizLinePos run_limit_pos
	horizSphereSynPos run_initial_pos
	FrameTime += 5
	horizLinePos run_limit_pos
	horizSphereSynPos run_initial_pos
	
	
	--框阵向下运行
	FrameTime += 120
	FrameTime = randomHoldSpherePos run_initial_pos (run_initial_pos + 700) 30
	linearForwardPos -300 run_limit_pos        --linearForwardPos h hor
	
	--球阵收回零位，框阵到达平面
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型004 - 球阵逐列波
	--==============================================================================
	--逐列波
	FrameTime = sinSphereSingleYNPos 300 1 160 5 middle_pos      --sinSpherePos amp count dur delay hor
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	FrameTime += 5
	horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	--==============================================================================
	--造型005 - 球阵蛇形波
	--==============================================================================
	--框阵波动
	--sinLineFirstTwoPos 100 400 2 200 middle_pos 
	--框阵奇偶上下逐个波动
	--sinLineOddEvenDelayPos amp pos count dur delay hor
	sinLineOddEvenDelayPos 100 400 2 180 30 middle_pos
	
	--DOMINO
	--sinSphereSnakePos amp count dur delay hor da 振幅 次数 周期 延时 基准 振幅增量
	FrameTime = sinSphereSnakePos 150 2 120 5 middle_pos 50    --400帧运行时间
	--horizLineDisPos (middle_pos+400) (middle_pos-400)
	
	--==============================================================================
	--造型006 - 球阵射线波
	--==============================================================================
	--1、2动，3、4静止
	sinLineFirstTwoPos 100 400 2 180 middle_pos 
	
	--Y轴向右端
	FrameTime = sinSphereRateYPos 200 2 160 10 middle_pos 150 1    --360帧
	
	--框阵翻转
	FrameTime += 60
	horizLineBasePos -400 middle_pos 
	--sinLineOddEvenDelayPos -100 -400 2 180 30 middle_pos
	sinLineFirstTwoPos 100 400 2 180 middle_pos
	

	--Y轴向左端
	FrameTime = sinSphereRateYPos 200 2 160 10 middle_pos 150 2    --360帧
	FrameTime += 60
	horizLinePos middle_pos
	
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型007 - 横向4行波波动，并翻转
	--==============================================================================
	--造型准备
	FrameTime += 60
	rateSphereCYPos 300 middle_pos
	--horizLineDisPos run_limit_pos run_initial_pos 
	linearForwardPos 900 (run_initial_pos + 50)
	
	--框阵分组波动
	--sinRateLinePos pos amp count dur hor 高度 振幅 次数 周期 基准
	--sinRateLinePos 900 100 2 120 (run_initial_pos+50)
	sinRateLinePos 900 100 2 120 (run_initial_pos + 50)
	
	--启动分层波动
	--sinXRateYSpherePos amp count dur delay hor high da 振幅 次数 周期 基准 分层基准偏距 振幅增量
	FrameTime = sinXRateYBSpherePos 150 2 120 10 middle_pos 300 20

	
	
	--造型翻转
	FrameTime += 120
	linearForwardPos -900 (run_limit_pos - 50)
	rateSphereCYPos -300 middle_pos
	sinRateLinePos -900 100 2 120 (run_limit_pos - 50)
	
	--启动分层波动
	--sinXRateYSpherePos amp count dur delay hor high da 振幅 次数 周期 基准 分层基准偏距 振幅增量
	FrameTime = sinXRateYBSpherePos 150 2 120 10 middle_pos -300 20
	--linearForwardPos -1000 run_limit_pos
	--linearForwardPos 900 (run_initial_pos + 50)
	
	--==============================================================================
	--造型008 - 侧面X1次交叉
	--==============================================================================
	--到达中平面
	FrameTime += 60
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 5
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--1 打开
	FrameTime += 120
	rateYCOESpherePos 300 middle_pos           --球横向X交叉
	horizLineDisPos run_limit_pos run_initial_pos
	
	--2 交叉
	FrameTime += 120
	rateYCOESpherePos -300 middle_pos           --球横向X交叉
	horizLineDisPos run_initial_pos run_limit_pos 
	
	
	--弹簧再次压缩
	FrameTime += 60
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos           --球横向X交叉
	horizLinePos middle_pos 
	
	--==============================================================================
	--造型009 - 抛物面
	--==============================================================================
	--框阵打开，球阵向上呈抛物面 
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
	
	--回中
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos
	horizLinePos middle_pos 
	
	--==============================================================================
	--造型010 - 悬布面
	--==============================================================================
	--1 框阵向上打开，球阵呈悬布面
	--悬布造型高度
	corner_high = 1010
	FrameTime += 90
	cornerSpherePos corner_high run_initial_pos 1        --cornerSpherePos 高度系数 基准 
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15   --停留0.5秒
	cornerSpherePos corner_high run_initial_pos 1        --cornerSpherePos 高度系数 基准 
	horizLineDisPos run_limit_pos run_initial_pos
	
	FrameTime += 90
	cornerSpherePos corner_high run_initial_pos 3        --cornerSpherePos 高度系数 基准 
	--horizLineDisPos  run_initial_pos run_limit_pos
	LineFirstTwoDisPos -500 middle_pos
	LineLastTwoDisPos 500 middle_pos
	
	FrameTime += 15   --停留0.5秒
	cornerSpherePos corner_high run_initial_pos 3        --cornerSpherePos 高度系数 基准 
	--horizLineDisPos run_initial_pos run_limit_pos
	LineFirstTwoDisPos -500 middle_pos
	LineLastTwoDisPos 500 middle_pos
	
	FrameTime += 90
	cornerSpherePos corner_high run_initial_pos 2        --cornerSpherePos 高度系数 基准 
	--horizLineDisPos  run_initial_pos run_limit_pos
	LineFirstTwoDisPos 500 middle_pos
	LineLastTwoDisPos 500 middle_pos
	
	FrameTime += 15   --停留0.5秒
	cornerSpherePos corner_high run_initial_pos 2        --cornerSpherePos 高度系数 基准 
	--horizLineDisPos run_initial_pos run_limit_pos
	LineFirstTwoDisPos 500 middle_pos
	LineLastTwoDisPos 500 middle_pos
	
	FrameTime += 90
	cornerSpherePos corner_high run_initial_pos 4        --cornerSpherePos 高度系数 基准 
	--horizLineDisPos  run_initial_pos run_limit_pos
	LineFirstTwoDisPos 500 middle_pos
	LineLastTwoDisPos -500 middle_pos
	
	FrameTime += 15   --停留0.5秒
	cornerSpherePos corner_high run_initial_pos 4        --cornerSpherePos 高度系数 基准 
	--horizLineDisPos run_initial_pos run_limit_pos
	LineFirstTwoDisPos 500 middle_pos
	LineLastTwoDisPos -500 middle_pos
	
	
	--回到中平面
	FrameTime += 90
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos
	
	--==============================================================================
	--造型011 - 球阵列波推动上下框阵移动
	--==============================================================================
	--1 框阵奇偶分开
	FrameTime += 60
	linearSymAPos 100 80 middle_pos
	
	--2 奇数组间歇性上升
	--LineOddDisDelayPos pos d dis count delay cycle hold hor
	LineOddDisDelayPos 100 100 80 4 30 120 90 middle_pos
	--LineEvenDisDelayPos pos d dis count delay cycle hold hor
	LineEvenDisDelayPos 100 100 80 4 90 120 90 middle_pos 
	
	
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
	--造型012 - 6框呈现静态造型
	--==============================================================================
	--哑铃型
	FrameTime += 200
	--CompositeOEAPos high pos hor 高度 偏离基准位置 基准高
	CompositeOEAPos 300 100 middle_pos
	
	FrameTime += 200
	CompositeOEAPos -300 -100 middle_pos

	--贝壳型
	FrameTime += 200
	CompositeOEBPos 300 100 middle_pos
	
	FrameTime += 200
	CompositeOEBPos -300 -100 middle_pos
	
	FrameTime += 200
	CompositeOEBPos 300 -100 middle_pos
	
	--回中平面
	FrameTime += 60
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	--FrameTime += 5
	--horizSphereSynPos middle_pos
	--horizLinePos middle_pos
	
	
	--==============================================================================
	--造型013 - 球框爆炸，球框在中平面一起炸开
	--==============================================================================
	--到达中平面         	
	FrameTime += 15
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos

	--球框爆炸
	FrameTime += 20
	randomLinePos run_limit_pos run_initial_pos
	randomSpherePos run_limit_pos run_initial_pos
	
	--下落
	FrameTime += 180
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	--FrameTime += 5
	--horizSphereSynPos run_initial_pos
	--horizLinePos run_initial_pos
	
	--==============================================================================
	--造型014 - 一个个放烟花，在空间形成一个造型
	--==============================================================================
	--回中平面
	--FrameTime += 15
	--horizSphereSynPos run_initial_pos
	--horizLinePos run_initial_pos
	
	--球快速上升
	--randomUpHorizSpherePos pmin pmax dur dmin dmax hor 最小位置 最大位置 单个时间 最短延时 最长延时 基准
	FrameTime = randomUpHorizSpherePos run_initial_pos run_limit_pos 30 30 120 run_initial_pos
	--horizLinePos run_initial_pos
	
	
	FrameTime += 240
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	

	
	
	--==============================================================================
	--造型015 - 笑脸造型
	--==============================================================================
	--smileSpherePos a pos1 b pos2 hor 咧嘴幅度系数 咧嘴距离基准高度 眼睛幅度系数 眼睛距离基准高度 基准
	FrameTime += 120
	smileFSpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileFSpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达起始平面
	FrameTime += 120
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos
	horizLinePos run_initial_pos
	
	--==============================================================================
	--谢幕造型 - 球框阵回到零位
	--==============================================================================
	--回到零位
	FrameTime += 90
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	FrameTime
	
)

