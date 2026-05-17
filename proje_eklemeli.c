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

void kitapBilgiYazdir(int i) {
    printf("ISBN: %s\n", kitaplar[i].isbn);
    printf("Ad: %s\n", kitaplar[i].ad);
    printf("Yazar: %s\n", kitaplar[i].yazar);
    printf("Yayinevi: %s\n", kitaplar[i].yayinevi);
    printf("Yil: %d\n", kitaplar[i].yil);
    printf("Stok: %d\n", kitaplar[i].stok);
    printf("Konum: %s\n", kitaplar[i].konum);
    printf("-------------------\n");
}

int isbnIleKitapBul(char isbn[]) {
    for(int i = 0; i < kitapSayisi; i++) {
        if(strcmp(kitaplar[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
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
        printf("Dosya acilamadi. Kaydetme islemi yapilamadi.\n");
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

    if(isbnIleKitapBul(kitaplar[kitapSayisi].isbn) != -1) {
        printf("Bu ISBN numarasina sahip kitap zaten kayitli.\n");
        return;
    }

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
        kitapBilgiYazdir(i);
    }
}

void kitapAra() {
    char aranacak[50];
    int secim, bulundu = 0;

    printf("\nArama kriteri seciniz:\n");
    printf("1- ISBN\n");
    printf("2- Kitap adi\n");
    printf("3- Yazar\n");
    printf("4- Yayinevi\n");
    printf("Secim: ");
    scanf("%d", &secim);
    getchar();

    printf("Aranacak bilgi: ");
    fgets(aranacak, 50, stdin);
    satirSonuTemizle(aranacak);

    for(int i = 0; i < kitapSayisi; i++) {
        if((secim == 1 && strcmp(aranacak, kitaplar[i].isbn) == 0) ||
           (secim == 2 && strstr(kitaplar[i].ad, aranacak) != NULL) ||
           (secim == 3 && strstr(kitaplar[i].yazar, aranacak) != NULL) ||
           (secim == 4 && strstr(kitaplar[i].yayinevi, aranacak) != NULL)) {
            printf("\nKitap bulundu:\n");
            kitapBilgiYazdir(i);
            bulundu = 1;
        }
    }

    if(bulundu == 0) {
        printf("Kitap bulunamadi.\n");
    }
}

void kitapGuncelle() {
    char arananIsbn[20];
    int index;

    printf("\nGuncellenecek kitap ISBN: ");
    fgets(arananIsbn, 20, stdin);
    satirSonuTemizle(arananIsbn);

    index = isbnIleKitapBul(arananIsbn);
    if(index == -1) {
        printf("Kitap bulunamadi.\n");
        return;
    }

    printf("\nMevcut kitap bilgileri:\n");
    kitapBilgiYazdir(index);

    printf("Yeni kitap adi: ");
    fgets(kitaplar[index].ad, 50, stdin);
    satirSonuTemizle(kitaplar[index].ad);

    printf("Yeni yazar: ");
    fgets(kitaplar[index].yazar, 50, stdin);
    satirSonuTemizle(kitaplar[index].yazar);

    printf("Yeni yayinevi: ");
    fgets(kitaplar[index].yayinevi, 50, stdin);
    satirSonuTemizle(kitaplar[index].yayinevi);

    printf("Yeni yayin yili: ");
    scanf("%d", &kitaplar[index].yil);

    printf("Yeni stok: ");
    scanf("%d", &kitaplar[index].stok);
    getchar();

    printf("Yeni konum: ");
    fgets(kitaplar[index].konum, 30, stdin);
    satirSonuTemizle(kitaplar[index].konum);

    dosyayaKaydet();
    printf("Kitap bilgileri guncellendi.\n");
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

void kitapSiralaAdaGore() {
    struct Kitap gecici;

    for(int i = 0; i < kitapSayisi - 1; i++) {
        for(int j = i + 1; j < kitapSayisi; j++) {
            if(strcmp(kitaplar[i].ad, kitaplar[j].ad) > 0) {
                gecici = kitaplar[i];
                kitaplar[i] = kitaplar[j];
                kitaplar[j] = gecici;
            }
        }
    }

    printf("Kitaplar ada gore siralandi.\n");
    kitapListele();
}

void oduncAl() {
    char arananIsbn[20];
    char kullaniciNo[20];
    char tarih[15];
    FILE *dosya;

    printf("\nOdunc alinacak kitap ISBN: ");
    fgets(arananIsbn, 20, stdin);
    satirSonuTemizle(arananIsbn);

    for(int i = 0; i < kitapSayisi; i++) {
        if(strcmp(kitaplar[i].isbn, arananIsbn) == 0) {
            if(kitaplar[i].stok > 0) {
                printf("Kullanici numarasi: ");
                fgets(kullaniciNo, 20, stdin);
                satirSonuTemizle(kullaniciNo);

                printf("Odunc alma tarihi (GG/AA/YYYY): ");
                fgets(tarih, 15, stdin);
                satirSonuTemizle(tarih);

                kitaplar[i].stok--;
                dosyayaKaydet();

                dosya = fopen("odunc_kayitlari.txt", "a");
                if(dosya != NULL) {
                    fprintf(dosya, "%s\t%s\t%s\tIADE_EDILMEDI\n", kullaniciNo, arananIsbn, tarih);
                    fclose(dosya);
                }

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
            printf("Not: Odunc kayitlari dosyasinda iade durumunu final duzenlemesinde ayrica guncelleyebilirsiniz.\n");
            return;
        }
    }
    printf("Kitap bulunamadi.\n");
}

void raporGoster() {
    int toplamStok = 0;
    int stoguBiten = 0;

    for(int i = 0; i < kitapSayisi; i++) {
        toplamStok += kitaplar[i].stok;
        if(kitaplar[i].stok == 0) {
            stoguBiten++;
        }
    }

    printf("\n--- ENVANTER RAPORU ---\n");
    printf("Kayitli kitap turu sayisi: %d\n", kitapSayisi);
    printf("Toplam stok adedi: %d\n", toplamStok);
    printf("Stogu biten kitap turu sayisi: %d\n", stoguBiten);
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
        printf("\nGiris basarili. Yetki: Yonetici\n");
        return 1;
    }

    if(strcmp(kullaniciAdi, "personel") == 0 && strcmp(sifre, "1234") == 0) {
        printf("\nGiris basarili. Yetki: Personel\n");
        return 2;
    }

    if(strcmp(kullaniciAdi, "ogrenci") == 0 && strcmp(sifre, "1234") == 0) {
        printf("\nGiris basarili. Yetki: Ogrenci\n");
        return 3;
    }

    printf("\nHatali giris.\n");
    return 0;
}

int main() {
    int secim;
    int rol;

    dosyadanOku();

    rol = girisYap();
    if(rol == 0) {
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
        printf("7- Kitap Guncelle\n");
        printf("8- Kitaplari Ada Gore Sirala\n");
        printf("9- Rapor Goster\n");
        printf("0- Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);
        getchar();

        if(rol == 3 && !(secim == 2 || secim == 3 || secim == 5 || secim == 0)) {
            printf("Bu islem icin yetkiniz yok.\n");
            continue;
        }

        if(rol == 2 && !(secim == 1 || secim == 2 || secim == 3 || secim == 5 || secim == 6 || secim == 7 || secim == 8 || secim == 0)) {
            printf("Bu islem icin yetkiniz yok.\n");
            continue;
        }

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
            case 7:
                kitapGuncelle();
                break;
            case 8:
                kitapSiralaAdaGore();
                break;
            case 9:
                raporGoster();
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
