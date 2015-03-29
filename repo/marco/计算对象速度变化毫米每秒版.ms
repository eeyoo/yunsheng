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
			
			object_num = selection.count
			
			--average_speed = 0

			--对象速度矩阵
			object_speed = #()
			
			--对象矩阵的速度矩阵
			--array_speed = #()
			
			--对象最大速度矩阵
			--max_speed_array = #()
			
			--最大速度
			max_speed = 0
			
			
			--计算每个选中对象的速度
			for i = 1 to object_num do
			(
-
				--对象速度矩阵
				--object_speed = #()
				
				for t = animationrange.start to animationrange.end do
				(
					--at time t current_pos = selection.center
					--at time (t-30f) last_pos = selection.center
					at time t current_pos = selection[i].center
					at time (t-30f) last_pos = selection[i].center
					
					--frame_speed = (distance current_pos last_pos)*FrameRate
					frame_speed = (distance current_pos last_pos)
					
					--收集速度
					--append array_speed frame_speed
					append object_speed frame_speed
					
				)
				
				--收集对象的速度矩阵
				--append array_speed object_speed
				
				--输出对象最大速度值
				--速度矩阵排序
				sort object_speed
				--average_speed += frame_speed
					
				n = object_speed.count
				max_speed = object_speed[n]
					
				--format "Frame %: %\n" t frame_speed to:output_file
				format "Object % Max Speed %: %\n" i max_speed to:output_file
			)
			

			
			
			--average_speed /= (animationrange.end-animationrange.start)
			--format "Average Speed: %\n" average_speed to:output_file
			
			--速度矩阵排序
			--sort array_speed
			--输出速度值到文件
			--for i = 1 to array_speed.count do ( format "frame % speed: %\n" i array_speed[i] to:output_file)
			--输出最大帧速
			--index = array_speed.count
			--format "Max Frame Speed: %\n" array_speed[index] to:output_file
			
			close output_file
			--打开输出文件
			edit output_name
		)--end if
	)--end if
)--end macroScript