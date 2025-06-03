#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

template<typename K, typename V>
class HashNode {
public:
	K key;
	V value;
	bool usuniety;
	HashNode(K k, V v) : key(k), value(v), usuniety(false) {}
};


template<typename K, typename V>
class HashTable {
private:
	HashNode<K, V>** table;
	unsigned int capacity;
	unsigned int size;
	float loadFactor;
	float maxLoadFactor;
public:
	HashTable(unsigned int cap, float maxLoad = 0.8) : capacity(cap), size(0), maxLoadFactor(maxLoad), loadFactor(0.0f) {
		table = new HashNode<K, V>* [capacity];
		for (unsigned int i = 0; i < capacity; ++i) {
			table[i] = nullptr;
		}
	}
	~HashTable() {
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr) {
				delete table[i];
			}
		}
		delete[] table;
	}
	unsigned int hashFunction1(K key, unsigned int cap) {
		return key % cap;
	}

	unsigned int hashFunction2(K key, unsigned int cap) {
		if (size == 0) return key % cap; // lub inna prosta funkcja
		unsigned int denom = (size / cap);
		if (denom == 0) denom = 1;
		return (int)(((int)(loadFactor * key) % size) / (float)denom) % cap;
	}

	unsigned int hashFunction3(K key, unsigned int cap) {
		unsigned int temp = key, hash = 0;
		while (temp != 0) {
			hash += temp % 10;
			temp /= 10;
		}
		return hash % cap;
	}
	void resizeAndReHash1() {
		unsigned int newCapacity = capacity * 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr) {
				unsigned int index = hashFunction1(table[i]->key, newCapacity);
				while (newTable[index] != nullptr) {
					index = (index + 1) % newCapacity;
				}
				newTable[index] = table[i];
			}
		}
		delete[] table;
		table = newTable;
		capacity = newCapacity;
	}
	void resizeAndReHash2() {
		unsigned int newCapacity = capacity * 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr) {
				unsigned int index = hashFunction2(table[i]->key, newCapacity);
				while (newTable[index] != nullptr) {
					index = (index + 1) % newCapacity;
				}
				newTable[index] = table[i];
			}
		}
		delete[] table;
		table = newTable;
		capacity = newCapacity;
	}
	void resizeAndReHash3() {
		unsigned int newCapacity = capacity * 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr) {
				unsigned int index = hashFunction3(table[i]->key, newCapacity);
				while (newTable[index] != nullptr) {
					index = (index + 1) % newCapacity;
				}
				newTable[index] = table[i];
			}
		}
		delete[] table;
		table = newTable;
		capacity = newCapacity;
	}
	void downsizeAndReHash1() {
		unsigned int newCapacity = capacity / 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr && !table[i]->usuniety) {
				unsigned int index = hashFunction1(table[i]->key, newCapacity);
				while (newTable[index] != nullptr) {
					index = (index + 1) % newCapacity;
				}
				newTable[index] = table[i];
			}
			else if (table[i] != nullptr && table[i]->usuniety) {
				delete table[i]; // Clean up deleted nodes
			}
		}

		delete[] table;
		table = newTable;
		capacity = newCapacity;
	}
	void downsizeAndReHash2() {
		unsigned int newCapacity = capacity / 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr && !table[i]->usuniety) {
				unsigned int index = hashFunction2(table[i]->key, newCapacity);
				while (newTable[index] != nullptr) {
					index = (index + 1) % newCapacity;
				}
				newTable[index] = table[i];
			}
			else if (table[i] != nullptr && table[i]->usuniety) {
				delete table[i]; // Clean up deleted nodes
			}
		}
		delete[] table;
		table = newTable;
		capacity = newCapacity;
	}
	void downsizeAndReHash3() {
		unsigned int newCapacity = capacity / 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr && !table[i]->usuniety) {
				unsigned int index = hashFunction3(table[i]->key, newCapacity);
				while (newTable[index] != nullptr) {
					index = (index + 1) % newCapacity;
				}
				newTable[index] = table[i];
			}
			else if (table[i] != nullptr && table[i]->usuniety) {
				delete table[i]; // Clean up deleted nodes
			}
		}
		delete[] table;
		table = newTable;
		capacity = newCapacity;
	}
	void insert1(K key, V value) {
		if (loadFactor > maxLoadFactor) {
			resizeAndReHash1();
		}
		unsigned int index = hashFunction1(key, capacity);
		int firstUsuniety = -1;
		while (table[index] != nullptr) {
			if (table[index]->usuniety && firstUsuniety == -1) {
				firstUsuniety = index;
			}
			index = (index + 1) % capacity;
		}
		if (firstUsuniety != -1) {
			delete table[firstUsuniety];
			table[firstUsuniety] = new HashNode<K, V>(key, value);
		}
		else {
			table[index] = new HashNode<K, V>(key, value);
		}
		size++;
		loadFactor = (float)size / capacity;
	}

	void insert2(K key, V value) {
		if (loadFactor > maxLoadFactor) {
			resizeAndReHash2();
		}
		unsigned int index = hashFunction2(key, capacity);
		int firstUsuniety = -1;
		while (table[index] != nullptr) {
			if (table[index]->usuniety && firstUsuniety == -1) {
				firstUsuniety = index;
			}
			index = (index + 1) % capacity;
		}
		if (firstUsuniety != -1) {
			delete table[firstUsuniety];
			table[firstUsuniety] = new HashNode<K, V>(key, value);
		}
		else {
			table[index] = new HashNode<K, V>(key, value);
		}
		size++;
		loadFactor = (float)size / capacity;
	}

	void insert3(K key, V value) {
		if (loadFactor > maxLoadFactor) {
			resizeAndReHash3();
		}
		unsigned int index = hashFunction3(key, capacity);
		int firstUsuniety = -1;
		while (table[index] != nullptr) {
			if (table[index]->usuniety && firstUsuniety == -1) {
				firstUsuniety = index;
			}
			index = (index + 1) % capacity;
		}
		if (firstUsuniety != -1) {
			delete table[firstUsuniety];
			table[firstUsuniety] = new HashNode<K, V>(key, value);
		}
		else {
			table[index] = new HashNode<K, V>(key, value);
		}
		size++;
		loadFactor = (float)size / capacity;
	}

	V search1(K key) {
		unsigned int index = hashFunction1(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr && collisions < capacity) {
			if (!table[index]->usuniety && table[index]->key == key) {
				return table[index]->value;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
		return V();
	}

	V search2(K key) {
		unsigned int index = hashFunction2(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr && collisions < capacity) {
			if (!table[index]->usuniety && table[index]->key == key) {
				return table[index]->value;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
		return V();
	}

	V search3(K key) {
		unsigned int index = hashFunction3(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr && collisions < capacity) {
			if (!table[index]->usuniety && table[index]->key == key) {
				return table[index]->value;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
		return V();
	}

	void remove1(K key) {
		unsigned int index = hashFunction1(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr && collisions < capacity) {
			if (!table[index]->usuniety && table[index]->key == key) {
				table[index]->usuniety = true;
				size--;
				loadFactor = (float)size / capacity;
				if (loadFactor <= maxLoadFactor / 4) {
					downsizeAndReHash1();
				}
				return;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
	}
	void remove2(K key) {
		unsigned int index = hashFunction2(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr && collisions < capacity) {
			if (!table[index]->usuniety && table[index]->key == key) {
				table[index]->usuniety = true;
				size--;
				loadFactor = (float)size / capacity;
				if (loadFactor <= maxLoadFactor / 4) {
					downsizeAndReHash2();
				}
				return;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
	}

	void remove3(K key) {
		unsigned int index = hashFunction3(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr && collisions < capacity) {
			if (!table[index]->usuniety && table[index]->key == key) {
				table[index]->usuniety = true;
				size--;
				loadFactor = (float)size / capacity;
				if (loadFactor <= maxLoadFactor / 4) {
					downsizeAndReHash3();
				}
				return;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
	}

	unsigned int getSize() const {
		return size;
	}
	unsigned int getCapacity() const {
		return capacity;
	}
	float getLoadFactor() const {
		return loadFactor;
	}
	float getMaxLoadFactor() const {
		return maxLoadFactor;
	}
};

int main() {
	srand(time(NULL)); // Inicjalizacja generatora liczb losowych
	const unsigned int iteracje = 1000000;
	//const unsigned int iteracje = 12000;

	unsigned int* klucze = new unsigned int [iteracje];

	for (unsigned int i = 0; i < iteracje; i++) {
		klucze[i] = rand() % 25000000; // Generowanie losowych kluczy
		//klucze[i] = i;
	}

	const string resultsFiles[] = {
		"HashingFunction1.csv",
		"HashingFunction2.csv",
		"HashingFunction3.csv",
	};
	const int resultsFilesAmount = sizeof(resultsFiles) / sizeof(resultsFiles[0]); // Obliczenie liczby plikow

	// Tablica do przechowywania czasow sortowania  
	long long** algorithmsTimes = new long long* [2];
	for (int i = 0; i < 2; i++) {
		algorithmsTimes[i] = new long long[iteracje];
	}


	ofstream file;

	for (int i = 0; i < resultsFilesAmount; i++) {

		file.open(resultsFiles[i]);

		if (!file.is_open()) {
			cerr << "Nie mozna otworzyc pliku: " << resultsFiles[i] << endl;
			return 1;
		}

		file << "Iteracja, Dodawanie elementu, Usuwanie elementu";
		file << endl;
		cout << "\nNaglowek napisany dla pliku: " << resultsFiles[i] << endl;

		switch (i)
		{
		case 0:
		{
			HashTable<int, int> hashTable1(100000);
			//HashTable<int, int> hashTable1(8000);
			for (unsigned int j = 0; j < iteracje; j++) {
				auto start = chrono::high_resolution_clock::now();
				hashTable1.insert1(klucze[j], j);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[0][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				if (j + 1 == iteracje / 10 || j + 1 == iteracje / 5 || j + 1 == iteracje / 2 || j + 1 == iteracje) {
					cout << "Dodano " << j + 1 << " elementow." << endl;
				}
			}
			for (long int j = iteracje - 1; j >= 0; j--) {
				auto start = chrono::high_resolution_clock::now();
				hashTable1.remove1(klucze[j]);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[1][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				if (j + 1 == iteracje / 10 || j + 1 == iteracje / 5 || j + 1 == iteracje / 2 || j + 1 == iteracje) {
					cout << "Usunieto " << iteracje - j << " elementow." << endl;
				}
			}
		}
		break;

		case 1:
		{
			HashTable<int, int> hashTable2(100000);
			//HashTable<int, int> hashTable2(8000);
			for (unsigned int j = 0; j < iteracje; j++) {
				auto start = chrono::high_resolution_clock::now();
				hashTable2.insert2(klucze[j], j);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[0][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				if (j + 1 == iteracje / 10 || j + 1 == iteracje / 5 || j + 1 == iteracje / 2 || j + 1 == iteracje) {
					cout << "Dodano " << j + 1 << " elementow." << endl;
				}
			}
			for (long int j = iteracje - 1; j >= 0; j--) {
				auto start = chrono::high_resolution_clock::now();
				hashTable2.remove2(klucze[j]);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[1][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				if (j + 1 == iteracje / 10 || j + 1 == iteracje / 5 || j + 1 == iteracje / 2 || j + 1 == iteracje) {
					cout << "Usunieto " << iteracje - j << " elementow." << endl;
				}
			}
		}
		break;

		case 2:
		{
			HashTable<int, int> hashTable3(100000);
			//HashTable<int, int> hashTable3(8000);
			for (unsigned int j = 0; j < iteracje; j++) {
				auto start = chrono::high_resolution_clock::now();
				hashTable3.insert3(klucze[j], j);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[0][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				if (j + 1 == iteracje / 10 || j + 1 == iteracje / 5 || j + 1 == iteracje / 2 || j + 1 == iteracje) {
					cout << "Dodano " << j + 1 << " elementow." << endl;
				}
			}
			for (long int j = iteracje - 1; j >= 0; j--) {
				auto start = chrono::high_resolution_clock::now();
				hashTable3.remove3(klucze[j]);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[1][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
				if (j + 1 == iteracje / 10 || j + 1 == iteracje / 5 || j + 1 == iteracje / 2 || j + 1 == iteracje) {
					cout << "Usunieto " << iteracje - j << " elementow." << endl;
				}
			}
		}
		break;

		default:
			cerr << "Nieznany plik: " << resultsFiles[i] << endl;
			return 1;
		}

		cout << "Zapisuje czasy do pliku: " << resultsFiles[i] << endl;

		for (unsigned int j = 0; j < iteracje; j++) {
			file << j+1 << "," << algorithmsTimes[0][j] << "," << algorithmsTimes[1][j];
			file << endl;
		}

		file.close();

	}
	for (int i = 0; i < 2; i++) {
		delete[] algorithmsTimes[i];
	}
	delete[] algorithmsTimes;
	delete[] klucze;
	return 0;
}