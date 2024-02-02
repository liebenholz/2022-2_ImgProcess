void CDIPFWDoc::HOG {
    hog.HOG_Algorithm(m_nHeight, w_nWidth);
 }

// Various DIPFW Docs...
// ......

// Pixel Grey Level Inverse
void CDIPFWDoc::OnPointprocessingOnInverse() {
    int i, j;
    BYTE** plmg = CreateResultImage(m_nWidth, M_nheight);

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nwidth; j++) {
            plmg[i][j] = 255 - m_pImgOpen[i][j];
        }
    }
    MakeNewWindow(plmg, m_nWidth, m_nHeight);
}

// Pixel Grey Level 50 Darker
void CDIPFWDoc::OnPointprocessingOnSubtraction() {
    int i, j;
    BYTE** plmg = CreateResultImage(m_nWidth, M_nheight);

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nwidth; j++) {
            plmg[i][j] = (m_pImgOpen[i][j] - 50 < 0) ? 0 : m_pImgOpen[i][j] - 50;
        }
    }
    MakeNewWindow(plmg, m_nWidth, m_nHeight);
}

// Pixel Grey Level 1.2 times Brighter
void CDIPFWDoc::OnPointprocessingOnMultiplication() {
    int i, j;
    BYTE** plmg = CreateResultImage(m_nWidth, M_nheight);

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nwidth; j++) {
            plmg[i][j] = (m_pImgOpen[i][j] * 1.2 > 255) ? 255 : m_pImgOpen[i][j] * 1.2;
        }
    }
    MakeNewWindow(plmg, m_nWidth, m_nHeight);
}