
// DataAcquisitionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DataAcquisition.h"
#include "DataAcquisitionDlg.h"
#include "afxdialogex.h"

#include "C://KAOS30/Lib/LSF_Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDataAcquisitionDlg dialog



CDataAcquisitionDlg::CDataAcquisitionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA_ACQUISITION_DIALOG, pParent)
	, m_sCameraTemperature(_T("No Camera"))
	, m_dSetCameraTemperature(-20)
	, m_fExposureTime(0)
	, m_sCameraStatus(_T(""))
	, m_sDirectory(_T(""))
	, m_nRepeatNumber(1)
	, m_sFilter(_T(""))
	, m_sFrameType(_T(""))
	, m_sObjectName(_T(""))
	, m_sReadoutMode(_T(""))
	, m_sObserver(_T(""))
	, m_sRepeatStatus(_T(""))
	, m_nMaxIntensity(0)
	, m_nMinIntensity(0)
	, m_sAvgIntensity(_T("0"))
	, m_nPixelPositionX(0)
	, m_nPixelPositionY(0)
	, m_nPIxelValue(0)
	, m_sSeeing(_T(""))
	, m_sSaveFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataAcquisitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_FULL_IMAGE, m_picDisplayFullImage);
	DDX_Control(pDX, IDC_BUTTON_CONNECT_CAMERA, m_btnConnectCamera);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT_CAMERA, m_btnDisconnectCamera);
	DDX_Text(pDX, IDC_EDIT_CAMERA_TEMPERATURE, m_sCameraTemperature);
	DDX_Text(pDX, IDC_EDIT_SET_CAMERA_TEMPERATURE, m_dSetCameraTemperature);
	DDX_Control(pDX, IDC_BUTTON_ON_CAMERA_COOLER, m_btnOnCameraCooler);
	DDX_Control(pDX, IDC_BUTTON_OFF_CAMERA_COOLER, m_btnOffCameraCooler);
	DDX_Control(pDX, IDC_BUTTON_ABORT_CAMERA_EXPOSURE, m_btnAbortCameraExposure);
	DDX_Control(pDX, IDC_BUTTON_START_CAMERA_EXPOSURE, m_btnStartCameraExposure);
	DDX_Control(pDX, IDC_COMBO_CAMERA_FRAME_TYPE, m_cmbFrameType);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_cmbFilter);
	DDX_Control(pDX, IDC_COMBO_BINNING_X, m_cmbBinningX);
	DDX_Control(pDX, IDC_COMBO_BINNING_Y, m_cmbBinningY);
	DDX_Text(pDX, IDC_EDIT_EXPOSURE_TIME, m_fExposureTime);
	DDX_Text(pDX, IDC_EDIT_CAMERA_STATUS, m_sCameraStatus);
	DDX_Control(pDX, IDC_COMBO_READOUT_MODE, m_cmbReadoutMode);
	DDX_Control(pDX, IDC_EDIT_EXPOSURE_TIME, m_editExposureTime);
	DDX_Text(pDX, IDC_EDIT_DIRECTORY, m_sDirectory);
	DDX_Control(pDX, IDC_CHECK_AUTO_SAVE, m_chkAutoSave);
	DDX_Text(pDX, IDC_EDIT_REPEAT_NUMBER, m_nRepeatNumber);
	DDV_MinMaxInt(pDX, m_nRepeatNumber, 1, 65535);
	DDX_CBString(pDX, IDC_COMBO_FILTER, m_sFilter);
	DDX_CBString(pDX, IDC_COMBO_CAMERA_FRAME_TYPE, m_sFrameType);
	DDX_Text(pDX, IDC_EDIT_OBJECT_NAME, m_sObjectName);
	DDX_Control(pDX, IDC_BUTTON_LOAD_FILTER, m_btnLoadFilter);
	DDX_CBString(pDX, IDC_COMBO_READOUT_MODE, m_sReadoutMode);
	DDX_Text(pDX, IDC_EDIT_OBSERVER, m_sObserver);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD_IMAGE, m_prgDownloadImage);
	DDX_Text(pDX, IDC_EDIT_REPEAT_STATUS, m_sRepeatStatus);
	DDX_Control(pDX, IDC_EDIT_REPEAT_NUMBER, m_editRepeatNumber);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_CLICK_IMAGE, m_picDisplayClickImage);
	DDX_Text(pDX, IDC_EDIT3, m_nMaxIntensity);
	DDX_Text(pDX, IDC_EDIT7, m_nMinIntensity);
	DDX_Text(pDX, IDC_EDIT8, m_sAvgIntensity);
	DDX_Text(pDX, IDC_EDIT_PIXEL_POSITION_X, m_nPixelPositionX);
	DDX_Text(pDX, IDC_EDIT_PIXEL_POSITION_Y, m_nPixelPositionY);
	DDX_Text(pDX, IDC_EDIT_PIXEL_VALUE, m_nPIxelValue);
	DDX_Text(pDX, IDC_EDIT_SEEING, m_sSeeing);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_STAR_SEEING, m_picDisplayStarSeeing);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_STAR_SEEING_X, m_picDisplayStarSeeingX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_SEEING_DIFFERENCE, m_picDisplaySeeingDifference);
	DDX_Text(pDX, IDC_EDIT_SAVE_FILE_NAME, m_sSaveFileName);
	DDX_Control(pDX, IDC_EDIT_SAVE_FILE_NAME, m_editSaveFileName);
}

BEGIN_MESSAGE_MAP(CDataAcquisitionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_CAMERA, &CDataAcquisitionDlg::OnClickedButtonConnectCamera)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_CAMERA, &CDataAcquisitionDlg::OnClickedButtonDisconnectCamera)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ON_CAMERA_COOLER, &CDataAcquisitionDlg::OnClickedButtonOnCameraCooler)
	ON_EN_KILLFOCUS(IDC_EDIT_SET_CAMERA_TEMPERATURE, &CDataAcquisitionDlg::OnKillfocusEditSetCameraTemperature)
	ON_EN_SETFOCUS(IDC_EDIT_SET_CAMERA_TEMPERATURE, &CDataAcquisitionDlg::OnSetfocusEditSetCameraTemperature)
	ON_BN_CLICKED(IDC_BUTTON_OFF_CAMERA_COOLER, &CDataAcquisitionDlg::OnClickedButtonOffCameraCooler)
	ON_BN_CLICKED(IDC_BUTTON_START_CAMERA_EXPOSURE, &CDataAcquisitionDlg::OnClickedButtonStartCameraExposure)
	ON_MESSAGE(SEND_TO_ARRAY, &CDataAcquisitionDlg::OnGetImageData)
	ON_MESSAGE(WM_DAP, &CDataAcquisitionDlg::OnGetMessageData)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_EN_SETFOCUS(IDC_EDIT_EXPOSURE_TIME, &CDataAcquisitionDlg::OnSetfocusEditExposureTime)
	ON_EN_KILLFOCUS(IDC_EDIT_EXPOSURE_TIME, &CDataAcquisitionDlg::OnKillfocusEditExposureTime)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FILTER, &CDataAcquisitionDlg::OnBnClickedButtonLoadFilter)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_FITS_FILE, &CDataAcquisitionDlg::OnBnClickedButtonSaveFitsFile)
	ON_CBN_SELCHANGE(IDC_COMBO_CAMERA_FRAME_TYPE, &CDataAcquisitionDlg::OnSelchangeComboCameraFrameType)
	ON_BN_CLICKED(IDC_BUTTON_SET_SAVE_PATH, &CDataAcquisitionDlg::OnBnClickedButtonSetSavePath)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER, &CDataAcquisitionDlg::OnSelchangeComboFilter)
	ON_CBN_SELCHANGE(IDC_COMBO_READOUT_MODE, &CDataAcquisitionDlg::OnSelchangeComboReadoutMode)
	ON_EN_SETFOCUS(IDC_EDIT_REPEAT_NUMBER, &CDataAcquisitionDlg::OnSetfocusEditRepeatNumber)
	ON_EN_KILLFOCUS(IDC_EDIT_REPEAT_NUMBER, &CDataAcquisitionDlg::OnKillfocusEditRepeatNumber)
	ON_EN_SETFOCUS(IDC_EDIT_OBJECT_NAME, &CDataAcquisitionDlg::OnSetfocusEditObjectName)
	ON_EN_KILLFOCUS(IDC_EDIT_OBJECT_NAME, &CDataAcquisitionDlg::OnKillfocusEditObjectName)
	ON_CBN_SETFOCUS(IDC_COMBO_FILTER, &CDataAcquisitionDlg::OnSetfocusComboFilter)
	ON_CBN_KILLFOCUS(IDC_COMBO_FILTER, &CDataAcquisitionDlg::OnKillfocusComboFilter)
	ON_CBN_SETFOCUS(IDC_COMBO_CAMERA_FRAME_TYPE, &CDataAcquisitionDlg::OnSetfocusComboCameraFrameType)
	ON_CBN_KILLFOCUS(IDC_COMBO_CAMERA_FRAME_TYPE, &CDataAcquisitionDlg::OnKillfocusComboCameraFrameType)
	ON_EN_SETFOCUS(IDC_EDIT_OBSERVER, &CDataAcquisitionDlg::OnSetfocusEditObserver)
	ON_EN_KILLFOCUS(IDC_EDIT_OBSERVER, &CDataAcquisitionDlg::OnKillfocusEditObserver)
	ON_CBN_SETFOCUS(IDC_COMBO_READOUT_MODE, &CDataAcquisitionDlg::OnSetfocusComboReadoutMode)
	ON_CBN_KILLFOCUS(IDC_COMBO_READOUT_MODE, &CDataAcquisitionDlg::OnKillfocusComboReadoutMode)
	ON_MESSAGE(REPEAT_EXPOSURE, &CDataAcquisitionDlg::OnRepeatExposure)
	ON_MESSAGE(PROGRESS_BAR, &CDataAcquisitionDlg::OnProgressBar)
	ON_BN_CLICKED(IDC_BUTTON_ABORT_CAMERA_EXPOSURE, &CDataAcquisitionDlg::OnBnClickedButtonAbortCameraExposure)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_EDIT_OBSERVER, &CDataAcquisitionDlg::OnChangeEditObserver)
	ON_EN_CHANGE(IDC_EDIT_OBJECT_NAME, &CDataAcquisitionDlg::OnChangeEditObjectName)
	ON_EN_CHANGE(IDC_EDIT_EXPOSURE_TIME, &CDataAcquisitionDlg::OnChangeEditExposureTime)
	ON_EN_CHANGE(IDC_EDIT_REPEAT_NUMBER, &CDataAcquisitionDlg::OnChangeEditRepeatNumber)
	ON_EN_CHANGE(IDC_EDIT_SET_CAMERA_TEMPERATURE, &CDataAcquisitionDlg::OnChangeEditSetCameraTemperature)
END_MESSAGE_MAP()


// CDataAcquisitionDlg message handlers

BOOL CDataAcquisitionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	pLibFLI = new CLIB_FLI;
	pLibAscom = new CLIB_ASCOM;
	pLibControl = new CLIB_CONTROL;

	g_Camera.nControlMode = CONTROL_MODE_VIRTUAL;
//	g_Camera.nControlMode = CONTROL_MODE_ASCOM;
//	g_Camera.nControlMode = CONTROL_MODE_FLI;

	g_Filter.nControlMode = CONTROL_MODE_VIRTUAL; // add 20170904 by Tae-Geun
//	g_Filter.nControlMode = CONTROL_MODE_FLI; // add 20170904 by Tae-Geun

	g_Camera.hDAPdlg = GetSafeHwnd();
	pLibControl->GetDialogHandle(g_Camera.hDAPdlg); // add 20170912 by Tae-Geun

	g_Camera.bImage = false;
	g_Camera.bScriptMode = false;
	g_Camera.bScriptAutofocusMode = false;
	g_Filter.bSetScriptFilter = false;

	m_btnDisconnectCamera.EnableWindow(FALSE);
	m_btnOnCameraCooler.EnableWindow(FALSE);
	m_btnOffCameraCooler.EnableWindow(FALSE);
	m_btnStartCameraExposure.EnableWindow(FALSE);
	m_btnAbortCameraExposure.EnableWindow(FALSE);

	m_cmbFrameType.AddString(_T("BIAS"));
	m_cmbFrameType.AddString(_T("DARK"));
	m_cmbFrameType.AddString(_T("FLAT"));
	m_cmbFrameType.AddString(_T("OBJECT"));
	m_cmbFrameType.SetCurSel(0);
	m_editExposureTime.EnableWindow(FALSE);
	
	LoadFilterList(); 

	for (int i = 1; i <= 4; i++) {

		CString sIndex;
		sIndex.Format(_T("%d"), i);
		m_cmbBinningX.AddString(sIndex);
		m_cmbBinningY.AddString(sIndex);
	}

	m_cmbBinningX.SetCurSel(0);
	m_cmbBinningY.SetCurSel(0);

	g_Camera.nStartPixelX = 0;
	g_Camera.nStartPixelY = 0;
	g_nFrameTypeFromScript = 0;

	m_chkAutoSave.SetCheck(BST_CHECKED);

	m_prgDownloadImage.SetRange(0, 50);//change 20170929 sybyeon

	g_Camera.sSaveDirectory = OBS_DIR;
//	g_Camera.sSaveDirectory = _T("C:\\KAOS30\\OBS");

	CString sFolderName;
	CTime CurTime;
	CurTime = CTime::GetCurrentTime();
	CTime NoonTime(CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), 12, 0, 0);
	CTimeSpan TimeGap = CurTime - NoonTime; 
	if (TimeGap.GetTotalMinutes() < 0) {
		CurTime -= CTimeSpan(1, 0, 0, 0);
		sFolderName.Format(_T("%04d%02d%02d"),
			CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());
	}
	else
		sFolderName.Format(_T("%04d%02d%02d"),
			CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());

	CString sCreateFolderPath;
	sCreateFolderPath.Format(_T("%s\\%s"), g_Camera.sSaveDirectory, sFolderName);
	if (CreateDirectory(sCreateFolderPath, NULL) == ERROR_PATH_NOT_FOUND)
		AfxMessageBox(_T("Make sure that Folder 'KAOS30' exists."));
	m_sDirectory = sFolderName;
	UpdateData(FALSE);

	g_Camera.nClickAreaWidth = 32;
	g_Camera.nClickAreaHeight = 32;

	g_dIntensityOnRadius = NULL;//add 20170829 sybyeon
	g_ClickedPixelData = NULL;
	g_dClickAreaIntensity = NULL;
	g_dFitIntensityOnRadius = NULL;//add 20170830 sybyeon
	g_dDifference = NULL;//add 20170907 sybyeon

	g_bClick = false;// add 20170913 sybyeon
	g_bAFPExposure = false;//add 20170913 sybyeon

	g_nClickedStartPointX = -1;//add 20170928 sybyeon
	g_nClickedStartPointY = -1;//add 20170928 sybyeon

	g_Camera.nClickCount = 0;//test

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataAcquisitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE) {

		if (IDYES == this->MessageBox(L"Are you sure you want to exit the Data Acquisition Package?", L"Message", MB_YESNO)) {

			CWnd* pWnd = FindWindow(NULL, MAIN_PROGRAM);
			if (pWnd != NULL)
				pWnd->SendMessage(WM_MAIN, (WPARAM)ID_DAP, (LPARAM)EXIT_DIALOG);

			DeleteMemory(); // add 20170923 by Tae-Geun
		}
		else
			return;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDataAcquisitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DisplayScienceImage();
		DisplayClickedImage();
		DisplayStarSeeing();
		DisplayStarSeeingOnX();// add 20170905 sybyeon
		DisplaySeeingDifference();//add 20170907 sybyeon

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDataAcquisitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDataAcquisitionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

long CDataAcquisitionDlg::OnGetMessageData(WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = FindWindow(NULL, MAIN_PROGRAM);
	bool bResult = false;

	int nMessage = (WPARAM)wParam;
	switch (nMessage) {

	case SET_FRAME_TYPE:
	{
		g_nFrameTypeFromScript = lParam; // add 20170920 by Tae-Geun
		OnSelchangeComboCameraFrameType();

		if (pWnd != NULL)
			pWnd->SendMessage(WM_SMP, (WPARAM)SET_FRAME_TYPE, (LPARAM)g_Camera.bFrameType);
	}
	break;
	case SET_FILTER:
	{
		g_Filter.lSetFilterIndex = lParam;
		OnSelchangeComboFilter();
	}
	break;
	case SET_EXPOSURE_TIME:
	{
		g_Camera.fExposureTime = *(float *)&lParam; // change 20710920 by Tae-Geun
		m_fExposureTime = g_Camera.fExposureTime;
		UpdateData(FALSE);

		bResult = true;
		if (pWnd != NULL)
			pWnd->SendMessage(WM_SMP, (WPARAM)SET_FRAME_TYPE, (LPARAM)bResult);
	}
	break;
	case START_CAMERA_EXPOSURE:
	{
		SetCameraExposure();
		StartCameraExposure();
	}
	break;

	case ABORT_CAMERA_EXPOSURE: // add 20170920 by Tae-Geun
	{
		pLibControl->AbortExposure(g_Camera.nControlMode);
	}
	break;

	case SET_SCRIPT_MODE: // add 20170920 by Tae-Geun
	{
		if (lParam) {

			g_Camera.bScriptMode = true;
			m_chkAutoSave.SetCheck(BST_CHECKED);

			UpdateData(FALSE);
			SetTimer(SET_FILTER_COMPLETE, 500, NULL);
		}
		else {

			g_Camera.bScriptMode = false;
			m_btnStartCameraExposure.EnableWindow(TRUE);
			m_btnAbortCameraExposure.EnableWindow(FALSE);

			KillTimer(SET_FILTER_COMPLETE);
		}
	}
	break;

	case SET_AUTOFOCUS_SCRIPT_MODE: // add 20171227 by Tae-Geun
	{
		if (lParam) {

			g_Camera.bScriptMode = false;

			g_Camera.bScriptAutofocusMode = true;
			m_chkAutoSave.SetCheck(BST_UNCHECKED);

			UpdateData(FALSE);
		}
		else {

			g_Camera.bScriptAutofocusMode = false;
			m_btnStartCameraExposure.EnableWindow(TRUE);
			m_btnAbortCameraExposure.EnableWindow(FALSE);

			KillTimer(SET_FILTER_COMPLETE);
		}
	}
	break;

	case GET_STRING_PARAMETER: // add 20170920 by Tae-Geun
	{
		CString sSection, sKey, sSMPFilePath;
		CStringA cKey;
		sSMPFilePath = _T("C:\\KAOS30\\CFG\\SMP.txt");
		sSection = _T("Script Information");

		TCHAR cDec[32];	
		sKey = _T("TARGET");
		GetPrivateProfileString(sSection, sKey, _T(""), cDec, 32, sSMPFilePath);
		g_FitsHeader.sTargetName = cDec;

	}
	break;

	case START_EXPOSURE_AFP ://change 20170918 sybyeon
	{
		g_bAFPExposure = true;

		if (!g_Camera.bLink) {
			SendSeeingValue();
			return 0;
		}
		int nStart = lParam;
		if (g_Camera.nControlMode == CONTROL_MODE_VIRTUAL) {

			if (nStart == AFP_TEST_START)
				pLibControl->SetCameraFrameType(g_Camera.nControlMode, AFP_TEST_START);
			else
				pLibControl->SetCameraFrameType(g_Camera.nControlMode, AFP_TEST_CONTINUE);
		}
		SetCameraExposure();
		StartCameraExposure();

	}
	break;
	case FILTER_POSITION ://add 20171205 sybyeon
	{
		if (!g_Camera.bLink)//add 20171207 sybyeon
			return 0;

		CWnd* pWnd = FindWindow(NULL, L"Auto Focus Package");
		if (pWnd != NULL)
			pWnd->SendMessage(WM_AFP, (WPARAM)FILTER_POSITION, g_Filter.lGetFilterIndex);
	}
	break;
	}

	return 0;
}

void CDataAcquisitionDlg::OnTimer(UINT_PTR nIDEvent) // change 20170920 by Tae-Geun
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent) {

	case GET_CAMERA_TEMPERATURE:
	{
		pLibControl->GetCameraTemperature(g_Camera.nControlMode, &g_Camera.dTemperature);
		g_Camera.sTemperature.Format(_T("%.2f"), g_Camera.dTemperature);

		if (g_Camera.dTemperature > 100)
			g_Camera.sTemperature = "No Camera";

		m_sCameraTemperature = g_Camera.sTemperature;
		UpdateData(FALSE);
	}
	break;

	case GET_CAMERA_STATUS:
	{
		pLibControl->GetCameraStatus(g_Camera.nControlMode, &g_Camera.sStatus); // change 20170830 by Tae-Geun
		m_sCameraStatus = g_Camera.sStatus;
		UpdateData(FALSE);
	}
	break;

	case SET_FILTER_COMPLETE:
	{
		if (g_Camera.bScriptMode || g_Camera.bScriptAutofocusMode) {

			if (g_Filter.bSetScriptFilter) {

				g_Filter.bSetScriptFilter = false;
				
				pLibControl->GetFilterIndex(g_Filter.nControlMode, &g_Filter.lGetFilterIndex); // change 20170911 by Tae-Geun
				m_cmbFilter.SetCurSel(g_Filter.lGetFilterIndex);
				UpdateData(TRUE);

				CWnd* pWnd = FindWindow(NULL, MAIN_PROGRAM); // change 20170920 by Tae-Geun
				if (pWnd != NULL)
					pWnd->SendMessage(WM_SMP, 0, true);
			}
		}
	}
	break;
	case GET_CAMERA_READOUT_MODE://add 20171225 sybyeon
 	{
		long lReadoutIndex;
		pLibControl->GetCameraReadoutModeIndex(g_Camera.nControlMode, &lReadoutIndex);
		m_cmbReadoutMode.SetCurSel(lReadoutIndex);
		pLibControl->SetCameraReadoutMode(g_Camera.nControlMode, lReadoutIndex);
	}
	break;
	case GET_FILTER_POSITION://add 20171225 sybyeon
	{
		long lFilterIndex;
		pLibControl->GetFilterIndex(g_Camera.nControlMode, &lFilterIndex);
		m_cmbFilter.SetCurSel(lFilterIndex);
		pLibControl->SetFilterIndex(g_Filter.nControlMode, lFilterIndex);
	}
	break;
	case CHECK_FILTER_MOVING://add 20171225 sybyeon
	{
		/*
		long status;
		FLIGetDeviceStatus(g_DeviceFilter, &status);//status==41 when moving
		if (status == 41)
		*/
	}
	break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CDataAcquisitionDlg::SetAllTimer()
{
	SetTimer(GET_CAMERA_TEMPERATURE, INTERVAL_CAMERA_TEMPERATURE, NULL);
	SetTimer(GET_CAMERA_STATUS, INTERVAL_CAMERA_STATUS, NULL);
	SetTimer(GET_CAMERA_READOUT_MODE, 500, NULL);//add 20171225 sybyeon
	SetTimer(GET_FILTER_POSITION, 500, NULL);//add 20171225 sybyeon

}

void CDataAcquisitionDlg::KillAllTimer()
{
	KillTimer(GET_CAMERA_TEMPERATURE);
	KillTimer(GET_CAMERA_STATUS);
	KillTimer(GET_CAMERA_READOUT_MODE);//add 20171225 sybyeon	
	KillTimer(GET_FILTER_POSITION);//add 20171225 sybyeon

}

void CDataAcquisitionDlg::OnClickedButtonConnectCamera()
{
	// TODO: Add your control notification handler code here
	g_Camera.bDriver = pLibControl->ConnectCameraDriver(g_Camera.nControlMode); // change 20170830 by Tae-Geun 

	if (g_Camera.bDriver) {

		g_Camera.bLink = pLibControl->LinkCamera(g_Camera.nControlMode); // change 20170830 by Tae-Geun
		pLibControl->GetCameraPixelSize(g_Camera.nControlMode, &g_Camera.dPixelSizeX, &g_Camera.dPixelSizeY); // change 20170830 by Tae-Geun
		pLibControl->GetCameraImageSize(g_Camera.nControlMode, &g_Camera.nImageWidth, &g_Camera.nImageHeight); // change 20170830 by Tae-Geun
		pLibControl->SetCameraFrameType(g_Camera.nControlMode, m_cmbFrameType.GetCurSel()); // change 20170831 by Tae-Geun

		g_Filter.bLink = pLibControl->LinkFilter(g_Filter.nControlMode); // change 20170904 by Tae-Geun
		pLibControl->GetCountFilter(g_Filter.nControlMode, &g_Filter.lCountFilter); // add 20170904 by Tae-Geun

		if (g_Camera.bLink && g_Filter.bLink) {

			AfxMessageBox(_T("Camera and Filter is connected."));

			GetCameraReadoutMode();
			pLibControl->GetFilterIndex(g_Filter.nControlMode, &g_Filter.lGetFilterIndex); // change 20170904 by Tae-Geun
			m_cmbFilter.SetCurSel(g_Filter.lGetFilterIndex);
			UpdateData(FALSE);

			//add 20171207 sybyeon
			CWnd* pWnd = FindWindow(NULL, L"Auto Focus Package");
			if (pWnd != NULL)
				pWnd->SendMessage(WM_AFP, (WPARAM)FILTER_POSITION, g_Filter.lGetFilterIndex);

			SetAllTimer();

			m_btnConnectCamera.EnableWindow(FALSE);
			m_btnLoadFilter.EnableWindow(FALSE);
			m_btnDisconnectCamera.EnableWindow(TRUE);
			m_btnOnCameraCooler.EnableWindow(TRUE);
			m_btnStartCameraExposure.EnableWindow(TRUE);
		}
		else
			AfxMessageBox(_T("Camera or Filter is not connected."));
	}
	else
		AfxMessageBox(_T("Device Driver is not connected."));
}


void CDataAcquisitionDlg::OnClickedButtonDisconnectCamera()
{
	// TODO: Add your control notification handler code here
	g_Camera.bLink = pLibControl->UnLinkCamera(g_Camera.nControlMode); // change 20170830 by Tae-Geun
	g_Filter.bLink = pLibControl->UnLinkFilter(g_Filter.nControlMode); // change 20170904 by Tae-Geun

	if (!g_Camera.bLink && !g_Filter.bLink) {

		AfxMessageBox(_T("Camera and Filter is disconnected."));

		KillAllTimer();

		m_cmbReadoutMode.ResetContent();

		//add 20170918 sybyeon
		g_Camera.bImage = false;
		g_bClick = false;

		m_btnConnectCamera.EnableWindow(TRUE);
		m_btnLoadFilter.EnableWindow(TRUE);
		m_btnDisconnectCamera.EnableWindow(FALSE);
		m_btnOnCameraCooler.EnableWindow(FALSE);
		m_btnOffCameraCooler.EnableWindow(FALSE);
		m_btnStartCameraExposure.EnableWindow(FALSE);
	}
	else
		AfxMessageBox(_T("Camera and Filter is not disconnected."));
}


void CDataAcquisitionDlg::OnClickedButtonOnCameraCooler()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	pLibControl->SetCameraTemperature(g_Camera.nControlMode, m_dSetCameraTemperature); // change 20170831 by Tae-Geun

	m_btnOnCameraCooler.EnableWindow(FALSE);
	m_btnOffCameraCooler.EnableWindow(TRUE);
}

void CDataAcquisitionDlg::OnClickedButtonOffCameraCooler()
{
	// TODO: Add your control notification handler code here

	pLibControl->SetCameraTemperature(g_Camera.nControlMode, 20.0); // change 20170831 by Tae-Geun

	m_btnOnCameraCooler.EnableWindow(TRUE);
	m_btnOffCameraCooler.EnableWindow(FALSE);
}

void CDataAcquisitionDlg::OnClickedButtonStartCameraExposure()
{
	// TODO: Add your control notification handler code here
	CString sRepeatNumber;
	UpdateData(TRUE);
	g_Camera.nRepeatNumber = m_nRepeatNumber;
	g_Camera.nRepeatNumberCount = 0;
	sRepeatNumber.Format(_T("%d/%d"), g_Camera.nRepeatNumberCount + 1, g_Camera.nRepeatNumber);
	m_sRepeatStatus = sRepeatNumber;
	UpdateData(FALSE);

	SetCameraExposure();
	StartCameraExposure();
}


void CDataAcquisitionDlg::OnBnClickedButtonAbortCameraExposure()
{
	// TODO: Add your control notification handler code here
	g_Camera.nRepeatNumberCount = g_Camera.nRepeatNumber;
	pLibControl->AbortExposure(g_Camera.nControlMode);

	m_btnStartCameraExposure.EnableWindow(TRUE);
	m_btnAbortCameraExposure.EnableWindow(FALSE);
}

void CDataAcquisitionDlg::GetCameraReadoutMode() // change 20170831 by Tae-Geun
{
	CString sReadoutMode;
	for (int i = 0; i < 3; i++) {
		pLibControl->GetCameraReadoutMode(g_Camera.nControlMode, i, &g_Camera.cCameraReadoutMode);
		sReadoutMode = g_Camera.cCameraReadoutMode;
		if (sReadoutMode != _T("")) {
			m_cmbReadoutMode.InsertString(-1, sReadoutMode);
		}
		else
			break;
	}
	m_cmbReadoutMode.SetCurSel(1); // change 20171223 by Tae-Geun : 1MHz default mode
	pLibControl->SetCameraReadoutMode(g_Camera.nControlMode, 1);//add 20171225 sybyeon
}

void CDataAcquisitionDlg::SetCameraExposure()
{
	UpdateData(TRUE);
	m_btnStartCameraExposure.EnableWindow(FALSE);
	m_btnAbortCameraExposure.EnableWindow(TRUE);


	if (!g_Camera.bScriptMode)
		g_Camera.fExposureTime = m_fExposureTime;

	g_Camera.lXBinning = m_cmbBinningX.GetCurSel() + 1;
	g_Camera.lYBinning = m_cmbBinningY.GetCurSel() + 1;
	pLibControl->SetCameraBin(g_Camera.nControlMode, g_Camera.lXBinning, g_Camera.lYBinning); // change 20170831 by Tae-Geun

	//add 20171129 sybyeon 
	int nReadoutModeIndex = m_cmbReadoutMode.GetCurSel();
	pLibControl->SetCameraReadoutMode(g_Camera.nControlMode, nReadoutModeIndex);
	m_cmbReadoutMode.SetCurSel(nReadoutModeIndex);

	//add 20170927 sybyeon
	if (g_bClick && g_bAFPExposure) {

		g_Camera.nStartPixelX = g_nClickedStartPointX;
		g_Camera.nStartPixelY = g_nClickedStartPointY;
		g_Camera.nImageWidth = g_Camera.nClickAreaWidth;
		g_Camera.nImageHeight = g_Camera.nClickAreaHeight;
	}
	else {
	
		pLibControl->GetCameraImageSize(g_Camera.nControlMode, &g_Camera.nImageWidth, &g_Camera.nImageHeight);
		g_Camera.nStartPixelX = 0;
		g_Camera.nStartPixelY = 0;
	}

	pLibControl->SetCameraImageArea(g_Camera.nControlMode, g_Camera.nStartPixelX, g_Camera.nStartPixelY, g_Camera.nImageWidth, g_Camera.nImageHeight);
	pLibControl->SetCameraExposureTime(g_Camera.nControlMode, g_Camera.fExposureTime); // add 20170901 by Tae-Geun
}

void CDataAcquisitionDlg::SetImageArrayMemory() // add 20170831 by Tae-Geun
{
	//pLibControl->GetCameraImageSize(g_Camera.nControlMode, &g_Camera.nImageWidth, &g_Camera.nImageHeight);//del 20170927 sybyeon

	if (g_Camera.nFullImageArray != NULL) {

		delete[] g_Camera.nFullImageArray;
		g_Camera.nFullImageArray = NULL;
	}

	g_Camera.nFullImageArray = new unsigned short[g_Camera.nImageWidth * g_Camera.nImageHeight * sizeof(unsigned short)];
}

void CDataAcquisitionDlg::StartCameraExposure()
{
	int timeref, status = 0;
	ffgstm(g_cUTC, &timeref, &status);

	//change 20170819 sybyeon
	if (g_Camera.bScriptMode) {
		m_sObjectName = g_FitsHeader.sTargetName;
		UpdateData(FALSE);
	}

	if (g_TCP.bOpen) {

		CWnd* pWnd = FindWindow(NULL, L"KAOS30 Telescope Control Package");
		if (pWnd != NULL)
			pWnd->SendMessage(WM_TCP, (WPARAM)UPDATE_INFOMATION, (LPARAM)true);
	}
	pLibControl->StartExposure(g_Camera.nControlMode); // change 20170901 by Tae-Geun
}


afx_msg LRESULT CDataAcquisitionDlg::OnRepeatExposure(WPARAM wParam, LPARAM lParam)
{
	if (g_Camera.bScriptMode) {

		return 0;
	}
	else {

		CString sRepeatStatus;
		g_Camera.nRepeatNumberCount++;

		if (g_Camera.nRepeatNumberCount < g_Camera.nRepeatNumber) {
			sRepeatStatus.Format(_T("%d/%d"), g_Camera.nRepeatNumberCount + 1, g_Camera.nRepeatNumber);
			m_sRepeatStatus = sRepeatStatus;
			UpdateData(FALSE);
			SetCameraExposure();
			StartCameraExposure();
		}
	}
	return 0;
}

long CDataAcquisitionDlg::OnGetImageData(WPARAM wParam, LPARAM lParam)
{
	if (!lParam) { // add 20170912 by Tae-Geun

		m_btnStartCameraExposure.EnableWindow(TRUE);
		m_btnAbortCameraExposure.EnableWindow(FALSE);
		return 0;
	}

	g_bNewImage = true;

	SetImageArrayMemory(); // add 20170912 by Tae-Geun
	pLibControl->GetImageArray(g_Camera.nControlMode); // add 20170912 by Tae-Geun
	for (int i = 0; i < g_Camera.nImageWidth * g_Camera.nImageHeight; i++) { // add 20170912 by Tae-Geun

		g_Camera.nFullImageArray[i] = pLibControl->g_nCameraImageArray[i];
	}

	CalculateImageScale();
	CalculateImageIntensity();

	g_dZoomFactor = 1;
	g_rectZoom.SetRect(0, 0, g_Camera.nImageWidth, g_Camera.nImageHeight);

	DisplayScienceImage();

	if (g_dIntensityOnRadius != NULL) { // change 20170923 by Tae-Geun : Return Memory

		for (int i = 0; i < 2; i++)
			delete[] g_dIntensityOnRadius[i];

		delete[] g_dIntensityOnRadius;
		g_dIntensityOnRadius = NULL;
	}

	if (g_dFitIntensityOnRadius != NULL) { // change 20170923 by Tae-Geun

		for (int i = 0; i < 2; i++)
			delete[] g_dFitIntensityOnRadius[i];

		delete[] g_dFitIntensityOnRadius;
		g_dFitIntensityOnRadius = NULL;
	}

	ColorContourClickArea();//add 20170913 sybyeon
	CalculateImageSeeing();  //add 20170913 sybyeon
	CalculatePlotOnRadius();//add 20170913 sybyeon
	
	if (g_bAFPExposure) //add sybyeon
		SendSeeingValue();

	DisplayClickedImage();
	DisplayStarSeeing();//add 20170830 sybyeon
	DisplayStarSeeingOnX();//add 20170906 sybyeon
	DisplaySeeingDifference();// add 20170906 sybyeon

	g_bNewImage = false;//add 20170906 sybyeon

	m_nPixelPositionX = 0;
	m_nPixelPositionY = 0;
	m_nPIxelValue = 0;

	UpdateData(FALSE);

	g_Camera.bImage = true;
	g_bAFPExposure = false;

	g_nDisplayImageWidth = g_Camera.nImageWidth;//add 20171225 sybyeon
	g_nDisplayImageHeight = g_Camera.nImageHeight;//add 20171225 sybyeon


	if (m_chkAutoSave.GetCheck())
		SaveFitsFile();

	if (g_Camera.bScriptMode) { // change 20170920 by Tae-Geun

		CWnd* pWnd = FindWindow(NULL, MAIN_PROGRAM);
		if (pWnd != NULL)
			pWnd->SendMessage(WM_SMP, (WPARAM)1111, (LPARAM)true);
	}
	else {

		m_btnStartCameraExposure.EnableWindow(TRUE);
		m_btnAbortCameraExposure.EnableWindow(FALSE);
	}

	::PostMessage(g_Camera.hDAPdlg, REPEAT_EXPOSURE, 0, 0);

	return 0;
}

void CDataAcquisitionDlg::CalculateImageIntensity()
{
	int nMaxIntensity = 0;
	int nMinIntensity = 65535;
	g_dAverageIntensity = 0.0;// change 20170830 sybyeon: declared in Dlg header to use it for color contour on the subframe
	double dSum = 0.0;
	int nSize = g_Camera.nImageWidth * g_Camera.nImageHeight;

	for (int i = 0; i < nSize; i++) {

		if (nMinIntensity >= g_Camera.nFullImageArray[i])
			nMinIntensity = g_Camera.nFullImageArray[i];

		if (nMaxIntensity <= g_Camera.nFullImageArray[i])
			nMaxIntensity = g_Camera.nFullImageArray[i];

		dSum = dSum + (double)g_Camera.nFullImageArray[i];
	}

	g_dAverageIntensity = dSum / (double)nSize;
	g_Camera.dImageBackground = g_dAverageIntensity;

	m_nMaxIntensity = nMaxIntensity;
	m_nMinIntensity = nMinIntensity;

	CString sAverageIntensity;
	sAverageIntensity.Format(_T("%.2f"), g_dAverageIntensity);
	m_sAvgIntensity = sAverageIntensity;

	UpdateData(FALSE);
}

void CDataAcquisitionDlg::CalculateImageScale()
{
	if (g_Camera.PixelData != NULL) {

		delete[] g_Camera.PixelData;
		g_Camera.PixelData = NULL;
	}

	int nSamples = g_Camera.nImageWidth;
	int nSampleLine = g_Camera.nImageWidth * (g_Camera.nImageHeight / 2);
	g_Camera.nImageSize = g_Camera.nImageWidth * g_Camera.nImageHeight;
	int *nPixelArray = new int[g_Camera.nImageWidth];

	for (int i = 0; i < nSamples; i++)
		nPixelArray[i] = g_Camera.nFullImageArray[i + nSampleLine];

	int nMin = 65535;
	int nMax = 0;
	for (int i = 0; i < nSamples; i++) {

		if (nMin >= nPixelArray[i])
			nMin = nPixelArray[i];

		if (nMax <= nPixelArray[i])
			nMax = nPixelArray[i];
	}

	int nTemp = 0;
	double dMedian = 0.0;
	for (int col = 0; col < nSamples - 1; col++) {

		for (int row = 0; row < nSamples - col - 1; row++) {

			if (nPixelArray[row + 1] < nPixelArray[row]) {

				nTemp = nPixelArray[row];
				nPixelArray[row] = nPixelArray[row + 1];
				nPixelArray[row + 1] = nTemp;
			}
		}
	}

	dMedian = (double)(nPixelArray[nSamples / 2] + nPixelArray[nSamples / 2 + 1]) / 2.0;

	double dZ1 = dMedian - (double)nMin;
	double dZ2 = (double)nMax - dMedian;

	if (dZ1 < 0)
		nMin = (int)(dMedian - dZ2);

	if (dZ2 > 2000)
		nMax = (int)(dMedian + dZ1);

	g_Camera.nScaleMin = nMin;
	g_Camera.nScaleMax = nMax;

	g_Camera.nFullImageScale = new unsigned short[g_Camera.nImageSize];
	for (int i = 0; i < g_Camera.nImageSize; i++) {

		if ((int)g_Camera.nFullImageArray[i] < g_Camera.nScaleMin) {

			g_Camera.nFullImageScale[i] = 0;
		}
		else if ((int)g_Camera.nFullImageArray[i] > g_Camera.nScaleMax) {

			g_Camera.nFullImageScale[i] = 255;
		}
		else
			g_Camera.nFullImageScale[i] = (int)(255.0*((double)(g_Camera.nFullImageArray[i] - g_Camera.nScaleMin) / (double)(g_Camera.nScaleMax - g_Camera.nScaleMin)));
	}

	g_Camera.PixelData = new BYTE[g_Camera.nImageSize * 4];

	int k = 0;
	for (int y = 0; y < g_Camera.nImageHeight; y++) {
		for (int x = 0; x < g_Camera.nImageWidth; x++) {

			g_Camera.PixelData[y * g_Camera.nImageWidth * 4 + x * 4 + 0] = (BYTE)g_Camera.nFullImageScale[k];
			g_Camera.PixelData[y * g_Camera.nImageWidth * 4 + x * 4 + 1] = (BYTE)g_Camera.nFullImageScale[k];
			g_Camera.PixelData[y * g_Camera.nImageWidth * 4 + x * 4 + 2] = (BYTE)g_Camera.nFullImageScale[k];
			g_Camera.PixelData[y * g_Camera.nImageWidth * 4 + x * 4 + 3] = 0;
			k++;
		}
	}

	delete[] g_Camera.nFullImageScale;
	g_Camera.nFullImageScale = NULL;

	delete[] nPixelArray;
	nPixelArray = NULL;

	return;
}

void CDataAcquisitionDlg::CalculateImageSeeing() //add 20170819 by Tae-Geun
{
	//===== remove hotpixel
	try {

		FitLSF fwhm;
		fwhm.CalculateFWHM(g_dClickAreaIntensity);
	}
	catch (...) {

		g_Camera.dSeeing = 0.0;
		return;
	}

	g_Camera.dSeeing = g_Camera.dImageFwhm * 2.0858; //Pixel Scale = 206265 * pixelsize (0.009mm) / Focal Length (890mm) //change 20171226 sybyeon :2.06->2.0858
	m_sSeeing.Format(_T("%.3f"), g_Camera.dSeeing);//change 20171226 sybyeon
	TRACE("Seeing = %.3f\n", g_Camera.dSeeing);
	UpdateData(FALSE);

}


void CDataAcquisitionDlg::DisplayScienceImage()
{
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DISPLAY_FULL_IMAGE);
	CDC *pDCc = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);

	HBITMAP hBmp = ::CreateBitmap(g_Camera.nImageWidth, g_Camera.nImageHeight, 1, 32, g_Camera.PixelData);

	CDC memDC;
	memDC.CreateCompatibleDC(m_picDisplayFullImage.GetDC());
	memDC.SelectObject(hBmp);

	pDCc->SetStretchBltMode(COLORONCOLOR);
	pDCc->StretchBlt(0, 0, rect.right, rect.bottom, &memDC
		, g_rectZoom.left, g_rectZoom.top, g_rectZoom.right - g_rectZoom.left, g_rectZoom.bottom - g_rectZoom.top, SRCCOPY);

	CPen pen;
	pen.CreatePen(PS_SOLID, 0, RGB(150, 250, 250));

	pDCc->SelectObject(pen);

	pDCc->MoveTo(rect.right / 2, 0);
	pDCc->LineTo(rect.right / 2, rect.bottom / 2 - 10);
	pDCc->MoveTo(rect.right, rect.bottom / 2);
	pDCc->LineTo(rect.right / 2 + 10, rect.bottom / 2);
	pDCc->MoveTo(rect.right / 2, rect.bottom);
	pDCc->LineTo(rect.right / 2, rect.bottom / 2 + 10);
	pDCc->MoveTo(0, rect.bottom / 2);
	pDCc->LineTo(rect.right / 2 - 10, rect.bottom / 2);

	//change 20170928 sybyeon
	int nHalfClickImageSize = (int)((double)g_Camera.nClickAreaWidth / 2.0);
	int nHalfBoxSize = nHalfClickImageSize;
	CPoint pointLT, pointRB;
	if (g_bClick) {

		pointLT.x = (int)((double)(g_nClickedStartPointX - (nHalfBoxSize - nHalfClickImageSize) - g_rectZoom.left) / (double)(g_rectZoom.right - g_rectZoom.left)*(double)(rect.right - rect.left));
		pointLT.y = (int)((double)(g_nClickedStartPointY - (nHalfBoxSize - nHalfClickImageSize) - g_rectZoom.top) / (double)(g_rectZoom.bottom - g_rectZoom.top)*(double)(rect.bottom - rect.top));
		pointRB.x = (int)((double)(g_nClickedStartPointX + (nHalfBoxSize + nHalfClickImageSize) - g_rectZoom.left) / (double)(g_rectZoom.right - g_rectZoom.left)*(double)(rect.right - rect.left));
		pointRB.y = (int)((double)(g_nClickedStartPointY + (nHalfBoxSize + nHalfClickImageSize) - g_rectZoom.top) / (double)(g_rectZoom.bottom - g_rectZoom.top)*(double)(rect.bottom - rect.top));

		if (rect.PtInRect(pointLT) && rect.PtInRect(pointRB)) {

			pDCc->MoveTo(pointLT.x, pointLT.y);
			pDCc->LineTo(pointRB.x, pointLT.y);
			pDCc->LineTo(pointRB.x, pointRB.y);
			pDCc->LineTo(pointLT.x, pointRB.y);
			pDCc->LineTo(pointLT.x, pointLT.y);
		}
	}


	memDC.DeleteDC();
	DeleteObject(hBmp);
	pWnd->ReleaseDC(pDCc);

}

void CDataAcquisitionDlg::DisplayClickedImage() // change 20170831 by Tae-Geun
{
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DISPLAY_CLICK_IMAGE);
	CDC *pDCc = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(m_picDisplayClickImage.GetDC());

	if (!g_Camera.bImage) { // change 20170913 sybyeon

		delete[] g_ClickedPixelData;
		g_ClickedPixelData = NULL;

		g_ClickedPixelData = new BYTE[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight * 4];
		for (int i = 0; i < g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight * 4; i++)
			g_ClickedPixelData[i] = 255;
	}

	HBITMAP hBmp = ::CreateBitmap(g_Camera.nClickAreaWidth, g_Camera.nClickAreaHeight, 1, 32, g_ClickedPixelData);

	memDC.SelectObject(hBmp);
	pDCc->SetStretchBltMode(COLORONCOLOR);
	pDCc->StretchBlt(1, 1, rect.right-2, rect.bottom-2, &memDC, 0, 0, g_Camera.nClickAreaWidth, g_Camera.nClickAreaHeight, SRCCOPY);//change 20170829 sybyeon

	if (!g_Camera.bImage || !g_bClick)//change 20170913 sybyeon 
		return;

	//add 20170913 sybyeon
	CString sClickPosition;
	sClickPosition.Format(_T("x = %d, y = %d"), g_nClickedStartPointX + 15, g_nClickedStartPointY + 15);
	CFont font3;
	font3.CreateFont(15, 7, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	pDCc->SelectObject(font3);
	pDCc->SetBkColor(RGB(255, 255, 255));
	pDCc->TextOutW(rect.right / 2, rect.bottom - 17, sClickPosition);


	//add 20170905 sybyeon :cross line
	CPen pen;
	pen.CreatePen(PS_SOLID, 0, RGB(150, 250, 250));

	pDCc->SelectObject(pen);

	pDCc->MoveTo((int)((double)rect.right / 2.0), 1);//change 20170913 sybyeon
	pDCc->LineTo((int)((double)rect.right / 2.0), rect.bottom - 1);
	pDCc->MoveTo(1, (int)((double)rect.bottom / 2.0));
	pDCc->LineTo(rect.right - 1, (int)((double)rect.bottom / 2.0));
	
	memDC.DeleteDC();
	DeleteObject(hBmp);
	pWnd->ReleaseDC(pDCc);
}

//add 20170829 sybyeon
void CDataAcquisitionDlg::DisplayStarSeeing()
{
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DISPLAY_STAR_SEEING);
	CDC *pDc = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(m_picDisplayStarSeeing.GetDC());

	//======background
	BYTE *nBackground = new BYTE[4];
	for (int i = 0; i<4; i++)
		nBackground[i] = (BYTE)255;

	HBITMAP hBmp = ::CreateBitmap(1, 1, 1, 32, nBackground);

	memDC.SelectObject(hBmp);
	pDc->SetStretchBltMode(COLORONCOLOR);
	pDc->StretchBlt(1, 1, rect.right - 2, rect.bottom - 2, &memDC, 0, 0, 1, 1, SRCCOPY);

	delete[] nBackground;
	nBackground = NULL;

	CPen pen1, pen2, pen3;
	pen1.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	pDc->SelectObject(pen1);

	//===== axis
	pDc->MoveTo(15, rect.bottom - 15);
	pDc->LineTo(rect.right - 15, rect.bottom - 15);
	pDc->LineTo(rect.right - 15 - 10, rect.bottom - 15 - 6);
	pDc->MoveTo(rect.right - 15, rect.bottom - 15);
	pDc->LineTo(rect.right - 15 - 10, rect.bottom - 15 + 6);
	pDc->MoveTo(15, rect.bottom - 15);
	pDc->LineTo(15, 15);
	pDc->LineTo(15 - 6, 15 + 10);
	pDc->MoveTo(15, 15);
	pDc->LineTo(15 + 6, 15 + 10);

	//add 20170908 sybyeon
	CFont font1, font2;
	font1.CreateFont(15, 7, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	font2.CreateFont(15, 7, 900, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	pDc->SelectObject(font1);
	pDc->SetBkMode(TRANSPARENT);
	pDc->TextOutW(rect.right - 60, rect.bottom - 15, _T("Radius"));
	pDc->SelectObject(font2);
	pDc->TextOutW(0, 80, _T("Intensity"));



	if (g_dIntensityOnRadius==NULL || !g_bClick)// change 20170913 sybyeon
		return;

	CRect rectPlot;//add 20170907 sybyeon
	rectPlot.left = rect.left + 15;
	rectPlot.top = rect.top + 15;
	rectPlot.right = rect.right - 15;
	rectPlot.bottom = rect.bottom - 15;

	double dMaxRadius;// change 20170905 sybyeon
	int nR, nI, nThickness;

	//======plot //change 20170905 sybyeon
	pen2.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pDc->SelectObject(pen2);
	CPoint point;

	dMaxRadius = 10.0;
	nR = 0, nI = 0;
	nThickness = 1;

	for (int i = 0; i < g_Camera.nClickAreaWidth* g_Camera.nClickAreaHeight; i++) {

		nR = (int)((g_dIntensityOnRadius[0][i] / dMaxRadius) * ((double)rect.right - 45.0) + 15.0);
		nI = (int)((1.0 - (g_dIntensityOnRadius[1][i] - g_dClickAreaMinIntensity) / (g_dClickAreaMaxIntensity - g_dClickAreaMinIntensity))*((double)rect.bottom - 45.0) + 30.0);

		point.x = nR;//change 20170907 sybyeon
		point.y = nI;

		if (rectPlot.PtInRect(point)) 
			pDc->Rectangle(nR - nThickness, nI - nThickness, nR + nThickness, nI + nThickness);//change 20170913 sybyeon
	}



	//=======fitting plot // add 20170830 sybyeon //change 20170905 sybyeon
	pen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDc->SelectObject(pen3);

	dMaxRadius = 10.0;
	nR = 0, nI = 0;
	nThickness = 1;
	for (int i = 0; i < g_Camera.nClickAreaWidth* g_Camera.nClickAreaHeight*25; i++) {

		nR = (int)((g_dFitIntensityOnRadius[0][i] / dMaxRadius) * ((double)rect.right - 45.0) + 15.0);
		nI = (int)((1.0 - (g_dFitIntensityOnRadius[1][i] - g_dClickAreaMinIntensity) / (g_dClickAreaMaxIntensity - g_dClickAreaMinIntensity))*((double)rect.bottom - 45.0) + 30.0);

		point.x = nR;//change 20170907 sybyeon
		point.y = nI;
		if (rectPlot.PtInRect(point))
			pDc->Ellipse(nR - nThickness, nI - nThickness, nR + nThickness, nI + nThickness);//change 20170913 sybyeon
	}

	//add 20170911 sybyeon
	CString sClickAreaMaxIntensity;
	sClickAreaMaxIntensity.Format(_T("%.0f"), g_dClickAreaMaxIntensity);
	pDc->SelectObject(font1);
	pDc->SetBkMode(TRANSPARENT);
	pDc->TextOutW(30, 30, sClickAreaMaxIntensity);

	memDC.DeleteDC();
	DeleteObject(hBmp);
	pWnd->ReleaseDC(pDc);

}

void CDataAcquisitionDlg::OnBnClickedButtonLoadFilter()
{
	// TODO: Add your control notification handler code here
	LoadFilterList();
}


void CDataAcquisitionDlg::LoadFilterList() // change 20170832 by Tae-Geun : Return Memory
{

	// TODO: Add your control notification handler code here
	if (g_Filter.sFilterList != NULL) {

		delete[] g_Filter.sFilterList;
		g_Filter.sFilterList = NULL;
	}

	CStdioFile file;
	CFileException exception;

	CString strPath;	strPath.Empty();
	strPath.Format(_T("%s\\CFG\\FilterList.txt"), WORK_DIR);
	 
	g_Filter.sFilterList = new CString[100];
	CString sReadLine;
	int nFilterCount = 0;

	if (file.Open(strPath, CFile::modeRead, &exception)) {

		while (file.ReadString(sReadLine)) {

			g_Filter.sFilterList[nFilterCount] = sReadLine; // change 20171223 by sybyeon
			nFilterCount++;
		}
		file.Close();
	}
	for (int i = m_cmbFilter.GetCount() - 1; i >= 0; i--)
	{
		m_cmbFilter.DeleteString(i);
	}
	for (int i = 0; i < nFilterCount; i++) {
		m_cmbFilter.InsertString(-1, g_Filter.sFilterList[i]);
	}

}

void CDataAcquisitionDlg::OnBnClickedButtonSaveFitsFile()
{
	// TODO: Add your control notification handler code here
	if (g_Camera.bImage)//add 20170819 sybyeon
		SaveFitsFile();
}


void CDataAcquisitionDlg::OnBnClickedButtonSetSavePath()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);//add 20170819 sybyeon
	ITEMIDLIST *pidlBrowse;
	TCHAR       pszPathname[MAX_PATH];
	BROWSEINFO  BrInfo;

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select Directory");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	pidlBrowse = ::SHBrowseForFolder(&BrInfo);
	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, pszPathname);
	}
	g_Camera.sSaveDirectory = (LPCTSTR)pszPathname;

	//change 20170819 sybyeon
	CString sFolderName;
	CTime CurTime;
	CurTime = CTime::GetCurrentTime();
	CTime NoonTime(CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), 12, 0, 0);
	CTimeSpan TimeGap = CurTime - NoonTime;
	if (TimeGap.GetTotalMinutes() < 0) {
		CurTime -= CTimeSpan(1, 0, 0, 0);
		sFolderName.Format(_T("%04d%02d%02d"),
			CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());
	}
	else
		sFolderName.Format(_T("%04d%02d%02d"),
			CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());

	CString sCreateFolderPath;
	sCreateFolderPath.Format(_T("%s\\%s"), g_Camera.sSaveDirectory, sFolderName);
	if (CreateDirectory(sCreateFolderPath, NULL) == ERROR_PATH_NOT_FOUND)
		AfxMessageBox(_T("Make sure that Folder 'KAOS30' exists."));
	m_sDirectory = sFolderName;
	UpdateData(FALSE);
}

void CDataAcquisitionDlg::OnSelchangeComboCameraFrameType()
{
	// TODO: Add your control notification handler code here

	int nFrameIndex;
	if (g_Camera.bScriptMode) {

		nFrameIndex = g_nFrameTypeFromScript;
	}
	else {

		nFrameIndex = m_cmbFrameType.GetCurSel();
	}
	switch (nFrameIndex) {
	case 0: {
		g_Camera.nFrameType = CAMERA_FRAME_TYPE_BIAS;
		g_Camera.fExposureTime = 0;
		break;
	}
	case 1: {
		g_Camera.nFrameType = CAMERA_FRAME_TYPE_DARK;
		break;
	}
	case 2: {
		g_Camera.nFrameType = CAMERA_FRAME_TYPE_FLAT;
		break;
	}
	case 3: {
		g_Camera.nFrameType = CAMERA_FRAME_TYPE_LIGHT;
		break;
	}
	}

	m_fExposureTime = g_Camera.fExposureTime;
	UpdateData(FALSE);

	if (g_Camera.nFrameType == CAMERA_FRAME_TYPE_BIAS)
		m_editExposureTime.EnableWindow(FALSE);
	else
		m_editExposureTime.EnableWindow(TRUE);

	g_Camera.bFrameType = pLibControl->SetCameraFrameType(g_Camera.nControlMode, g_Camera.nFrameType); // change 20170831 by Tae-Geun
	m_cmbFrameType.SetCurSel(nFrameIndex);
	UpdateData(TRUE);
}

void CDataAcquisitionDlg::OnSelchangeComboFilter() // 20170920 by Tae-Geun
{
	// TODO: Add your control notification handler code here

	if (g_Camera.bScriptMode || g_Camera.bScriptAutofocusMode) {

		DWORD dwThreadID;

		g_Filter.m_ghThreadChangeFilter = NULL;
		if (g_Filter.m_ghThreadChangeFilter != NULL)
			CloseHandle(g_Filter.m_ghThreadChangeFilter);

		g_Filter.m_ghThreadChangeFilter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFilterProcess, this, 0, &dwThreadID);

		CWnd* pWnd = FindWindow(NULL, L"Auto Focus Package"); // add 20171224 by Tae-Geun
		if (pWnd != NULL)
			pWnd->SendMessage(WM_AFP, (WPARAM)FILTER_POSITION, g_Filter.lSetFilterIndex);
	}
	else {

		g_Filter.lSetFilterIndex = m_cmbFilter.GetCurSel();

		m_btnStartCameraExposure.EnableWindow(FALSE);
		g_Filter.bSetFilter = pLibControl->SetFilterIndex(g_Filter.nControlMode, g_Filter.lSetFilterIndex); // change 20170911 by Tae-Geun
		m_btnStartCameraExposure.EnableWindow(TRUE);

		pLibControl->GetFilterIndex(g_Filter.nControlMode, &g_Filter.lGetFilterIndex); // change 20170911 by Tae-Geun
		m_cmbFilter.SetCurSel(g_Filter.lGetFilterIndex);
		UpdateData(TRUE);

		//add 20171204 sybyeon
		CWnd* pWnd = FindWindow(NULL, L"Auto Focus Package");
		if (pWnd != NULL)
			pWnd->SendMessage(WM_AFP, (WPARAM)FILTER_POSITION, g_Filter.lGetFilterIndex);
	}
}

DWORD ThreadFilterProcess(CDataAcquisitionDlg* pValue)
{
	g_Filter.bSetFilter = pLibControl->SetFilterIndex(g_Filter.nControlMode, g_Filter.lSetFilterIndex); // change 20170911 by Tae-Geun
	g_Filter.bSetScriptFilter = true;

	g_Filter.m_ghThreadChangeFilter = NULL;

	return TRUE;
}

void CDataAcquisitionDlg::OnSelchangeComboReadoutMode()
{
	// TODO: Add your control notification handler code here
	int nReadoutModeIndex = m_cmbReadoutMode.GetCurSel();
	pLibControl->SetCameraReadoutMode(g_Camera.nControlMode, nReadoutModeIndex); // change 20170831 by Tae-Geun
	m_cmbReadoutMode.SetCurSel(nReadoutModeIndex);

	UpdateData(TRUE);
}

// =========================================================================== Set / Kill Focus
void CDataAcquisitionDlg::OnSetfocusEditSetCameraTemperature()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusEditSetCameraTemperature()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}

void CDataAcquisitionDlg::OnSetfocusEditRepeatNumber()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusEditRepeatNumber()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}


void CDataAcquisitionDlg::OnSetfocusEditObjectName()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusEditObjectName()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}

void CDataAcquisitionDlg::OnSetfocusComboFilter()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}

void CDataAcquisitionDlg::OnKillfocusComboFilter()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}


void CDataAcquisitionDlg::OnSetfocusComboCameraFrameType()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusComboCameraFrameType()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}


void CDataAcquisitionDlg::OnSetfocusEditObserver()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusEditObserver()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}


void CDataAcquisitionDlg::OnSetfocusComboReadoutMode()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusComboReadoutMode()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}

void CDataAcquisitionDlg::OnSetfocusEditExposureTime()
{
	// TODO: Add your control notification handler code here
	KillAllTimer();
}


void CDataAcquisitionDlg::OnKillfocusEditExposureTime()
{
	// TODO: Add your control notification handler code here
	SetAllTimer();
}


afx_msg LRESULT CDataAcquisitionDlg::OnProgressBar(WPARAM wParam, LPARAM lParam)
{
	m_prgDownloadImage.SetPos(wParam);
	return 0;
}


void CDataAcquisitionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	m_picDisplayFullImage.GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (!rect.PtInRect(point) || !g_Camera.bImage)
		return;
	if (g_Camera.nClickAreaWidth == g_Camera.nImageWidth)//add 20170928 sybyeon
		return;

	g_bClick = true; //add 20170913 sybyeon

	if (!g_bNewImage) { // add 20170831 by Tae-Geun

		delete[] g_ClickedPixelData;
		delete[] g_dClickAreaIntensity;

		g_ClickedPixelData = NULL;
		g_dClickAreaIntensity = NULL;
	}

	g_ClickedPixelData = new BYTE[g_Camera.nClickAreaWidth * g_Camera.nClickAreaHeight * 4];
	g_dClickAreaIntensity = new double[g_Camera.nClickAreaWidth * g_Camera.nClickAreaHeight]; //change 20170828 sybyeon : 48*48 ->nClickedImageWidth* nClickedImageHeight

	double dClickedPointX, dClickedPointY;
	dClickedPointX = (double)g_Camera.nImageWidth*((double)point.x - (double)rect.left) / ((double)rect.right - (double)rect.left);
	dClickedPointY = (double)g_Camera.nImageHeight*((double)point.y - (double)rect.top) / ((double)rect.bottom - (double)rect.top);

	double dZoomClickPointX, dZoomClickPointY;
	dZoomClickPointX = (double)g_rectZoom.left + dClickedPointX / g_dZoomFactor;
	dZoomClickPointY = (double)g_rectZoom.top + dClickedPointY / g_dZoomFactor;

	double dClickedStartPointX, dClickedStartPointY;
	dClickedStartPointX = dZoomClickPointX - (double)g_Camera.nClickAreaWidth / 2.0;
	dClickedStartPointY = dZoomClickPointY - (double)g_Camera.nClickAreaHeight / 2.0;

	if (dClickedStartPointX < 0)
		dClickedStartPointX = 0;
	if (dClickedStartPointY < 0)
		dClickedStartPointY = 0;

	if (dClickedStartPointX + (double)g_Camera.nClickAreaWidth >(double)g_Camera.nImageWidth)
		dClickedStartPointX = (double)g_Camera.nImageWidth - g_Camera.nClickAreaWidth;
	if (dClickedStartPointY + (double)g_Camera.nClickAreaHeight >(double)g_Camera.nImageHeight)
		dClickedStartPointY = (double)g_Camera.nImageHeight - (double)g_Camera.nClickAreaHeight;

	g_nClickedStartPointX = (int)dClickedStartPointX; //change 20170830 sybyeon : declare in DAP header
	g_nClickedStartPointY = (int)dClickedStartPointY;

	// add 20170830 sybyeon: make the pixel with maximum value center on the subframe
	g_dClickAreaMaxIntensity = 0.0;
	g_dClickAreaMinIntensity = 65535.0;//add 20170905 sybyeon
	double dClickIntensity;
	int nMaxIndexX, nMaxIndexY;
	int nOffSetX, nOffSetY;
	for (int y = 0; y < g_Camera.nClickAreaHeight; y++) {
		for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {
			dClickIntensity = g_Camera.nFullImageArray[(y + g_nClickedStartPointY)*g_Camera.nImageWidth + (x + g_nClickedStartPointX)];
			if (g_dClickAreaMaxIntensity < dClickIntensity) {
				g_dClickAreaMaxIntensity = dClickIntensity;
				nMaxIndexX = x;
				nMaxIndexY = y;
			}
			if (g_dClickAreaMinIntensity > dClickIntensity)//add 20170905 sybyeon
				g_dClickAreaMinIntensity = dClickIntensity;

		}
	}

	nOffSetX = (int)(((double)g_Camera.nClickAreaWidth) / 2.0 - (double)nMaxIndexX);//change 20171224 sybyeon
	nOffSetY = (int)(((double)g_Camera.nClickAreaHeight) / 2.0 - (double)nMaxIndexY);

	g_nClickedStartPointX = g_nClickedStartPointX - nOffSetX;
	g_nClickedStartPointY = g_nClickedStartPointY - nOffSetY;

	ColorContourClickArea();//add 20170830 sybyeon 
	CalculateImageSeeing();  //add 20170819 by Tae-Geun
	CalculatePlotOnRadius();//add 20170830 sybyeon 

	DisplayScienceImage();//add 20170918 sybyeon
	DisplayClickedImage();
	DisplayStarSeeing();// add 20170829 sybyeon
	DisplayStarSeeingOnX();// add 20170901 sybyeon
	DisplaySeeingDifference(); //add 20170906 sybyeon

	CDialogEx::OnLButtonDown(nFlags, point);
}

BOOL CDataAcquisitionDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	m_picDisplayFullImage.GetWindowRect(&rect);

	double dZoomPointX, dZoomPointY;
	dZoomPointX = (double)g_Camera.nImageWidth*(double)(pt.x - rect.left) / (double)(rect.right - rect.left);
	dZoomPointY = (double)g_Camera.nImageHeight*(double)(pt.y - rect.top) / (double)(rect.bottom - rect.top);

	double dZoomZoomPointX, dZoomZoomPointY;
	dZoomZoomPointX = (double)g_rectZoom.left + dZoomPointX / g_dZoomFactor;
	dZoomZoomPointY = (double)g_rectZoom.top + dZoomPointY / g_dZoomFactor;

	if (!rect.PtInRect(pt))
		return 0;
	if (!g_Camera.bImage)
		return 0;

	if (zDelta > 0) {

		if (g_dZoomFactor > 64)
			return 0;
		g_dZoomFactor = g_dZoomFactor *1.3;
	}
	else {

		g_dZoomFactor = g_dZoomFactor / 1.3;
		if (g_dZoomFactor < 1)
			g_dZoomFactor = 1;
	}

	g_rectZoom.left = (long)(dZoomZoomPointX - dZoomPointX / g_dZoomFactor);
	g_rectZoom.top = (long)(dZoomZoomPointY - dZoomPointY / g_dZoomFactor);
	g_rectZoom.right = (long)(dZoomZoomPointX - dZoomPointX / g_dZoomFactor + (double)g_Camera.nImageWidth / g_dZoomFactor);
	g_rectZoom.bottom = (long)(dZoomZoomPointY - dZoomPointY / g_dZoomFactor + (double)g_Camera.nImageHeight / g_dZoomFactor);

	if (g_rectZoom.top < 0) {

		g_rectZoom.top = 0;
		g_rectZoom.bottom = (long)((double)g_Camera.nImageHeight / g_dZoomFactor);
	}
	if (g_rectZoom.bottom > g_Camera.nImageHeight) {

		g_rectZoom.top = (long)((double)g_Camera.nImageHeight - (double)g_Camera.nImageHeight / g_dZoomFactor);
		g_rectZoom.bottom = (long)g_Camera.nImageHeight;
	}
	if (g_rectZoom.left < 0) {

		g_rectZoom.left = 0;
		g_rectZoom.right = (long)(g_Camera.nImageWidth / g_dZoomFactor);
	}
	if (g_rectZoom.right > g_Camera.nImageWidth) {

		g_rectZoom.left = (long)((double)g_Camera.nImageWidth - (double)g_Camera.nImageWidth / g_dZoomFactor);
		g_rectZoom.right = (long)g_Camera.nImageWidth;
	}

	DisplayScienceImage();

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


//add 20170819 sybyeon 
void CDataAcquisitionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE); // add 20170921 by Tae-Geun 

	CRect rect;
	m_picDisplayFullImage.GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (!rect.PtInRect(point))
		return;
	if (!g_Camera.bImage)
		return;


	double dClickedPointX, dClickedPointY;
	dClickedPointX = (double)g_nDisplayImageWidth*((double)point.x - (double)rect.left) / ((double)rect.right - (double)rect.left);//change 20171225 sybyeon
	dClickedPointY = (double)g_nDisplayImageHeight*((double)point.y - (double)rect.top) / ((double)rect.bottom - (double)rect.top);//change 20171225 sybyeon

	double dZoomClickPointX, dZoomClickPointY;
	dZoomClickPointX = (double)g_rectZoom.left + dClickedPointX / g_dZoomFactor;
	dZoomClickPointY = (double)g_rectZoom.top + dClickedPointY / g_dZoomFactor;

	m_nPixelPositionX = (int)dZoomClickPointX;
	m_nPixelPositionY = (int)dZoomClickPointY;

	m_nPIxelValue = g_Camera.nFullImageArray[m_nPixelPositionY * g_nDisplayImageWidth + m_nPixelPositionX];//change 20171225 sybyeon

	UpdateData(FALSE);

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDataAcquisitionDlg::SaveFitsFile()
{
	fitsfile *infptr; // pointer to the FITS file; defined in fitsio.h
	int nStatus = 0;
	long naxes[2] = { g_Camera.nImageWidth, g_Camera.nImageHeight }, fpixel[2] = { 1, 1 };
	unsigned short *pixels = NULL;
	int bitpix = 16, naxis = 2;
	pixels = (unsigned short*)malloc(naxes[0] * naxes[1] * sizeof(unsigned short));
	for (int i = 0; i < naxes[0] * naxes[1]; i++) {
		pixels[i] = g_Camera.nFullImageArray[i];
	}

	CString sFileName, sFolderName, sFilePath;
	CString sFilePathCheck;
	CStringA cFilePath;
	UpdateData(TRUE);
	sFolderName = m_sDirectory;

	for (int i = 1; i < 9999; i++) {
		nStatus = 0;

		if (g_Camera.bScriptMode)
			sFileName.Format(_T("%s_%04d.fit"), g_FitsHeader.sTargetName, i);
		else if (m_sObjectName == _T(""))
			sFileName.Format(_T("%s_%04d.fit"), m_sFrameType, i);
		else {

			g_FitsHeader.sTargetName = m_sObjectName;
			sFileName.Format(_T("%s_%04d.fit"), g_FitsHeader.sTargetName, i);
		}
		sFilePath.Format(_T("%s\\%s\\%s"), g_Camera.sSaveDirectory, sFolderName, sFileName);
		sFilePathCheck.Format(_T("%s\\%s"), g_Camera.sSaveDirectory, sFolderName);

		cFilePath = sFilePath;
		fits_create_file(&infptr, cFilePath, &nStatus);
		fits_create_img(infptr, TUSHORT, naxis, naxes, &nStatus);

		if (GetFileAttributes(sFilePathCheck) == INVALID_FILE_ATTRIBUTES) {
			AfxMessageBox(_T("Path doesn't exist. Set file path."));
			break;
		}

		if (nStatus != FILE_NOT_CREATED)
			break;
	}

	//=================================================-Fits File Header

	CString sSection, sKey, sTCPFilePath;
	CStringA cKey;
	sTCPFilePath = _T("C:\\KAOS30\\CFG\\TCP.txt");
	sSection = _T("TCS Information");
	const int nLen = 50;
	UpdateData(TRUE);

	//0.1 DATE //UTC
	cKey = "DATE-OBS";
	fits_update_key(infptr, TSTRING, cKey, g_cUTC, "YYYY-MM-DDThh:mm:ss observation start, UT ", &nStatus);
	//1. OBSTYPE = <-- - DAP
	cKey = "OBSTYPE";
	char *chrObsType = "";
	switch (g_Camera.nFrameType) {
	case 0:
		chrObsType = "BIAS";
		break;
	case 1:
		chrObsType = "DARK";
		break;
	case 2:
		chrObsType = "FLAT";
		break;
	case 3:
		chrObsType = "OBJECT";
		break;
	}
	fits_update_key(infptr, TSTRING, cKey, chrObsType, "", &nStatus);
	//1.1 IMAGETYP//add 20170817 sybyeon
	cKey = "IMAGETYP";
	switch (g_Camera.nFrameType) {
	case 0:
		chrObsType = "BIAS";
		break;
	case 1:
		chrObsType = "DARK";
		break;
	case 2:
		chrObsType = "FLAT";
		break;
	case 3:
		chrObsType = "LIGHT";
		break;
	}
	fits_update_key(infptr, TSTRING, cKey, chrObsType, "", &nStatus);
	//2. OBJECT = <-- - DAP
	cKey = "OBJECT";
	char chrObject[nLen];
	strcpy_s(chrObject, CStringA(m_sObjectName).GetString());//cstring->char array
	fits_update_key(infptr, TSTRING, cKey, chrObject, "Name of the observed target", &nStatus);
	//3. EXPTIME = <-- - DAP
	cKey = "EXPTIME";
	ffpkyf(infptr, cKey, g_Camera.fExposureTime, 2, "Exposure time in second", &nStatus);
	//3.1 EXPOSURE
	cKey = "EXPOSURE";
	ffpkyf(infptr, cKey, g_Camera.fExposureTime, 2, "Exposure time in second", &nStatus);
	//6. RA
	TCHAR cRa[nLen];	char chrRa[nLen];
	sKey = _T("RA");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cRa, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cRa, nLen, chrRa, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrRa, "Right Ascension of the target object", &nStatus);
	//7. DEC
	TCHAR cDec[nLen];	char chrDec[nLen];
	sKey = _T("DEC");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cDec, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cDec, nLen, chrDec, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrDec, "Declination of the target object", &nStatus);
	//8. EQUINOX
	TCHAR cEquinox[nLen];
	sKey = _T("EQUINOX");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cEquinox, nLen, sTCPFilePath);
	double dEquinox = _wtof(cEquinox);
	ffpkyg(infptr, cKey, dEquinox, 1, "Epoch of the target object", &nStatus);
	//9. ZENITH
	TCHAR cZenith[nLen];
	sKey = _T("ZENITH"); cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cZenith, nLen, sTCPFilePath);
	double dZenith = _wtof(cZenith);
	ffpkyg(infptr, cKey, dZenith, 1, "Zenith distance of the target", &nStatus);
	//10. AZIMUTH
	TCHAR cAzimuth[nLen];
	sKey = _T("AZIMUTH");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cAzimuth, nLen, sTCPFilePath);
	double dAzimuth = _wtof(cAzimuth);
	ffpkyg(infptr, cKey, dAzimuth, 1, "Target Airmass at observation beginning", &nStatus);
	//11. FOCUS = <-- - AFP 
	cKey = "FOCUS";
	fits_update_key(infptr, TSTRING, cKey, "", "Focus value of telescope", &nStatus);
	//12. CCD - TEMP = <-- - DAP//change 20170817 sybyeon
	cKey = "CCD-TEMP";
	double dCCDTemp = _wtof(g_Camera.sTemperature);//cstring->double
	ffpkyg(infptr, cKey, dCCDTemp, 2, "Temperature of the CCD chip (Celcius)", &nStatus);
	//12.1 XPIXSZ
	cKey = "XPIXSZ";
	ffpkyg(infptr, cKey, g_Camera.dPixelSizeX, 2, "Pixel Width in microns (after binning)", &nStatus);
	//12.2 YPIXSZ
	cKey = "YPIXSZ";
	ffpkyg(infptr, cKey, g_Camera.dPixelSizeY, 2, "Pixel Height in microns (after binning)", &nStatus);
	//12.3 XBINNING	
	cKey = "XBINNING";
	fits_update_key(infptr, TLONG, cKey, &g_Camera.lXBinning, "Binning factor in width", &nStatus);
	//12.4 YBINNING
	cKey = "YBINNING";
	fits_update_key(infptr, TLONG, cKey, &g_Camera.lYBinning, "Binning factor in Height", &nStatus);
	//13. READOUTM =<---DAP
	cKey = "READOUTM";
	char chrReadoutMode[nLen];
	strcpy_s(chrReadoutMode, CStringA(m_sReadoutMode).GetString());//cstring->char array
	fits_update_key(infptr, TSTRING, cKey, chrReadoutMode, "Readout Mode", &nStatus);
	//14. RDNOISE = 
	cKey = "RDNOISE";
	fits_update_key(infptr, TSTRING, cKey, "", "Readout noise of the CCD chip (electron)", &nStatus);
	//15. FILTER = <-- - DAP
	cKey = "FILTER";
	char chrFilter[nLen];
	strcpy_s(chrFilter, CStringA(m_sFilter).GetString());//cstring->char array
	fits_update_key(infptr, TSTRING, cKey, chrFilter, "Filter used in observation", &nStatus);
	//16. GAIN =
	cKey = "GAIN";
	fits_update_key(infptr, TSTRING, cKey, "", "System gain of the camera", &nStatus);
	//17. AIRMASS = <-- - TCP
	TCHAR cAirmass[nLen];
	sKey = _T("AIRMASS");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cAirmass, nLen, sTCPFilePath);
	double dAirmass = _wtof(cAirmass);//cstring->double
	ffpkyg(infptr, cKey, dAirmass, 2, "Target Airmass at observation beginning", &nStatus);
	//18. ST = <-- - TCP: LST
	TCHAR cLST[nLen];	char chrLST[nLen];
	sKey = _T("LST");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cLST, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cLST, nLen, chrLST, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrLST, "Local Sidereal Time at obs beginning ", &nStatus);
	//19. TEL_RA = <-- - TCP
	TCHAR cTelRa[nLen];		char chrTelRa[nLen];
	sKey = _T("TEL_RA");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cTelRa, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cTelRa, nLen, chrTelRa, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrTelRa, "RA of the telescope pointing at beginning", &nStatus);
	//20. TEL_DEC = <-- - TCP
	TCHAR cTelDec[nLen];	char chrTelDec[nLen];
	sKey = _T("TEL_DEC");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cTelDec, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cTelDec, nLen, chrTelDec, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrTelDec, "Dec of the telescope pointing at beginning", &nStatus);
	//20.1 JD
	int year, month, day, hour, minute;
	double second;
	int A, Y, M;
	double JDN, JulianDate;
	fits_str2time(g_cUTC, &year, &month, &day, &hour, &minute, &second, &nStatus);
	A = (14 - month) / 12;
	Y = year + 4800 - A;
	M = month + 12 * A - 3;
	JDN = day + int(((153 * M) + 2) / 5) + 365 * Y + int(Y / 4) - int(Y / 100) + int(Y / 400) - 32045;
	JulianDate = JDN + ((double(hour) - 12) / 24) + (double(minute) / 1440) + (double(second) / 86400);
	cKey = "JD";
	ffpkyg(infptr, cKey, JulianDate, 10, "Julian Date", &nStatus);
	//21. TELESCOP = <-- - TCP
	TCHAR cTelescope[nLen];		char chrTelescope[nLen];
	sKey = _T("TELESCOP");	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cTelescope, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cTelescope, nLen, chrTelescope, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrTelescope, "Telescope used to obtain the image", &nStatus);
	//21.1 INSTRUME	
	cKey = "INSTRUME";
	fits_update_key(infptr, TSTRING, cKey, "FLIPro0 MicroLine16803", "instrument or camera used", &nStatus);
	//22. OBSERVAT = <-- - TCP
	TCHAR cObservatory[nLen];
	char chrObservatory[nLen];
	sKey = _T("OBSERVAT");
	cKey = sKey;
	GetPrivateProfileString(sSection, sKey, _T(""), cObservatory, nLen, sTCPFilePath);
	WideCharToMultiByte(CP_ACP, 0, cObservatory, nLen, chrObservatory, nLen, NULL, NULL);	//tchar*->char*
	fits_update_key(infptr, TSTRING, cKey, chrObservatory, "Observatory", &nStatus);
	//23. OBSERVER=<---DAP
	cKey = "OBSERVER";
	char chrObserver[nLen];
	strcpy_s(chrObserver, CStringA(m_sObserver).GetString());//cstring->char array
	fits_update_key(infptr, TSTRING, cKey, chrObserver, "The observers who obtain the image", &nStatus);
	//23.1 SWCREATE
	cKey = "SWCREATE";
	fits_update_key(infptr, TSTRING, cKey, "KAOS30 v1.04", "Name of software", &nStatus); // change 20171223 by Tae-Geun

	fits_write_img(infptr, TUSHORT, fpixel[0] * fpixel[1], naxes[0] * naxes[1], pixels, &nStatus);
	fits_close_file(infptr, &nStatus);

	//add 20171204 sybyeon
	m_sSaveFileName = sFilePath;
	UpdateData(FALSE);
	m_editSaveFileName.SetSel(0, -1);
	m_editSaveFileName.ReplaceSel(m_sSaveFileName);
	m_editSaveFileName.SetFocus();

	free(pixels);
	SaveObservationLog(sFileName);
}

//change 20170810 sybyeon
void CDataAcquisitionDlg::SaveObservationLog(CString sFileName)
{
	CStdioFile file;
	CFileException exception;
	CFileFind filefind;
	CString cFilePath;
	CString sReadLine;
	CString sWriteFirstLine, sWriteLine;

	CString sLogFileName;
	CTime CurTime;
	CurTime = CTime::GetCurrentTime();
	CTime NoonTime(CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), 12, 0, 0);
	CTimeSpan TimeGap = CurTime - NoonTime;
	if (TimeGap.GetTotalMinutes() < 0) {
		CurTime -= CTimeSpan(1, 0, 0, 0);
		sLogFileName.Format(_T("%04d%02d%02d"),
			CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());
	}
	else
		sLogFileName.Format(_T("%04d%02d%02d"),
			CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay());


	cFilePath.Format(_T("%s\\%s.txt"), LOG_DIR, sLogFileName);
	sWriteFirstLine.Format(_T("%-30s%-23s%-16s%-12s%-13s%-9s%-9s%-8s%-9s\n")
		, _T("File Name"), _T("Date-UTC"), _T("Target")
		, _T("RA"), _T("Dec"), _T("ObsType"), _T("ExpTime"), _T("Filter"), _T("Airmass"));

	UpdateData(TRUE);

	CString sSection, sKey, sTCPFilePath;
	sTCPFilePath = _T("C:\\KAOS30\\CFG\\TCP.txt");
	sSection = _T("TCS Information");
	const int nLen = 50;

	CString sDateUTC = (CString)g_cUTC;

	CString sTarget = m_sObjectName;
	if (sTarget == _T(""))
		sTarget = m_sFrameType;

	CString sRA;
	TCHAR cRA[nLen];
	sKey = _T("RA");
	GetPrivateProfileString(sSection, sKey, _T(""), cRA, nLen, sTCPFilePath);
	sRA = (LPCTSTR)cRA; //tchar array->cstring

	CString sDec;
	TCHAR cDec[nLen];
	sKey = _T("DEC");
	GetPrivateProfileString(sSection, sKey, _T(""), cDec, nLen, sTCPFilePath);
	sDec = (LPCTSTR)cDec; //tchar array->cstring

	CString sObsType = m_sFrameType;
	float fExpTime = m_fExposureTime;
	CString sFilter = m_sFilter;

	CString sAirmass;
	TCHAR cAirmass[nLen];
	sKey = _T("AIRMASS");
	GetPrivateProfileString(sSection, sKey, _T(""), cAirmass, nLen, sTCPFilePath);
	sAirmass = (LPCTSTR)cAirmass; //tchar array->cstring

	if (!filefind.FindFile(cFilePath, 0)) {
		if (file.Open(cFilePath, CFile::modeCreate | CFile::modeWrite, &exception)) {
			file.WriteString(sWriteFirstLine);
			file.Close();
		}
	}
	if (file.Open(cFilePath, CFile::modeReadWrite, &exception)) {
		while (file.ReadString(sReadLine)) {
		}
		sWriteLine.Format(_T("%-30s%-23s%-16s%-12s%-13s%-9s%-9.2f%-8s%-9s\n")
			, sFileName, sDateUTC, sTarget, sRA, sDec, sObsType, fExpTime, sFilter, sAirmass);
		file.WriteString(sWriteLine);
		file.Close();
	}
}

//change 20171121 sybyeon
void CDataAcquisitionDlg::ColorContourClickArea()
{
	if (!g_Camera.bImage|| !g_bClick)//add 20170913 sybyeon
		return;

	//change 20170830 sybyeon : categorize to color the contour area -->ColorContourClickArea
	double dTemp, dMaxYellow, dWhiteMax;
	int *nColorContour = new int[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight];//change 20170927 sybyeon
	for (int y = 0; y < g_Camera.nClickAreaHeight; y++) {
		for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {
			
			if (!g_bAFPExposure)//change 20170927 sybyeon
				dTemp = (double)g_Camera.nFullImageArray[(y + g_nClickedStartPointY)*g_Camera.nImageWidth + (x + g_nClickedStartPointX)];
			else
				dTemp = (double)g_Camera.nFullImageArray[y *  g_Camera.nClickAreaWidth + x];

			g_dClickAreaIntensity[y *  g_Camera.nClickAreaWidth + x] = dTemp;

			if (g_dClickAreaMaxIntensity < 10000.0)
				dMaxYellow = g_dClickAreaMaxIntensity;
			else
				dMaxYellow = 10000.0;

			dWhiteMax = (double)g_Camera.nScaleMax - (double)(g_Camera.nScaleMax - g_Camera.nScaleMin)*0.2;
			
			nColorContour[y *  g_Camera.nClickAreaWidth + x] = 1;//white
			if (dTemp > dWhiteMax)
				nColorContour[y *  g_Camera.nClickAreaWidth + x] = 2;//blue
			if (dTemp> dWhiteMax + (dMaxYellow - dWhiteMax)* 15.0 / 100.0)
				nColorContour[y *  g_Camera.nClickAreaWidth + x] = 3;//green
			if (dTemp > dWhiteMax + (dMaxYellow - dWhiteMax)* 40.0 / 100.0)
				nColorContour[y *  g_Camera.nClickAreaWidth + x] = 4;//yellow
			if (dTemp>10000.0)
				nColorContour[y *  g_Camera.nClickAreaWidth + x] = 5;//orange
			if (dTemp>35000.0)
				nColorContour[y *  g_Camera.nClickAreaWidth + x] = 6;//red
			if (dTemp == 65535.0)
				nColorContour[y *  g_Camera.nClickAreaWidth + x] = 0;//black

		}
	}


	for (int y = 0; y < g_Camera.nClickAreaHeight; y++) {
		for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {

			switch (nColorContour[y *  g_Camera.nClickAreaWidth + x]) {
			case 0: { //black
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 0;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 0;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 0;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}
			case 1: {//white
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 255;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 255;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 255;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}
			case 2: {//blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 255;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 0;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 0;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}
			case 3: {//green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 0;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 180;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 0;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}
			case 4: {//yellow
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 0;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 255;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 255;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}
			case 5: { //orange
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 0;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 127;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 255;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}
			case 6: { //red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 0] = 0;//Blue
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 1] = 0;//Green
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 2] = 255;//Red
				g_ClickedPixelData[4 * y *  g_Camera.nClickAreaWidth + 4 * x + 3] = 0;
				break;
			}

			}

		}
	}

	delete[] nColorContour; // add 20710912 by Tae-Geun : Return Memory
	nColorContour = NULL;
}

//add 20170830 sybyeon
void CDataAcquisitionDlg::CalculatePlotOnRadius()
{

	if (!g_Camera.bImage || !g_bClick)	//add 20170913 sybyeon
		return;

	//add 20170913 sybyeon
	if (g_bClick) {
		g_dClickAreaMaxIntensity = 0.0;
		g_dClickAreaMinIntensity = 65535.0;
		double dClickIntensity;
		for (int y = 0; y < g_Camera.nClickAreaHeight; y++) {
			for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {
				dClickIntensity = g_dClickAreaIntensity[y*g_Camera.nClickAreaWidth + x];//change 201740927 sybyeon
				if (g_dClickAreaMaxIntensity < dClickIntensity)
					g_dClickAreaMaxIntensity = dClickIntensity;
				if (g_dClickAreaMinIntensity > dClickIntensity)
					g_dClickAreaMinIntensity = dClickIntensity;

			}
		}

	}

	//add 20170829 sybyeon: calculate to plot intensity on radius graph
	if (g_dIntensityOnRadius != NULL) { // change 20170923 by Tae-Geun : Return Memory

		for (int i = 0; i < 2; i++)
			delete[] g_dIntensityOnRadius[i];

		delete[] g_dIntensityOnRadius;
		g_dIntensityOnRadius = NULL;
	}
	if (g_dDifference != NULL) {

		delete[] g_dDifference;
		g_dDifference = NULL;
	}

	g_dIntensityOnRadius = new double*[2];
	g_dIntensityOnRadius[0] = new double[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight];
	g_dIntensityOnRadius[1] = new double[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight];

	g_dDifference = new double[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight];

	double dFitIntensity;
	double dRadius = 0.0;
	int k = 0;
	for (int y = 0; y < g_Camera.nClickAreaHeight; y++) {
		for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {
			dRadius = sqrt(pow((double)x - g_Camera.dFitCenterX, 2.0) + pow((double)y - g_Camera.dFitCenterY, 2.0));//change 20170911 sybyeon
			g_dIntensityOnRadius[0][k] = dRadius;
			g_dIntensityOnRadius[1][k] = g_dClickAreaIntensity[y* g_Camera.nClickAreaWidth + x];

			dFitIntensity = g_Camera.dFitBackground + g_Camera.dFitAmplitude
				* exp(-((pow((double)x - g_Camera.dFitCenterX, 2.0) / (2.0*pow(g_Camera.dFitSigma, 2.0)))
					+ (pow((double)y - g_Camera.dFitCenterY, 2.0) / (2.0*pow(g_Camera.dFitSigma, 2.0)))));//add 20170906 sybyeon
			g_dDifference[k] = g_dIntensityOnRadius[1][k] - dFitIntensity;
			k++;
		}
	}

	//test
	CStdioFile file;
	CFileException exception;

	CString strPath;	strPath.Empty();
	strPath = _T("C:\\KAOS30\\CFG\\TEST.txt");

	CString sLine;
	CString sLines;

	for (int i = 0; i < k; i++) {

		sLine.Format(_T("%f\t%f\n"), g_dIntensityOnRadius[0][i], g_dIntensityOnRadius[1][i]);//change 20171223 sybyeon
		sLines += sLine;
	}
	if (file.Open(strPath, CFile::modeWrite, &exception)) {

		file.Seek(0, CFile::begin);
		file.WriteString(sLines);

		file.Close();
	}

	//add sybyeon 20170830: calculate to plot fitting graph
	if (g_dFitIntensityOnRadius != NULL) { // change 20170923 by Tae-Geun

		for (int i = 0; i < 2; i++)
			delete[] g_dFitIntensityOnRadius[i];

		delete[] g_dFitIntensityOnRadius;
		g_dFitIntensityOnRadius = NULL;
	}

	g_dFitIntensityOnRadius = new double*[2];
	g_dFitIntensityOnRadius[0] = new double[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight * 25];
	g_dFitIntensityOnRadius[1] = new double[g_Camera.nClickAreaWidth*g_Camera.nClickAreaHeight * 25];

	double dFitRadius;
	double dX, dY;//add 20170906 sybyeon
	k = 0;
	// change 20170906 sybyeon
	for (int y = 0; y < g_Camera.nClickAreaHeight * 5; y++) {
		for (int x = 0; x < g_Camera.nClickAreaWidth * 5; x++) {

			dX = (double)x / 5.0;
			dY = (double)y / 5.0;
			dFitRadius = sqrt(pow(dX - g_Camera.dFitCenterX, 2.0) + pow(dY - g_Camera.dFitCenterY, 2.0));
			dFitIntensity = g_Camera.dFitBackground + g_Camera.dFitAmplitude
						  * exp(-((pow(dX - g_Camera.dFitCenterX, 2.0) / (2.0*pow(g_Camera.dFitSigma, 2.0)))
						  + (pow(dY - g_Camera.dFitCenterY, 2.0) / (2.0*pow(g_Camera.dFitSigma, 2.0)))));
			
			g_dFitIntensityOnRadius[0][k] = dFitRadius;
			g_dFitIntensityOnRadius[1][k] = dFitIntensity;
			k++;
		}
	}

	

}


//add 20170901 sybyeon
void CDataAcquisitionDlg::DisplayStarSeeingOnX()
{

	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DISPLAY_STAR_SEEING_X);
	CDC *pDc = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(m_picDisplayStarSeeingX.GetDC());

	//======background
	BYTE *nBackground = new BYTE[4];
	for (int i = 0; i<4; i++)
		nBackground[i] = (BYTE)255;

	HBITMAP hBmp = ::CreateBitmap(1, 1, 1, 32, nBackground);

	memDC.SelectObject(hBmp);
	pDc->SetStretchBltMode(COLORONCOLOR);
	pDc->StretchBlt(1, 1, rect.right - 2, rect.bottom - 2, &memDC, 0, 0, 1, 1, SRCCOPY);

	delete[] nBackground; // change 20170912 by Tae-Geun : Return Memory
	nBackground = NULL;

	CPen pen1, pen2, pen3;
	pen1.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	pDc->SelectObject(pen1);

	//===== axis
	pDc->MoveTo(15, rect.bottom - 15);
	pDc->LineTo(rect.right - 15, rect.bottom - 15);
	pDc->LineTo(rect.right - 15 - 10, rect.bottom - 15 - 6);
	pDc->MoveTo(rect.right - 15, rect.bottom - 15);
	pDc->LineTo(rect.right - 15 - 10, rect.bottom - 15 + 6);
	pDc->MoveTo(15, rect.bottom - 15);
	pDc->LineTo(15, 15);
	pDc->LineTo(15 - 6, 15 + 10);
	pDc->MoveTo(15, 15);
	pDc->LineTo(15 + 6, 15 + 10);

	//add 20170908 sybyeon
	CFont font1, font2;
	font1.CreateFont(15, 7, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	font2.CreateFont(15, 7, 900, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	pDc->SelectObject(font1);
	pDc->SetBkMode(TRANSPARENT);
	pDc->TextOutW(rect.right - 30, rect.bottom - 15, _T("X"));
	pDc->SelectObject(font2);
	pDc->TextOutW(0, 80, _T("Intensity"));

	if (g_dIntensityOnRadius == NULL || !g_bClick)//change 20170913 sybyeon
		return;


	CRect rectPlot;//add 20170907 sybyeon
	rectPlot.left = rect.left + 15;
	rectPlot.top = rect.top + 15;
	rectPlot.right = rect.right - 15;
	rectPlot.bottom = rect.bottom - 15;

	double dMaxRadius, dMaxIntensity;
	int nX, nI, nThickness;

	//======plot
	pen2.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pDc->SelectObject(pen2);
	CPoint point;//add 20170906 sybyeon

	dMaxRadius = 10.0;
	dMaxIntensity = 256.0*256.0;

	nX = 0, nI = 0;
	nThickness = 1;
	// calculate to plot intensity on x graph
	int nCenterY = (int)(g_Camera.nClickAreaHeight / 2.0);

	double *dIntensityOnX = new double[g_Camera.nClickAreaWidth];
	for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {
		dIntensityOnX[x] = g_dClickAreaIntensity[nCenterY*g_Camera.nClickAreaWidth + x];
	}
	//display intensity on x graph
	for (int i = 0; i < g_Camera.nClickAreaWidth; i++) {

		nX = (int)(((double)i / (double)g_Camera.nClickAreaWidth) * ((double)rect.right - 45.0) + 15.0);
		nI = (int)((1.0 - (dIntensityOnX[i] - g_dClickAreaMinIntensity) / (g_dClickAreaMaxIntensity - g_dClickAreaMinIntensity))*((double)rect.bottom - 45.0) + 30.0);//change 20170905 sybyeon

		point.x = nX;//change 20170906 sybyeon
		point.y = nI;
		if (rectPlot.PtInRect(point))
			pDc->Rectangle(nX - nThickness, nI - nThickness, nX + nThickness, nI + nThickness);//change 20170913 sybyeon
	}



	//=======fitting plot 
	//calculate to plot fitting graph//change 20170906 sybyeon
	double *dFitIntensityOnX = new double[g_Camera.nClickAreaWidth * 10];
	double dX, dFitIntensity;
	for (int x = 0; x < g_Camera.nClickAreaWidth * 10; x++) {
		dX = (double)x / 10.0;
		dFitIntensity = g_Camera.dFitBackground + g_Camera.dFitAmplitude
			* exp(-((pow(dX - 15.0, 2.0) / (2.0*pow(g_Camera.dFitSigma, 2.0)))));//change 20170905 sybyeon
		dFitIntensityOnX[x] = dFitIntensity;
	}

	pen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDc->SelectObject(pen3);

	//display fitting graph //change 20170906 sybyeon
	nX = 0, nI = 0;
	for (int i = 0; i < g_Camera.nClickAreaWidth * 10; i++) {

		nX = (int)(((double)i / ((double)g_Camera.nClickAreaWidth*10.0)) * ((double)rect.right - 45.0) + 15.0);
		nI = (int)((1.0 - (dFitIntensityOnX[i] - g_dClickAreaMinIntensity) / (g_dClickAreaMaxIntensity - g_dClickAreaMinIntensity))*((double)rect.bottom - 45.0) + 30.0);//change 20170905 sybyeon

		point.x = nX;//change 20170906 sybyeon
		point.y = nI;
		if (rectPlot.PtInRect(point)) {
			if (i == 0)
				pDc->MoveTo(nX, nI);
			else
				pDc->LineTo(nX, nI);
		}
	}

	memDC.DeleteDC();
	DeleteObject(hBmp);
	pWnd->ReleaseDC(pDc);

	delete[] dIntensityOnX; // add 20170912 by Tae-Geun : Return Memory
	delete[] dFitIntensityOnX;
	dIntensityOnX = NULL;
	dFitIntensityOnX = NULL;
}

//add 20170906 sybyeon
void CDataAcquisitionDlg::DisplaySeeingDifference()
{

	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DISPLAY_SEEING_DIFFERENCE);
	CDC *pDc = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(m_picDisplaySeeingDifference.GetDC());

	//======background
	BYTE *nBackground = new BYTE[4];
	for (int i = 0; i<4; i++)
		nBackground[i] = (BYTE)255;

	HBITMAP hBmp = ::CreateBitmap(1, 1, 1, 32, nBackground);

	memDC.SelectObject(hBmp);
	pDc->SetStretchBltMode(COLORONCOLOR);
	pDc->StretchBlt(1, 1, rect.right - 2, rect.bottom - 2, &memDC, 0, 0, 1, 1, SRCCOPY);

	delete[] nBackground; // change 20170912 by Tae-Geun : Return Memory
	nBackground = NULL;


	CPen pen1, pen2, pen3;
	pen1.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	pDc->SelectObject(pen1);

	//===== axis
	pDc->MoveTo(15, (int)((double)rect.bottom / 2.0));
	pDc->LineTo(rect.right - 15, (int)((double)rect.bottom / 2.0));
	pDc->LineTo(rect.right - 15 - 10, (int)((double)rect.bottom / 2.0) - 6);
	pDc->MoveTo(rect.right - 15, (int)((double)rect.bottom / 2.0));
	pDc->LineTo(rect.right - 15 - 10, (int)((double)rect.bottom / 2.0) + 6);

	pDc->MoveTo(15, rect.bottom - 15);
	pDc->LineTo(15, 15);
	pDc->LineTo(15 - 6, 15 + 10);
	pDc->MoveTo(15, 15);
	pDc->LineTo(15 + 6, 15 + 10);

	//add 20170908 sybyeon
	CFont font1, font2;
	font1.CreateFont(15, 7, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	font2.CreateFont(15, 7, 900, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	pDc->SelectObject(font1);
	pDc->SetBkMode(TRANSPARENT);
	pDc->TextOutW(rect.right - 60, rect.bottom / 2, _T("Radius"));
	pDc->SelectObject(font2);
	pDc->TextOutW(0, 90, _T("Difference"));



	if (g_dIntensityOnRadius == NULL || !g_bClick)//change 20170913 sybyeon
		return;


	double dMaxRadius, dMaxIntensity;
	int nR, nD, nThickness;

	//======plot 
	pen2.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pDc->SelectObject(pen2);
	CRect rectPlot;//add 20170907 sybyeon
	CPoint point;

	rectPlot.left = rect.left + 15;//add 20170907 sybyeon
	rectPlot.top = rect.top + 15;
	rectPlot.right = rect.right - 15;
	rectPlot.bottom = rect.bottom - 15;

	dMaxRadius = 10.0;
	dMaxIntensity = 256.0*256.0;
	nR = 0, nD = 0;
	nThickness = 1;

	for (int i = 0; i < g_Camera.nClickAreaWidth* g_Camera.nClickAreaHeight; i++) {

		nR = (int)((g_dIntensityOnRadius[0][i] / dMaxRadius) * ((double)rect.right - 45.0) + 15.0);
		nD = (int)((double)rect.bottom / 2.0 - g_dDifference[i] * ((double)rect.bottom - 15.0) / dMaxIntensity);

		point.x = nR;//change 20170907 sybyeon
		point.y = nD;
		if (rectPlot.PtInRect(point))
			pDc->Rectangle(nR - nThickness, nD - nThickness, nR + nThickness, nD + nThickness);//change 20170913 sybyeon
	}

}


void CDataAcquisitionDlg::SendSeeingValue()
{


	CWnd* pWnd = FindWindow(NULL, L"Auto Focus Package");
	if (g_bClick && g_Camera.bLink) {
		//change 20171224 sybyeon :seeing -> HFD
		double dDistance, dPixelValue;
		double dSumUpper = 0;
		double dSumLower = 0;
		double dHFD;
		double dOutRadius = 15.0;

		for (int y = 0; y < g_Camera.nClickAreaHeight; y++) {
			for (int x = 0; x < g_Camera.nClickAreaWidth; x++) {
				dDistance = sqrt(pow((double)x - 16.0, 2.0) + pow((double)y - 16.0, 2.0));

				if (dDistance < dOutRadius) {
					dPixelValue = g_dClickAreaIntensity[y*g_Camera.nClickAreaWidth + x] - g_Camera.dImageBackground;
					if (dPixelValue < 0)
						dPixelValue = 0;
					
					dSumUpper = dSumUpper + dPixelValue*dDistance;
					dSumLower = dSumLower + dPixelValue;

				}

			}
		}
		dHFD = 2.0*dSumUpper / dSumLower;

		long lSendHFD = (long)(dHFD*1000.0);
		if (pWnd != NULL)
			pWnd->SendMessage(WM_AFP, (WPARAM)GET_SEEING_VALUE, lSendHFD);
	}
	else if (!g_Camera.bLink) {
		if (pWnd != NULL)
			pWnd->SendMessage(WM_AFP, (WPARAM)GET_SEEING_VALUE, 99000);
		g_bAFPExposure = false;
		AfxMessageBox(_T("Connect the Camera."));
	}
	else {
		if (pWnd != NULL)
			pWnd->SendMessage(WM_AFP, (WPARAM)GET_SEEING_VALUE, 99000);
		g_bAFPExposure = false;
		AfxMessageBox(_T("Click the star for focusing."));
	}

}


void CDataAcquisitionDlg::OnChangeEditObserver()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}


void CDataAcquisitionDlg::OnChangeEditObjectName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}


void CDataAcquisitionDlg::OnChangeEditExposureTime()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	g_Camera.fExposureTime = m_fExposureTime;//add 20171204 sybyeon
}


void CDataAcquisitionDlg::OnChangeEditRepeatNumber()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}


void CDataAcquisitionDlg::OnChangeEditSetCameraTemperature()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}


void CDataAcquisitionDlg::DeleteMemory() // add 20170923 by Tae-Geun
{
	if (g_Camera.nFullImageArray != NULL) {

		delete[] g_Camera.nFullImageArray;
		g_Camera.nFullImageArray = NULL;
	}

	if (g_Camera.PixelData != NULL) {

		delete[] g_Camera.PixelData;
		g_Camera.PixelData = NULL;
	}

	if (g_ClickedPixelData != NULL) {

		delete[] g_ClickedPixelData;
		g_ClickedPixelData = NULL;
	}
	if (g_dClickAreaIntensity != NULL) {

		delete[] g_dClickAreaIntensity;
		g_dClickAreaIntensity = NULL;
	}

	if (g_Filter.sFilterList != NULL) {

		delete[] g_Filter.sFilterList;
		g_Filter.sFilterList = NULL;
	}

	if (g_dFitIntensityOnRadius != NULL) { // change 20170923 by Tae-Geun

		for (int i = 0; i < 2; i++)
			delete[] g_dFitIntensityOnRadius[i];

		delete[] g_dFitIntensityOnRadius;
		g_dFitIntensityOnRadius = NULL;
	}
	if (g_dIntensityOnRadius != NULL) { // change 20170923 by Tae-Geun : Return Memory

		for (int i = 0; i < 2; i++)
			delete[] g_dIntensityOnRadius[i];

		delete[] g_dIntensityOnRadius;
		g_dIntensityOnRadius = NULL;
	}
	if (g_dDifference != NULL) { // add 20170912 by Tae-Geun : Return Memory

		delete[] g_dDifference;
		g_dDifference = NULL;
	}

	delete pLibFLI;
	delete pLibAscom;
	delete pLibControl;
}
