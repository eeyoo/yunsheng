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
	--球阵和框阵起始零位，停止0.5秒
	--==============================================================================
	FrameTime += 15
	horizSphereSynPos initial_pos   --球初始状态在最高位置 ，0位
	horizLinePos initial_pos         --框初始状态在最高位置 ，0位	
	
	/*
	--到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos
	*/
	
	--到达起始平面
	FrameTime += 30
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	
	--==============================================================================
	--笑脸造型
	--==============================================================================
	--smileSpherePos a pos1 b pos2 hor 咧嘴幅度系数 咧嘴距离基准高度 眼睛幅度系数 眼睛距离基准高度 基准
	FrameTime += 120
	smileESpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileESpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达起始平面
	FrameTime += 120
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	
	--==============================================================================
	--笑脸造型
	--==============================================================================
	--smileSpherePos a pos1 b pos2 hor 咧嘴幅度系数 咧嘴距离基准高度 眼睛幅度系数 眼睛距离基准高度 基准
	FrameTime += 120
	smileE1SpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileE1SpherePos 3 50 8 100 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达起始平面
	FrameTime += 120
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	FrameTime += 5
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	
	--==============================================================================
	--笑脸造型
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
	FrameTime += 5
	horizSphereSynPos run_initial_pos   --中平面
	horizLinePos run_initial_pos
	
	
	--==============================================================================
	--笑脸造型1
	--==============================================================================
	--smileSpherePos a pos1 b pos2 hor 咧嘴幅度系数 咧嘴距离基准高度 眼睛幅度系数 眼睛距离基准高度 基准
	FrameTime += 120
	smileSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos
	
	--==============================================================================
	--笑脸造型2
	--==============================================================================
	FrameTime += 120
	smileDSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileDSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos
	
	--==============================================================================
	--笑脸造型3
	--==============================================================================
	FrameTime += 120
	smileBSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileBSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos
	
	--==============================================================================
	--笑脸造型4
	--==============================================================================
	FrameTime += 120
	smileCSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	FrameTime += 15
	smileCSpherePos 3 150 8 200 middle_pos
	horizLineDisPos run_limit_pos run_initial_pos
	
	--到达中平面
	FrameTime += 120
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos 
	FrameTime += 5
	horizSphereSynPos middle_pos   --中平面
	horizLinePos middle_pos
	
	
	
	FrameTime
	
)