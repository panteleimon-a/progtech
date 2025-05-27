#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional> // για το std::hash
using namespace std;

// Απλοποιημένη υλοποίηση του unordered_map με κατακερματισμό
template <typename K, typename V>
class MyUnorderedMap {
private:
    // Δομή για αποθήκευση των ζευγών κλειδιού-τιμής
    struct KeyValuePair {
        K key;
        V value;
        
        KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
    };
    
    // Ο πίνακας κατακερματισμού είναι ένα vector από λίστες ζευγών
    vector<list<KeyValuePair>> table;
    size_t count;     // Αριθμός στοιχείων
    size_t tableSize; // Μέγεθος του πίνακα
    double maxLoadFactor; // Μέγιστος συντελεστής φόρτωσης
    
    // Υπολογισμός του δείκτη (index) για ένα κλειδί
    size_t getIndex(const K& key) const {
        // Χρησιμοποιούμε το std::hash για κατακερματισμό
        return std::hash<K>{}(key) % tableSize;
    }
    
    // Επανακατανομή όταν ο πίνακας είναι πολύ γεμάτος
    void rehash() {
        size_t newSize = tableSize * 2;
        rehash(newSize);
    }
    
    // Επανακατανομή με συγκεκριμένο μέγεθος
    void rehash(size_t newSize) {
        vector<list<KeyValuePair>> oldTable = table;
        
        // Δημιουργία νέου πίνακα
        table.clear();
        table.resize(newSize);
        tableSize = newSize;
        count = 0;
        
        // Επανεισαγωγή των στοιχείων
        for (const auto& bucket : oldTable) {
            for (const auto& pair : bucket) {
                insert(pair.key, pair.value);
            }
        }
        
        cout << "Rehashed: Νέο μέγεθος = " << tableSize << endl;
    }
    
public:
    // Κλάση επαναλήπτη (iterator)
    class iterator {
    private:
        MyUnorderedMap<K, V>* map;
        size_t bucketIndex;
        typename list<KeyValuePair>::iterator listIt;
        
    public:
        // Κατασκευαστής
        iterator(MyUnorderedMap<K, V>* m, size_t bucket, typename list<KeyValuePair>::iterator it)
            : map(m), bucketIndex(bucket), listIt(it) {}
        
        // Προσπέλαση ζεύγους κλειδιού-τιμής
        pair<const K&, V&> operator*() {
            return pair<const K&, V&>(listIt->key, listIt->value);
        }
        
        // Προχώρηση στο επόμενο στοιχείο
        iterator& operator++() {
            // Προχώρηση μέσα στην τρέχουσα λίστα
            ++listIt;
            
            // Αν φτάσαμε στο τέλος της λίστας, πρέπει να πάμε στην επόμενη μη-κενή λίστα
            if (listIt == map->table[bucketIndex].end()) {
                // Αναζήτηση της επόμενης μη-κενής λίστας
                while (++bucketIndex < map->tableSize) {
                    if (!map->table[bucketIndex].empty()) {
                        listIt = map->table[bucketIndex].begin();
                        return *this;
                    }
                }
                
                // Αν δεν υπάρχει άλλη μη-κενή λίστα, έχουμε φτάσει στο τέλος
                bucketIndex = map->tableSize;
            }
            
            return *this;
        }
        
        // Σύγκριση επαναληπτών
        bool operator==(const iterator& other) const {
            if (bucketIndex != other.bucketIndex) return false;
            if (bucketIndex == map->tableSize) return true; // Και οι δύο είναι end()
            return listIt == other.listIt;
        }
        
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };
    
    // Κατασκευαστής
    MyUnorderedMap(size_t initialSize = 10, double loadFactor = 0.75)
        : tableSize(initialSize), count(0), maxLoadFactor(loadFactor) {
        table.resize(tableSize);
    }
    
    // Εισαγωγή ή ενημέρωση ζεύγους κλειδιού-τιμής
    void insert(const K& key, const V& value) {
        // Έλεγχος αν χρειάζεται rehashing
        if (static_cast<double>(count + 1) / tableSize > maxLoadFactor) {
            rehash();
        }
        
        size_t index = getIndex(key);
        
        // Έλεγχος αν το κλειδί υπάρχει ήδη
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value; // Ενημέρωση τιμής
                return;
            }
        }
        
        // Εισαγωγή νέου ζεύγους
        table[index].push_back(KeyValuePair(key, value));
        count++;
    }
    
    // Αναζήτηση τιμής με βάση το κλειδί
    bool find(const K& key, V& value) const {
        size_t index = getIndex(key);
        
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                value = pair.value;
                return true;
            }
        }
        
        return false;
    }
    
    // Προσπέλαση τιμής με τον τελεστή []
    V& operator[](const K& key) {
        size_t index = getIndex(key);
        
        // Έλεγχος αν το κλειδί υπάρχει
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        
        // Το κλειδί δεν υπάρχει, οπότε το προσθέτουμε με προεπιλεγμένη τιμή
        // Πρώτα ελέγχουμε αν χρειάζεται rehashing
        if (static_cast<double>(count + 1) / tableSize > maxLoadFactor) {
            rehash();
            index = getIndex(key); // Επανυπολογισμός μετά το rehashing
        }
        
        table[index].push_back(KeyValuePair(key, V()));
        count++;
        return table[index].back().value;
    }
    
    // Διαγραφή στοιχείου
    bool erase(const K& key) {
        size_t index = getIndex(key);
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                count--;
                return true;
            }
        }
        
        return false;
    }
    
    // Έλεγχος αν υπάρχει το κλειδί
    bool contains(const K& key) const {
        size_t index = getIndex(key);
        
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                return true;
            }
        }
        
        return false;
    }
    
    // Επιστροφή του πλήθους των στοιχείων
    size_t size() const {
        return count;
    }
    
    // Έλεγχος αν ο πίνακας είναι κενός
    bool empty() const {
        return count == 0;
    }
    
    // Καθαρισμός του πίνακα
    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        count = 0;
    }
    
    // Επιστροφή επαναλήπτη στην αρχή
    iterator begin() {
        // Εύρεση της πρώτης μη-κενής λίστας
        for (size_t i = 0; i < tableSize; i++) {
            if (!table[i].empty()) {
                return iterator(this, i, table[i].begin());
            }
        }
        return end();
    }
    
    // Επιστροφή επαναλήπτη στο τέλος
    iterator end() {
        return iterator(this, tableSize, typename list<KeyValuePair>::iterator());
    }
    
    // Εμφάνιση στατιστικών του πίνακα
    void printStats() const {
        cout << "=== Hash Table Statistics ===" << endl;
        cout << "Μέγεθος πίνακα: " << tableSize << endl;
        cout << "Αριθμός στοιχείων: " << count << endl;
        cout << "Συντελεστής φόρτωσης: " << static_cast<double>(count) / tableSize << endl;
        
        size_t emptyBuckets = 0;
        size_t maxBucketSize = 0;
        size_t totalCollisions = 0;
        
        for (const auto& bucket : table) {
            if (bucket.empty()) {
                emptyBuckets++;
            } else {
                size_t bucketSize = bucket.size();
                if (bucketSize > maxBucketSize) {
                    maxBucketSize = bucketSize;
                }
                if (bucketSize > 1) {
                    totalCollisions += (bucketSize - 1);
                }
            }
        }
        
        cout << "Κενοί κάδοι: " << emptyBuckets << " (" 
             << static_cast<double>(emptyBuckets) / tableSize * 100 << "%)" << endl;
        cout << "Μέγιστο μήκος αλυσίδας: " << maxBucketSize << endl;
        cout << "Συνολικές συγκρούσεις: " << totalCollisions << endl;
        cout << "============================" << endl;
    }
};

// Παράδειγμα χρήσης
int main() {
    // Δημιουργία ενός map με κλειδιά string και τιμές int
    MyUnorderedMap<string, int> ageMap;
    
    // Εισαγωγή ζευγών κλειδιού-τιμής
    ageMap.insert("Alice", 25);
    ageMap.insert("Bob", 30);
    ageMap.insert("Charlie", 35);
    ageMap.insert("David", 40);
    ageMap.insert("Eve", 45);
    
    // Χρήση του τελεστή []
    ageMap["Frank"] = 50;
    ageMap["Grace"] = 55;
    
    // Εμφάνιση στατιστικών
    ageMap.printStats();
    
    // Αναζήτηση και εμφάνιση τιμών
    int age;
    cout << "\nΑναζήτηση ηλικιών:" << endl;
    if (ageMap.find("Alice", age)) {
        cout << "Η ηλικία της Alice είναι " << age << endl;
    }
    
    if (ageMap.find("Bob", age)) {
        cout << "Η ηλικία του Bob είναι " << age << endl;
    }
    
    // Έλεγχος ύπαρξης κλειδιού
    cout << "\nΈλεγχος ύπαρξης:" << endl;
    cout << "Υπάρχει η Eve; " << (ageMap.contains("Eve") ? "Ναι" : "Όχι") << endl;
    cout << "Υπάρχει ο Harry; " << (ageMap.contains("Harry") ? "Ναι" : "Όχι") << endl;
    
    // Ενημέρωση τιμής
    ageMap["Alice"] = 26;
    
    // Διαγραφή στοιχείου
    ageMap.erase("Charlie");
    
    // Εμφάνιση όλων των ζευγών με χρήση επαναλήπτη
    cout << "\nΌλα τα ζεύγη κλειδιού-τιμής:" << endl;
    for (auto it = ageMap.begin(); it != ageMap.end(); ++it) {
        auto [key, value] = *it;
        cout << key << ": " << value << endl;
    }
    
    // Εισαγωγή περισσότερων στοιχείων για να προκληθεί rehashing
    cout << "\nΕισαγωγή περισσότερων στοιχείων..." << endl;
    ageMap.insert("Harry", 60);
    ageMap.insert("Ivy", 65);
    ageMap.insert("Jack", 70);
    ageMap.insert("Kate", 75);
    ageMap.insert("Leo", 80);
    ageMap.insert("Mia", 85);
    ageMap.insert("Noah", 90);
    ageMap.insert("Olivia", 95);
    
    // Εμφάνιση τελικών στατιστικών
    ageMap.printStats();
    
    return 0;
}
