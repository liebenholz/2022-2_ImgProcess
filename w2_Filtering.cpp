void CDIPFWDoc::HOG {
    hog.HOG_Algorithm(m_nHeight, w_nWidth);
 }

// Various DIPFW Docs...
// ......

// Pixel Grey Level Low Frequency Pass Filter
void CDIPFWDoc::OnFilteringLowPassFilter() {
    int i, j;
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            pImg[i][j] = 0.0;
        }
    }

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            pImg[i][j] += m_pImgOpen[i-1][j-1] / 18  + m_pImgOpen[i-1][j] / 18 + m_pImgOpen[i-1][j+1] / 18
                        + m_pImgOpen[i][j-1] / 18    + m_pImgOpen[i][j] * 5/9  + m_pImgOpen[i][j+1] / 18
                        + m_pImgOpen[i+1][j-1] / 18  + m_pImgOpen[i+1][j] / 18 + m_pImgOpen[i+1][j+1] / 18;
        }
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

// Pixel Grey Level High Frequency Pass Filter
void CDIPFWDoc::OnFilteringLHighPassFilter() {
    int i, j;
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            pImg[i][j] = 0.0;
        }
    }

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            pImg[i][j] += m_pImgOpen[i-1][j-1] * -1/9  + m_pImgOpen[i-1][j] * -1/9 + m_pImgOpen[i-1][j+1] * -1/9
                        + m_pImgOpen[i][j-1] * -1/9    + m_pImgOpen[i][j] * 8/9    + m_pImgOpen[i][j+1] * -1/9
                        + m_pImgOpen[i+1][j-1] * -1/9  + m_pImgOpen[i+1][j] * -1/9 + m_pImgOpen[i+1][j+1] * -1/9;
        }
    }

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nWidth; j++) {
            if(pImg[i][j] < 0 ) pImg[i][j] = -pImg[i][j];
        }
    }

    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

// Create Grey Level Pixel Salt and Pepper Noise 
void CDIPFWDoc::OnFilteringLOnImpulseNoise() {
    int i, j, k;
	BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);
	int image_size = m_nWidth * m_nHeight;

	// Impulse Amount
	float amount = 0.05;
	srand((int)time(NULL));

    // Copy Input Image First 
    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nWidth; j++) {
            pImg[i][j] = m_pImgOpen[i][j];
        }
    }

    // Salt and Pepper 
    for(k = 0; k < image_size * amount; k++) {
        i = rand() % m_nHeight;
        j = rand() % m_nWidth;
        pImg[i][j]= (rand()%2) * 255;
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}



// Pixel Grey Level Median Filter processing with 3*3 Filter
void CDIPFWDoc::OnFilteringMedianFilter() {
    int i, j;
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);
    BYTE median[9];

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            pImg[i][j] = 0.0;
        }
    }

    for(i = 1; i < m_nHeight-1; i++) {
        for(j = 1; j < m_nWidth-1; j++) {
            median[0] = m_pImgOpen[i-1][j-1]; median[1] = m_pImgOpen[i-1][j]; median[2] = m_pImgOpen[i-1][j+1];
            median[3] = m_pImgOpen[i][j-1];   median[4] = m_pImgOpen[i][j];   median[5] = m_pImgOpen[i][j+1];
            median[6] = m_pImgOpen[i+1][j-1]; median[7] = m_pImgOpen[i+1][j]; median[8] = m_pImgOpen[i+1][j+1];

            std::sort(median, median + 9);
            pImg[i][j] += median[4];
        }
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

