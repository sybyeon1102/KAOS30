
// AutoFocusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoFocus.h"
#include "AutoFocusDlg.h"
#include "afxdialogex.h"

#include "FindCenter.h"
#include <math.h>

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


// CAutoFocusDlg dialog



CAutoFocusDlg::CAutoFocusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTOFOCUS_DIALOG, pParent)
	, m_sFocuserDriver(_T("No ASCOM Focuser Driver"))
	, m_sFocuserLinkIndicator(_T("No Focuser"))
	, m_sCurrentPosition(_T(""))
	, m_lSetPosition(0)
	, m_lIncremental(851)
	, m_sSeeing(_T(""))
	, m_sProgressStatus(_T("0 / 0"))
	, m_sCurrentFilter(_T(""))
	, m_lBestFocus(0)
	, m_lStartPosition(7235)
	, m_lEndPosition(7235)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoFocusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SELECT_FOCUSER, m_btnSelectFocuser);
	DDX_Text(pDX, IDC_EDIT_FOCUSER_DRIVER, m_sFocuserDriver);
	DDX_Control(pDX, IDC_BUTTON_CONNECT_FOCUSER, m_btnConnectFocuser);
	DDX_Control(pDX, IDC_BUTTON_DISCONNECT_FOCUSER, m_btnDisconnectFocuser);
	DDX_Text(pDX, IDC_EDIT_FOCUSER_LINK_INDICATOR, m_sFocuserLinkIndicator);
	DDX_Text(pDX, IDC_EDIT_CURRENT_POSITION, m_sCurrentPosition);
	DDX_Control(pDX, IDC_BUTTON_SET_FOCUSER_POSITION, m_btnSetFocuserPosition);
	DDX_Text(pDX, IDC_EDIT_SET_POSITION, m_lSetPosition);
	//  DDV_MinMaxLong(pDX, m_lSetPosition, 0, 200000);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_V_CURVE, m_picDisplayVCurve);
	DDX_Control(pDX, IDC_EDIT_LOOP, m_editLoop);
	DDX_Text(pDX, IDC_EDIT_INCREMENTAL, m_lIncremental);
	DDX_Text(pDX, IDC_EDIT_INCREMENTAL, m_lIncremental);
	DDX_Text(pDX, IDC_EDIT_SEEING, m_sSeeing);
	DDX_Text(pDX, IDC_EDIT_PROGRESSING, m_sProgressStatus);
	DDX_Control(pDX, IDC_BUTTON_START_EXPOSURE, m_btnStartExposure);
	DDX_Control(pDX, IDC_BUTTON_ABORT_AUTO_FOCUSING, m_btnAbortAutoFocusing);
	DDX_Text(pDX, IDC_EDIT_CURRENT_FILTER, m_sCurrentFilter);
	DDX_Text(pDX, IDC_EDIT_BEST_FOCUS, m_lBestFocus);
	DDX_Text(pDX, IDC_EDIT_START_POSITION, m_lStartPosition);
	DDX_Text(pDX, IDC_EDIT_END_POSITION, m_lEndPosition);
	//  DDX_Control(pDX, IDC_CHECK_OFFSET, m);
	DDX_Control(pDX, IDC_CHECK_OFFSET, m_btnOffset);
}

BEGIN_MESSAGE_MAP(CAutoFocusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FOCUSER, &CAutoFocusDlg::OnClickedButtonSelectFocuser)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT_FOCUSER, &CAutoFocusDlg::OnClickedButtonConnectFocuser)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_FOCUSER, &CAutoFocusDlg::OnClickedButtonDisconnectFocuser)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SET_FOCUSER_POSITION, &CAutoFocusDlg::OnClickedButtonSetFocuserPosition)
	ON_EN_KILLFOCUS(IDC_EDIT_SET_POSITION, &CAutoFocusDlg::OnKillfocusEditSetPosition)
	ON_EN_SETFOCUS(IDC_EDIT_SET_POSITION, &CAutoFocusDlg::OnSetfocusEditSetPosition)
	ON_MESSAGE(WM_AFP, &CAutoFocusDlg::OnGetMessageFromDlg)
	ON_BN_CLICKED(IDC_BUTTON_START_EXPOSURE, &CAutoFocusDlg::OnBnClickedButtonStartExposure)
	ON_EN_SETFOCUS(IDC_EDIT_INCREMENTAL, &CAutoFocusDlg::OnSetfocusEditIncremental)
	ON_EN_KILLFOCUS(IDC_EDIT_INCREMENTAL, &CAutoFocusDlg::OnKillfocusEditIncremental)
	ON_EN_SETFOCUS(IDC_EDIT_START_STEP, &CAutoFocusDlg::OnSetfocusEditStartStep)
	ON_EN_KILLFOCUS(IDC_EDIT_START_STEP, &CAutoFocusDlg::OnKillfocusEditStartStep)
	ON_MESSAGE(MOVE_FOCUS_NEXT, &CAutoFocusDlg::OnMoveFocusToNextStep)
	ON_BN_CLICKED(IDC_BUTTON_ABORT_AUTO_FOCUSING, &CAutoFocusDlg::OnBnClickedButtonAbortAutoFocusing)
	ON_BN_CLICKED(IDC_RADIO1, &CAutoFocusDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAutoFocusDlg::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT_SET_POSITION, &CAutoFocusDlg::OnChangeEditSetPosition)
	ON_EN_CHANGE(IDC_EDIT_INCREMENTAL, &CAutoFocusDlg::OnChangeEditIncremental)
	ON_EN_CHANGE(IDC_EDIT_START_STEP, &CAutoFocusDlg::OnChangeEditStartStep)
ON_EN_SETFOCUS(IDC_EDIT_END_POSITION, &CAutoFocusDlg::OnSetfocusEditEndPosition)
ON_EN_KILLFOCUS(IDC_EDIT_END_POSITION, &CAutoFocusDlg::OnKillfocusEditEndPosition)
ON_EN_SETFOCUS(IDC_EDIT_START_POSITION, &CAutoFocusDlg::OnSetfocusEditStartPosition)
ON_EN_KILLFOCUS(IDC_EDIT_START_POSITION, &CAutoFocusDlg::OnKillfocusEditStartPosition)
ON_EN_CHANGE(IDC_EDIT_START_POSITION, &CAutoFocusDlg::OnChangeEditStartPosition)
ON_EN_CHANGE(IDC_EDIT_END_POSITION, &CAutoFocusDlg::OnChangeEditEndPosition)
END_MESSAGE_MAP()


// CAutoFocusDlg message handlers

BOOL CAutoFocusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//m_rbButtonIn.SetCheck(BST_CHECKED);
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

//	g_Focuser.nControlMode = CONTROL_MODE_VIRTUAL; // change 20170912 by Tae-Geun	
	g_Focuser.nControlMode = CONTROL_MODE_ASCOM;

	m_btnConnectFocuser.EnableWindow(FALSE);
	m_btnDisconnectFocuser.EnableWindow(FALSE);
	m_btnSetFocuserPosition.EnableWindow(FALSE);
	m_btnStartExposure.EnableWindow(FALSE);
	m_btnAbortAutoFocusing.EnableWindow(FALSE);

	g_ScriptMode = false;
	g_AutoFocusScriptMode = false;
	g_Focuser.lCount = -1;//add 20170919 sybyeon
	g_bDisplay = false;//add 20170920 sybyeon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoFocusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE) {

		if (IDYES == this->MessageBox(L"Are you sure you want to exit the KAOS30 AFP?", L"Message", MB_YESNO)) {

			CWnd* pWnd = FindWindow(NULL, L"KAOS30 v1.04"); // change 20171223 by Tae-Geun

			if (pWnd != NULL) 
				pWnd->SendMessage(WM_MAIN, (WPARAM)ID_AFP, (LPARAM)EXIT_DIALOG);
			
			if (g_sFilterList != NULL) {

				delete[] g_sFilterList;
				g_sFilterList = NULL;
			}
			if (g_lFocusValues != NULL) {

				delete[] g_lFocusValues;
				g_lFocusValues = NULL;
			}
			if (g_sFilterNames != NULL) {

				delete[] g_sFilterNames;
				g_sFilterNames = NULL;
			}
			if (g_lFocusOffsets != NULL) {

				delete[] g_lFocusOffsets;
				g_lFocusOffsets = NULL;
			}
		}
		else
			return;
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoFocusDlg::OnPaint()
{
	// Draw the Graph
	DisplayVCurve();
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoFocusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CAutoFocusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

afx_msg LRESULT CAutoFocusDlg::OnGetMessageFromDlg(WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = FindWindow(NULL, L"KAOS30 v1.04");
	int nMessage = (WPARAM)wParam;
	switch (nMessage) {

	case SET_FOCUS_POSTION:
	{
		g_ScriptMode = true;

		if (!g_Focuser.bLink) {

			if (pWnd != NULL)
				pWnd->SendMessage(WM_SMP, (WPARAM)SET_FOCUS_POSTION, (LPARAM)false);
		}

		g_Focuser.lSetPosition = (long)lParam;
		m_lSetPosition = g_Focuser.lSetPosition;

		UpdateData(FALSE);

		SetFocusPosition();
	}
	break;
	case GET_SEEING_VALUE: // change 20170919 sybyeon
	{
		long lSeeing = (long)lParam;
		g_Focuser.dSeeing = (double)lSeeing / 1000.0;
		CString sSeeing;
		sSeeing.Format(_T("%.2f"), g_Focuser.dSeeing);
		m_sSeeing = sSeeing;

		if (lSeeing != 99000 && g_bReadyToMoveFocus) {

			if (g_Focuser.lCount == -1)
				return 0;

			g_dFocusValue[g_Focuser.lCount] = (double)g_Focuser.lCurrentPosition;
			g_dSeeingValue[g_Focuser.lCount] = g_Focuser.dSeeing;

			g_Focuser.lCount++;
			PostMessage(MOVE_FOCUS_NEXT, 0, 0);


			CString sProgressStatus;
			sProgressStatus.Format(_T("%d / %d"), g_Focuser.lCount + 1, g_Focuser.lStepNumber);
			if (g_Focuser.lCount != g_Focuser.lStepNumber)
				m_sProgressStatus = sProgressStatus;

			g_bReadyToMoveFocus = false;

		}
		else { //when Seeing value is not valid
			m_btnStartExposure.EnableWindow(TRUE);
			m_btnAbortAutoFocusing.EnableWindow(FALSE);
			m_btnSetFocuserPosition.EnableWindow(TRUE);
			m_btnDisconnectFocuser.EnableWindow(TRUE);

			PostMessage(MOVE_FOCUS_NEXT, (WPARAM)BACK_TO_START, 0);
		}
		UpdateData(FALSE);

	}
	break;
	case FILTER_POSITION://add 20171204 sybyeon
	{
		g_lFilterPosition = (long)lParam;
		long lFocus;
		for (int i = 0; i < g_nFocusCount; i++) {//change 20171223 sybyeon
			if (g_sFilterNames[i] == g_sFilterList[g_lFilterPosition]) {
				lFocus = g_lFocusValues[i];
				break;
			}
		}
		//add 20171205 sybyeon
		if (g_Focuser.bLink && lFocus != 0) {

			g_Focuser.lSetPosition = lFocus;
			PostMessage(MOVE_FOCUS_NEXT, (WPARAM)FOCUS_FOR_FILTER, 0);

			//add 20171205 sybyeon
			m_lBestFocus = lFocus;
			m_sCurrentFilter = g_sFilterList[g_lFilterPosition];//change 20171224 sybyeon
			UpdateData(FALSE);
		}
		else if (g_Focuser.bLink && lFocus == 0) {//add 20171224 sybyeon

			m_sCurrentFilter = g_sFilterList[g_lFilterPosition];
			UpdateData(FALSE);
		}
	}
	break;
	case AUTO_FOCUS_START:
	{
		g_AutoFocusScriptMode = true;

		if (!g_Focuser.bLink) {

			if (pWnd != NULL)
				pWnd->SendMessage(WM_SMP, (WPARAM)AUTO_FOCUS_START, (LPARAM)false);
		}

		StartAutoFocus();
	}
	break;
	}

	return 0;
}

void CAutoFocusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent) {

	case GET_FOCUSER_POSITION:
	{
		pLibControl->GetFocuserPosition(g_Focuser.nControlMode, &g_Focuser.lCurrentPosition);
		m_sCurrentPosition.Format(_T("%d"), g_Focuser.lCurrentPosition);
		UpdateData(FALSE);
	}
	break;
	case CHECK_FOCUSER_MOVING:
	{
		g_Focuser.bMoving = pLibControl->GetFocuserIsMoving(g_Focuser.nControlMode);

		if (!g_Focuser.bMoving) {

			if (g_ScriptMode) {

				g_ScriptMode = false;
				CWnd* pWnd = FindWindow(NULL, L"KAOS30 v1.04");
				if (pWnd != NULL)
					pWnd->SendMessage(WM_SMP, 0, true);
			}
			if (g_Focuser.lCount == -1) {

				m_btnSetFocuserPosition.EnableWindow(TRUE);
				m_btnStartExposure.EnableWindow(TRUE);
				m_btnDisconnectFocuser.EnableWindow(TRUE);
			}
			if (g_Focuser.lSetPosition == g_Focuser.lCurrentPosition || g_Focuser.lCount == g_Focuser.lStepNumber) {

				if (g_Focuser.lCount != -1) {

					GetSeeingValue();
					g_Focuser.lSetPosition++;
				}
			}
		}
	}
	break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CAutoFocusDlg::OnClickedButtonSelectFocuser()
{
	// TODO: Add your control notification handler code here
	g_Focuser.bDriver = pLibControl->ConnectFocuserDriver(g_Focuser.nControlMode, &g_Focuser.sFocuserModel);

	if (g_Focuser.bDriver) {

		m_sFocuserDriver = g_Focuser.sFocuserModel;
		m_btnConnectFocuser.EnableWindow(TRUE);
	}
	else
		m_sFocuserDriver = _T("No ASCOM Focuser Driver");

	UpdateData(FALSE);
}



void CAutoFocusDlg::OnClickedButtonConnectFocuser()
{
	// TODO: Add your control notification handler code here
	g_Focuser.bLink = pLibControl->LinkFocuser(g_Focuser.nControlMode);

	if (g_Focuser.bLink) {

		m_sFocuserLinkIndicator = _T("Connected.");
		UpdateData(FALSE);

		SetTimer(GET_FOCUSER_POSITION, INTERVAL_GET_FOCUSER_POSITION, NULL);
		SetTimer(CHECK_FOCUSER_MOVING, INTERVAL_CHECK_FOCUSER_MOVING, NULL);

		m_btnSelectFocuser.EnableWindow(FALSE);
		m_btnConnectFocuser.EnableWindow(FALSE);
		m_btnDisconnectFocuser.EnableWindow(TRUE);
		m_btnSetFocuserPosition.EnableWindow(TRUE);
		m_btnStartExposure.EnableWindow(TRUE);

		//add 20171205 sybyeon : to get filter and focus value
		if (g_sFilterList != NULL) {

			delete[] g_sFilterList;
			g_sFilterList = NULL;
		}
		if (g_lFocusValues != NULL) {

			delete[] g_lFocusValues;
			g_lFocusValues = NULL;
		}
		if (g_sFilterNames != NULL) {

			delete[] g_sFilterNames;
			g_sFilterNames = NULL;
		}
		if (g_lFocusOffsets != NULL) {//add 20171226 sybyeon

			delete[] g_lFocusOffsets;
			g_lFocusOffsets = NULL;
		}
		

		CStdioFile file;
		CFileException exception;
		CString sReadLine;
		CString strPath;	strPath.Empty();

		CString *sFocusValues = new CString[100];
		CString *sFocusOffsets = new CString[100];//add 20171226 sybyeon
		g_sFilterList = new CString[100];
		g_lFocusValues = new long[100];//change 20171223 sybyeon
		g_lFocusOffsets = new long[100];//add 20171225 sybyeon
		g_sFilterNames = new CString[100];//add 20171223 sybyeon
		g_nFocusCount = 0;//change 20171223 sybyeon
		int i = 0;

		strPath = _T("C:\\KAOS30\\CFG\\FilterList.txt");
		if (file.Open(strPath, CFile::modeRead, &exception)) {

			while (file.ReadString(sReadLine)) {

				g_sFilterList[i] = sReadLine;//change 20171223 sybyeon
				i++;
			}
			file.Close();
		}

		//add 20171223 sybyeon
		strPath = _T("C:\\KAOS30\\CFG\\FocusList.txt");
		if (file.Open(strPath, CFile::modeRead, &exception)) {

			while (file.ReadString(sReadLine)) {

				AfxExtractSubString(g_sFilterNames[g_nFocusCount], sReadLine, 0, ':');
				AfxExtractSubString(sFocusValues[g_nFocusCount], sReadLine, 1, ':');
				AfxExtractSubString(sFocusOffsets[g_nFocusCount], sReadLine, 2, ':');//add 20171226 sybyeon
				g_lFocusValues[g_nFocusCount] = _wtol(sFocusValues[g_nFocusCount]);//CString->long
				g_lFocusOffsets[g_nFocusCount] = _wtol(sFocusOffsets[g_nFocusCount]);//add 20171226 sybyeon
				g_sFilterNames[g_nFocusCount].Remove('\t');
				g_nFocusCount++;
			}
			file.Close();
		}

		delete[] sFocusValues;
		sFocusValues = NULL;
		delete[] sFocusOffsets;//add 20171226 sybyeon
		sFocusOffsets = NULL;//add 20171226 sybyeon

		//add 20171205 sybyeon
		CWnd* pWndDAP = FindWindow(NULL, L"Data Acquisition Package");
		if (pWndDAP != NULL)
			pWndDAP->SendMessage(WM_DAP, (WPARAM)FILTER_POSITION, 0);

	}
	else
		AfxMessageBox(_T("No Focuser"));
}



void CAutoFocusDlg::OnClickedButtonDisconnectFocuser()
{
	// TODO: Add your control notification handler code here
	g_Focuser.bLink = pLibControl->UnLinkFocuser(g_Focuser.nControlMode);

	if (!g_Focuser.bLink) {

		KillTimer(GET_FOCUSER_POSITION);
		KillTimer(CHECK_FOCUSER_MOVING);

		m_sFocuserLinkIndicator = _T("Disconnected.");
		m_sCurrentPosition = _T("");
		UpdateData(FALSE);

		m_btnSelectFocuser.EnableWindow(TRUE);
		m_btnConnectFocuser.EnableWindow(TRUE);
		m_btnDisconnectFocuser.EnableWindow(FALSE);
		m_btnSetFocuserPosition.EnableWindow(FALSE);
		m_btnStartExposure.EnableWindow(FALSE);
	}
}

void CAutoFocusDlg::OnClickedButtonSetFocuserPosition()
{
	// TODO: Add your control notification handler code here
	if (g_Focuser.bLink) {

		m_btnSetFocuserPosition.EnableWindow(FALSE);
		m_btnStartExposure.EnableWindow(FALSE);
		g_ScriptMode = false;
		SetFocusPosition();
	}
	
}

void CAutoFocusDlg::SetFocusPosition()
{
	if (g_ScriptMode) {

		m_lSetPosition = g_Focuser.lSetPosition;
		UpdateData(FALSE);
	}
	else {

		UpdateData(TRUE);
		g_Focuser.lSetPosition = m_lSetPosition;
	}
	pLibControl->SetFocuserPosition(g_Focuser.nControlMode, g_Focuser.lSetPosition);
}


void CAutoFocusDlg::OnKillfocusEditSetPosition()
{
	// TODO: Add your control notification handler code here
	SetTimer(GET_FOCUSER_POSITION, INTERVAL_GET_FOCUSER_POSITION, NULL);
	SetTimer(CHECK_FOCUSER_MOVING, INTERVAL_CHECK_FOCUSER_MOVING, NULL);//add 20170919 sybyeon

}


void CAutoFocusDlg::OnSetfocusEditSetPosition()
{
	// TODO: Add your control notification handler code here
	KillTimer(GET_FOCUSER_POSITION);
	KillTimer(CHECK_FOCUSER_MOVING);//add 20170919 sybyeon
}

void CAutoFocusDlg::OnBnClickedButtonStartExposure() // change 20171227 by Tae-Geun
{
	StartAutoFocus(); // add 20171227 by Tae-Geun
}

void CAutoFocusDlg::StartAutoFocus() // add 20171227 by Tae-Geun
{
	m_btnStartExposure.EnableWindow(FALSE);
	m_btnAbortAutoFocusing.EnableWindow(TRUE);
	m_btnSetFocuserPosition.EnableWindow(FALSE);
	m_btnDisconnectFocuser.EnableWindow(FALSE);

	g_bDisplay = false;
	g_bReadyToMoveFocus = false;

	UpdateData(TRUE);

	//g_Focuser.lStartPosition = m_lStartPosition;

	g_Focuser.lStartPosition = g_Focuser.lCurrentPosition - m_lStartPosition;//change 20171225 sybyeon

	g_Focuser.lStepNumber = (m_lEndPosition + m_lStartPosition) / m_lIncremental + 1;
	g_Focuser.lCount = 0;
	g_Focuser.lIncremental = m_lIncremental;


	CString sProgress;
	sProgress.Format(_T("1 / %d"), g_Focuser.lStepNumber);
	m_sProgressStatus = sProgress;

	if (g_dFocusValue != NULL) {
		delete[] g_dFocusValue;
		g_dFocusValue = NULL;
	}
	if (g_dSeeingValue != NULL) {
		delete[] g_dSeeingValue;
		g_dSeeingValue = NULL;
	}
	g_dFocusValue = new double[g_Focuser.lStepNumber];
	g_dSeeingValue = new double[g_Focuser.lStepNumber];

	g_Focuser.lSetPosition = g_Focuser.lStartPosition;
	pLibControl->SetFocuserPosition(g_Focuser.nControlMode, g_Focuser.lSetPosition);

	UpdateData(FALSE);
}

void CAutoFocusDlg::DisplayVCurve() {

	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_DISPLAY_V_CURVE);
	CDC *pDc = pWnd->GetDC();

	CRect rect;
	pWnd->GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(m_picDisplayVCurve.GetDC());

	//Background
	BYTE *nBackground = new BYTE[4];
	for (int i = 0; i < 4; i++)
		nBackground[i] = (BYTE)255;

	HBITMAP hBmp = ::CreateBitmap(1, 1, 1, 32, nBackground);

	memDC.SelectObject(hBmp);
	pDc->SetStretchBltMode(COLORONCOLOR);
	pDc->StretchBlt(1, 1, rect.right - 2, rect.bottom - 2, &memDC, 0, 0, 1, 1, SRCCOPY);
	
	delete[] nBackground;
	nBackground = NULL;

	CPen pen1, pen2, pen3;
	pen1.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	pDc->SelectObject(pen1);//pen for axis
	
	//drawing axis
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

	CFont font1, font2;
	font1.CreateFont(15, 7, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	font2.CreateFont(15, 7, 900, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Calibri"));
	pDc->SelectObject(font1);
	pDc->SetBkMode(TRANSPARENT);
	pDc->TextOutW(rect.right - 60, rect.bottom - 15, _T("Focus"));
	pDc->SelectObject(font2);
	pDc->TextOutW(0, 160, _T("Half Diameter Flux(HDF)"));

	if (!g_bDisplay)
		return;

	//plot
	pen2.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pDc->SelectObject(pen2);

	int nPointThickness = 1;
	int nFocus, nSeeing;

	//save min, max of focus and seeing(HFD) for plot scale
	double dMinFocus = 200000.0, dMaxFocus = 0.0;//change 20171225 sybyeon
	double dMinSeeing = 50.0, dMaxSeeing = 0;
	for (int i = 0; i < g_Focuser.lStepNumber; i++) {

		if (dMinFocus > g_dFocusValue[i])
			dMinFocus = g_dFocusValue[i];
		if (dMaxFocus < g_dFocusValue[i])
			dMaxFocus = g_dFocusValue[i];

		if (dMinSeeing > g_dSeeingValue[i])
			dMinSeeing = g_dSeeingValue[i];
		if (dMaxSeeing < g_dSeeingValue[i])
			dMaxSeeing = g_dSeeingValue[i];
	}

	for (int i = 0; i < g_Focuser.lStepNumber; i++) {
		TRACE("i = %d, Focus = %f, HDF = %f\n", i, g_dFocusValue[i], g_dSeeingValue[i]);
		nFocus = (int)((g_dFocusValue[i] - dMinFocus) / (dMaxFocus - dMinFocus) * ((double)rect.right - 40.0) + 20.0);
		nSeeing = (int)((1.0 - (g_dSeeingValue[i] - dMinSeeing) / (dMaxSeeing - dMinSeeing)) *((double)rect.bottom - 40.0) + 20.0);

		pDc->Rectangle(nFocus - nPointThickness, nSeeing - nPointThickness, nFocus + nPointThickness, nSeeing + nPointThickness);
	}

	
	// fitting
	FindCenter pPlotting;
	pPlotting.PlotData(g_dFocusValue, g_dSeeingValue, g_Focuser.lStepNumber);

	double dPlotA = pPlotting.g_dFirstOrder;
	double dPlotB = pPlotting.g_dSecondOrder;
	double dPlotC = pPlotting.g_dThirdOrder;

	long lBestFocus;
	double dCurvature;

	lBestFocus = long((-1.0)*dPlotB / (2 * dPlotA));//change 20171224 sybyeon

	dCurvature = dPlotA;

	CFont font; // add 20170924 by Tae-Geun 
	font.CreateFont(16, 6, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET
		, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, FF_DONTCARE, _T("Arial"));
	pDc->SelectObject(font);// change 20170928 sybyeon :font1->font
	CString sBestFocus;


	if (lBestFocus > (long)dMinFocus && lBestFocus < (long)dMaxFocus && dCurvature > 0) {

		m_sProgressStatus = "Complete";
		UpdateData(FALSE);

		g_Focuser.lSetPosition = lBestFocus;
		pLibControl->SetFocuserPosition(g_Focuser.nControlMode, g_Focuser.lSetPosition);

		pDc->SetTextColor(RGB(0, 0, 255));
		sBestFocus.Format(_T("Best Focus = %d"), lBestFocus);
		pDc->TextOut(40, 10, sBestFocus);

		m_lBestFocus = lBestFocus;//add 20171205 sybyeon
		UpdateData(FALSE);
		
		//**change focus values**
		long lChangedFilterOffset;//add 20171226 sybyeon
		//change 20171227 sybyeon
		if (m_btnOffset.GetCheck()) {
			for (int i = 0; i < g_nFocusCount; i++) {
				if (g_sFilterNames[i] == g_sFilterList[g_lFilterPosition]) {
					g_lFocusValues[i] = lBestFocus;
					lChangedFilterOffset = g_lFocusOffsets[i];//change 20171226 sybyeon
					break;
				}
			}
			for (int i = 0; i < g_nFocusCount; i++) {//add 20171226 sybyeon
			if (g_sFilterNames[i] != "Empty")
			g_lFocusValues[i] = lBestFocus + g_lFocusOffsets[i] - lChangedFilterOffset;
			}
		}
		else {
			for (int i = 0; i < g_nFocusCount; i++) {
				if (g_sFilterNames[i] == g_sFilterList[g_lFilterPosition]) {
					g_lFocusValues[i] = lBestFocus;
					break;
				}
			}
		}

		CStdioFile file;
		CFileException exception;

		CString strPath;	strPath.Empty();
		strPath = _T("C:\\KAOS30\\CFG\\FocusList.txt");

		CString sLine;
		CString sLines;

		for (int i = 0; i < g_nFocusCount; i++) {

			sLine.Format(_T("%s\t:%d\t:%d\n"), g_sFilterNames[i], g_lFocusValues[i], g_lFocusOffsets[i]);//change 20171223 sybyeon
			sLines += sLine;
		}
		if (file.Open(strPath, CFile::modeWrite, &exception)) {

			file.Seek(0, CFile::begin);
			file.WriteString(sLines);

			file.Close();
		}

		if (g_AutoFocusScriptMode) {

			g_AutoFocusScriptMode = false;
			CWnd* pWnd = FindWindow(NULL, L"KAOS30 v1.04");
			if (pWnd != NULL)
				pWnd->SendMessage(WM_SMP, 0, true);
		}
	}
	else {
		m_sProgressStatus = "Fail";
		PostMessage(MOVE_FOCUS_NEXT, (WPARAM)BACK_TO_START, 0);//add 20171205 sybyeon

	}

	// fitting plot
	pen3.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pDc->SelectObject(pen3);

	nFocus = 0;
	nSeeing = 0;
	double dFitHDF;
	CPoint pntFit;//add 20171225 sybyeon
	bool bFirstPoint = true;//add 20171225 sybyeon
	for (int i = (int)dMinFocus; i < (int)dMaxFocus; i++) {

		dFitHDF = dPlotA * pow((double)i, 2.0) + dPlotB*(double)i + dPlotC;

		nFocus = (int)((i - dMinFocus) / (dMaxFocus - dMinFocus) * ((double)rect.right - 40.0) + 20.0);
		nSeeing = (int)((1.0 - ((dFitHDF - dMinSeeing) /(dMaxSeeing - dMinSeeing)))*((double)rect.bottom - 40.0) + 20.0);

		//add 20171225 sybyeon
		pntFit.x = nFocus;
		pntFit.y = nSeeing;
		if (rect.PtInRect(pntFit)) {

			if (bFirstPoint) {

				pDc->MoveTo(nFocus, nSeeing);
				bFirstPoint = false;
			}
			else
				pDc->LineTo(nFocus, nSeeing);
		}

	}


	DeleteObject(font);
	DeleteObject(font1);
	DeleteObject(font2);

	memDC.DeleteDC();
	DeleteObject(hBmp);
	pWnd->ReleaseDC(pDc);
}

void CAutoFocusDlg::OnSetfocusEditIncremental()
{
	// TODO: Add your control notification handler code here
	KillTimer(GET_FOCUSER_POSITION);
	KillTimer(CHECK_FOCUSER_MOVING);
}


void CAutoFocusDlg::OnKillfocusEditIncremental()
{
	// TODO: Add your control notification handler code here
	SetTimer(GET_FOCUSER_POSITION, INTERVAL_GET_FOCUSER_POSITION, NULL);
	SetTimer(CHECK_FOCUSER_MOVING, INTERVAL_CHECK_FOCUSER_MOVING, NULL);
}


void CAutoFocusDlg::OnSetfocusEditStartStep()
{
	// TODO: Add your control notification handler code here
	KillTimer(GET_FOCUSER_POSITION);
	KillTimer(CHECK_FOCUSER_MOVING);
}


void CAutoFocusDlg::OnKillfocusEditStartStep()
{
	// TODO: Add your control notification handler code here
	SetTimer(GET_FOCUSER_POSITION, INTERVAL_GET_FOCUSER_POSITION, NULL);
	SetTimer(CHECK_FOCUSER_MOVING, INTERVAL_CHECK_FOCUSER_MOVING, NULL);
}


afx_msg LRESULT CAutoFocusDlg::OnMoveFocusToNextStep(WPARAM wParam, LPARAM lParam)
{
	if (wParam == BACK_TO_START) {
		long lBestFocus;
		for (int i = 0; i < g_nFocusCount; i++) {
			if (g_sFilterNames[i] == g_sFilterList[g_lFilterPosition]) {

				lBestFocus = g_lFocusValues[i];
				break;
			}
		}
		pLibControl->SetFocuserPosition(g_Focuser.nControlMode, lBestFocus);
	}
	else if (wParam == FOCUS_FOR_FILTER) {
		pLibControl->SetFocuserPosition(g_Focuser.nControlMode, g_Focuser.lSetPosition);
		
		//add 20171207 sybyeon
		m_btnSetFocuserPosition.EnableWindow(FALSE);
		m_btnStartExposure.EnableWindow(FALSE);
	}
	else {

		if (g_Focuser.lCount < g_Focuser.lStepNumber) {
			g_Focuser.lSetPosition = g_Focuser.lCurrentPosition + g_Focuser.lIncremental;
			pLibControl->SetFocuserPosition(g_Focuser.nControlMode, g_Focuser.lSetPosition);
		}
	}

	return 0;
}


void CAutoFocusDlg::GetSeeingValue()
{

	CWnd* pWndDAP = FindWindow(NULL, L"Data Acquisition Package");
	if (g_Focuser.lCount == 0) {

		if (pWndDAP != NULL)
			pWndDAP->SendMessage(WM_DAP, (WPARAM)START_EXPOSURE_AFP, AFP_TEST_START);
		g_bReadyToMoveFocus = true;
	}
	else if (g_Focuser.lCount < g_Focuser.lStepNumber) {

		if (pWndDAP != NULL)
			pWndDAP->SendMessage(WM_DAP, (WPARAM)START_EXPOSURE_AFP, AFP_TEST_CONTINUE);
		g_bReadyToMoveFocus = true;
	}
	else if (g_Focuser.lCount == g_Focuser.lStepNumber) {

		g_bDisplay = true;
		DisplayVCurve();

		g_Focuser.lCount = -1;

		//when Auto focusing is completed
		m_btnStartExposure.EnableWindow(TRUE);
		m_btnAbortAutoFocusing.EnableWindow(FALSE);
		m_btnSetFocuserPosition.EnableWindow(TRUE);
		m_btnDisconnectFocuser.EnableWindow(TRUE);
	}

}


void CAutoFocusDlg::OnBnClickedButtonAbortAutoFocusing()
{
	// TODO: Add your control notification handler code here
	g_Focuser.lCount = - 1;
	m_btnStartExposure.EnableWindow(TRUE);
	m_btnAbortAutoFocusing.EnableWindow(FALSE);
	m_btnSetFocuserPosition.EnableWindow(TRUE);

}


void CAutoFocusDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CAutoFocusDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CAutoFocusDlg::OnChangeEditSetPosition()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}


void CAutoFocusDlg::OnChangeEditIncremental()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}


void CAutoFocusDlg::OnChangeEditStartStep()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}

void CAutoFocusDlg::OnSetfocusEditEndPosition()
{
	// TODO: Add your control notification handler code here
	KillTimer(GET_FOCUSER_POSITION);
	KillTimer(CHECK_FOCUSER_MOVING);
}


void CAutoFocusDlg::OnKillfocusEditEndPosition()
{
	// TODO: Add your control notification handler code here
	SetTimer(GET_FOCUSER_POSITION, INTERVAL_GET_FOCUSER_POSITION, NULL);
	SetTimer(CHECK_FOCUSER_MOVING, INTERVAL_CHECK_FOCUSER_MOVING, NULL);
}


void CAutoFocusDlg::OnSetfocusEditStartPosition()
{
	// TODO: Add your control notification handler code here
	KillTimer(GET_FOCUSER_POSITION);
	KillTimer(CHECK_FOCUSER_MOVING);
}


void CAutoFocusDlg::OnKillfocusEditStartPosition()
{
	// TODO: Add your control notification handler code here
	SetTimer(GET_FOCUSER_POSITION, INTERVAL_GET_FOCUSER_POSITION, NULL);
	SetTimer(CHECK_FOCUSER_MOVING, INTERVAL_CHECK_FOCUSER_MOVING, NULL);
}


//add 20171224 sybyeon
void CAutoFocusDlg::OnChangeEditStartPosition()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}


//add 20171224 sybyeon
void CAutoFocusDlg::OnChangeEditEndPosition()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);

}


void CAutoFocusDlg::Wait(DWORD dwMilliSecond) // add 20171227 by Tae-Geun
{
	MSG msg;
	DWORD dwStart;

	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMilliSecond) {

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
