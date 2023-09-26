#include <iostream>
#include<bits/stdc++.h>
using namespace std ;

int key[3][3] ; //Sebagai kunci global batas ordo matriks

int mod26(int x) {
    return x >= 0 ? (x%26) : 26-(abs(x)%26) ; 
}

// Find Determinant Function
int findDeterminant(int m[3][3] , int n){
    int det;
    if(n == 2) {
        det = m[0][0] * m[1][1] - m[0][1]*m[1][0] ;
    }
    else det = 0 ;

    return mod26(det);
}

// Find Inverse Matrix Function
int findDeterminantInverse(int R , int D = 26) {
    int i = 0 ;
    int p[100] = {0,1};
    int q[100] = {0} ;

    while(R!=0) {
        q[i] = D/R ;
        int oldD = D ;
        D = R ;
        R = oldD%R ;
        if(i>1) {
            p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
        }

        i++ ;
    }

    if (i == 1) {
        return 1;
    } 
    else {
        return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
    }
}

// Find GCD Function
int gcd(int m, int n) {
    if (n > m) {
        swap(m,n);
    }
    
    do {
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);
    
    return m;
}

// Multiplying Matrix Function
void multiplyMatrix(int a[1000][3] , int a_rows , int a_cols ,  int b[1000][3] , int b_rows , int b_cols , int res[1000][3]) {
    for(int i=0 ; i < a_rows ; i++) {
        for(int j=0 ; j < b_cols ; j++) {
            for(int k=0 ; k < b_rows ; k++) {
                res[i][j] += a[i][k]*b[k][j] ;
            }
            res[i][j] = mod26(res[i][j]) ;
        }
    }
}

// Find the Key Function
void findKey() {
    string plainteks, cipherteks;
    int key[2][2], det, detInv, adj[2][2], plainteksInv[2][2], plainMatrix[2][2], cipMatrix[2][2], counter;
    int p, c;
    int transpose[2][2];
    
    cout << "Input Plaintext : ";
    cin.ignore();
    getline(cin, plainteks);
    
    // Plaintext assigned to Plainmatrix 
    counter = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            p = toupper(plainteks[counter]) - 65;
            plainMatrix[i][j] = p;
            counter++;
        }
    }
    
    cout << "Input Ciphertext : ";
    getline(cin, cipherteks);
    
    // Ciphertext assigned to Ciphermatrix
    counter = 0;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            c = toupper(cipherteks[counter]) - 65;
            cipMatrix[i][j] = c;
            counter++;
        }
    }
    
    // Determinant
    det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
    if(gcd(det, 26) == 1) {
        detInv = findDeterminantInverse(det, 26);
        
        // Calculate Adjoint
        adj[0][0] = plainMatrix[1][1];
        adj[0][1] = (-1) * plainMatrix[0][1];
        adj[1][0] = (-1) * plainMatrix[1][0];
        adj[1][1] = plainMatrix[0][0];
        
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                plainteksInv[i][j] = detInv * adj[i][j];
                if (plainteksInv[i][j] < 0) {
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
                } else {
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            } 
        }
        
        // Find the Key
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                key [i][j] = 0;
                for(int k = 0; k < 2; k++) {
                    key [i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
                }
                key [i][j] %= 26;
            }
        }
        
 
        for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            transpose[j][i] = key[i][j];
            }
        }
    
        for(int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << (transpose[i][j]) << "\t";
            }
            cout <<endl;
        }       
    } else {
        cout << "Determinant not relative " << endl;
        cout << "Key not found" << endl << endl;
    }
 
}

// Find Inverse Function
void findInverse(int m[3][3] , int n , int m_inverse[3][3] ) {
    int adj[3][3] = {0};

    int det = findDeterminant(m , n);
    int detInverse = findDeterminantInverse(det);

    if(n == 2) {
        adj[0][0] = m[1][1];
        adj[1][1] = m[0][0];
        adj[0][1] = -m[0][1];
        adj[1][0] = -m[1][0];
    }

    for(int i = 0; i < n ; i++) {
        for(int j = 0; j < n ; j++) {
            m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;
        }
    }
}

// Encryption Function
string encrypt(string pt, int n) {
    // C = Cipher, P = Plain
    int P[1000][3] = {0} ;
    int C[1000][3] = {0} ;
    int ptIter = 0  ;

    while(pt.length()%n != 0) {
        pt += "x" ;
    }
    int row = (pt.length())/n;

    for(int i = 0; i < row ; i++) {
        for(int j = 0; j < n; j++) {
            P[i][j] = pt[ptIter++] - 'a' ;
        }
    }

    multiplyMatrix(P, row, n, key, n, n, C) ;

    string ct = "" ;
    for(int i = 0 ; i < row ; i++) {
        for(int j = 0 ; j < n ; j++) {
            ct += (C[i][j] + 'a');
        }
    }

    return ct ;
}

// Decryption Function
string decrypt(string ct, int n) {
    int P[1000][3] = {0} ;
    int C[1000][3] = {0} ;
    int ctIter = 0 ;

    int row = ct.length()/n;

    for(int i = 0; i < row ; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = ct[ctIter++] - 'a' ;
        }
    }

    int k_inverse[3][3] = {0};
    findInverse(key, n, k_inverse);
    multiplyMatrix(C, row, n, k_inverse, n, n, P) ;

    string pt = "" ;
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < n; j++) {
            pt += (P[i][j] + 'a');
        }
    }

    return pt ;
}

int main(void) {
    bool menuActive = true;
    string pt, ct;
    int n ;
    int pilih;

    while(menuActive){
        cout << "Choose : " <<endl;
        cout << "1. Encryption" <<endl;
        cout << "2. Decryption" <<endl;
        cout << "3. Find Key" <<endl;
        cout << "4. Exit" <<endl;
        cin >> pilih;

        switch(pilih) {
            case 1:
                    cout << "Input Text   : ";
                    cin >> pt;
                    
                    cout << "Input Ordo Matrix (2x2) : ";
                    cin >> n;

                    for(int i = 0; i < n; i++) {
                        for(int j = 0; j < n; j++) {
                            cout << "Input Matrix : "; 
                            cin >> key[i][j];
                        }
                    }

                    cout << "\nPlaintext : " << pt << endl;

                    ct = encrypt(pt, n) ;
                    cout << "Encrypted Text : " << ct << endl;

                    break;
            case 2:
                    cout << "Input Text : " ;
                    cin >> ct;
                    
                    cout << "Input Ordo Matrix (2x2) : ";
                    cin >> n ;

                    for(int i = 0; i < n; i++) {
                        for(int j=0; j<n; j++) {
                            cout << "Input Mtarix : "; 
                            cin >> key[i][j];
                        }
                    }
 
                    cout << "\nChipertext  : " << ct << endl;

                    cout << "Decrypted Text : " << decrypt(ct, n) << endl;

                    break;
            case 3:
                    cout << endl;
                    findKey();

                    break;
            default:
                    cout << "\nInvalid" << endl;

                    break;
        }
    }
}