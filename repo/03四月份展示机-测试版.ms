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
down_limit_pos = -1300
middle_pos = (initial_pos + down_limit_pos)/2

FrameTime = 0
animate on
(

	--==============================================================================
	--造型001 - 球阵和框阵保持同一平面
	--==============================================================================
	--球阵和框阵保持零位
	FrameTime += 15
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	
	--==============================================================================
	--造型002 - 框阵分为奇偶两组构成区间，同时球阵区间内随机分布
	--==============================================================================
	FrameTime += 240
	randomSpherePos initial_pos down_limit_pos
	horizLineDisPos initial_pos down_limit_pos
	FrameTime += 120
	randomSpherePos initial_pos down_limit_pos
	horizLineDisPos initial_pos down_limit_pos
	
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
	--造型003 - 球阵在顶端随机落下，框阵在底部向上运行，与球阵产生呼应
	--==============================================================================
	--中平面停止
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--球运行至顶端，框运行至底部
	FrameTime += 120
	horizSphereSynPos initial_pos
	horizLinePos down_limit_pos
	
	--框阵向上运行呼应
	FrameTime += 120
	randomSpherePos initial_pos (down_limit_pos+300)
	linearForwardPos 300 down_limit_pos       --linearForwardPos h hor
	
	--球阵收回零位，框阵到达平面
	FrameTime += 120
	horizSphereSynPos initial_pos
	horizLinePos (down_limit_pos+300)
	
	--框阵向上运行呼应
	FrameTime += 120
	randomSpherePos initial_pos down_limit_pos
	linearForwardPos -300 (down_limit_pos+300)  --linearBackwardPos h hor
	
	--球阵与框阵运行至-800，耗时1秒
	FrameTime += 120
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLinePos middle_pos
	
	--==============================================================================
	--造型004 - 框阵分为奇偶两组构成区间，球阵在区间内由中心启动正弦波动形成水滴涟漪
	--==============================================================================
	--框阵打开
	FrameTime += 120
	horizLineDisPos initial_pos down_limit_pos
	
	--球阵启动波动
	FrameTime = sinSphereCPos 200 4 240 middle_pos 100    --sinSphereCPos 振幅 周期数 周期时间 基准面 振幅增量
	
	--状态停留
	FrameTime += 15
	horizSphereSynPos middle_pos
	horizLineDisPos initial_pos down_limit_pos
	
	--==============================================================================
	--谢幕造型 - 球框阵回到零位
	--==============================================================================
	--回到零位
	FrameTime += 120
	horizSphereSynPos initial_pos
	horizLinePos initial_pos
	
	FrameTime
	
)

