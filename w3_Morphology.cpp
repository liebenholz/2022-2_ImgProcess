void CDIPFWDoc::HOG {
    hog.HOG_Algorithm(m_nHeight, w_nWidth);
 }

// Various DIPFW Docs...
// ......

// Pixel Grey Level Erosion with 3*3 Filter
void CDIPFWDoc::OnMorphologyErosion() {
    int i, j;
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);
    BYTE erosion[9];

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nWidth; j++) {
            pImg[i][j] = 0;
        }
    }

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            erosion[0] = m_pImgOpen[i-1][j-1]; erosion[1] = m_pImgOpen[i-1][j]; erosion[2] = m_pImgOpen[i-1][j+1];
            erosion[3] = m_pImgOpen[i][j-1];   erosion[4] = m_pImgOpen[i][j];   erosion[5] = m_pImgOpen[i][j+1];
            erosion[6] = m_pImgOpen[i+1][j-1]; erosion[7] = m_pImgOpen[i+1][j]; erosion[8] = m_pImgOpen[i+1][j+1];

            std::sort(erosion, erosion + 9);
            pImg[i][j] += erosion[0];
        }
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

// Pixel Grey Level Dilation with 3*3 Filter
void CDIPFWDoc::OnMorphologyDilation() {
    int i, j;
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);
    BYTE dilation[9]; BYTE erosion[9];

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nWidth; j++) {
            pImg[i][j] = 0;
        }
    }

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            dilation[0] = m_pImgOpen[i-1][j-1]; dilation[1] = m_pImgOpen[i-1][j]; dilation[2] = m_pImgOpen[i-1][j+1];
            dilation[3] = m_pImgOpen[i][j-1];   dilation[4] = m_pImgOpen[i][j];   dilation[5] = m_pImgOpen[i][j+1];
            dilation[6] = m_pImgOpen[i+1][j-1]; dilation[7] = m_pImgOpen[i+1][j]; dilation[8] = m_pImgOpen[i+1][j+1];

            std::sort(dilation, dilation + 9);
            pImg[i][j] += dilation[8];
        }
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

// Pixel Grey Level Opening with 3*3 Filter
// Opening : Dilation of Erosion
void CDIPFWDoc::OnMorphologyOpening() {
    int i, j;
	BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);
	BYTE temp[256][256];
	BYTE erosion[9]; BYTE dilation[9];


	for (i = 0; i < m_nHeight; i++) {
		for (j = 0; j < m_nWidth; j++) {
			pImg[i][j] = 0;
		}
	}

	// Erosion 
	for (i = 1; i < m_nHeight - 1; i++) {
		for (j = 1; j < m_nWidth - 1; j++) {
			erosion[0] = m_pImgOpen[i - 1][j - 1]; erosion[1] = m_pImgOpen[i - 1][j]; erosion[2] = m_pImgOpen[i - 1][j + 1];
			erosion[3] = m_pImgOpen[i][j - 1];     erosion[4] = m_pImgOpen[i][j];     erosion[5] = m_pImgOpen[i][j + 1];
			erosion[6] = m_pImgOpen[i + 1][j - 1]; erosion[7] = m_pImgOpen[i + 1][j]; erosion[8] = m_pImgOpen[i + 1][j + 1];

			std::sort(erosion, erosion + 9);
			temp[i][j] = erosion[0];
		}
	}

	// Dilation
	for (i = 2; i < m_nHeight - 2; i++) {
		for (j = 2; j < m_nWidth - 2; j++) {
			dilation[0] = temp[i - 1][j - 1]; dilation[1] = temp[i - 1][j]; dilation[2] = temp[i - 1][j + 1];
			dilation[3] = temp[i][j - 1];     dilation[4] = temp[i][j];     dilation[5] = temp[i][j + 1];
			dilation[6] = temp[i + 1][j - 1]; dilation[7] = temp[i + 1][j]; dilation[8] = temp[i + 1][j + 1];

			std::sort(dilation, dilation + 9);
			pImg[i][j] = dilation[8];
		}
	}
	MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

// Pixel Grey Level Closing with 3*3 Filter
// Closing : Erosion of Dilation 
void CDIPFWDoc::OnMorphologyClosing() {
    int i, j;
	BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);
	BYTE temp[256][256];
	BYTE erosion[9]; BYTE dilation[9];

	for (i = 0; i < m_nHeight; i++) {
		for (j = 0; j < m_nWidth; j++) {
			pImg[i][j] = 0;
		}
	}

	// Dilation 
	for (i = 1; i < m_nHeight - 1; i++) {
		for (j = 1; j < m_nWidth - 1; j++) {
			dilation[0] = m_pImgOpen[i - 1][j - 1]; dilation[1] = m_pImgOpen[i - 1][j]; dilation[2] = m_pImgOpen[i - 1][j + 1];
			dilation[3] = m_pImgOpen[i][j - 1];     dilation[4] = m_pImgOpen[i][j];     dilation[5] = m_pImgOpen[i][j + 1];
			dilation[6] = m_pImgOpen[i + 1][j - 1]; dilation[7] = m_pImgOpen[i + 1][j]; dilation[8] = m_pImgOpen[i + 1][j + 1];

			std::sort(dilation, dilation + 9);
			temp[i][j] = dilation[8];
		}
	}

	// Erosion
	for (i = 2; i < m_nHeight - 2; i++) {
		for (j = 2; j < m_nWidth - 2; j++) {
			erosion[0] = temp[i - 1][j - 1]; erosion[1] = temp[i - 1][j]; erosion[2] = temp[i - 1][j + 1];
			erosion[3] = temp[i][j - 1];     erosion[4] = temp[i][j];     erosion[5] = temp[i][j + 1];
			erosion[6] = temp[i + 1][j - 1]; erosion[7] = temp[i + 1][j]; erosion[8] = temp[i + 1][j + 1];

			std::sort(erosion, erosion + 9);
			pImg[i][j] = erosion[0];
		}
	}
	MakeNewWindow(pImg, m_nWidth, m_nHeight);
}