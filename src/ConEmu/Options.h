
#pragma once

class CSettings
{
public:
    CSettings();
    ~CSettings();

    TCHAR Config[MAX_PATH];

    int DefaultBufferHeight; bool ForceBufferHeight; bool AutoScroll;
    
	LONG FontWidth();
	LONG FontHeight();
	BYTE FontCharSet();
private:
    LOGFONT LogFont, LogFont2;
public:
	wchar_t FontFile[MAX_PATH];
	LOGFONT ConsoleFont;
    COLORREF Colors[0x20];
    bool isExtendColors;
    char nExtendColor;

    /* Background image */
    WCHAR sBgImage[MAX_PATH];
    char isShowBgImage;
	bool isBackgroundImageValid;
	u8 bgImageDarker;

    /* Command Line (Registry) */
    LPTSTR psCmd;
    /* Command Line ("/cmd" arg) */
    LPTSTR psCurCmd;
	private:
	/* 'Default' command line (if nor Registry, nor /cmd specified) */
	WCHAR  szDefCmd[10];
	public:
    /* "Active" command line */
    LPCTSTR GetCmd();
	/* "Default" command line "far/cmd", based on /BufferHeight switch */
	LPCTSTR GetDefaultCmd();
    /* OUR(!) startup info */
    STARTUPINFOW ourSI;
    /* If Attach to PID requested */
    DWORD nAttachPID; HWND hAttachConWnd;

    DWORD FontSizeX;
    DWORD FontSizeX2;
    DWORD FontSizeX3;
    bool isFullScreen;
    char isFixFarBorders;
	struct tag_CharRanges {
		bool bUsed;
		wchar_t cBegin, cEnd;
	} icFixFarBorderRanges[10];
    BYTE isPartBrush75, isPartBrush50, isPartBrush25;
    bool isCursorV;
	bool isCursorBlink;
    bool isCursorColor;
    char isRClickSendKey;
    wchar_t *sRClickMacro;
    bool isSentAltEnter;
    bool isMinToTray;
    bool isForceMonospace, isProportional;
    bool isUpdConHandle;
	bool isRSelFix;
    BYTE isDragEnabled;
    BYTE isDropEnabled;
    DWORD nLDragKey, nRDragKey;
    bool isDefCopy;
    bool isDnDsteps;
    bool isGUIpb;
    char isTabs; bool isTabSelf, isTabRecent, isTabLazy;
	wchar_t *sTabCloseMacro;
    DWORD wndWidth, wndHeight, ntvdmHeight; // � ��������
    int wndX, wndY; // � ��������
    bool wndCascade;
    DWORD nSlideShowElapse;
    DWORD nIconID;
    bool isTryToCenter;
    RECT rcTabMargins;
    bool isTabFrame;
    bool isMulti; BYTE icMultiNew, icMultiNext, icMultiRecreate; bool isMultiNewConfirm;

    // ��������� �����
    WCHAR szTabConsole[32];
    WCHAR szTabEditor[32];
    WCHAR szTabEditorModified[32];
    WCHAR szTabViewer[32];
    DWORD nTabLenMax;

    bool isVisualizer;
    char nVizNormal, nVizFore, nVizTab, nVizEOL, nVizEOF;
    wchar_t cVizTab, cVizEOL, cVizEOF;

    char isAllowDetach;
    bool isCreateAppWindow; 
    bool isScrollTitle;
    DWORD ScrollTitleLen;
    
    UINT nMainTimerElapse; // �������������, � ������� �� ������� ����������� �����
    //bool isAdvLangChange; // � ����� ��� ConIme � ����� ������� �� �������� ����, ���� �� ������� WM_SETFOCUS. �� ��� ���� �������� ������ �������� ������
    bool isSkipFocusEvents;
    //bool isLangChangeWsPlugin;
	char isMonitorConsoleLang;
    
    DWORD nAffinity;

	// Debugging - "c:\\temp\\ConEmuVCon-%i-%i.dat"
	BYTE isAdvLogging;
	//wchar_t szDumpPackets[MAX_PATH];
	// Debugging
	bool isConVisible;
    
    // Working variables...
    HBITMAP hBgBitmap;
    COORD   bgBmp;
    HDC     hBgDc;
    HFONT   mh_Font, mh_Font2;
    WORD    CharWidth[0x10000]; //, Font2Width[0x10000];

    HWND hMain, hColors, hInfo;

    bool LoadImageFrom(TCHAR *inPath, bool abShowErrors=false);
    static BOOL CALLBACK wndOpProc(HWND hWnd2, UINT messg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK mainOpProc(HWND hWnd2, UINT messg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK colorOpProc(HWND hWnd2, UINT messg, WPARAM wParam, LPARAM lParam);
    static BOOL CALLBACK infoOpProc(HWND hWnd2, UINT messg, WPARAM wParam, LPARAM lParam);
    void LoadSettings();
    void InitSettings();
    BOOL SaveSettings();
    bool ShowColorDialog(HWND HWndOwner, COLORREF *inColor);
    static BOOL CALLBACK EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, LPVOID aFontCount);
    void UpdateMargins(RECT arcMargins);
    static void Dialog();
    void UpdatePos(int x, int y);
    void UpdateSize(UINT w, UINT h);
    void UpdateTTF(BOOL bNewTTF);
    void Performance(UINT nID, BOOL bEnd);
	void SetArgBufferHeight(int anBufferHeight);
	void InitFont(LPCWSTR asFontName=NULL, int anFontHeight=-1, int anQuality=-1);
protected:
    LRESULT OnInitDialog();
	LRESULT OnInitDialog_Main();
	LRESULT OnInitDialog_Color();
	LRESULT OnInitDialog_Info();
    LRESULT OnButtonClicked(WPARAM wParam, LPARAM lParam);
    LRESULT OnColorButtonClicked(WPARAM wParam, LPARAM lParam);
    LRESULT OnEditChanged(WPARAM wParam, LPARAM lParam);
    LRESULT OnColorEditChanged(WPARAM wParam, LPARAM lParam);
    LRESULT OnComboBox(WPARAM wParam, LPARAM lParam);
    LRESULT OnColorComboBox(WPARAM wParam, LPARAM lParam);
    LRESULT OnTab(LPNMHDR phdr);
private:
    COLORREF acrCustClr[16]; // array of custom colors
    BOOL mb_IgnoreEditChanged, mb_IgnoreTtfChange;
    i64 mn_Freq;
    i64 mn_FPS[20]; int mn_FPS_CUR_FRAME;
    i64 mn_Counter[tPerfInterval-gbPerformance];
    i64 mn_CounterMax[tPerfInterval-gbPerformance];
    DWORD mn_CounterTick[tPerfInterval-gbPerformance];
    HWND hwndTip;
    void RegisterTipsFor(HWND hChildDlg);
    HFONT CreateFontIndirectMy(LOGFONT *inFont);
	void RecreateFont(WORD wFromID);
    // Theming
    HMODULE mh_Uxtheme;
    typedef HRESULT (STDAPICALLTYPE *SetWindowThemeT)(HWND hwnd,LPCWSTR pszSubAppName,LPCWSTR pszSubIdList);
    SetWindowThemeT SetWindowThemeF;
    typedef HRESULT (STDAPICALLTYPE *EnableThemeDialogTextureT)(HWND hwnd,DWORD dwFlags);
    EnableThemeDialogTextureT EnableThemeDialogTextureF;
	UINT mn_MsgUpdateCounter;
	//wchar_t temp[MAX_PATH];
	UINT mn_MsgRecreateFont;
	int IsChecked(HWND hParent, WORD nCtrlId);
	int GetNumber(HWND hParent, WORD nCtrlId);
	int SelectString(HWND hParent, WORD nCtrlId, LPCWSTR asText);
	int SelectStringExact(HWND hParent, WORD nCtrlId, LPCWSTR asText);
	BOOL mb_TabHotKeyRegistered;
	void RegisterTabs();
	void UnregisterTabs();
	static DWORD CALLBACK EnumFontsThread(LPVOID apArg);
	HANDLE mh_EnumThread;
	WORD mn_LastChangingFontCtrlId;
};
