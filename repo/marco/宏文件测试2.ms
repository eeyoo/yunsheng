--==============================================================================
--脚本说明：测试宏脚本技术
--版本 1.0
--日期 2015-3-26
--作者 吴飞林
--==============================================================================

macroScript Hello category:"HowTo"
(
	debug = newScript()
	
	--矩阵化
	selection as array
	num = selection.count
	
	if num > 0 then
	(
	
		--for i = 1 to num do format "object %: %\n" i selection[i] to:debug
		
		for i = 1 to num do
		(
			object_speed = #()
			
			--计算选中对象的最大速度
			for t = animationrange.start to animationrange.end do
			(
				at time t current_pos = selection[i].center
				at time (t-30f) last_pos = selection[i].center
				frame_speed = (distance current_pos last_pos)
					
				--收集帧速
				append object_speed frame_speed
			)
			
			sort object_speed
			end = object_speed.count
			max_speed = object_speed[end]
			
			format "% max speed: %\n" selection[i].name max_speed to:debug
		)
		
	)--end if
	
)--end macroScript