//
// Created by DerikZS on 06/04/2026.
//

#ifndef LAB01_2025_1_ZS_SOBRECARGA_H
#define LAB01_2025_1_ZS_SOBRECARGA_H

void operator! (CadenaDeCaracteres &cadena);
void operator <= (CadenaDeCaracteres &cadena, const char *cad);
void operator <= (CadenaDeCaracteres &cadena, int num);
void operator <= (CadenaDeCaracteres &cadena1, CadenaDeCaracteres &cadena2);
bool operator += (CadenaDeCaracteres &cadena,char *cad);

#endif //LAB01_2025_1_ZS_SOBRECARGA_H