print("lua ��ʱ�������ʾ��.........")
print("�޸�lua,������нű�����Ч��")

--������������
function  themefun(count)
	local themeprex = "����"
	local themename = string.format("%s%d",themeprex,count)
	local w_themename = DMCA2W(themename)
	local w_themeoldname = DMCA2W("")
	g_pDMRes:SetCurTheme(w_themename:GetBuffer(),w_themeoldname:GetBuffer())	
	w_themename:ReleaseBuffer()--GetBuffer��һ��ReleaseBuffer����Ȼ�ڴ��޷��ͷ�,δ֪����
	w_themeoldname:ReleaseBuffer()
	g_pDMApp:RedrawAll()
end

widget_wnd = nil
-- WidgetWnd��ʼ����DMEVT_SCRIPT_START����
function DMEVT_SCRIPT_START(args)
	print("��ʼ����......")
	local duiwnd = args.m_pSender
	widget_wnd = duiwnd
	duiwnd:DM_SetTimer(123,11) --����1234��ʱ��
	return 1
end

function DMEVT_SCRIPT_TIMER(args)
	-- ÿ�������������
	t = os.time()
	themefun(t%17)
	return 1
end

function DMEVT_SCRIPT_END(args)
	-- ֹͣ��ʱ��
	widget_wnd:DM_KillTimer(123)
	return 1
end







