--==============================================================================
--脚本说明：交互方式计算选取对象的速度并输出速度文件
--版本 1.0
--日期 2015-3-20
--作者 吴飞林
--==============================================================================



macroScript SpeedSheet category:"HowTo"
(
if selection.count > 0 then
(
 output_name = getSaveFileName caption:"SpeedSheet File" types:"SpeedSheet (*.ssh)|*.ssh|All Files (*.*)|*.*|"
 if output_name != undefined then
 (
  output_file = createfile output_name
  at time animationrange.start format "Object(s): %\n" (selection as array) to:output_file
  average_speed = 0
  for t = animationrange.start to animationrange.end do
  (
   at time t current_pos = selection.center
   at time (t-1f) last_pos = selection.center
   frame_speed = (distance current_pos last_pos)*FrameRate
   average_speed += frame_speed
   format "Frame %: %\n" t frame_speed to:output_file
  )
  average_speed /= (animationrange.end-animationrange.start)
  format "Average Speed: %\n" average_speed to:output_file
  close output_file
  edit output_name
 )--end if
)--end if
)--end macroScript