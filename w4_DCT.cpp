void CDIPFWDoc::HOG {
    hog.HOG_Algorithm(m_nHeight, w_nWidth);
}

// Various DIPFW Docs...
// ......

// Discrete Cosine Transformation with Linear Basic Function
void CDIPFWDoc::OnCompressionDCT() {
    int i, j, k, l, m;
    double pi = 3.1416;
    double sum = 0.0;
    double sq;
    double temp[8][8];
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);

    // b(x,u) = b^-1(x,u) = k(u) * cos[(2x+1)u*pi/2N]
    // k(u) = sqrt(1/N) (u=0) , sqrt(2/N) (u=1, 2, ... N-1)
    // N = 8
    double basisFunc[8][8];

    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            // b(x,u) = k(u) * cos[(2x+1)*u*pi/(2*8)]
            // (u = 0) : k(u) = cos(0) / sqrt(8) = 1 / sqrt(8)
            if(i==0) sq = 1 / sqrt(8);
            // (u = 1, 2, ... 7) : k(u) = sqrt(2) / sqrt(8)
            // b(x,u) = cos[(2x+1)u*pi/2*8] / sqrt(8/2) (u=1, 2, ... 7)
            else sq = sqrt(2) / sqrt(8);
            basisFunc[i][j] = cos((2 * j + 1) * i * pi / (2 * 8)) * sq;
        }
    }

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nWidth; j++) {
            sum = 0.0;
            for(k = 0; k < 8; k++) {
                for(l = 0; l < 8; l++) {
                    sum = 0.0;
                    for(m = 0; m < 8; m++) {
                        // F = B * f * Bt
                        // temp = B * f
                        sum += basisFunc[k][m] * m_pImgOpen[m][l];
                    }
                    temp[k][l] = sum;
                }
            }
            sum = 0.0;
            for(k = 0; k < 8; k++) {
                for(l = 0; l < 8; l++) {
                    sum = 0.0;
                    for(m = 0; m < 8; m++) {
                        // F = temp * Bt
                        // Bt[x][y] = B[y][x]
                        sum += temp[k][m] * basisFucn[l][m];
                    }
                    temp[i * 8 + k][j * 8 + l] = sum;
                }
            }
        }
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}

// Inverse Discrete Cosine Transformation with Linear Basic Function
void CDIPFWDoc::OnCompressionIDCT() {
    int i, j;
    BYTE** pImg = CreateResultImage(m_nWidth, m_nHeight);

    // b(x,u) = b^-1(x,u) = k(u) * cos[(2x+1)u*pi/2N]
    // k(u) = sqrt(1/N) (u=0) , sqrt(2/N) (u=1, 2, ... N-1)
    // N = 8
    double basisFunct[8][8];

    for(j = 0; j < 8; j++) {
        // b(x,u) = cos[(2x+1)*u*pi/2*8] / sqrt(8) 
        // (u=0) : cos(0) / sqrt(8) = 1 / sqrt(8)
        basicFunct[0][j] = 1 / sqrt(8);
        for(i = 1;  i< 8; i++) {
            // b(x,u) = cos[(2x+1)u*pi/2*8] / sqrt(8/2) (u=1, 2, ... 7)
            basicFunct[i][j] = (cos(2i+1)*j*pi/16) / 2;
        }
    }

    for(i = 0; i < m_nHeight; i++) {
        for(j = 0; j < m_nWidth; j++) {
            pImg[i][j] += m_pImgOpen[i/8][j] * basicFunct[i%8][j%8];
        }
    }
    MakeNewWindow(pImg, m_nWidth, m_nHeight);
}