--==============================================================================
--脚本说明：球阵和框阵结合造型设计
--版本 1.0
--日期 2015-3-20
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
--最大演示范围，1.4米
--==================================================================================

initial_pos = 0
middle_pos = -700
down_limit_pos = -1400

FrameTime = 0

animate on
(
	--==============================================================================
	--球阵和框阵起始零位，停止0.5秒
	--==============================================================================
	FrameTime += 15
	horizSphereSynPos initial_pos   --球初始状态在最高位置 ，0位
	horizLinePos initial_pos         --框初始状态在最高位置 ，0位	
	
	--==============================================================================
	--球阵被框阵压缩和释放，球阵呈横向X交叉
	--==============================================================================
	-----------------------------------中平面之上-----------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateXOESpherePos 100 -700            --球横向X交叉
	horizLineDisPos 0 -700
	FrameTime += 15   --停留0.5秒
	rateXOESpherePos 100 -700            --球横向X交叉
	horizLineDisPos 0 -700
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos -700         --球横向X交叉
	horizLinePos -700
	
	--3 弹簧再次释放
	FrameTime += 120
	rateXOESpherePos 100 -700            --球横向X交叉
	horizLineDisPos 0 -700
	FrameTime += 15
	rateXOESpherePos 100 -700            --球横向X交叉
	horizLineDisPos 0 -700
	
	--4 弹簧再次压缩
	FrameTime += 120
	horizSphereSynPos -700           --球横向X交叉
	horizLinePos -700
	FrameTime += 5
	horizSphereSynPos -700           --球横向X交叉
	horizLinePos -700
	
	----------------------------------中平面以下---------------------------------------
	--1 弹簧释放
	FrameTime += 120
	rateXOESpherePos 100 -1400            --球横向X交叉
	horizLineDisPos -700 -1400
	FrameTime += 15
	rateXOESpherePos 100 -1400           --球横向X交叉
	horizLineDisPos -700 -1400
	
	--2 弹簧压缩
	FrameTime += 120
	horizSphereSynPos -1400          --球至底部
	horizLinePos -1400
	
	--3 弹簧再次释放
	FrameTime += 120
	rateXOESpherePos 100 -1400            --球横向X交叉
	horizLineDisPos -700 -1400
	FrameTime += 15
	rateXOESpherePos 100 -1400           --球横向X交叉
	horizLineDisPos -700 -1400
	
	--4 弹簧再次压缩
	FrameTime += 120
	horizSphereSynPos -1400          --球至底部
	horizLinePos -1400
	
	
	------------------------------------中平面-------------------------------------------
	--1 同时到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位	
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos
	
	--2 框阵打开，球阵横向X字形
	FrameTime += 120
	rateXCOESpherePos 100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	FrameTime += 15
	rateXCOESpherePos 100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	
	--3 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	FrameTime += 15
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	
	--4 再次弹开
	FrameTime += 120
	rateXCOESpherePos -100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	FrameTime += 15
	rateXCOESpherePos -100 middle_pos     --rateXCOESpherePos a hor
	horizLineDisPos 0 -1400
	
	--5 回到中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --球初始状态在最高位置 ，0位
	horizLinePos middle_pos        --框初始状态在最高位置 ，0位
	
	
	---------------------------------------------------------------------------
	--==============================================================================
	--造型008 - 弹簧系列之横向X字形
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
	rateXCOESpherePos 300 middle_pos            --球横向X交叉
	horizLineBasePos 300 middle_pos       --horizLineBasePos 偏距 中心高
	
	--3 弹簧释放
	FrameTime += 60
	rateXCOESpherePos 500 middle_pos            --球横向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高
	
	--4 弹簧压缩
	FrameTime += 60
	rateXCOESpherePos 300 middle_pos            --球横向X交叉
	horizLineBasePos 300 middle_pos       --horizLineBasePos 偏距 中心高

	--5 弹簧释放
	FrameTime += 60
	rateXCOESpherePos 500 middle_pos            --球横向X交叉
	horizLineBasePos 500 middle_pos       --horizLineBasePos 偏距 中心高

	--6 弹簧压缩
	FrameTime += 60
	rateXCOESpherePos 200 middle_pos            --球横向X交叉
	horizLineBasePos 200 middle_pos       --horizLineBasePos 偏距 中心高
 
	--7 回到中平面
	FrameTime += 30
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos       
	FrameTime += 5
	horizSphereSynPos middle_pos   
	horizLinePos middle_pos 
	
	
	FrameTime
	
)