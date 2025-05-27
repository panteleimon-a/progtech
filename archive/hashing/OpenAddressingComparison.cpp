#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// Υλοποίηση των τριών μεθόδων ανοιχτής διευθυνσιοδότησης
class HashTableOpenAddressing {
private:
    enum SlotStatus { EMPTY, OCCUPIED, DELETED };
    
    struct HashEntry {
        int key;
        SlotStatus status;
        
        HashEntry() : status(EMPTY) {}
    };
    
    vector<HashEntry> table;
    int size;      // Αριθμός στοιχείων
    int capacity;  // Μέγεθος πίνακα
    int collisions; // Μετρητής συγκρούσεων
    
    // Κύρια συνάρτηση κατακερματισμού
    int h1(int key) const {
        return key % capacity;
    }
    
    // Δευτερεύουσα συνάρτηση κατακερματισμού για διπλό κατακερματισμό
    int h2(int key) const {
        return 1 + (key % (capacity - 1));
    }
    
    // Συναρτήσεις διερεύνησης θέσης
    
    // Γραμμική διερεύνηση: h(k, i) = (h1(k) + i) % m
    int linearProbing(int key, int i) const {
        return (h1(key) + i) % capacity;
    }
    
    // Τετραγωνική διερεύνηση: h(k, i) = (h1(k) + i + i*i) % m
    int quadraticProbing(int key, int i) const {
        return (h1(key) + i + i*i) % capacity;
    }
    
    // Διπλός κατακερματισμός: h(k, i) = (h1(k) + i*h2(k)) % m
    int doubleHashing(int key, int i) const {
        return (h1(key) + i * h2(key)) % capacity;
    }
    
public:
    enum ProbingMethod { LINEAR, QUADRATIC, DOUBLE };
    
    // Κατασκευαστής
    HashTableOpenAddressing(int m) : capacity(m), size(0), collisions(0) {
        table.resize(capacity);
    }
    
    // Εισαγωγή στοιχείου με την επιλεγμένη μέθοδο διερεύνησης
    void insert(int key, ProbingMethod method) {
        if (size >= capacity) {
            cout << "Ο πίνακας είναι πλήρης!" << endl;
            return;
        }
        
        int i = 0;
        int index;
        
        do {
            // Επιλογή μεθόδου διερεύνησης
            switch(method) {
                case LINEAR:
                    index = linearProbing(key, i);
                    break;
                case QUADRATIC:
                    index = quadraticProbing(key, i);
                    break;
                case DOUBLE:
                    index = doubleHashing(key, i);
                    break;
            }
            
            // Αν βρούμε κενή θέση ή διαγραμμένη, εισάγουμε το κλειδί
            if (table[index].status == EMPTY || table[index].status == DELETED) {
                table[index].key = key;
                table[index].status = OCCUPIED;
                size++;
                return;
            }
            
            // Αν υπάρχει σύγκρουση, αυξάνουμε τον μετρητή συγκρούσεων
            if (i == 0) {
                collisions++;
            }
            
            i++;
        } while (i < capacity);
        
        // Αν φτάσουμε εδώ, ο πίνακας είναι γεμάτος ή δεν βρέθηκε θέση
        cout << "Δεν ήταν δυνατή η εισαγωγή του κλειδιού " << key << endl;
    }
    
    // Εμφάνιση του πίνακα
    void display() const {
        cout << "Πίνακας κατακερματισμού (μέγεθος: " << capacity << ", στοιχεία: " << size << "):" << endl;
        for (int i = 0; i < capacity; i++) {
            cout << setw(2) << i << ": ";
            if (table[i].status == OCCUPIED) {
                cout << table[i].key;
            } else if (table[i].status == DELETED) {
                cout << "<διαγραμμένο>";
            } else {
                cout << "<κενό>";
            }
            cout << endl;
        }
        cout << "Συγκρούσεις: " << collisions << endl;
    }
    
    // Επαναφορά του πίνακα
    void clear() {
        for (int i = 0; i < capacity; i++) {
            table[i].status = EMPTY;
        }
        size = 0;
        collisions = 0;
    }
    
    // Επιστροφή του αριθμού συγκρούσεων
    int getCollisions() const {
        return collisions;
    }
};

// Συνάρτηση για την εκτέλεση του πειράματος με την επιλεγμένη μέθοδο
void runExperiment(const vector<int>& keys, HashTableOpenAddressing::ProbingMethod method) {
    string methodName;
    switch(method) {
        case HashTableOpenAddressing::LINEAR:
            methodName = "Γραμμική Διερεύνηση";
            break;
        case HashTableOpenAddressing::QUADRATIC:
            methodName = "Τετραγωνική Διερεύνηση";
            break;
        case HashTableOpenAddressing::DOUBLE:
            methodName = "Διπλός Κατακερματισμός";
            break;
    }
    
    cout << "\n=== " << methodName << " ===" << endl;
    HashTableOpenAddressing hashTable(17);
    
    // Εισαγωγή των κλειδιών
    for (int key : keys) {
        hashTable.insert(key, method);
    }
    
    // Εμφάνιση του τελικού πίνακα
    hashTable.display();
    
    // Αποθήκευση των αποτελεσμάτων για σύγκριση
    cout << "Μέθοδος: " << methodName << ", Συγκρούσεις: " << hashTable.getCollisions() << endl;
}

int main() {
    // Τα κλειδιά που θα εισαχθούν
    vector<int> keys = {23, 38, 42, 59, 63, 71, 84, 92};
    
    cout << "Σύγκριση μεθόδων ανοιχτής διευθυνσιοδότησης" << endl;
    cout << "Κλειδιά: ";
    for (int key : keys) {
        cout << key << " ";
    }
    cout << endl;
    
    // Εκτέλεση του πειράματος για κάθε μέθοδο
    runExperiment(keys, HashTableOpenAddressing::LINEAR);
    runExperiment(keys, HashTableOpenAddressing::QUADRATIC);
    runExperiment(keys, HashTableOpenAddressing::DOUBLE);
    
    return 0;
}
