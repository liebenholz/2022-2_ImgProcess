// DIPFWDoc.h : CDIPFWDoc Ŭ������ �������̽�
//


#pragma once

typedef unsigned char BYTE;

class CDIPFWDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CDIPFWDoc();
	DECLARE_DYNCREATE(CDIPFWDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();

// �����Դϴ�.
public:
	virtual ~CDIPFWDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int	   getWidth();
	int	   getHeight();
	BYTE*  getOpenImg();
	BYTE** getRGBImg();

	void InitImage();
	void ReadyDisplayImage();
	void CopyClipboard(BYTE* m_pImgSrc, int nWidth, int nHeight);
	BYTE** CreateResultImage(int nWidth, int nHeight);
	void CreateNewImage(BYTE*** pImg, int nWidth, int nHeight);
	void ReleaseImage(BYTE** pImg);
	void MakeNewWindow(BYTE* m_pImgResult, int nWidth, int nHeight);
	void MakeNewWindow(BYTE** m_pImgResult, int nWidth, int nHeight);

protected:
	BYTE*	m_pImgOpen1D;	// 1D open image
	BYTE**  m_pImgOpen;		// 2D open image
	BYTE*	m_pImgResult1D;	// for temporary storing
	BYTE**	m_pImgResult;	// for temporary storing	
	BYTE**	m_pImgRGB;		// for display

	int		m_nWidth;		// image width
	int		m_nHeight;		// image height

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnPointprocessingTestcase();
	afx_msg void OnPointprocessingTestcase32789();
	afx_msg void StoreImg1();
	afx_msg void StoreImg2();
	afx_msg void Moravec();
	afx_msg void HOG();
	afx_msg void OnPointprocessingOninverse();
	afx_msg void OnPointprocessingOnsubtraction();
	afx_msg void OnPointprocessingOnmultiplication();
};


