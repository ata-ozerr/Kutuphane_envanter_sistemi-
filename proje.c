#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Kitap {
    char isbn[20];
    char ad[50];
    char yazar[50];
    char yayinevi[50];
    int yil;
    int stok;
    char konum[30];
};

struct Kitap kitaplar[MAX];
int kitapSayisi = 0;

void satirSonuTemizle(char *str) {
    size_t uzunluk = strlen(str);
    if (uzunluk > 0 && str[uzunluk - 1] == '\n') {
        str[uzunluk - 1] = '\0';
    }
}

void dosyadanOku() {
    FILE *dosya;
    dosya = fopen("kitaplar.txt", "r");

    if(dosya == NULL) {
        return;
    }

    while(fscanf(dosya, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d\t%[^\n]\n",
                  kitaplar[kitapSayisi].isbn,
                  kitaplar[kitapSayisi].ad,
                  kitaplar[kitapSayisi].yazar,
                  kitaplar[kitapSayisi].yayinevi,
                  &kitaplar[kitapSayisi].yil,
                  &kitaplar[kitapSayisi].stok,
                  kitaplar[kitapSayisi].konum) == 7) {

        kitapSayisi++;
        if (kitapSayisi >= MAX) break;
    }

    fclose(dosya);
}

void dosyayaKaydet() {
    FILE *dosya;
    dosya = fopen("kitaplar.txt", "w");

    if(dosya == NULL) {
        return;
    }

    for(int i = 0; i < kitapSayisi; i++) {
        fprintf(dosya, "%s\t%s\t%s\t%s\t%d\t%d\t%s\n",
                kitaplar[i].isbn,
                kitaplar[i].ad,
                kitaplar[i].yazar,
                kitaplar[i].yayinevi,
                kitaplar[i].yil,
                kitaplar[i].stok,
                kitaplar[i].konum);
    }

    fclose(dosya);
}

void kitapEkle() {
    if (kitapSayisi >= MAX) {
        printf("\nDaha fazla kitap eklenemez.\n");
        return;
    }

    printf("\nISBN: ");
    fgets(kitaplar[kitapSayisi].isbn, 20, stdin);
    satirSonuTemizle(kitaplar[kitapSayisi].isbn);

    printf("Kitap adi: ");
    fgets(kitaplar[kitapSayisi].ad, 50, stdin);
    satirSonuTemizle(kitaplar[kitapSayisi].ad);

    printf("Yazar: ");
    fgets(kitaplar[kitapSayisi].yazar, 50, stdin);
    satirSonuTemizle(kitaplar[kitapSayisi].yazar);

    printf("Yayinevi: ");
    fgets(kitaplar[kitapSayisi].yayinevi, 50, stdin);
    satirSonuTemizle(kitaplar[kitapSayisi].yayinevi);

    printf("Yayin yili: ");
    scanf("%d", &kitaplar[kitapSayisi].yil);

    printf("Stok: ");
    scanf("%d", &kitaplar[kitapSayisi].stok);
    getchar();

    printf("Konum: ");
    fgets(kitaplar[kitapSayisi].konum, 30, stdin);
    satirSonuTemizle(kitaplar[kitapSayisi].konum);

    kitapSayisi++;
    dosyayaKaydet();
    printf("Kitap eklendi.\n");
}

void kitapListele() {
    if(kitapSayisi == 0) {
        printf("\nKayitli kitap yok.\n");
        return;
    }

    printf("\n--- KITAP LISTESI ---\n");
    for(int i = 0; i < kitapSayisi; i++) {
        printf("ISBN: %s\n", kitaplar[i].isbn);
        printf("Ad: %s\n", kitaplar[i].ad);
        printf("Yazar: %s\n", kitaplar[i].yazar);
        printf("Yayinevi: %s\n", kitaplar[i].yayinevi);
        printf("Yil: %d\n", kitaplar[i].yil);
        printf("Stok: %d\n", kitaplar[i].stok);
        printf("Konum: %s\n", kitaplar[i].konum);
        printf("-------------------\n");
    }
}

void kitapAra() {
    char aranacak[50];
    int bulundu = 0;

    printf("\nAranacak kitap adi: ");
    fgets(aranacak, 50, stdin);
    satirSonuTemizle(aranacak);

    for(int i = 0; i < kitapSayisi; i++) {
        if(strcmp(aranacak, kitaplar[i].ad) == 0) {
            printf("\nKitap bulundu\n");
            printf("ISBN: %s\n", kitaplar[i].isbn);
            printf("Ad: %s\n", kitaplar[i].ad);
            printf("Yazar: %s\n", kitaplar[i].yazar);
            printf("Yayinevi: %s\n", kitaplar[i].yayinevi);
            printf("Yil: %d\n", kitaplar[i].yil);
            printf("Stok: %d\n", kitaplar[i].stok);
            printf("Konum: %s\n", kitaplar[i].konum);
            bulundu = 1;
        }
    }

    if(bulundu == 0) {
        printf("Kitap bulunamadi.\n");
    }
}

void kitapSil() {
    char arananIsbn[20];

    printf("\nSilinecek kitap ISBN: ");
    fgets(arananIsbn, 20, stdin);
    satirSonuTemizle(arananIsbn);

    for(int i = 0; i < kitapSayisi; i++) {
        if(strcmp(kitaplar[i].isbn, arananIsbn) == 0) {
            for(int j = i; j < kitapSayisi - 1; j++) {
                kitaplar[j] = kitaplar[j + 1];
            }
            kitapSayisi--;
            dosyayaKaydet();
            printf("Kitap silindi.\n");
            return;
        }
    }
    printf("Kitap bulunamadi.\n");
}

void oduncAl() {
    char arananIsbn[20];

    printf("\nOdunc alinacak kitap ISBN: ");
    fgets(arananIsbn, 20, stdin);
    satirSonuTemizle(arananIsbn);

    for(int i = 0; i < kitapSayisi; i++) {
        if(strcmp(kitaplar[i].isbn, arananIsbn) == 0) {
            if(kitaplar[i].stok > 0) {
                kitaplar[i].stok--;
                dosyayaKaydet();
                printf("Kitap odunc alindi. Kalan Stok: %d\n", kitaplar[i].stok);
            } else {
                printf("Kitap stokta yok.\n");
            }
            return;
        }
    }
    printf("Kitap bulunamadi.\n");
}

void iadeEt() {
    char arananIsbn[20];

    printf("\nIade edilecek kitap ISBN: ");
    fgets(arananIsbn, 20, stdin);
    satirSonuTemizle(arananIsbn);

    for(int i = 0; i < kitapSayisi; i++) {
        if(strcmp(kitaplar[i].isbn, arananIsbn) == 0) {
            kitaplar[i].stok++;
            dosyayaKaydet();
            printf("Kitap iade edildi. Yeni Stok: %d\n", kitaplar[i].stok);
            return;
        }
    }
    printf("Kitap bulunamadi.\n");
}

int girisYap() {
    char kullaniciAdi[20];
    char sifre[20];

    printf("\n===== KULLANICI GIRISI =====\n");
    printf("Kullanici adi: ");
    scanf("%s", kullaniciAdi);

    printf("Sifre: ");
    scanf("%s", sifre);
    getchar();

    if(strcmp(kullaniciAdi, "admin") == 0 && strcmp(sifre, "1234") == 0) {
        printf("\nGiris basarili.\n");
        return 1;
    }

    printf("\nHatali giris.\n");
    return 0;
}

int main() {
    int secim;

    dosyadanOku();

    if(girisYap() == 0) {
        return 0;
    }

    while(1) {
        printf("\n===== KUTUPHANE SISTEMI =====\n");
        printf("1- Kitap Ekle\n");
        printf("2- Kitap Listele\n");
        printf("3- Kitap Ara\n");
        printf("4- Kitap Sil\n");
        printf("5- Odunc Al\n");
        printf("6- Iade Et\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);
        getchar();

        switch(secim) {
            case 1:
                kitapEkle();
                break;
            case 2:
                kitapListele();
                break;
            case 3:
                kitapAra();
                break;
            case 4:
                kitapSil();
                break;
            case 5:
                oduncAl();
                break;
            case 6:
                iadeEt();
                break;
            case 0:
                printf("Program kapatildi.\n");
                return 0;
            default:
                printf("Gecersiz secim.\n");
        }
    }
    return 0;
}