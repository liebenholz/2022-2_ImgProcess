import java.lang.Math;

public class DiscreteCosineTrans {

    public static void main(String[] args) {
        double sq;
        double pi = Math.acos(-1);
        double basisFunc[][] = new double[8][8];

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                // b(x,u) = k(u) * cos[(2x+1)*u*pi/(2*8)]
                // (u = 0) : k(u) = cos(0) / sqrt(8) = 1 / sqrt(8)
                if(i==0) sq = 1 / Math.sqrt(8);
                // (u = 1, 2, ... 7) : k(u) = sqrt(2) / sqrt(8)
                // b(x,u) = cos[(2x+1)u*pi/2*8] / sqrt(8/2) (u=1, 2, ... 7)
                else sq = Math.sqrt(2) / Math.sqrt(8);
                basisFunc[i][j] = Math.cos((2 * j + 1) * i * pi / (2 * 8)) * sq;
            }
        }
        
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                System.out.printf("%.6f ", basisFunc[i][j]);
            }
            System.out.println();
        }
    }
}

