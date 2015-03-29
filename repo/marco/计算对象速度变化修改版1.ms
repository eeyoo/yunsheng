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
			at time animationrange.start format "Object(s): %\n" (selection as array) to:output_file
			 
			--average_speed = 0
			--max_speed = 0
			
			array_speed = #()
			for t = animationrange.start to animationrange.end do
			(
				at time t current_pos = selection.center
				at time (t-30f) last_pos = selection.center
				frame_speed = (distance current_pos last_pos)
				
				--收集帧速
				append array_speed frame_speed
				
				--average_speed += frame_speed
				
				--format "Frame %: %\n" t frame_speed to:output_file
			)
			
			--max_speed = max array_speed
			
			
			--average_speed /= (animationrange.end-animationrange.start)
			--format "Average Speed: %\n" average_speed to:output_file
			
			--速度矩阵排序
			sort array_speed
			--输出速度值到文件
			--for i = 1 to array_speed.count do ( format "frame % speed: %\n" i array_speed[i] to:output_file)
			--输出最大帧速
			end = array_speed.count
			format "Max Speed: %\n" array_speed[end] to:output_file
			
			close output_file
			--打开输出文件
			edit output_name
		)--end if
	)--end if
)--end macroScript