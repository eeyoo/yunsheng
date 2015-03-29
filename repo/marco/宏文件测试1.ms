--==============================================================================
--脚本说明：测试宏脚本技术
--版本 1.0
--日期 2015-3-26
--作者 吴飞林
--==============================================================================

macroScript Hello category:"HowTo"
(
	debug = newScript()
	
	if selection.count > 0 then
	(
	
		format "Object(s): %\n" (selection as array) to:debug
			
		num = selection.count
		
		print num to:debug	
		
		for i = 1 to num do format "object %: %\n" i selection[i] to:debug
		--print num to:debug
		
		
	
	)--end if
	
)--end macroScript