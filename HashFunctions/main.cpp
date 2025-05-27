#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;

template<typename K, typename V>
class HashNode {
public:
	K key;
	V value;
	HashNode(K k, V v) : key(k), value(v) {}
};

template<typename K, typename V>
class HashTable {
private:
	HashNode<K, V>** table;
	unsigned int capacity;
	unsigned int size;
	unsigned float loadFactor;
	unsigned float maxLoadFactor;
public:
	HashTable(unsigned int cap, unsigned int maxLoad = 0.8) : capacity(cap), size(0), maxLoadFactor(maxLoad) {
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
	unsigned int hashFunction2(K key, unsigned int cap, unsigned int size) {
		return (loadFactor * key % size) / (size / cap);
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
				unsigned int index = hashFunction2(table[i]->key, newCapacity, size);
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
	void downsizeAndReHash2() {
		unsigned int newCapacity = capacity / 2;
		HashNode<K, V>** newTable = new HashNode<K, V>* [newCapacity];
		for (unsigned int i = 0; i < newCapacity; ++i) {
			newTable[i] = nullptr;
		}
		for (unsigned int i = 0; i < capacity; ++i) {
			if (table[i] != nullptr) {
				unsigned int index = hashFunction2(table[i]->key, newCapacity, size);
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
	void downsizeAndReHash3() {
		unsigned int newCapacity = capacity / 2;
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
	void insert1(K key, V value) {
		if (size >= capacity * maxLoadFactor) {
			resizeAndReHash1();
		}
		unsigned int index = hashFunction1(key, capacity);
		while (table[index] != nullptr) {
			index = (index + 1) % capacity;
		}
		table[index] = new HashNode<K, V>(key, value);
		size++;
		loadFactor = (float)size / capacity;
	}
	void insert2(K key, V value) {
		if (size >= capacity * maxLoadFactor) {
			resizeAndReHash2();
		}
		unsigned int index = hashFunction2(key, capacity, size);
		while (table[index] != nullptr) {
			index = (index + 1) % capacity;
		}
		table[index] = new HashNode<K, V>(key, value);
		size++;
		loadFactor = (float)size / capacity;
	}
	void insert3(K key, V value) {
		if (size >= capacity * maxLoadFactor) {
			resizeAndReHash3();
		}
		unsigned int index = hashFunction3(key, capacity);
		while (table[index] != nullptr) {
			index = (index + 1) % capacity;
		}
		table[index] = new HashNode<K, V>(key, value);
		size++;
		loadFactor = (float)size / capacity;
	}
	V search1(K key) {
		unsigned int index = hashFunction1(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr || collisions < capacity) {
			if (table[index]->key == key) {
				return table[index]->value;
			}
			index = (index + 1) % capacity;
			collisions++;
		}
		return V();
	}
	V search2(K key) {
		unsigned int index = hashFunction2(key, capacity, size);
		unsigned int collisions = 0;
		while (table[index] != nullptr || collisions < capacity) {
			if (table[index]->key == key) {
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
		while (table[index] != nullptr || collisions < capacity) {
			if (table[index]->key == key) {
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
		while (table[index] != nullptr || collisions < capacity) {
			if (table[index]->key == key) {
				delete table[index];
				table[index] = nullptr;
				size--;
				loadFactor = (float)size / capacity;
				if (loadFactor <= maxLoadFactor / 4) {
					downsizeAndReHash1();
				}
				return;
			}
			index = (index + 1) % capacity;
		}
	}
	void remove2(K key) {
		unsigned int index = hashFunction2(key, capacity, size);
		unsigned int collisions = 0;
		while (table[index] != nullptr || collisions < capacity) {
			if (table[index]->key == key) {
				delete table[index];
				table[index] = nullptr;
				size--;
				loadFactor = (float)size / capacity;
				if (loadFactor <= maxLoadFactor / 4) {
					downsizeAndReHash2();
				}
				return;
			}
			index = (index + 1) % capacity;
		}
	}
	void remove3(K key) {
		unsigned int index = hashFunction3(key, capacity);
		unsigned int collisions = 0;
		while (table[index] != nullptr || collisions < capacity) {
			if (table[index]->key == key) {
				delete table[index];
				table[index] = nullptr;
				size--;
				loadFactor = (float)size / capacity;
				if (loadFactor <= maxLoadFactor / 4) {
					downsizeAndReHash3();
				}
				return;
			}
			index = (index + 1) % capacity;
		}
	}
	unsigned int getSize() const {
		return size;
	}
	unsigned int getCapacity() const {
		return capacity;
	}
	unsigned float getLoadFactor() const {
		return loadFactor;
	}
	unsigned float getMaxLoadFactor() const {
		return maxLoadFactor;
	}
}

int main() {
	srand(time(NULL)); // Inicjalizacja generatora liczb losowych
	const unsigned int iteracje = 1000000;

	unsigned int klucze[iteracje];

	for (unsigned int i = 0; i < iteracje; i++) {
		klucze[i] = rand() % 25000000; // Generowanie losowych kluczy
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
		sortTimes[i] = new long long[iteracje];
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
			HashTable<int, int> hashTable1(1000);
			for (unsigned int j = 0; j < iteracje; j++) {
				auto start = chrono::high_resolution_clock::now();
				hashTable1.insert1(klucze[j], j);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[0][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			}
			for (unsigned int j = iteracje-1; j >= 0; j--) {
				auto start = chrono::high_resolution_clock::now();
				hashTable1.remove1(klucze[j]);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[1][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			}
		}
			break;

		case 1:
			HashTable<int, int> hashTable2(1000);
			for (unsigned int j = 0; j < iteracje; j++) {
				auto start = chrono::high_resolution_clock::now();
				hashTable2.insert2(klucze[j], j);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[0][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			}
			for (unsigned int j = iteracje - 1; j >= 0; j--) {
				auto start = chrono::high_resolution_clock::now();
				hashTable2.remove2(klucze[j]);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[1][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			}
			break;

		case 2:
			HashTable<int, int> hashTable3(1000);
			for (unsigned int j = 0; j < iteracje; j++) {
				auto start = chrono::high_resolution_clock::now();
				hashTable3.insert3(klucze[j], j);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[0][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			}
			for (unsigned int j = iteracje - 1; j >= 0; j--) {
				auto start = chrono::high_resolution_clock::now();
				hashTable3.remove3(klucze[j]);
				auto end = chrono::high_resolution_clock::now();
				algorithmsTimes[1][j] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			}
			break;

		default:
			cerr << "Nieznany plik: " << resultsFiles[i] << endl;
			return 1;
		}

		cout << "Zapisuje czasy do pliku: " << resultsFiles[i] << endl;

		for (unsigned int j = 0; j < iteracje; j++) {
			file << j << "," << algorithmsTimes[0][j] << "," << algorithmsTimes[1][j];
			file << endl;
		}

		file.close();

	}
	return 0;
}