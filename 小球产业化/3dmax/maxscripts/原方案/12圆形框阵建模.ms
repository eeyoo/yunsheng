--重置场景
resetMaxFile #noprompt


num = 12
rot_arr = eulerangles 0 0 45
rot_arr1 = eulerangles 15 0 0

--创建球阵
LineArray = #()
for i = 1 to num do
(
	LineArray[i] = torus segs:48 radius1:(200 + 30*(i-1)) radius2:5 position:[0,0,0] wirecolor: [255, 255, 255]
	--rotate LineArray[i] rot_arr
	--rotate LineArray[i] rot_arr1	
)

