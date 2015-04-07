--==============================================================================
--脚本说明：交互方式计算选取对象的速度并输出速度文件
--版本 1.0
--日期 2015-3-20
--作者 吴飞林
--==============================================================================

macroScript MySpeedSheet category:"HowTo"
(
	if selection.count > 0 then
	(
		output_name = getSaveFileName caption:"SpeedSheet File" types:"SpeedSheet (*.ssh)|*.ssh|All Files (*.*)|*.*|"
		
		if output_name != undefined then
		(
			output_file = createfile output_name
			--at time animationrange.start format "Object(s): %\n" (selection as array) to:output_file
			
			
			--矩阵化
			--selection as array
			
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
						at time (t-1f) last_pos = selection[i].center
						frame_speed = (distance current_pos last_pos)*FrameRate
							
						--收集帧速
						append object_speed frame_speed
						
						--format "Frame % speed: %\n" t frame_speed to:output_file
					)
					
					sort object_speed
					end = object_speed.count
					max_speed = object_speed[end]
					
					format "% MAX speed: %\n" selection[i].name max_speed to:output_file
				)
		
			)--end if
			
			close output_file
			--打开输出文件
			edit output_name
		)--end if
	)--end if
)--end macroScript