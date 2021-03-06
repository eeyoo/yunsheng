
--==============================================================================
--脚本意图： 用于快速创建标准基本体并指定空间位置，如球体等
--版本： 1.0
--日期： 2015-2-16
--作者： 吴飞林
--==============================================================================

--重置场景
--resetMaxFile #noprompt

--创建球阵
row = 8
column = 4

--cx = (row + 1)/2
--cy = (column + 1)/2

--首先创建7x15二维矩阵
BallArray = #()
for i = 1 to (2*row-1)  do
(
	append BallArray #()
	for j = 1 to (2*column-1) do
	(  
		BallArray[i][j] = 0
	)
)

--对7x15二维矩阵奇数行和奇数列赋值球体对象
for i = 1 to (2*row-1) by 2 do
(
	
	for j = 1 to (2*column-1) by 2 do
	(  
		x = -280 + 40*(i-1)
		y = -120 + 40*(j-1)
		BallArray[i][j] = sphere radius:15 position:[x,y,0] wirecolor: [255, 255, 255] 
	)
)
