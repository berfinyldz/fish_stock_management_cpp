#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <locale.h>

using namespace std;

#define mavi "\033[38;2;0;150;255m"
#define kirmizi "\033[38;2;255;0;0m"
#define reset "\033[0m"

struct node {
	int balikid;
	char baliktur[50];
	int balikstok;
	float balikfiyat;
	node* next;
};

node* head = NULL;

int iduret()
{
	int id;
	bool var;

	do
	{
		var = false;
		id = rand() % 1000;

		node* temp = head;

		while (temp != NULL)
		{
			if (temp->balikid == id)
			{
				var = true;
				break;
			}

			temp = temp->next;
		}

	} while (var);

	return id;
}

void dosyadanal()
{
	ifstream oku("balik.dat", ios::binary);

	if (!oku)
	{
		return;
	}

	node veri;

	while (oku.read((char*)&veri, sizeof(node)))
	{
		node* yeni = new node;

		*yeni = veri;
		yeni->next = NULL;

		if (head == NULL)
		{
			head = yeni;
		}
		else
		{
			node* temp = head;

			while (temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = yeni;
		}
	}

	oku.close();
}

void dosyayaaktar()
{
	ofstream yaz("balik.dat", ios::binary);

	node* temp = head;

	while (temp != NULL)
	{
		node veri = *temp;

		yaz.write((char*)&veri, sizeof(node));

		temp = temp->next;
	}

	yaz.close();
}

void balikekle()
{
	node* yeni = new node;

	yeni->balikid = iduret();

	cout << "Balýk Türü: ";
	cin >> yeni->baliktur;

	cout << "Stok: ";
	cin >> yeni->balikstok;

	cout << "Fiyat: ";
	cin >> yeni->balikfiyat;

	yeni->next = NULL;

	if (head == NULL)
	{
		head = yeni;
	}
	else
	{
		node* temp = head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = yeni;
	}

	dosyayaaktar();

	cout << "\nBalýk eklendi!\n\n";
}

void baliklistele()
{
	if (head == NULL)
	{
		cout << "Liste boþ!\n\n";
		return;
	}

	node* temp = head;

	while (temp != NULL)
	{
		cout << "ID: " << temp->balikid
			<< " | Tür: " << temp->baliktur
			<< " | Stok: " << temp->balikstok
			<< " | Fiyat: " << temp->balikfiyat
			<< endl;

		temp = temp->next;
	}

	cout << endl;
}

void balikara()
{
	int id;
	bool bulundu = false;

	cout << "Aranacak Balýk ID: ";
	cin >> id;

	node* temp = head;

	while (temp != NULL)
	{
		if (temp->balikid == id)
		{
			cout << "\nKayýt Bulundu!\n";

			cout << "ID: " << temp->balikid
				<< " | Tür: " << temp->baliktur
				<< " | Stok: " << temp->balikstok
				<< " | Fiyat: " << temp->balikfiyat
				<< endl << endl;

			bulundu = true;
			break;
		}

		temp = temp->next;
	}

	if (bulundu == false)
	{
		cout << "\nBalýk bulunamadý!\n\n";
	}
}

void balikguncelle()
{
	int id;
	bool bulundu = false;

	cout << "Güncellenecek ID: ";
	cin >> id;

	node* temp = head;

	while (temp != NULL)
	{
		if (temp->balikid == id)
		{
			cout << "Yeni stok: ";
			cin >> temp->balikstok;

			cout << "Yeni fiyat: ";
			cin >> temp->balikfiyat;

			dosyayaaktar();

			cout << "\nBilgiler güncellendi!\n\n";

			bulundu = true;
			break;
		}

		temp = temp->next;
	}

	if (bulundu == false)
	{
		cout << "\nBalýk bulunamadý!\n\n";
	}
}

void baliksil()
{
	int id;
	bool bulundu = false;

	cout << "Silinecek ID: ";
	cin >> id;

	node* temp = head;
	node* onceki = NULL;

	while (temp != NULL)
	{
		if (temp->balikid == id)
		{
			if (onceki == NULL)
			{
				head = temp->next;
			}
			else
			{
				onceki->next = temp->next;
			}

			delete temp;

			dosyayaaktar();

			cout << "\nBalýk silindi!\n\n";

			bulundu = true;
			break;
		}

		onceki = temp;
		temp = temp->next;
	}

	if (bulundu == false)
	{
		cout << "\nBalýk bulunamadý!\n\n";
	}
}
int main()
{
	setlocale(LC_ALL, "Turkish");
	dosyadanal();

	char secim;

	do
	{
		cout << mavi << "==========================" << reset << endl;
		cout << mavi << "   BALIK OTOMASYONU" << reset << endl;
		cout << mavi << "==========================" << reset << endl;

		cout << "1- Kayýt Ekle\n";
		cout << "2- Kayýt Listele\n";
		cout << "3- Kayýt Güncelle\n";
		cout << "4- Kayýt Sil\n";
		cout << "5- Kayýt Ara\n";
		cout << "6- Çýkýþ\n";

		cout << "\nSeçim: ";

		secim = _getche();

		system("cls");

		switch (secim)
		{
		case '1':
			balikekle();
			break;

		case '2':
			baliklistele();
			break;

		case '3':
			balikguncelle();
			break;

		case '4':
			baliksil();
			break;

		case '5':
			balikara();
			break;

		case '6':
			cout << "Program kapatýlýyor...";
			break;

		default:
			cout << "Hatalý seçim!\n\n";
		}

	} while (secim != '6');

	return 0;
}