# Kütüphane Envanter Yönetim Sistemi

Bu proje, kütüphanelerde bulunan kitapların, kullanıcıların ve ödünç alma-iade işlemlerinin bilgisayar ortamında yönetilmesi amacıyla geliştirilmiştir. Sistem C programlama dili kullanılarak hazırlanmıştır.

## Projenin Amacı

Projenin amacı, kütüphane envanterinin düzenli bir şekilde takip edilmesini sağlamaktır. Sistem sayesinde kitap ekleme, silme, güncelleme, listeleme, arama, ödünç alma, iade etme ve raporlama işlemleri yapılabilmektedir.

## Proje Kapsamı

Bu sistemde kitap bilgileri, kullanıcı rolleri ve ödünç alma işlemleri yönetilmektedir. Kitaplara ait ISBN, kitap adı, yazar, yayınevi, yayın yılı, stok ve konum bilgileri tutulmaktadır. Ayrıca kullanıcı türlerine göre yetkilendirme yapılmaktadır.

## Kullanılan Teknolojiler

- C programlama dili
- Dosya işlemleri
- Struct veri yapısı
- Temel sıralama ve arama işlemleri
- GitHub sürüm kontrol sistemi

## Kullanıcı Rolleri

Sistemde üç farklı kullanıcı rolü bulunmaktadır:

### Yönetici

Yönetici sistemdeki tüm işlemleri gerçekleştirebilir.

Yetkileri:

- Kitap ekleme
- Kitap silme
- Kitap güncelleme
- Kitap listeleme
- Kitap arama
- Ödünç alma
- İade etme
- Kitapları sıralama
- Envanter raporu görüntüleme

### Personel

Personel, kitap ve ödünç işlemlerinin büyük kısmını gerçekleştirebilir.

Yetkileri:

- Kitap ekleme
- Kitap güncelleme
- Kitap listeleme
- Kitap arama
- Ödünç alma
- İade etme
- Kitapları sıralama

### Öğrenci

Öğrenci sınırlı yetkiye sahiptir.

Yetkileri:

- Kitap listeleme
- Kitap arama
- Ödünç alma

## Giriş Bilgileri

Programda örnek kullanıcı girişleri aşağıdaki gibidir:

```text
Yönetici:
Kullanıcı adı: admin
Şifre: 1234

Personel:
Kullanıcı adı: personel
Şifre: 1234

Öğrenci:
Kullanıcı adı: ogrenci
Şifre: 1234
