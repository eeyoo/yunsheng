--==============================================================================
--�ű���ͼ���������Ͳ�ͬϵ�л���
--�汾 1.0
--���� 2015-3-17
--���� �����
--==============================================================================

--�������͵���������
fileIn "sphereLib.ms"

-------------------------------�������ͺ���-------------------------------------
--==============================================================================
--���п�ͬ���ﵽָ��λ��
--������pos - ָ��Z��λ��ֵ
--==============================================================================
fn horizLinePos pos frame:FrameTime n:num =
(
	at time frame (
		for i = 1 to n do LineArray[i].pos.z = pos
	)

)

--==============================================================================
--������ż�������ԶԳƷֲ�
--������ pos  - ��Ի�׼�߶�
--������ pos   - ����
--������ hor  - ��׼�߶�
--==============================================================================
fn setLinePos pos1 pos2 pos3 pos4 frame:FrameTime =
(
	
	at time frame (
		LineArray[1].pos.z = pos1
		LineArray[2].pos.z = pos2
		LineArray[3].pos.z = pos3
		LineArray[4].pos.z = pos4
	)

)

--==============================================================================
--���λ�÷ֲ�
--������rmin, rmax - ���λ�����޺�����
--==============================================================================
fn randomLinePos rmin rmax frame:FrameTime n:num =
(
	for i = 1 to n do
	(
		at time frame (
			pos = random rmin rmax
			LineArray[i].pos.z = pos
		)
	)
)

--==============================================================================
--���λ�÷ֲ���holdס
--������rmin, rmax - ���λ�����޺�����
--������hold       - ����λ��ʱ��
--==============================================================================
fn randomLineHoldPos rmin rmax hold frame:FrameTime n:num =
(
	pos_array = #()
	
	at time frame (
		for i = 1 to n do
		(
			rand = random rmin rmax
			append pos_array rand
			
			LineArray[i].pos.z = rand
		)
	)
	
	at time (frame+hold) (
		for i = 1 to n do
		(
			LineArray[i].pos.z = pos_array[i]
		)
	)
	
	return frame+hold
)

--==============================================================================
--������ż���룬
--������pos1 - ������λ�ã�pos2 - ż����λ��
--==============================================================================
fn horizLineDisPos pos1 pos2 frame:FrameTime n:num =
(
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			LineArray[i].pos.z = pos1
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			LineArray[i].pos.z = pos2
		)
	)

)

--==============================================================================
--������ż���룬����׼��
--������pos - ����������ż���£�����������ż����
--������hor - ���ĸ�
--==============================================================================
fn horizLineBasePos pos hor frame:FrameTime n:num =
(
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			LineArray[i].pos.z = pos + hor
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			LineArray[i].pos.z = -pos + hor
		)
	)

)

--==============================================================================
--��������׶��
--����1 pos - ׶�θ߶�
--����2 hor  - ���ĸ�
--==============================================================================
fn linearForwardPos pos hor frame:FrameTime n:num =
(
	dh = pos/(n-1)
	
	for i = 1 to n do
	(
		at time frame (
			
			LineArray[i].pos.z = dh*(n-i) + hor
		)
	)
)

--==============================================================================
--����������
--����1 a - ����ϵ��
--����2 hor  - ���ĸ�
--==============================================================================
fn parabForwardPos a hor frame:FrameTime n:num =
(
	for i = 1 to n do
	(
		at time frame (
			x = n-i
			pos = a*x*x + hor
			LineArray[i].pos.z = pos
		)
	)
)

--==============================================================================
--����������
--����1 amp - ��������
--����2 hor - ���ĸ�
--==============================================================================
fn sinForwardPos amp hor frame:FrameTime n:num =
(
	for i = 1 to n do
	(
		at time frame (
			
			x = 120*(n-i)/n  --��Сֵ0�����ֵ90
			LineArray[i].pos.z = amp*sin(x) + hor
		)
	)
)

--------------------------------------------------------------------------------
-----------------------------���¶Գƾ�̬����-----------------------------------
--------------------------------------------------------------------------------
--==============================================================================
--������ż�������ԶԳƷֲ�
--������ pos  - ��Ի�׼�߶�
--������ d    - ����
--������ hor  - ��׼�߶�
--==============================================================================
fn linearSymAPos pos d hor frame:FrameTime n:num =
(
	--������
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			x = (i+1)/2
			LineArray[i].pos.z = pos-d*(x-1) + hor
		)
	)
	--ż����
	for i = 2 to n by 2 do
	(
		at time frame (
			x = i/2
			LineArray[i].pos.z = -pos+d*(x-1) + hor
		)
	)

)

--==============================================================================
--������ż�������ԶԳƷֲ�
--������ amp - �Գ�׶�η��ȣ������������ϣ�������������
--������ d   - ����
--������ hor  - ���ĸ�
--==============================================================================
fn linearSymBPos pos d hor frame:FrameTime n:num =
(
	for i = 1 to n-1 by 2 do
	(
		at time frame (
			x = (n-i+1)/2
			LineArray[i].pos.z = pos-d*(x-1) + hor
		)
	)
	
	for i = 2 to n by 2 do
	(
		at time frame (
			x = (n-i)/2
			LineArray[i].pos.z = -pos+d*x + hor
		)
	)
	
)

--------------------------------------------------------------------------------
----------------------------����ʱЧ��----------------------------------------
--------------------------------------------------------------------------------
--==============================================================================
--���ͺ������������ָ��ƽ��
--����1��pos1   - ��ʼλ��
--����2��pos2   - ����λ��
--����3��dur    - ����������ʱ��
--����4��delay  - ��ʱʱ�� 
--������hold   - ��������ʱ��
--==============================================================================
fn horizLineDelayPos pos1 pos2 dur delay hold frame:FrameTime n:num =
(

	for i = 1 to n do
	(
		frame += delay
		at time frame ( LineArray[i].pos.z = pos1 )
		
		at time (frame + dur) ( LineArray[i].pos.z = pos2 )
		
		at time (frame + dur + hold) ( LineArray[i].pos.z = pos2 )
	)
	
	return (frame + dur + hold)
)

--==============================================================================
--���ͺ������������ָ��ƽ��
--����1��pos1   - ��ʼλ��
--����2��pos2   - ����λ��
--����3��dur    - ����������ʱ��
--����4��delay  - ��ʱʱ�� 
--������hold   - ��������ʱ��
--==============================================================================
fn horizLineDelay1Pos pos dur delay hold hor frame:FrameTime n:num =
(
	
	for i = 1 to n do
	(
		frame += delay
		at time frame ( LineArray[i].pos.z = hor )
		
		at time (frame + dur) ( LineArray[i].pos.z = pos )
		
		at time (frame + dur + hold) ( LineArray[i].pos.z = pos )
	)
	
	return (frame + dur + hold)
)


--==============================================================================
--���ͺ�������ʱЧ����׶��
--����1��pos1   - ��ʼλ��
--����2��pos2   - ����λ��
--����3��dur    - ����������ʱ��
--����4��delay  - ��ʱʱ��
--������hold   - ��������ʱ��
--==============================================================================
fn linearLineDelayPos pos1 pos2 dur delay hold frame:FrameTime n:num =
(

	h = pos2-pos1
	dh = h/(n-1)
	
	for i = 1 to n do
	(
		frame += delay
		at time frame ( LineArray[i].pos.z = pos1 )
		
		at time (frame + dur) LineArray[i].pos.z = pos2 - dh*(i-1)
		
		at time (frame + dur + hold) LineArray[i].pos.z = pos2 - dh*(i-1)
	)
	
	return (frame + dur + hold)
)


--==============================================================================
--���ͺ�������ʱЧ����׶��
--������pos    - ׶���ܸ߶�
--������dur    - ����������ʱ��
--������delay  - ��������ʱʱ��
--������hold   - ��������ʱ��
--������hor    - ��׼�߶�
--==============================================================================
fn rateLineDelayPos pos dur delay hold hor frame:FrameTime n:num =
(
	a = pos/(n-1)
	
	for i = 1 to n do
	(
		--frame += delay
		at time frame ( LineArray[i].pos.z = hor )
		
		at time (frame + dur) LineArray[i].pos.z = a*(n-i) + hor
		
		at time (frame + dur + hold) LineArray[i].pos.z = a*(n-i) + hor
		
		frame += delay
	)
	
	return (frame - delay + dur + hold)
)

--==============================================================================
--���ͺ�������ʱЧ�������Ҳ���
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineLoopDelayPos amp count dur delay hor frame:FrameTime n:num =
(
	enter = frame
	c = 8  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	for i = 1 to n do
	(
		temp = frame
		for t = 1 to (c*count+1) do
		(
			at time temp ( LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += df	
		)
		frame += delay
	)

	return (enter + (n-1)*delay + count*dur)
)

--==============================================================================
--���ͺ������м俪ʼ�������
--����1��pos    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn LineSingleLoopDelayPos pos dur delay hor frame:FrameTime n:num =
(
	start = frame
	for i = 1 to n do
	(
		--start += delay
		at time start ( LineArray[i].pos.z = hor )
		at time (start+dur/2) ( LineArray[i].pos.z = pos+hor )
		at time (start+dur) ( LineArray[i].pos.z = hor )
		start += delay
	)

	return (frame + n*delay + dur)
)

------------------------------------����------------------------------------
--==============================================================================
--���ͺ���������������λ��
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn LineOddDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--1�ſ�
		LineArray[1].pos.z = pos + hor 
		--3�ſ�
		LineArray[3].pos.z = -pos + hor
	)

)

--==============================================================================
--���ͺ���������ż����λ��
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn LineEvenDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--2�ſ�
		LineArray[2].pos.z = pos + hor 
		--4�ſ�
		LineArray[4].pos.z = -pos + hor
	)

)

--==============================================================================
--���ͺ�����1��2�ſ�λ��
--������pos    - �������
--������hor    - ���ĸ�
--==============================================================================
fn LineFirstTwoDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--1�ſ�
		LineArray[1].pos.z = pos + hor 
		--2�ſ�
		LineArray[2].pos.z = -pos + hor
	)

)

--==============================================================================
--���ͺ�����3��4�ſ�λ��
--������pos    - �������
--������hor    - ���ĸ�
--==============================================================================
fn LineLastTwoDisPos pos hor frame:FrameTime n:num =
(
	at time frame ( 
		--3�ſ�
		LineArray[3].pos.z = pos + hor 
		--4�ſ�
		LineArray[4].pos.z = -pos + hor
	)

)


----------------------------------��̬��ʱ����----------------------------------
--==============================================================================
--���ͺ������������Ҳ���������ֻ��һ����
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLinePos amp count dur hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( for i = 1 to n do LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
		temp += df
	)

	return frame+count*dur
)

--==============================================================================
--���ͺ���������4�ȷ������Ҳ���
--������pos    - ����ֲ��߶�
--������amp    - �������
--������count  - ����������
--������dur    - ��������һ������ʱ��
--������delay  - ��ʱʱ��
--������hor    - ���ĸ�
--==============================================================================
fn sinRateLinePos pos amp count dur hor frame:FrameTime n:num =
(
	a = pos/(n-1)
	
	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	temp = frame
	for t = 1 to (c*count+1) do
	(
		at time temp ( for i = 1 to n do LineArray[i].pos.z = amp*sin(dt*(t-1)) + a*(n-i) + hor )
		temp += df
	)

	return frame+count*dur
)


--==============================================================================
--���ͺ�������������������Ҳ���
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineDelayPos amp count dur delay hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	for t = 1 to (c*count+1) do
	(
		temp = frame
		for i = 1 to n do
		(
			at time temp (  LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += delay
		)
		
		frame += df
	)

	return frame-df + (n-1)*delay
)

--==============================================================================
--���ͺ����������������������Ҳ���
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineOddDelayPos amp count dur delay hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	for t = 1 to (c*count+1) do
	(
		temp = frame
		for i = 1 to n-1 by 2 do
		(
			at time temp (  LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += delay
		)
		
		frame += df
	)

	return frame-df + (n-1)*delay
)


--==============================================================================
--���ͺ���������ż�����������Ҳ���
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineEvenDelayPos amp count dur delay hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	for t = 1 to (c*count+1) do
	(
		temp = frame
		for i = 2 to n by 2 do
		(
			at time temp (  LineArray[i].pos.z = amp*sin(dt*(t-1)) + hor )
			temp += delay
		)
		
		frame += df
	)

	return frame-df + (n-1)*delay
)

--==============================================================================
--���ͺ����������Ϊ��ż���飬��������Ҳ���
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineOddEvenDelayPos amp pos count dur delay hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	start_odd = frame
	start_even = frame
	
	--�������������
	for i = 1 to (n-1) by 2 do
	(
		temp = start_odd
		for t = 1 to (c*count+1) do 
		(
			--temp = start_odd
			at time temp (
			
				LineArray[i].pos.z = amp*sin(dt*(t-1)) + pos + hor
			)
			temp += df
		)
		start_odd += delay
	)
	
	--ż�����������
	for i = 2 to n by 2 do
	(
		temp = start_even
		for t = 1 to (c*count+1) do 
		(
			--temp = start_even
			at time temp (
			
				LineArray[i].pos.z = -amp*sin(dt*(t-1)) - pos + hor
			)
			temp += df
		)
		start_even += delay
	)

	return frame + n*delay
)

--==============================================================================
--���ͺ�����1��2�ԳƲ�����3��4��ֹ
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineFirstTwoPos amp pos count dur hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	temp = frame
	for t = 1 to (c*count+1) do 
	(
		at time temp (
			
			LineArray[1].pos.z = amp*sin(dt*(t-1)) + pos + hor
				
			LineArray[3].pos.z = pos + hor
				
			LineArray[2].pos.z = -amp*sin(dt*(t-1)) - pos + hor	
				
			LineArray[4].pos.z = -pos + hor
		)
		
		temp += df		
	)
	

	return frame + count*dur
)

--==============================================================================
--���ͺ�����1��2��ֹ��3��4����
--����1��amp    - �������
--����2��count  - ����������
--����3��dur    - ��������һ������ʱ��
--����4��delay  - ��ʱʱ��
--����5��hor    - ���ĸ�
--==============================================================================
fn sinLineLastTwoPos amp pos count dur hor frame:FrameTime n:num =
(

	c = 4  --���ڻ��ֵ�λ��
	dt = 360/c --���ڻ���һ��λ��ӦԲ�ܶ���
	df = dur/c --���ڻ���һ��λ��Ӧʱ��
	
	temp = frame
	for t = 1 to (c*count+1) do 
	(
		at time temp (
			
			LineArray[1].pos.z = pos + hor
				
			LineArray[3].pos.z = amp*sin(dt*(t-1)) + pos + hor
				
			LineArray[2].pos.z =  -pos + hor	
				
			LineArray[4].pos.z = -amp*sin(dt*(t-1)) - pos + hor
		)
		
		temp += df		
	)
	

	return frame + count*dur
)



--==============================================================================
--���ͺ����������������Ъ���˶�
--������pos    - ��ʼλ��
--������d       - λ������
--������count   - ������
--������delay   - ������ʱ����ʱ��
--������cycle   - ����ʱ��
--������hold    - ����ʱ��
--������hor     - ���ĸ�
--˵����һ������ʱ�����λ�ñ仯ʱ���뱣���յ�λ��ʱ��
--==============================================================================
fn LineOddDelayPos pos d count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + hor )
	
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + hor )
		at time (start+dur+hold) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--���ͺ����������������Ъ���˶��������
--������pos    - ��ʼλ��
--������d       - λ������
--������count   - ������
--������delay   - ������ʱ����ʱ��
--������cycle   - ����ʱ��
--������hold    - ����ʱ��
--������hor     - ���ĸ�
--˵����һ������ʱ�����λ�ñ仯ʱ���뱣���յ�λ��ʱ��
--==============================================================================
fn LineOddDisDelayPos pos d dis count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
	
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		at time (start+dur+hold) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--���ͺ����������������Ъ���˶��������
--������pos    - ��ʼλ��
--������d       - λ������
--������count   - ������
--������delay   - ������ʱ����ʱ��
--������cycle   - ����ʱ��
--������hold    - ����ʱ��
--������hor     - ���ĸ�
--˵����һ������ʱ�����λ�ñ仯ʱ���뱣���յ�λ��ʱ��
--==============================================================================
fn LineOddDisHoldDelayPos pos d dis count delay delay1 cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
	
	
	for t = 1 to count do
	(
		pos += d
		--at time (start+dur) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		temp = start
		for i = 1 to n-1 by 2 do 
		( 
			at time (temp + dur) ( LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
			temp += delay1
		)
		
		for i = 1 to n-1 by 2 do 
		( 
			at time (temp + dur + hold) ( LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
			temp += delay1
		)
		 
		--at time (start+dur+hold) ( for i = 1 to n-1 by 2 do LineArray[i].pos.z = pos + dis*(n-i-1)/2 + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--���ͺ���������ż�����Ъ���˶�
--������pos    - ��ʼλ��
--������d       - λ������
--������count   - ������
--������delay   - ������ʱ����ʱ��
--������cycle   - ����ʱ��
--������hold    - ����ʱ��
--������hor     - ���ĸ�
--˵����һ������ʱ�����λ�ñ仯ʱ���뱣���յ�λ��ʱ��
--==============================================================================
fn LineEvenDelayPos pos d count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos + hor )
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos + hor )
		at time (start+dur+hold) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)

--==============================================================================
--���ͺ���������ż�����Ъ���˶��������
--������pos    - ��ʼλ��
--������d       - λ������
--������count   - ������
--������delay   - ������ʱ����ʱ��
--������cycle   - ����ʱ��
--������hold    - ����ʱ��
--������hor     - ���ĸ�
--˵����һ������ʱ�����λ�ñ仯ʱ���뱣���յ�λ��ʱ��
--==============================================================================
fn LineEvenDisDelayPos pos d dis count delay cycle hold hor frame:FrameTime n:num =
(
	start = frame
	dur = cycle - hold
	
	start += delay
	at time start ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos - dis*(n-i)/2 + hor )
	
	for t = 1 to count do
	(
		pos += d
		at time (start+dur) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos - dis*(n-i)/2 + hor )
		at time (start+dur+hold) ( for i = 2 to n by 2 do LineArray[i].pos.z = -pos - dis*(n-i)/2 + hor )
		
		start += cycle
	)
	
	return frame+delay+count*cycle
)


-----------------------------������������-----------------------------------
--==============================================================================
--��򸴺����ͺ�������ʱЧ����׶�Σ����ȶ������
--������pos    - ׶���ܸ߶�
--������dur    - ����������ʱ��
--������delay  - ��������ʱʱ��
--������hold   - ��������ʱ��
--������hor    - ��׼�߶�
--���ò���������ļ��أ���˵�е�ͨ������û�����⣬ʣ�µ����ҷ���
--==============================================================================
fn rateCompositeADelayPos pos dur delay hold hor frame:FrameTime n:6 =
(
	start = frame
	a = pos/(n-1)
	
	for i = 1 to n do
	(
		--������ʼ֡
		start = frame +  delay*(i-1) --��4��ʱΪ0
		
		--�ȴ�����
		at time start ( 
			if (i<=4) then
				LineArray[5-i].pos.z = hor 
			
			if (i==5) then   --��Ȧ
				SphereRectOutHorizPos hor

			if (i==6) then   --��Ȧ			
				SphereRectInHorizPos hor
		)
		
		--���е�Ŀ��λ��
		at time (start + dur) (
			if (i<=4) then
				LineArray[5-i].pos.z = a*(i-1) + hor
			
			if (i==5) then   --��Ȧ
				SphereRectOutHorizPos (a*(i-1) + hor)
			
			if (i==6) then   --��Ȧ			
				SphereRectInHorizPos (a*(i-1) + hor)
		)
		
		--������������
		at time (start + dur + hold) (
			if (i<=4) then
				LineArray[5-i].pos.z = a*(i-1) + hor
			
			if (i==5) then   --��Ȧ
				SphereRectOutHorizPos (a*(i-1) + hor)
			
			if (i==6) then   --��Ȧ			
				SphereRectInHorizPos (a*(i-1) + hor)
		)		
	)

	return (start + dur + hold)
)

--==============================================================================
--��򸴺����ͺ�������ʱЧ����׶�Σ����ȶ������
--������pos    - ׶���ܸ߶�
--������dur    - ����������ʱ��
--������delay  - ��������ʱʱ��
--������hold   - ��������ʱ��
--������hor    - ��׼�߶�
--���ò���������ļ��أ���˵�е�ͨ������û�����⣬ʣ�µ����ҷ���
--==============================================================================
fn rateCompositeBDelayPos pos dur delay hold hor frame:FrameTime n:6 =
(
	start = frame
	a = pos/(n-1)
	
	for i = 1 to n do
	(
		--������ʼ֡
		start = frame +  delay*(i-1) --��4��ʱΪ0
		
		--�ȴ�����
		at time start (		
			if (i==1) then   --��Ȧ			
				SphereRectInHorizPos hor
			
			if (i==2) then   --��Ȧ
				SphereRectOutHorizPos hor
			
			if (i>=3) then
				LineArray[i-2].pos.z = hor
		)
		
		--���е�Ŀ��λ��
		at time (start + dur) (
			if (i==1) then   --��Ȧ			
				SphereRectInHorizPos (a*(n-i) + hor)
			
			if (i==2) then   --��Ȧ
				SphereRectOutHorizPos (a*(n-i) + hor)
			
			if (i>=3) then
				LineArray[i-2].pos.z = a*(n-i) + hor
		)
		
		--������������
		at time (start + dur + hold) (
			if (i==1) then   --��Ȧ			
				SphereRectInHorizPos (a*(n-i) + hor)
			
			if (i==2) then   --��Ȧ
				SphereRectOutHorizPos (a*(n-i) + hor)
			
			if (i>=3) then
				LineArray[i-2].pos.z = a*(n-i) + hor
		)		
	)

	return (start + dur + hold)
)

--==============================================================================
--��򸴺����ͣ���׼�ԳƷֲ���������
--������pos    - ׶���ܸ߶�
--������dur    - ����������ʱ��
--������delay  - ��������ʱʱ��
--������hold   - ��������ʱ��
--������hor    - ��׼�߶�
--���ò���������ļ��أ���˵�е�ͨ������û�����⣬ʣ�µ����ҷ���
--==============================================================================
fn CompositeOEAPos high pos hor frame:FrameTime n:6 =
(
	a = high/4
	
	at time frame (
		--������
		for i = 1 to (n-1) by 2 do
		(
			if (i==1) then --����Ȧ
				SphereRectInHorizPos (a*(i-1)+pos+hor)
			if (i > 1) then (
				LineArray[i-2].pos.z = a*(i-1)+pos+hor
			)
		)
		
		--ż����
		for i = 2 to n by 2 do
		(
			if (i==2) then --����Ȧ
			SphereRectOutHorizPos (-a*(i-2)-pos+hor)
			if (i > 2) then
				LineArray[i-2].pos.z = -a*(i-2)-pos+hor
		)
	)
	
)

--==============================================================================
--��򸴺����ͣ���׼�ԳƷֲ���������
--������pos    - ׶���ܸ߶�
--������dur    - ����������ʱ��
--������delay  - ��������ʱʱ��
--������hold   - ��������ʱ��
--������hor    - ��׼�߶�
--���ò���������ļ��أ���˵�е�ͨ������û�����⣬ʣ�µ����ҷ���
--==============================================================================
fn CompositeOEBPos high pos hor frame:FrameTime n:6 =
(
	a = high/4
	
	at time frame (
		--������
		for i = 1 to (n-1) by 2 do
		(
			if (i==1) then --����Ȧ
			SphereRectInHorizPos (a*(n-i-1)+pos+hor)
			if (i > 1) then (
				LineArray[i-2].pos.z = a*(n-i-1)+pos+hor
			)
		)
		
		--ż����
		for i = 2 to n by 2 do
		(
			if (i==2) then --����Ȧ
			SphereRectOutHorizPos (-a*(n-i)-pos+hor)
			if (i > 2) then
				LineArray[i-2].pos.z = -a*(n-i)-pos+hor
		)
	)
	
)

--==============================================================================
--��ը���ͣ������������߱�ը
--������pos    - ���߶�
--������d      - ��С�߶�
--������dur    - ��ըʱ��
--������hor    - ��׼�߶�
--���ò���������ļ��أ���˵�е�ͨ������û�����⣬ʣ�µ����ҷ���
--==============================================================================
fn boomLinePos pos d dur hor frame:FrameTime n:num =
(

	at time frame (
		--����ڻ�׼λ��
		for i = 1 to n do ( LineArray[i].pos.z = hor )
		horizSphereSynPos hor
	)
	
	at time (frame + dur) (
		--��ż���·���
		for i = 1 to (n-1) by 2 do ( LineArray[i].pos.z = random (hor+d) (hor+pos) )
		for i = 2 to n by 2 do ( LineArray[i].pos.z = random (hor-pos) (hor-d) )
	)
	
	return (frame+dur)
)
